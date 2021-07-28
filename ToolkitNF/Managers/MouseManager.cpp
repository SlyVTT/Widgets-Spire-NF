#include "MouseManager.hpp"

#include "../Globals/GUIToolkitNFGlobals.hpp"
#include <libndls.h>

MouseManager::MouseManager()
{

}


MouseManager& MouseManager::Get( void )
{
       static MouseManager m_mouse;
       return m_mouse;
}


unsigned int MouseManager::InternalGetX( void )
{
       return m_x;
}


unsigned int MouseManager::InternalGetY( void )
{
       return m_y;
}


bool MouseManager::InternalGetB( void )
{
       return m_b;
}

void MouseManager::InternalSetSensibility( float factor )
{
    if (factor>10.0f)
        m_sensibility = 10.0f;
    else if (factor <0.1f)
        m_sensibility = 0.1f;
    else
        m_sensibility = factor;
}

void MouseManager::InternalSetDefaultSensibility( void )
{
    m_sensibility = 1.0f;
}

void MouseManager::InternalInitialize( void )
{
       m_x = SCREEN_WIDTH_GUI / 2;
       m_y = SCREEN_HEIGHT_GUI / 2;
       m_b = false;
}

bool MouseManager::IsKeyArrowEvent( void )
{
       return Get().keyevent_arrow;
}

bool MouseManager::IsKeyArrowPressEvent( void )
{
       return Get().keypressevent_arrow;
}

bool MouseManager::IsKeyArrowReleaseEvent( void )
{
       return Get(). keyreleaseevent_arrow;
}


void MouseManager::InternalLogic( void )
{
       touchpad_report_t touchpad;
       touchpad_scan(&touchpad);

       // We copy the former state of the touchpad and update the new status inot ad-hoc variables
       m_kbNONE_Previous = m_kbNONE;
       m_kbNONE = touchpad_arrow_pressed(TPAD_ARROW_NONE);
       keypressevent_arrow = (!m_kbNONE_Previous && m_kbNONE) ? true : false;
       keyreleaseevent_arrow= (m_kbNONE_Previous && !m_kbNONE) ? true : false;

       // We check if there are some event to be updated for the CLICK button of the touchpad
       m_kbCLICK_Previous = m_kbCLICK;
       m_kbCLICK = touchpad_arrow_pressed(TPAD_ARROW_CLICK);
       m_kbCLICK_Press_Event = (!m_kbCLICK_Previous && m_kbCLICK) ? true : false;
       m_kbCLICK_Release_Event = (m_kbCLICK_Previous && !m_kbCLICK) ? true : false;

       // As well as for all the direction arrows
       m_kbUP_Previous = m_kbUP;
       m_kbUP = touchpad_arrow_pressed(TPAD_ARROW_UP);
       m_kbUP_Press_Event = (!m_kbUP_Previous && m_kbUP) ? true : false;
       m_kbUP_Release_Event = (m_kbUP_Previous && !m_kbUP) ? true : false;

       m_kbUPRIGHT_Previous = m_kbUPRIGHT;
       m_kbUPRIGHT = touchpad_arrow_pressed(TPAD_ARROW_UPRIGHT);
       m_kbUPRIGHT_Press_Event = (!m_kbUPRIGHT_Previous && m_kbUPRIGHT) ? true : false;
       m_kbUPRIGHT_Release_Event = (m_kbUPRIGHT_Previous && !m_kbUPRIGHT) ? true : false;

       m_kbRIGHT_Previous = m_kbRIGHT;
       m_kbRIGHT = touchpad_arrow_pressed(TPAD_ARROW_RIGHT);
       m_kbRIGHT_Press_Event = (!m_kbRIGHT_Previous && m_kbRIGHT) ? true : false;
       m_kbRIGHT_Release_Event = (m_kbRIGHT_Previous && !m_kbRIGHT) ? true : false;

       m_kbRIGHTDOWN_Previous = m_kbRIGHTDOWN;
       m_kbRIGHTDOWN = touchpad_arrow_pressed(TPAD_ARROW_RIGHTDOWN);
       m_kbRIGHTDOWN_Press_Event = (!m_kbRIGHTDOWN_Previous && m_kbRIGHTDOWN) ? true : false;
       m_kbRIGHTDOWN_Release_Event = (m_kbRIGHTDOWN_Previous && !m_kbRIGHTDOWN) ? true : false;

       m_kbDOWN_Previous = m_kbDOWN;
       m_kbDOWN = touchpad_arrow_pressed(TPAD_ARROW_DOWN);
       m_kbDOWN_Press_Event = (!m_kbDOWN_Previous && m_kbDOWN) ? true : false;
       m_kbDOWN_Release_Event = (m_kbDOWN_Previous && !m_kbDOWN) ? true : false;

       m_kbDOWNLEFT_Previous = m_kbDOWNLEFT;
       m_kbDOWNLEFT = touchpad_arrow_pressed(TPAD_ARROW_DOWNLEFT);
       m_kbDOWNLEFT_Press_Event = (!m_kbDOWNLEFT_Previous && m_kbDOWNLEFT) ? true : false;
       m_kbDOWNLEFT_Release_Event = (m_kbDOWNLEFT_Previous && !m_kbDOWNLEFT) ? true : false;

       m_kbLEFT_Previous = m_kbLEFT;
       m_kbLEFT = touchpad_arrow_pressed(TPAD_ARROW_LEFT);
       m_kbLEFT_Press_Event = (!m_kbLEFT_Previous && m_kbLEFT) ? true : false;
       m_kbLEFT_Release_Event = (m_kbLEFT_Previous && !m_kbLEFT) ? true : false;

       m_kbLEFTUP_Previous = m_kbLEFTUP;
       m_kbLEFTUP = touchpad_arrow_pressed(TPAD_ARROW_LEFTUP);
       m_kbLEFTUP_Press_Event = (!m_kbLEFTUP_Previous && m_kbLEFTUP) ? true : false;
       m_kbLEFTUP_Release_Event = (m_kbLEFTUP_Previous && !m_kbLEFTUP) ? true : false;



       int dx = 0, dy = 0;
       int x = (int) m_x;
       int y= (int) m_y;


       static bool tp_last_contact = touchpad.contact;
       if(touchpad.contact && !touchpad.pressed)
       {
              static int tp_last_x = touchpad.x;
              static int tp_last_y = touchpad.y;

              if(tp_last_contact)
              {
                     dx = (touchpad.x - tp_last_x) / 10;
                     dy = (tp_last_y - touchpad.y) / 10;
              }

              tp_last_x = touchpad.x;
              tp_last_y = touchpad.y;
              tp_last_contact = touchpad.contact;
       }
       else
       {
              tp_last_contact = false;
       }


       x+=(dx * m_sensibility) ;
       y+=(dy * m_sensibility);

       // this block the cursor at the side of the screen
       if (x<0)
       {
              x=0;
       };
       if (y<0)
       {
              y=0;
       };
       if (x>=320)
       {
              x=320;
       };
       if (y>=240)
       {
              y=240;
       };

       m_x = (unsigned int) x;
       m_y = (unsigned int) y;
       m_b = m_kbCLICK;

}


