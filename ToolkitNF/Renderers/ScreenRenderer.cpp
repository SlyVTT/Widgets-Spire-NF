#include "ScreenRenderer.hpp"



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

       screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);

       if(screen == NULL)
       {
              printf("Couldn't initialize display: %s\n", SDL_GetError());
              SDL_Quit();
              exit(EXIT_FAILURE);
       }

       SDL_FillRect( screen, 0, 0xFFFF);
       SDL_Flip(screen);

#else

       screen = gui_gc_global_GC();

       gui_gc_setRegion(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
       gui_gc_begin(screen);

       gui_gc_setAlpha(screen, GC_A_OFF);

       gui_gc_setColorRGB(screen, 255, 255, 255);
       gui_gc_fillRect(screen, 0, 0, 320, 240);

       gui_gc_blit_to_screen(screen);

#endif
}


void ScreenRenderer::InternalClose( void )
{
#if RENDER_WITH_SDL == 1

       SDL_FreeSurface( screen );
       SDL_Quit();

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
       SDL_Flip(screen);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_fillRect(screen, 0, 0, 320, 240);
       gui_gc_blit_to_screen(screen);

#endif
}


void ScreenRenderer::InternalDrawPixel( unsigned int x1, unsigned int y1, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       pixelRGBA( screen, x1, y1, R, G, B, A);

#else

       if ((x1>=0) && (x1<=SCREEN_WIDTH) && (y1>=0) && (y1<=SCREEN_HEIGHT))
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
       SDL_GetRGB(getpixel(screen, x, y), screen->format, &r, &g, &b);
       return (unsigned char) r;

#else

       if ((x>=0) && (x<=SCREEN_WIDTH) && (y>=0) && (y<=SCREEN_HEIGHT))
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
       SDL_GetRGB(getpixel(screen, x, y), screen->format, &r, &g, &b);
       return (unsigned char) g;

#else

       if ((x>=0) && (x<=SCREEN_WIDTH) && (y>=0) && (y<=SCREEN_HEIGHT))
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
       SDL_GetRGB(getpixel(screen, x, y), screen->format, &r, &g, &b);
       return (unsigned char) b;

#else

       if ((x>=0) && (x<=SCREEN_WIDTH) && (y>=0) && (y<=SCREEN_HEIGHT))
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

       return ((unsigned int) getpixel(screen, x, y));

#else

       if ((x>=0) && (x<=SCREEN_WIDTH) && (y>=0) && (y<=SCREEN_HEIGHT))
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