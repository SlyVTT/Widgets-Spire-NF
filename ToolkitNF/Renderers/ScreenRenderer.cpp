#include "ScreenRenderer.hpp"

#include "../Globals/GUIToolkitNFGlobals.hpp"


#if DEBUG_MODE == 1
    #include "../Debugger/Debugger.hpp"
#endif // DEBUG_MODE


#if RENDER_WITH_SDL == 1
uint32_t ScreenRenderer::_getpixel(SDL_Surface *surface, int x, int y)
{
       int bpp = surface->format->BytesPerPixel;
       /* Here p is the address to the pixel we want to retrieve */
       uint8_t *p = (uint8_t *)surface->pixels + y * surface->pitch + x * bpp;

       switch(bpp)
       {
       case 1:
              return *p;

       case 2:
              return *(uint16_t *)p;

       case 3:
              if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                     return p[0] << 16 | p[1] << 8 | p[2];
              else
                     return p[0] | p[1] << 8 | p[2] << 16;

       case 4:
              return *(uint32_t *)p;

       default:
              return 0;       /* shouldn't happen, but avoids warnings */
       }
}
#endif


ScreenRenderer::ScreenRenderer()
{

}

void ScreenRenderer::TakeScreenShot( void )
{
       std::string namebegin = "/documents/Widget/Screenshots/scrsh";
       std::string nameend = ".bmp.tns";
       std::string namemiddle = "000";
       bool screenshotdone = false;
       int i=0;

       do
       {
              std::string fullname = namebegin + namemiddle + nameend;
              if (!is_existing( fullname ))
              {
                     Get().WriteToBMP( fullname );
                     screenshotdone = true;
              }
              else
              {
                     i++;
                     namemiddle = std::to_string( i );
                     if (namemiddle.length()==1)
                     {
                            namemiddle = "00" + namemiddle;
                     };
                     if (namemiddle.length()==2)
                     {
                            namemiddle = "0" + namemiddle;
                     };
              }
       }
       while (!screenshotdone);
}


