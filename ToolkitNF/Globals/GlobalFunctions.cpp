#include "GlobalFunctions.hpp"

#include <sys/stat.h>

bool is_existing( const std::string& file )
{
    struct stat buffer;
    return (stat (file.c_str(), &buffer) == 0);
}


#if RENDER_WITH_SDL == 1

uint32_t getpixel(SDL_Surface *surface, int x, int y)
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