void MouseManager::InternalResetState( void )
{
       m_x = SCREEN_WIDTH_GUI / 2;
       m_y = SCREEN_HEIGHT_GUI / 2;
       m_b = false;

       m_sensibility = 1.0f;

        // general state variables for arrow keys event
       keyevent_arrow = false;
       keypressevent_arrow = false;
       keyreleaseevent_arrow = false;


       // Keys of the Touchpad
       m_kbUP_Previous = false;
       m_kbUPRIGHT_Previous = false;
       m_kbRIGHT_Previous = false;
       m_kbRIGHTDOWN_Previous = false;
       m_kbDOWN_Previous = false;
       m_kbDOWNLEFT_Previous = false;
       m_kbLEFT_Previous = false;
       m_kbLEFTUP_Previous = false;

       // Keys of the Touchpad
       m_kbUP = false;
       m_kbUP_Press_Event = false;
       m_kbUP_Release_Event = false;
       m_kbUPRIGHT = false;
       m_kbUPRIGHT_Press_Event = false;
       m_kbUPRIGHT_Release_Event = false;
       m_kbRIGHT = false;
       m_kbRIGHT_Press_Event = false;
       m_kbRIGHT_Release_Event = false;
       m_kbRIGHTDOWN = false;
       m_kbRIGHTDOWN_Press_Event = false;
       m_kbRIGHTDOWN_Release_Event = false;
       m_kbDOWN = false;
       m_kbDOWN_Press_Event = false;
       m_kbDOWN_Release_Event = false;
       m_kbDOWNLEFT = false;
       m_kbDOWNLEFT_Press_Event = false;
       m_kbDOWNLEFT_Release_Event = false;
       m_kbLEFT = false;
       m_kbLEFT_Press_Event = false;
       m_kbLEFT_Release_Event = false;
       m_kbLEFTUP = false;
       m_kbLEFTUP_Press_Event = false;
       m_kbLEFTUP_Release_Event = false;

       m_kbCLICK = false;
       m_kbCLICK_Previous = false;
       m_kbCLICK_Press_Event = false;
       m_kbCLICK_Release_Event = false;

       m_kbNONE = false;
       m_kbNONE_Previous = false;
}