void ScreenRenderer::WriteToBMP( std::string filename )
{

#if RENDER_WITH_SDL == 1

       SDL_SaveBMP( screen, filename.c_str() );

#else

       unsigned int headers[13];
       FILE * outfile;
       int extrabytes;
       int paddedsize;
       int x;
       int y;
       int n;
       unsigned char red, green, blue;

       extrabytes = 4 - ((SCREEN_WIDTH * 3) % 4);                 // How many bytes of padding to add to each
       // horizontal line - the size of which must
       // be a multiple of 4 bytes.
       if (extrabytes == 4)
              extrabytes = 0;

       paddedsize = ((SCREEN_WIDTH * 3) + extrabytes) * SCREEN_HEIGHT;

// Headers...
// Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".

       headers[0]  = paddedsize + 54;      // bfSize (whole file size)
       headers[1]  = 0;                    // bfReserved (both)
       headers[2]  = 54;                   // bfOffbits
       headers[3]  = 40;                   // biSize
       headers[4]  = SCREEN_WIDTH;  // biWidth
       headers[5]  = SCREEN_HEIGHT; // biHeight

// Would have biPlanes and biBitCount in position 6, but they're shorts.
// It's easier to write them out separately (see below) than pretend
// they're a single int, especially with endian issues...

       headers[7]  = 0;                    // biCompression
       headers[8]  = paddedsize;           // biSizeImage
       headers[9]  = 0;                    // biXPelsPerMeter
       headers[10] = 0;                    // biYPelsPerMeter
       headers[11] = 0;                    // biClrUsed
       headers[12] = 0;                    // biClrImportant

       outfile = fopen(filename.c_str(), "wb");

//
// Headers begin...
// When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
//

       fprintf(outfile, "BM");

       for (n = 0; n <= 5; n++)
       {
              fprintf(outfile, "%c", headers[n] & 0x000000FF);
              fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
              fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
              fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
       }

// These next 4 characters are for the biPlanes and biBitCount fields.

       fprintf(outfile, "%c", 1);
       fprintf(outfile, "%c", 0);
       fprintf(outfile, "%c", 24);
       fprintf(outfile, "%c", 0);

       for (n = 7; n <= 12; n++)
       {
              fprintf(outfile, "%c", headers[n] & 0x000000FF);
              fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
              fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
              fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
       }

//
// Headers done, now write the data...
//

       for (y = SCREEN_HEIGHT - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
       {
              for (x = 0; x < SCREEN_WIDTH ; x++)
              {

                     red = InternalGetPixelR( x, y );
                     green = InternalGetPixelG( x, y );
                     blue = InternalGetPixelB( x, y );

                     // Also, it's written in (b,g,r) format...

                     fprintf(outfile, "%c", blue);
                     fprintf(outfile, "%c", green);
                     fprintf(outfile, "%c", red);
              }
              if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
              {
                     for (n = 1; n <= extrabytes; n++)
                     {
                            fprintf(outfile, "%c", 0);
                     }
              }
       }

       fclose(outfile);

#endif
}


ScreenRenderer& ScreenRenderer::Get( void )
{
       static ScreenRenderer m_ScreenRenderer;
       return m_ScreenRenderer;
}


void ScreenRenderer::InternalInitialize( void )
{
#if RENDER_WITH_SDL == 1

       if(SDL_Init(SDL_INIT_VIDEO) == -1)
       {
              printf("Couldn't initialize SDL: %s\n", SDL_GetError());
              exit(EXIT_FAILURE);
       }

       screen = SDL_SetVideoMode(SCREEN_WIDTH_GUI, SCREEN_HEIGHT_GUI, 16, SDL_SWSURFACE);

       if(screen == NULL)
       {
              printf("Couldn't initialize display: %s\n", SDL_GetError());
              SDL_Quit();
              exit(EXIT_FAILURE);
       }

#else

       screen = gui_gc_global_GC();

       gui_gc_setRegion(screen, 0, 0, SCREEN_WIDTH_GUI, SCREEN_HEIGHT_GUI, 0, 0, SCREEN_WIDTH_GUI, SCREEN_HEIGHT_GUI);
       gui_gc_begin(screen);

       gui_gc_setAlpha(screen, GC_A_OFF);

#endif
}


void ScreenRenderer::InternalClose( void )
{
#if RENDER_WITH_SDL == 1

       SDL_FreeSurface( screen );
       //SDL_Quit();

#else

       gui_gc_finish( screen );

#endif

       printf("Exited cleanly\n");
}


void ScreenRenderer::InternalFlipScreen( void )
{
#if RENDER_WITH_SDL == 1

       SDL_Flip(screen);

#else

       gui_gc_blit_to_screen(screen);

#endif
}


void ScreenRenderer::InternalClearScreen( unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       Uint32 rgb_code = SDL_MapRGB(screen->format, R, G, B);
       SDL_FillRect( screen, 0, rgb_code);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_fillRect(screen, 0, 0, SCREEN_WIDTH_GUI, SCREEN_HEIGHT_GUI);

#endif
}


void ScreenRenderer::InternalDrawPixel( unsigned int x1, unsigned int y1, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       pixelRGBA( screen, x1, y1, R, G, B, A);

#else

       if ((x1<SCREEN_WIDTH) && (y1<SCREEN_HEIGHT))
       {
              uint16_t b = (B >> 3) & 0x1f;
              uint16_t g = ((G >> 2) & 0x3f) << 5;
              uint16_t r = ((R >> 3) & 0x1f) << 11;

              uint16_t color = (r | g | b);

              uint16_t ** off_buff = ((((uint16_t *****)screen)[9])[0])[0x8];
              *(off_buff[y1] + x1) = color;
       }

#endif
}


#if RENDER_WITH_SDL == 0
void ScreenRenderer::InternalDrawPixel( unsigned int x1, unsigned int y1, unsigned short valuecolor )
{

      if ((x1<SCREEN_WIDTH_GUI) && (y1<SCREEN_HEIGHT_GUI))
       {
              unsigned short ** off_buff = ((((unsigned short *****)screen)[9])[0])[0x8];
              *(off_buff[y1] + x1) = valuecolor;
       }
}
#endif


void ScreenRenderer::InternalDrawLine( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       lineRGBA( screen, x1, y1, x2, y2, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_drawLine(screen, x1, y1, x2, y2);

#endif
}


void ScreenRenderer::InternalDrawRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       rectangleRGBA( screen, x1, y1, x2, y2, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_drawRect(screen, x1, y1, x2-x1, y2-y1);

#endif
}


void ScreenRenderer::InternalDrawFilledRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       boxRGBA( screen, x1, y1, x2, y2, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_fillRect(screen, x1, y1, x2-x1, y2-y1);

#endif
}


void ScreenRenderer::InternalDrawRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       roundedRectangleRGBA( screen, x1, y1, x2, y2, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);

       gui_gc_drawArc(screen, x2-2*radius, y1, radius*2, radius*2, 0, 900);
       gui_gc_drawArc(screen, x1, y1, radius*2, radius*2, 900, 900);
       gui_gc_drawArc(screen, x1, y2-2*radius, radius*2, radius*2, 1800, 900);
       gui_gc_drawArc(screen, x2-2*radius, y2-2*radius, radius*2, radius*2, 2700, 900);

       gui_gc_drawLine(screen, x1+radius, y1, x2-radius, y1);
       gui_gc_drawLine(screen, x1+radius, y2, x2-radius, y2);
       gui_gc_drawLine(screen, x1, y1+radius, x1, y2-radius);
       gui_gc_drawLine(screen, x2, y1+radius, x2, y2-radius);

#endif
}


void ScreenRenderer::InternalDrawFilledRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       roundedBoxRGBA( screen, x1, y1, x2, y2, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);

       gui_gc_fillArc(screen, x2-2*radius, y1, radius*2, radius*2, 0, 900);
       gui_gc_fillArc(screen, x1, y1, radius*2, radius*2, 900, 900);
       gui_gc_fillArc(screen, x1, y2-2*radius, radius*2, radius*2, 1800, 900);
       gui_gc_fillArc(screen, x2-2*radius, y2-2*radius, radius*2, radius*2, 2700, 900);

       gui_gc_fillRect(screen, x1, y1+radius, x2-x1, y2-y1-2*radius );
       gui_gc_fillRect(screen, x1+radius, y1, x2-x1-2*radius, radius );
       gui_gc_fillRect(screen, x1+radius, y2-radius, x2-x1-2*radius, radius );

#endif
}


