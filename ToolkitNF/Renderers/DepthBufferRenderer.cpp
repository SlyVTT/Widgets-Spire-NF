#include "DepthBufferRenderer.hpp"



DepthBufferRenderer::DepthBufferRenderer()
{

}
void DepthBufferRenderer::TakeScreenShot( void )
{
       std::string namebegin = "/documents/Widget/Screenshots/dpbuf";
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


void DepthBufferRenderer::WriteToBMP( std::string filename )
{

#if RENDER_WITH_SDL == 1

       SDL_SaveBMP( depthbuffer, filename.c_str() );

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

DepthBufferRenderer& DepthBufferRenderer::Get( void )
{
       static DepthBufferRenderer m_depthbufferRenderer;
       return m_depthbufferRenderer;
}


void DepthBufferRenderer::InternalInitialize( void )
{
#if RENDER_WITH_SDL == 1

       if(SDL_Init(SDL_INIT_VIDEO) == -1)
       {
              printf("Couldn't initialize SDL: %s\n", SDL_GetError());
              exit(EXIT_FAILURE);
       }

       depthbuffer = SDL_CreateRGBSurface(0, 320, 240, 24, 0, 0, 0, 0);

       if(depthbuffer == NULL)
       {
              printf("Couldn't initialize display: %s\n", SDL_GetError());
              SDL_Quit();
              exit(EXIT_FAILURE);
       }

       SDL_FillRect( depthbuffer, 0, 0x0000);

#else

       depthbuffer = gui_gc_copy( gui_gc_global_GC() , SCREEN_WIDTH, SCREEN_HEIGHT );

       gui_gc_setRegion(depthbuffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
       gui_gc_begin(depthbuffer);

       gui_gc_setAlpha(depthbuffer, GC_A_OFF);

       gui_gc_setColorRGB(depthbuffer, 0, 0, 0);
       gui_gc_fillRect(depthbuffer, 0, 0, 320, 240);

#endif
}


void DepthBufferRenderer::InternalClose( void )
{
#if RENDER_WITH_SDL == 1

       SDL_FreeSurface( depthbuffer );
       SDL_Quit();

#else

       gui_gc_finish( depthbuffer );

#endif

       printf("Exited cleanly\n");
}


void DepthBufferRenderer::InternalFlipScreen( void )
{
#if RENDER_WITH_SDL == 1

       SDL_Flip(depthbuffer);

#else

       gui_gc_blit_to_screen(depthbuffer);

#endif
}


void DepthBufferRenderer::InternalClearScreen( unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       Uint32 rgb_code = SDL_MapRGB(depthbuffer->format, R, G, B);
       SDL_FillRect( depthbuffer, 0, rgb_code);
       SDL_Flip(depthbuffer);

#else

       gui_gc_setColorRGB(depthbuffer, R, G, B);
       gui_gc_fillRect(depthbuffer, 0, 0, 320, 240);

#endif
}


void DepthBufferRenderer::InternalDrawPixel( unsigned int x1, unsigned int y1, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       pixelRGBA( depthbuffer, x1, y1, R, G, B, A);

#else

       uint16_t b = (B >> 3) & 0x1f;
       uint16_t g = ((G >> 2) & 0x3f) << 5;
       uint16_t r = ((R >> 3) & 0x1f) << 11;

       uint16_t color = (r | g | b);

       uint16_t ** off_buff = ((((uint16_t *****)depthbuffer)[9])[0])[0x8];
       *(off_buff[y1] + x1) = color;

#endif
}


void DepthBufferRenderer::InternalDrawLine( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       lineRGBA( depthbuffer, x1, y1, x2, y2, R, G, B, A);

#else

       gui_gc_setColorRGB(depthbuffer, R, G, B);
       gui_gc_drawLine(depthbuffer, x1, y1, x2, y2);

#endif
}


void DepthBufferRenderer::InternalDrawRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       rectangleRGBA( depthbuffer, x1, y1, x2, y2, R, G, B, A);

#else

       gui_gc_setColorRGB(depthbuffer, R, G, B);
       gui_gc_drawRect(depthbuffer, x1, y1, x2-x1, y2-y1);

#endif
}


void DepthBufferRenderer::InternalDrawFilledRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       boxRGBA( depthbuffer, x1, y1, x2, y2, R, G, B, A);

#else

       gui_gc_setColorRGB(depthbuffer, R, G, B);
       gui_gc_fillRect(depthbuffer, x1, y1, x2-x1, y2-y1);

#endif
}


void DepthBufferRenderer::InternalDrawRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       roundedRectangleRGBA( depthbuffer, x1, y1, x2, y2, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(depthbuffer, R, G, B);

       gui_gc_drawArc(depthbuffer, x2-2*radius, y1, radius*2, radius*2, 0, 900);
       gui_gc_drawArc(depthbuffer, x1, y1, radius*2, radius*2, 900, 900);
       gui_gc_drawArc(depthbuffer, x1, y2-2*radius, radius*2, radius*2, 1800, 900);
       gui_gc_drawArc(depthbuffer, x2-2*radius, y2-2*radius, radius*2, radius*2, 2700, 900);

       gui_gc_drawLine(depthbuffer, x1+radius, y1, x2-radius, y1);
       gui_gc_drawLine(depthbuffer, x1+radius, y2, x2-radius, y2);
       gui_gc_drawLine(depthbuffer, x1, y1+radius, x1, y2-radius);
       gui_gc_drawLine(depthbuffer, x2, y1+radius, x2, y2-radius);

#endif
}


void DepthBufferRenderer::InternalDrawFilledRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       roundedBoxRGBA( depthbuffer, x1, y1, x2, y2, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(depthbuffer, R, G, B);

       gui_gc_fillArc(depthbuffer, x2-2*radius, y1, radius*2, radius*2, 0, 900);
       gui_gc_fillArc(depthbuffer, x1, y1, radius*2, radius*2, 900, 900);
       gui_gc_fillArc(depthbuffer, x1, y2-2*radius, radius*2, radius*2, 1800, 900);
       gui_gc_fillArc(depthbuffer, x2-2*radius, y2-2*radius, radius*2, radius*2, 2700, 900);

       gui_gc_fillRect(depthbuffer, x1, y1+radius, x2-x1, y2-y1-2*radius );
       gui_gc_fillRect(depthbuffer, x1+radius, y1, x2-x1-2*radius, radius );
       gui_gc_fillRect(depthbuffer, x1+radius, y2-radius, x2-x1-2*radius, radius );

#endif
}


void DepthBufferRenderer::InternalDrawCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       circleRGBA( depthbuffer, x, y, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(depthbuffer, R, G, B);
       gui_gc_drawArc(depthbuffer, x-radius, y-radius, radius*2, radius*2, 0, 3600);

#endif
}


void DepthBufferRenderer::InternalDrawFilledCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       filledCircleRGBA( depthbuffer, x, y, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(depthbuffer, R, G, B);
       gui_gc_fillArc(depthbuffer, x-radius, y-radius, radius*2, radius*2, 0, 3600);

#endif
}


unsigned char DepthBufferRenderer::InternalGetPixelR( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       Uint8 r,g,b;
       SDL_LockSurface( depthbuffer);
       SDL_GetRGB(getpixel(depthbuffer, x, y), depthbuffer->format, &r, &g, &b);
       return (unsigned char) r;

#else

       if ((x>=0) && (x<=SCREEN_WIDTH) && (y>=0) && (y<=SCREEN_HEIGHT))
       {
              char ** off_buff = ((((char *****)depthbuffer)[9])[0])[0x8];
              int res = *(unsigned short *) (off_buff[y] + 2*x);
              uint8_t r=(unsigned char) ((res >> 11 ) & 0b111111);
              return (unsigned char) (r<<3);
       }
#endif
}


unsigned char DepthBufferRenderer::InternalGetPixelG( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       Uint8 r,g,b;
       SDL_LockSurface( depthbuffer);
       SDL_GetRGB(getpixel(depthbuffer, x, y), depthbuffer->format, &r, &g, &b);
       return (unsigned char) g;

#else

       if ((x>=0) && (x<=SCREEN_WIDTH) && (y>=0) && (y<=SCREEN_HEIGHT))
       {
              char ** off_buff = ((((char *****)depthbuffer)[9])[0])[0x8];
              int res = *(unsigned short *) (off_buff[y] + 2*x);
              //uint8_t g=(unsigned char) ((res >> 6 ) & 0b11111);
              //return (unsigned char) (g<<3);
             uint8_t g=(unsigned char) ((res >> 5 ) & 0b111111);
              return (unsigned char) (g<<2);
       }

#endif
}


unsigned char DepthBufferRenderer::InternalGetPixelB( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       Uint8 r,g,b;
       SDL_LockSurface( depthbuffer);
       SDL_GetRGB(getpixel(depthbuffer, x, y), depthbuffer->format, &r, &g, &b);
       return (unsigned char) b;

#else

       if ((x>=0) && (x<=SCREEN_WIDTH) && (y>=0) && (y<=SCREEN_HEIGHT))
       {
              char ** off_buff = ((((char *****)depthbuffer)[9])[0])[0x8];
              int res = *(unsigned short *) (off_buff[y] + 2*x);
              uint8_t b=(unsigned char) (res & 0b11111);
              return (unsigned char) (b<<3);
       }

#endif
}


unsigned int DepthBufferRenderer::InternalGetPixel( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       return ((unsigned int) getpixel(depthbuffer, x, y));

#else

       if ((x>=0) && (x<=SCREEN_WIDTH) && (y>=0) && (y<=SCREEN_HEIGHT))
       {
              char ** off_buff = ((((char *****)depthbuffer)[9])[0])[0x8];
              return *(unsigned short *) (off_buff[y] + 2*x);
       }

#endif
}



#if RENDER_WITH_SDL == 1

void DepthBufferRenderer::InternalDrawSprite( SDL_Surface* sprite, Rect src, Rect pos )
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
       SDL_BlitSurface( sprite, &src_rect, depthbuffer, &screen_pos);
}

#else

void DepthBufferRenderer::InternalDrawSprite( spritegc* sprite, Rect src, Rect pos )
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
