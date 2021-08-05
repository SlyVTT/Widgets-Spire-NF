#include "../Globals/GUIToolkitNFGlobals.hpp"
#include "../Globals/GlobalFunctions.hpp"

#include "MouseManager.hpp"
#include "CursorsDesigns.hpp"


#include <libndls.h>

#include "../Renderers/ScreenRenderer.hpp"


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

       show = true;

       cursor = Cursor_Pointer;

       keyevent_arrow = false;
       keypressevent_arrow = false;
       keyreleaseevent_arrow = false;

       mouseevent = false;
       mousemoveevent = false;
       mouseclickevent = false;
       mousereleaseevent = false;


#if RENDER_WITH_SDL == 1

       // the transparent color is define as red (note that the sprite of the cursor are defined with this convention
       Uint32 transparency = 0xf800; //SDL_MapRGB(SDL_GetVideoSurface()->format, 255, 0, 0);

       cursor_pointer = nSDL_LoadImage(image_Arrow);
       SDL_SetColorKey(cursor_pointer, SDL_SRCCOLORKEY, transparency);

       cursor_triangle = nSDL_LoadImage(image_Triangle);
       SDL_SetColorKey(cursor_triangle, SDL_SRCCOLORKEY, transparency);

       cursor_roundclock = nSDL_LoadImage(image_Clock);
       SDL_SetColorKey(cursor_roundclock, SDL_SRCCOLORKEY, transparency);

       cursor_hourglass = nSDL_LoadImage(image_Hourglass);
       SDL_SetColorKey(cursor_hourglass, SDL_SRCCOLORKEY, transparency);

       cursor_topbottom = nSDL_LoadImage(image_TopBottomResize);
       SDL_SetColorKey(cursor_topbottom, SDL_SRCCOLORKEY, transparency);

       cursor_leftright = nSDL_LoadImage(image_LeftRightResize);
       SDL_SetColorKey(cursor_leftright, SDL_SRCCOLORKEY, transparency);

       cursor_handfinger = nSDL_LoadImage(image_HandFinger);
       SDL_SetColorKey(cursor_handfinger, SDL_SRCCOLORKEY, transparency);

#else

       cursor_pointer = (spritegc*) malloc(sizeof(spritegc));
       cursor_pointer->transparency = 0xf800;
       cursor_pointer->width = 20;
       cursor_pointer->height = 20;
       cursor_pointer->data = image_Arrow+4;

       cursor_triangle = (spritegc*) malloc(sizeof(spritegc));
       cursor_triangle->transparency = 0xf800;
       cursor_triangle->width = 20;
       cursor_triangle->height = 20;
       cursor_triangle->data = image_Triangle+4;

       cursor_roundclock = (spritegc*) malloc(sizeof(spritegc));
       cursor_roundclock->transparency = 0xf800;
       cursor_roundclock->width = 20;
       cursor_roundclock->height = 20;
       cursor_roundclock->data = image_Clock+4;

       cursor_hourglass = (spritegc*) malloc(sizeof(spritegc));
       cursor_hourglass->transparency = 0xf800;
       cursor_hourglass->width = 20;
       cursor_hourglass->height = 20;
       cursor_hourglass->data = image_Hourglass+4;

       cursor_topbottom = (spritegc*) malloc(sizeof(spritegc));
       cursor_topbottom->transparency = 0xf800;
       cursor_topbottom->width = 20;
       cursor_topbottom->height = 20;
       cursor_topbottom->data = image_TopBottomResize+4;

       cursor_leftright = (spritegc*) malloc(sizeof(spritegc));
       cursor_leftright->transparency = 0xf800;
       cursor_leftright->width = 20;
       cursor_leftright->height = 20;
       cursor_leftright->data = image_LeftRightResize+4;

       cursor_handfinger = (spritegc*) malloc(sizeof(spritegc));
       cursor_handfinger->transparency = 0xf800;
       cursor_handfinger->width = 20;
       cursor_handfinger->height = 20;
       cursor_handfinger->data = image_HandFinger+4;

#endif

}

