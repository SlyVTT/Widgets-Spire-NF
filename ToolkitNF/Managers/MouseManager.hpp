#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H


/// MouseManager class is a Singleton devoted to manage the touchpad hardware of the TI nSpire CX and CX-II

class MouseManager
{
public:

	MouseManager(MouseManager&) = delete;
	MouseManager& operator= (const MouseManager&) = delete;

	static MouseManager& Get( void );

	static void Initialize( void ) { Get().InternalInitialize(); };
    static void Logic( void ) { Get().InternalLogic(); };
    static void ResetState( void ) { Get().InternalResetState(); };

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

    virtual bool IsKeyArrowEvent( void );
    virtual bool IsKeyArrowPressEvent( void );
    virtual bool IsKeyArrowReleaseEvent( void );

private:
	MouseManager();

	void InternalInitialize( void );
	void InternalLogic( void );
    void InternalResetState( void );

    void  InternalSetSensibility( float factor );
    void  InternalSetDefaultSensibility( void );

    unsigned int InternalGetX( void );
    unsigned int InternalGetY( void );
    bool InternalGetB( void );

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
};

#endif // MOUSEMANAGER_H
