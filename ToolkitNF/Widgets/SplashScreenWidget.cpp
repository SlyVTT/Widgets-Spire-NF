#include "SplashScreenWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Managers/TimeManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"

#if DEBUG_MODE == 1
    #include "../Debugger/Debugger.hpp"
#endif // DEBUG_MODE

#if RENDER_WITH_SDL == 1
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#endif // RENDER_WITH_SDL


SplashScreenWidget::SplashScreenWidget() : Widget()
{
       widgettype = "SplashScreen";
       filereference = "";
       SetInvisible();
}

SplashScreenWidget::SplashScreenWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "SplashScreen";
       filereference = "";
       SetInvisible();
}

SplashScreenWidget::~SplashScreenWidget()
{

#if DEBUG_MODE == 1
    Debugger::TimerLog( "!!! Entering Splash Screen Destructor \n");
#endif // DEBUG_MODE


#if RENDER_WITH_SDL == 1

       if (image) SDL_FreeSurface( image );

#else

#if DEBUG_MODE == 1
    Debugger::TimerLog( "\t !!! Will free Data Memory if possible \n");
#endif // DEBUG_MODE

       if (image)
       {
           #if DEBUG_MODE == 1
    Debugger::TimerLog( "\t\t !!! OK, I need to clean everythinge \n");
#endif // DEBUG_MODE

              free( image->data );

              #if DEBUG_MODE == 1
    Debugger::TimerLog( "\t\t\t !!! Data Memory freed OK \n");
#endif // DEBUG_MODE

              free( image );

              #if DEBUG_MODE == 1
    Debugger::TimerLog( "\t\t\t !!! Image Structure Memory freed OK \n");
#endif // DEBUG_MODE

              image = nullptr;

              #if DEBUG_MODE == 1
    Debugger::TimerLog( "\t\t\t !!! Pointer Image set to NULLPTR OK \n");
#endif // DEBUG_MODE

       }
 #endif

#if DEBUG_MODE == 1
    Debugger::TimerLog( "!!! SplashScreen Destructor finished now");
#endif // DEBUG_MODE

}

void SplashScreenWidget::SetDuration( uint32_t duration )
{
       durationsplash = duration;
}

void SplashScreenWidget::Start( void )
{
       if (image==nullptr)  AssignImage( filereference );
       timerstart =TimeManager::GetTicks();
       SetVisible();
}

void SplashScreenWidget::AssignImage( std::string filename )
{

#if RENDER_WITH_SDL == 1

       if (image) SDL_FreeSurface( image);
       image = IMG_Load( filename.c_str() );

       filereference = filename;

       width = image->w + 6;
       height = image->h + 6;

       xpos = (SCREEN_WIDTH_GUI-image->w) /2 - 3;
       ypos = (SCREEN_HEIGHT_GUI-image->h)/2 - 3;
#else

       if (image)
       {
              free( image->data );
              free( image );
              image = nullptr;
       }

       image = ReadBMP( filename.c_str() );

       filereference = filename;

       width = image->width + 6;
       height = image->height + 6;

       xpos = (SCREEN_WIDTH_GUI-image->width) /2 - 3;
       ypos = (SCREEN_HEIGHT_GUI-image->height)/2 - 3;

#endif

}

void SplashScreenWidget::Logic( void )
{
       if (is_enabled && is_visible)
       {

              is_hovering = CursorOn(  );

              currenttimer = TimeManager::GetTicks();

              if ((currenttimer-timerstart) >= durationsplash)
              {
                     SetInvisible();

#if RENDER_WITH_SDL == 1

                     if (image) SDL_FreeSurface( image );

#else

                     if (image)
                     {
                            free( image->data );
                            free( image );
                            image = nullptr;
                     }

#endif
              }

              for (auto& c : children) c->Logic(  );     // Very few chance to occur, SplashScreen with children widgets is a bit strange
       }
}

void SplashScreenWidget::Render( void )
{
       if (is_visible)
       {

              if (image)
              {
                     Rect src_rect, screen_pos;

#if RENDER_WITH_SDL == 1

                     src_rect.x = 0;
                     src_rect.y = 0;
                     src_rect.w = image->w;
                     src_rect.h = image->h;

                     screen_pos.x = (SCREEN_WIDTH_GUI-image->w) /2;
                     screen_pos.y = (SCREEN_HEIGHT_GUI-image->h)/2;
                     screen_pos.w = image->w;
                     screen_pos.h = image->h;

#else

                     src_rect.x = 0;
                     src_rect.y = 0;
                     src_rect.w = image->width;
                     src_rect.h = image->height;

                     screen_pos.x = (SCREEN_WIDTH_GUI-image->width) /2;
                     screen_pos.y = (SCREEN_HEIGHT_GUI-image->height)/2;
                     screen_pos.w = image->width;
                     screen_pos.h = image->height;

#endif


                     ScreenRenderer::DrawFilledRoundedRectangle(  screen_pos.x-3, screen_pos.y-3, screen_pos.x+src_rect.w+3, screen_pos.y+ src_rect.h+3, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

                     if (!is_hovering)
                     {
                            ScreenRenderer::DrawRoundedRectangle( screen_pos.x-3, screen_pos.y-3, screen_pos.x+src_rect.w+3, screen_pos.y+ src_rect.h+3, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                     }
                     else
                     {
                            ScreenRenderer::DrawRoundedRectangle( screen_pos.x-3, screen_pos.y-3, screen_pos.x+src_rect.w+3, screen_pos.y+ src_rect.h+3, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                     }

                     ScreenRenderer::DrawImage( image, src_rect, screen_pos);
              }

              for (auto& c : children) c->Render( );
       }
       else  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE BUT DISABLED
       {

       }
}