void MouseManager::InternalClose( void )
{
#if RENDER_WITH_SDL == 1

       SDL_FreeSurface( cursor_pointer );
       SDL_FreeSurface( cursor_triangle );
       SDL_FreeSurface( cursor_roundclock );
       SDL_FreeSurface( cursor_hourglass );
       SDL_FreeSurface( cursor_topbottom );
       SDL_FreeSurface( cursor_leftright );
       SDL_FreeSurface( cursor_handfinger );

#else

       free( cursor_pointer );
       free( cursor_triangle );
       free( cursor_roundclock );
       free( cursor_hourglass );
       free( cursor_topbottom );
       free( cursor_leftright );
       free( cursor_handfinger );

#endif


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


       if (!mouseclickevent && m_kbCLICK)
       {
              mouseclickevent = true;
              mousereleaseevent = false;
       }

       if (mouseclickevent && !m_kbCLICK)
       {
              mouseclickevent = false;
              mousereleaseevent = true;
       }

       if ((mouseclickevent && m_kbCLICK) || (mousereleaseevent && !m_kbCLICK))
       {
              mouseclickevent = false;
              mousereleaseevent = false;
       }


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
       if (x>=SCREEN_WIDTH_GUI)
       {
              x=SCREEN_WIDTH_GUI;
       };
       if (y>=SCREEN_HEIGHT_GUI)
       {
              y=SCREEN_HEIGHT_GUI;
       };


       // check for mouse move
       if ((dx != 0) || (dy !=0))
       {
              mousemoveevent = true;
       }
       else
       {
              mousemoveevent = false;
       }

       // check if something new has happen with the mouse (either click/release or cursor move)
       if (mouseclickevent || mousereleaseevent || mousemoveevent)
       {
              mouseevent = true;
       }
       else
       {
              mousemoveevent = false;
       }

       m_x = (unsigned int) x;
       m_y = (unsigned int) y;
       m_b = m_kbCLICK;

}


void MouseManager::InternalRender()
{
       if(!show)
              return;

       Rect src_rect, screen_pos;
       src_rect.x = 0;
       src_rect.y = 0;
       src_rect.w = 20;
       src_rect.h = 20;


       if (cursor == Cursor_Pointer)
       {
              screen_pos.x = InternalGetX();
              screen_pos.y = InternalGetY();
              ScreenRenderer::DrawSprite(cursor_pointer, src_rect, screen_pos);
       }

       if (cursor == Cursor_Triangle)
       {
              screen_pos.x = InternalGetX();
              screen_pos.y = InternalGetY();
              ScreenRenderer::DrawSprite(cursor_triangle, src_rect, screen_pos);
       }

       if (cursor == Cursor_Roundclock)
       {
              screen_pos.x = InternalGetX() -10;
              screen_pos.y = InternalGetY() -10;
              ScreenRenderer::DrawSprite(cursor_roundclock, src_rect, screen_pos);
       }

       if (cursor == Cursor_Hourglass)
       {
              screen_pos.x = InternalGetX() -10;
              screen_pos.y = InternalGetY() -10;
              ScreenRenderer::DrawSprite(cursor_hourglass, src_rect, screen_pos);
       }

       if (cursor == Cursor_Leftrightresize)
       {
              screen_pos.x = InternalGetX() -10;
              screen_pos.y = InternalGetY() -10;
              ScreenRenderer::DrawSprite(cursor_leftright, src_rect, screen_pos);
       }

       if (cursor == Cursor_Topbottomresize)
       {
              screen_pos.x = InternalGetX() -10;
              screen_pos.y = InternalGetY() -10;
              ScreenRenderer::DrawSprite(cursor_topbottom, src_rect, screen_pos);
       }

       if (cursor == Cursor_Handfinger)
       {
              screen_pos.x = InternalGetX() -5;
              screen_pos.y = InternalGetY() -5;
              ScreenRenderer::DrawSprite(cursor_handfinger, src_rect, screen_pos);
       }


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


void MouseManager::InternalShowMouse()
{
       show=true;
}


void MouseManager::InternalHideMouse()
{
       show=false;
}


bool MouseManager::InternalIsMouseVisible()
{
       return show;
}

bool MouseManager::InternalIsMouseEvent()
{
       return mouseevent;
}


bool MouseManager::InternalIsMouseMoveEvent()
{
       return mousemoveevent;
}


bool MouseManager::InternalIsMouseClickEvent()
{
       return mouseclickevent;
}


bool MouseManager::InternalIsMouseReleaseEvent()
{
       return mousereleaseevent;
}


void MouseManager::InternalSetCursorType( CursorType type )
{
       cursor = type;
}
