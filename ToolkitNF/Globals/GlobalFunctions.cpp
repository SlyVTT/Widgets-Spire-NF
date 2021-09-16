#include "GlobalFunctions.hpp"

#include "../Debugger/Debugger.hpp"

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
       // Here p is the address to the pixel we want to retrieve
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
              return 0;       // shouldn't happen, but avoids warnings
       }
}

#else


imagegc* ReadBMP( std::string filename)
{
    FILE* f = fopen(filename.c_str(), "rb");

    if(f == NULL)
        return nullptr;

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    imagegc* image = (imagegc*) malloc( sizeof(imagegc));

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    image->width = width;
    image->height = height;
    uint16_t* imagedata = (uint16_t*) malloc( width * height * sizeof(uint16_t) );

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    char R,G,B;

    //----------------------------
    int offsetdata = *(int*)&info[10];
    int delta;


    if (offsetdata>54)
    {
        delta = offsetdata-54;
        fread(data, sizeof(unsigned char), delta, f );
    }
    //-----------------------------

    for(int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            B=data[j];
            G=data[j+1];
            R=data[j+2];

             uint16_t b = (B >> 3) & 0x1f;
             uint16_t g = ((G >> 2) & 0x3f) << 5;
             uint16_t r = ((R >> 3) & 0x1f) << 11;

             imagedata[(height-1-i)*width+j/3] = (uint16_t) (r | g | b);
        }
    }
    delete[] data;

    image->data = imagedata;

    fclose(f);
    return image;
}


#endif


