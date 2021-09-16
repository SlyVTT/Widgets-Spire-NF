#ifndef DEPTHBUFFERRENDERER_HPP
#define DEPTHBUFFERRENDERER_HPP

#include "../Globals/GUIToolkitNFGlobals.hpp"

#include <string>

#if RENDER_WITH_SDL == 1
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>
    #include <SDL/SDL_gfxPrimitives.h>
#else
    #include <ngc.h>
#endif


#include "../Globals/GlobalFunctions.hpp"



class DepthBufferRenderer
{
public:

	DepthBufferRenderer(DepthBufferRenderer&) = delete;
	DepthBufferRenderer& operator= (const DepthBufferRenderer&) = delete;

	static DepthBufferRenderer& Get( void );

	static void Initialize( void ) { Get().InternalInitialize(); };
	static void Close( void ) { Get().InternalClose(); };

    static void FlipScreen( void ) { Get().InternalFlipScreen(); };

    static void ClearScreen( unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalClearScreen( R, G, B, A ); };

    static void DrawPixel(unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawPixel( x, y, R, G, B, A ); };
    static void DrawLine( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawLine( x1, y1, x2, y2, R, G, B, A ); };
    static void DrawRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawRectangle( x1, y1, x2, y2, R, G, B, A ); };
    static void DrawFilledRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawFilledRectangle( x1, y1, x2, y2, R, G, B, A ); };
    static void DrawCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawCircle( x, y, radius, R, G, B, A ); };
    static void DrawFilledCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawFilledCircle( x, y, radius, R, G, B, A ); };

    static void DrawRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawRoundedRectangle( x1, y1, x2, y2, radius, R, G, B, A ); };
    static void DrawFilledRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawFilledRoundedRectangle( x1, y1, x2, y2, radius, R, G, B, A ); };

    static void TakeScreenShot( void );

#if RENDER_WITH_SDL == 1

     static void DrawSprite( SDL_Surface* sprite, Rect src, Rect pos ) { Get().InternalDrawSprite( sprite, src, pos ); };

#else

    static void DrawSprite( spritegc* sprite, Rect src, Rect pos ) { Get().InternalDrawSprite( sprite, src, pos ); };

#endif

    static unsigned int GetPixel( unsigned int x, unsigned int y) {return Get().InternalGetPixel( x, y ); };
    static unsigned char GetPixelR( unsigned int x, unsigned int y) {return Get().InternalGetPixelR( x, y ); };
    static unsigned char GetPixelG( unsigned int x, unsigned int y) {return Get().InternalGetPixelG( x, y ); };
    static unsigned char GetPixelB( unsigned int x, unsigned int y) {return Get().InternalGetPixelB( x, y ); };

private:
	DepthBufferRenderer();

	void InternalInitialize( void );
	void InternalClose( void );

	#if RENDER_WITH_SDL == 1
        uint32_t _getpixel(SDL_Surface *surface, int x, int y);
    #endif

    void InternalFlipScreen( void );

    void InternalClearScreen( unsigned short R, unsigned short G, unsigned short B, unsigned short A );

    void InternalDrawPixel(unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawLine( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawFilledRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawFilledCircle( unsigned int x, unsigned int y, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawFilledRoundedRectangle( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius, unsigned short R, unsigned short G, unsigned short B, unsigned short A );

    unsigned int InternalGetPixel( unsigned int x, unsigned int y);
    unsigned char InternalGetPixelR( unsigned int x, unsigned int y);
    unsigned char InternalGetPixelG( unsigned int x, unsigned int y);
    unsigned char InternalGetPixelB( unsigned int x, unsigned int y);

    #if RENDER_WITH_SDL == 1

     void InternalDrawSprite( SDL_Surface* sprite, Rect src, Rect pos );

#else

    void InternalDrawSprite( spritegc* sprite, Rect src, Rect pos );

#endif

    void WriteToBMP( std::string filename );


	static DepthBufferRenderer m_render;

#if RENDER_WITH_SDL == 1
     SDL_Surface *depthbuffer;
#else
     Gc depthbuffer;
#endif

};

#endif // DEPTHBUFFERRENDERER_HPP