void ScreenRenderer::InternalDrawCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       circleRGBA( screen, x, y, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_drawArc(screen, x-radius, y-radius, radius*2, radius*2, 0, 3600);

#endif
}


void ScreenRenderer::InternalDrawFilledCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       filledCircleRGBA( screen, x, y, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_fillArc(screen, x-radius, y-radius, radius*2, radius*2, 0, 3600);

#endif
}


unsigned char ScreenRenderer::InternalGetPixelR( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       Uint8 r,g,b;
       SDL_LockSurface( screen);
       SDL_GetRGB(_getpixel(screen, x, y), screen->format, &r, &g, &b);
       return (unsigned char) r;

#else

       if ((x<=SCREEN_WIDTH_GUI) && (y<=SCREEN_HEIGHT_GUI))
       {
              char ** off_buff = ((((char *****)screen)[9])[0])[0x8];
              int res = *(unsigned short *) (off_buff[y] + 2*x);
              uint8_t r=(unsigned char) ((res >> 11 ) & 0b111111);
              return (unsigned char) (r<<3);
       }
#endif
}


unsigned char ScreenRenderer::InternalGetPixelG( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       Uint8 r,g,b;
       SDL_LockSurface( screen);
       SDL_GetRGB(_getpixel(screen, x, y), screen->format, &r, &g, &b);
       return (unsigned char) g;

#else

       if ((x<=SCREEN_WIDTH_GUI) && (y<=SCREEN_HEIGHT_GUI))
       {
              char ** off_buff = ((((char *****)screen)[9])[0])[0x8];
              int res = *(unsigned short *) (off_buff[y] + 2*x);
              //uint8_t g=(unsigned char) ((res >> 6 ) & 0b11111);
              //return (unsigned char) (g<<3);
              uint8_t g=(unsigned char) ((res >> 5 ) & 0b111111);
              return (unsigned char) (g<<2);
       }

#endif
}


unsigned char ScreenRenderer::InternalGetPixelB( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       Uint8 r,g,b;
       SDL_LockSurface( screen);
       SDL_GetRGB(_getpixel(screen, x, y), screen->format, &r, &g, &b);
       return (unsigned char) b;

#else

       if ((x<=SCREEN_WIDTH_GUI) && (y<=SCREEN_HEIGHT_GUI))
       {
              char ** off_buff = ((((char *****)screen)[9])[0])[0x8];
              int res = *(unsigned short *) (off_buff[y] + 2*x);
              uint8_t b=(unsigned char) (res & 0b11111);
              return (unsigned char) (b<<3);
       }

#endif
}


unsigned int ScreenRenderer::InternalGetPixel( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       return ((unsigned int) _getpixel(screen, x, y));

#else

       if ((x<=SCREEN_WIDTH_GUI) && (y<=SCREEN_HEIGHT_GUI))
       {
              char ** off_buff = ((((char *****)screen)[9])[0])[0x8];
              return *(unsigned short *) (off_buff[y] + 2*x);
       }

#endif
}



#if RENDER_WITH_SDL == 1

void ScreenRenderer::InternalDrawSprite( SDL_Surface* sprite, Rect src, Rect pos )
{
       SDL_Rect src_rect, screen_pos;
       src_rect.x = src.x;
       src_rect.y = src.y;
       src_rect.w = src.w;
       src_rect.h = src.h;

       screen_pos.x = pos.x;
       screen_pos.y = pos.y;
       screen_pos.w = pos.w;
       screen_pos.h = pos.h;
       SDL_BlitSurface( sprite, &src_rect, screen, &screen_pos);
}

