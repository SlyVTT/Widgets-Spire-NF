#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H

#include "../Globals/GlobalFunctions.hpp"
#include "../Globals/GUIToolkitNFGlobals.hpp"

#if RENDER_WITH_SDL == 1
    #include <SDL/SDL.h>
#else
    #include <ngc.h>
#endif

#if TARGET_NSPIRE == 0
    #include <SDL/SDL.h>        // used to get access to SDL_Event
#endif // TARGET_NSPIRE



/// MouseManager class is a Singleton devoted to manage the touchpad hardware of the TI nSpire CX and CX-II

class MouseManager
{
public:

	MouseManager(MouseManager&) = delete;
	MouseManager& operator= (const MouseManager&) = delete;

    enum CursorType
    {
        Cursor_Pointer = 0,
        Cursor_Triangle = 1,
        Cursor_Roundclock = 2,
        Cursor_Hourglass = 3,
        Cursor_Leftrightresize = 4,
        Cursor_Topbottomresize = 5,
        Cursor_Handfinger = 6
    };

	static MouseManager& Get( void );

	static void Initialize( void ) { Get().InternalInitialize(); };
    static void Logic( void ) { Get().InternalLogic(); };
    static void ResetState( void ) { Get().InternalResetState(); };
    static void Render( void ) { Get().InternalRender(); };
    static void Close( void ) { Get().InternalClose(); };

    static void SetSensibility( float factor ) { Get().InternalSetSensibility( factor ); };
    static void SetDefaultSensibility( void ) { Get().InternalSetDefaultSensibility( ); };

    static unsigned int GetX( void ) { return Get().InternalGetX(); };
    static unsigned int GetY( void ) { return Get().InternalGetY(); };
    static bool GetB( void ) { return Get().InternalGetB(); };

       static bool kbUP( void ) { return Get().m_kbUP; };
       static bool kbUPRIGHT( void ) { return Get().m_kbUPRIGHT; };
       static bool kbRIGHT( void ) { return Get().m_kbRIGHT; };
       static bool kbRIGHTDOWN( void ) { return Get().m_kbRIGHTDOWN; };
       static bool kbDOWN( void ) { return Get().m_kbDOWN; };
       static bool kbDOWNLEFT( void ) { return Get().m_kbDOWNLEFT; };
       static bool kbLEFT( void ) { return Get().m_kbLEFT; };
       static bool kbLEFTUP( void ) { return Get().m_kbLEFTUP; };

        static bool kbUP_Press_Event( void ) { return Get().m_kbUP_Press_Event; };
       static bool kbUPRIGHT_Press_Event( void ) { return Get().m_kbUPRIGHT_Press_Event; };
       static bool kbRIGHT_Press_Event( void ) { return Get().m_kbRIGHT_Press_Event; };
       static bool kbRIGHTDOWN_Press_Event( void ) { return Get().m_kbRIGHTDOWN_Press_Event; };
       static bool kbDOWN_Press_Event( void ) { return Get().m_kbDOWN_Press_Event; };
       static bool kbDOWNLEFT_Press_Event( void ) { return Get().m_kbDOWNLEFT_Press_Event; };
       static bool kbLEFT_Press_Event( void ) { return Get().m_kbLEFT_Press_Event; };
       static bool kbLEFTUP_Press_Event( void ) { return Get().m_kbLEFTUP_Press_Event; };

    static bool kbUP_Release_Event( void ) { return Get().m_kbUP_Release_Event; };
    static bool kbUPRIGHT_Release_Event( void ) { return Get().m_kbUPRIGHT_Release_Event; };
    static bool kbRIGHT_Release_Event( void ) { return Get().m_kbRIGHT_Release_Event; };
    static bool kbRIGHTDOWN_Release_Event( void ) { return Get().m_kbRIGHTDOWN_Release_Event; };
    static bool kbDOWN_Release_Event( void ) { return Get().m_kbDOWN_Release_Event; };
    static bool kbDOWNLEFT_Release_Event( void ) { return Get().m_kbDOWNLEFT_Release_Event; };
    static bool kbLEFT_Release_Event( void ) { return Get().m_kbLEFT_Release_Event; };
    static bool kbLEFTUP_Release_Event( void ) { return Get().m_kbLEFTUP_Release_Event; };

    static bool IsKeyArrowEvent( void );
    static bool IsKeyArrowPressEvent( void );
    static bool IsKeyArrowReleaseEvent( void );


