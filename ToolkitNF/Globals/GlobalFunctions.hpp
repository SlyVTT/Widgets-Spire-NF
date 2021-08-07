#ifndef GLOBALFUNCTIONS_HPP_INCLUDED
#define GLOBALFUNCTIONS_HPP_INCLUDED

#include <string>


#include "../Globals/GUIToolkitNFGlobals.hpp"


#if RENDER_WITH_SDL == 1

    #include <SDL/SDL.h>

#else

    struct spritegc
    {
           unsigned short transparency;
           unsigned short width;
           unsigned short height;
           unsigned short* data;
    };

    struct imagegc
    {
           unsigned short width;
           unsigned short height;
           unsigned short* data;
    };

#endif



struct Rect
{
       unsigned int x;
       unsigned int y;
       unsigned int w;
       unsigned int h;
};


bool is_existing( const std::string& file );



#if RENDER_WITH_SDL == 1

    uint32_t getpixel(SDL_Surface *surface, int x, int y);

#else

    imagegc* ReadBMP( std::string filename);

#endif






#endif // GLOBALFUNCTIONS_HPP_INCLUDED
