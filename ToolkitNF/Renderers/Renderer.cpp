#include "Renderer.hpp"



#if RENDER_WITH_SDL == 1
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
       int bpp = surface->format->BytesPerPixel;
       /* Here p is the address to the pixel we want to retrieve */
       Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

       switch(bpp)
       {
       case 1:
              return *p;

       case 2:
              return *(Uint16 *)p;

       case 3:
              if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                     return p[0] << 16 | p[1] << 8 | p[2];
              else
                     return p[0] | p[1] << 8 | p[2] << 16;

       case 4:
              return *(Uint32 *)p;

       default:
              return 0;       /* shouldn't happen, but avoids warnings */
       }
}
#endif


Renderer::Renderer()
{

}


Renderer& Renderer::Get( void )
{
       static Renderer m_renderer;
       return m_renderer;
}


void Renderer::InternalInitialize( void )
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


void Renderer::InternalClose( void )
{
#if RENDER_WITH_SDL == 1

       SDL_FreeSurface( screen );
       SDL_Quit();

#else

       gui_gc_finish( screen );

#endif

       printf("Exited cleanly\n");
}


void Renderer::InternalFlipScreen( void )
{
#if RENDER_WITH_SDL == 1

       SDL_Flip(screen);

#else

       gui_gc_blit_to_screen(screen);

#endif
}


void Renderer::InternalClearScreen( unsigned short R, unsigned short G, unsigned short B, unsigned short A )
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


void Renderer::InternalDrawPixel( unsigned int x1, unsigned int y1, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       pixelRGBA( screen, x1, y1, R, G, B, A);

#else

       uint16_t b = (B >> 3) & 0x1f;
       uint16_t g = ((G >> 2) & 0x3f) << 5;
       uint16_t r = ((R >> 3) & 0x1f) << 11;

       uint16_t color = (r | g | b);

       uint16_t ** off_buff = ((((uint16_t *****)screen)[9])[0])[0x8];
       *(off_buff[y1] + x1) = color;

#endif
}


void Renderer::InternalDrawLine( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       lineRGBA( screen, x1, y1, x2, y2, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_drawLine(screen, x1, y1, x2, y2);

#endif
}


void Renderer::InternalDrawRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       rectangleRGBA( screen, x1, y1, x2, y2, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_drawRect(screen, x1, y1, x2-x1, y2-y1);

#endif
}


void Renderer::InternalDrawFilledRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       boxRGBA( screen, x1, y1, x2, y2, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_fillRect(screen, x1, y1, x2-x1, y2-y1);

#endif
}


void Renderer::InternalDrawRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
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


void Renderer::InternalDrawFilledRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
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


void Renderer::InternalDrawCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       circleRGBA( screen, x, y, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_drawArc(screen, x-radius, y-radius, radius*2, radius*2, 0, 3600);

#endif
}


void Renderer::InternalDrawFilledCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
#if RENDER_WITH_SDL == 1

       filledCircleRGBA( screen, x, y, radius, R, G, B, A);

#else

       gui_gc_setColorRGB(screen, R, G, B);
       gui_gc_fillArc(screen, x-radius, y-radius, radius*2, radius*2, 0, 3600);

#endif
}


unsigned char Renderer::InternalGetPixelR( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       Uint8 r,g,b;
       SDL_LockSurface( screen);
       SDL_GetRGB(getpixel(screen, x, y), screen->format, &r, &g, &b);
       return (unsigned char) r;

#else

       char ** off_buff = ((((char *****)screen)[9])[0])[0x8];
       int res = *(unsigned short *) (off_buff[y] + 2*x);
       uint8_t r=(unsigned char) ((res >> 11 ) & 0b111111);
       return (unsigned char) (r<<3);

#endif
}


unsigned char Renderer::InternalGetPixelG( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       Uint8 r,g,b;
       SDL_LockSurface( screen);
       SDL_GetRGB(getpixel(screen, x, y), screen->format, &r, &g, &b);
       return (unsigned char) g;

#else

       char ** off_buff = ((((char *****)screen)[9])[0])[0x8];
       int res = *(unsigned short *) (off_buff[y] + 2*x);
       uint8_t g=(unsigned char) ((res >> 6 ) & 0b11111);
       return (unsigned char) (g<<3);

#endif
}


unsigned char Renderer::InternalGetPixelB( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       Uint8 r,g,b;
       SDL_LockSurface( screen);
       SDL_GetRGB(getpixel(screen, x, y), screen->format, &r, &g, &b);
       return (unsigned char) b;

#else

       char ** off_buff = ((((char *****)screen)[9])[0])[0x8];
       int res = *(unsigned short *) (off_buff[y] + 2*x);
       uint8_t b=(unsigned char) (res & 0b11111);
       return (unsigned char) (b<<3);

#endif
}


unsigned int Renderer::InternalGetPixel( unsigned int x, unsigned int y )
{
#if RENDER_WITH_SDL == 1

       return ((unsigned int) getpixel(screen, x, y));

#else

       char ** off_buff = ((((char *****)screen)[9])[0])[0x8];
       return *(unsigned short *) (off_buff[y] + 2*x);

#endif
}