    static void ShowMouse() { Get().InternalShowMouse(); };
    static void HideMouse() { Get().InternalHideMouse(); };
    static bool IsMouseVisible() { return Get().InternalIsMouseVisible(); };
    static bool IsMouseEvent() { return Get().InternalIsMouseEvent(); };
    static bool IsMouseMoveEvent() { return Get().InternalIsMouseMoveEvent(); };
    static bool IsMouseClickEvent() { return Get().InternalIsMouseClickEvent(); };
    static bool IsMouseReleaseEvent() { return Get().InternalIsMouseReleaseEvent(); };
    static void SetCursorType( CursorType type ) { Get().InternalSetCursorType( type ); };



private:
	MouseManager();

	void InternalInitialize( void );
	void InternalLogic( void );
    void InternalResetState( void );
	void InternalRender( void );
	void InternalClose( void );

    void  InternalSetSensibility( float factor );
    void  InternalSetDefaultSensibility( void );

    unsigned int InternalGetX( void );
    unsigned int InternalGetY( void );
    bool InternalGetB( void );

    void InternalShowMouse();
    void InternalHideMouse();
    bool InternalIsMouseVisible();
    bool InternalIsMouseEvent();
    bool InternalIsMouseMoveEvent();
    bool InternalIsMouseClickEvent();
    bool InternalIsMouseReleaseEvent();
    void InternalSetCursorType( CursorType type );


	static MouseManager m_mouse;

	float m_sensibility;

	unsigned int m_x;
	unsigned int m_y;
	bool m_b;

	bool m_kbNONE;
	bool m_kbNONE_Previous;

	bool  m_kbCLICK;
	bool m_kbCLICK_Previous;
	bool m_kbCLICK_Press_Event;
	bool m_kbCLICK_Release_Event;

	       // Keys of the Touchpad
       bool m_kbUP;
       bool m_kbUP_Press_Event;
       bool m_kbUP_Release_Event;
       bool m_kbUPRIGHT;
       bool m_kbUPRIGHT_Press_Event;
       bool m_kbUPRIGHT_Release_Event;
       bool m_kbRIGHT;
       bool m_kbRIGHT_Press_Event;
       bool m_kbRIGHT_Release_Event;
       bool m_kbRIGHTDOWN;
       bool m_kbRIGHTDOWN_Press_Event;
       bool m_kbRIGHTDOWN_Release_Event;
       bool m_kbDOWN;
       bool m_kbDOWN_Press_Event;
       bool m_kbDOWN_Release_Event;
       bool m_kbDOWNLEFT;
       bool m_kbDOWNLEFT_Press_Event;
       bool m_kbDOWNLEFT_Release_Event;
       bool m_kbLEFT;
       bool m_kbLEFT_Press_Event;
       bool m_kbLEFT_Release_Event;
       bool m_kbLEFTUP;
       bool m_kbLEFTUP_Press_Event;
       bool m_kbLEFTUP_Release_Event;

	       // Keys of the Touchpad
       bool m_kbUP_Previous;
       bool m_kbUPRIGHT_Previous;
       bool m_kbRIGHT_Previous;
       bool m_kbRIGHTDOWN_Previous;
       bool m_kbDOWN_Previous;
       bool m_kbDOWNLEFT_Previous;
       bool m_kbLEFT_Previous;
       bool m_kbLEFTUP_Previous;


        // general state variables for arrow keys event
       bool keyevent_arrow;
       bool keypressevent_arrow;
       bool keyreleaseevent_arrow;



    bool show ;

    bool mouseevent ;
    bool mousemoveevent ;
    bool mouseclickevent ;
    bool mousereleaseevent ;

    CursorType cursor;


#if TARGET_NSPIRE == 0
        SDL_Event event;
        Uint8 *keys;
#endif


#if RENDER_WITH_SDL == 1

    SDL_Surface *cursor_pointer;
    SDL_Surface *cursor_triangle;
    SDL_Surface *cursor_roundclock;
    SDL_Surface *cursor_hourglass;
    SDL_Surface *cursor_topbottom;
    SDL_Surface *cursor_leftright;
    SDL_Surface *cursor_handfinger;

#else

    spritegc *cursor_pointer;
    spritegc *cursor_triangle;
    spritegc *cursor_roundclock;
    spritegc *cursor_hourglass;
    spritegc *cursor_topbottom;
    spritegc *cursor_leftright;
    spritegc *cursor_handfinger;

#endif

};

#endif // MOUSEMANAGER_H