#else

void ScreenRenderer::InternalDrawSprite( spritegc* sprite, Rect src, Rect pos )
{
       unsigned short value;
       unsigned char r,g,b;

       for( int i=0; i<sprite->width; i++)
       {
              for( int j=0; j<sprite->height; j++)
              {
                     value = sprite->data[j*sprite->width+i];

                     if ( value != sprite->transparency)
                     {
                            r = ( (value & 0b1111100000000000) >> 11 );
                            g = ( (value & 0b0000011111100000) >> 5 );
                            b = ( (value & 0b0000000000011111) );

                            InternalDrawPixel(pos.x+i, pos.y+j, r<<3, g<<2, b<<3, 255 );
                     }

              }
       }

}

#endif



#if RENDER_WITH_SDL == 1

void ScreenRenderer::InternalDrawImageBackground( SDL_Surface* image )
{
       SDL_Rect src_rect, screen_pos;
       src_rect.x = 0;
       src_rect.y = 0;
       src_rect.w = 320;
       src_rect.h = 240;

       screen_pos.x = 0;
       screen_pos.y = 0;
       screen_pos.w = 320;
       screen_pos.h = 240;
       SDL_BlitSurface( image, &src_rect, screen, &screen_pos);
}

#else

void ScreenRenderer::InternalDrawImageBackground( imagegc* image )
{
       uint16_t ** off_buff = ((((uint16_t *****)screen)[9])[0])[0x8];

       memcpy( off_buff[0], image->data, image->height*image->width*sizeof(uint16_t) );
}

#endif



#if RENDER_WITH_SDL == 1

void ScreenRenderer::InternalDrawImage( SDL_Surface* image, Rect src, Rect pos )
{
       SDL_Rect src_rect, screen_pos;
       src_rect.x = src.x;
       src_rect.y = src.y;
       src_rect.w = src.w;
       src_rect.h = src.h;

       screen_pos.x = pos.x;
       screen_pos.y = pos.y;
       screen_pos.w = pos.w;
       screen_pos.h = pos.h;
       SDL_BlitSurface( image, &src_rect, screen, &screen_pos);
}

#else

void ScreenRenderer::InternalDrawImage( imagegc* image, Rect src, Rect pos )
{

       // We check if we want to copy a part of the image that is inside the image
       if (src.x>image->width) return;
       if (src.y>image->height) return;

       // We check if we want to copy the image inside the screen
       if (pos.x>SCREEN_WIDTH_GUI) return;
       if (pos.y>SCREEN_HEIGHT_GUI) return;

       // We will do a sanity check of the src and pos coordinates to have accurate data for image blit
       // Note : As the Rect struct is using unsigned short, there is no need for checking negative values

       Rect src_cor, pos_cor;
       src_cor.x = src.x;
       src_cor.y = src.y;

       if (src_cor.x+src.w>image->width)
              src_cor.w = image->width - src_cor.x;
       else
              src_cor.w = src.w;

       if (src_cor.y+src.h>image->height)
              src_cor.h = image->height - src_cor.y;
       else
              src_cor.h = src.h;

       pos_cor.x = pos.x;
       pos_cor.y = pos.y;

       if (pos_cor.x+src_cor.w>SCREEN_WIDTH_GUI)
              pos_cor.w = SCREEN_WIDTH_GUI - pos_cor.x;
       else
              pos_cor.w = src_cor.w;

       if (pos_cor.y+src_cor.h>SCREEN_HEIGHT_GUI)
              pos_cor.h = SCREEN_HEIGHT_GUI - pos_cor.y;
       else
              pos_cor.h = src_cor.h;

       // Finally we check if the pos destination can copy the width and height of src, if not, we limit the copy to the destination capability

       if (pos_cor.w>src_cor.w) pos_cor.w=src_cor.w;
       if (pos_cor.h>src_cor.h) pos_cor.h=src_cor.h;


       char ** off_buff = ((((char *****)screen)[9])[0])[0x8];
       unsigned short* screenstart = (unsigned short*)&(*(off_buff[pos_cor.y] + pos_cor.x*2));
       //unsigned short* imagestart = (unsigned short*)&(image->data[ src_cor.y*image->width + src_cor.x]);
       unsigned short* imagestart = (unsigned short*) image->data ;
       imagestart +=  src_cor.y*image->width + src_cor.x;


       // Now we can do the image blit
       // for each validated line (given by pos_cor.h value)

       for (char u=0; u<pos_cor.h; u++)
       {
              memcpy( screenstart, imagestart, pos_cor.w*2 );
              screenstart += SCREEN_WIDTH_GUI;
              imagestart += image->width;
       }
}

#endif
