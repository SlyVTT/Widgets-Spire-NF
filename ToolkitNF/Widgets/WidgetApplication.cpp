#include "WidgetApplication.hpp"


#include "../Globals/GlobalFunctions.hpp"
#include "../Globals/GUIToolkitNFGlobals.hpp"
#if DEBUG_MODE == 1
    #include "../Debugger/Debugger.hpp"
#endif // DEBUG_MODE

#if RENDER_WITH_SDL == 1
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif // RENDER_WITH_SDL


#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Managers/TimeManager.hpp"

#include "../Renderers/ScreenRenderer.hpp"
#include "../Renderers/DepthBufferRenderer.hpp"

#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"
#include "../Engines/ThemeEngine.hpp"



#include "Widget.hpp"
#include "DesktopWidget.hpp"

#include <libndls.h>

#include <sys/stat.h>

#include <string>


unsigned int GlobalWdidgetIDCounter;



WidgetApplication::WidgetApplication()
{

}



WidgetApplication& WidgetApplication::Get( void )
{
       static WidgetApplication m_application;
       return m_application;
}


void WidgetApplication::InternalPutOnTop( Widget *widgetsearched )
{
       dynamic_cast<DesktopWidget*>(currentdesktop->rootwidgets[0])->PutOnTop( widgetsearched );
}


void WidgetApplication::InternalInitialize( void )
{

       GlobalWdidgetIDCounter = 0;


       DesktopFeatures *maindesktop = new DesktopFeatures;
       desktops.push_back( maindesktop );
       InternalSetCurrentDesktop( 0 );


       ScreenRenderer::Initialize();
       DepthBufferRenderer::Initialize();

       KeyManager::Initialize();

       MouseManager::Initialize();
       MouseManager::SetSensibility( 2.0f );
       MouseManager::SetCursorType( MouseManager::Cursor_Pointer );

       TimeManager::Initialize();

       ColorEngine::Initialize();
       ColorEngine::SetDefaultColorPreset();

       FontEngine::Initialize();
       FontEngine::SetDefaultFontPreset();
}


void WidgetApplication::InternalPrepareForRun( void )
{
       // We need to init the theme engine, by default, this is not done at startup to save memory
       InternalInitThemeEngine();
       // We apply the default theme while using theme (this is for safe use and avoid any risk of crash)
       InternalSetDefaultTheme();

       // We render the app for the first time so what we can see what's happening on the screen
       InternalRender();

       // we adjust the desktop
       for (auto&c  : currentdesktop->rootwidgets)
              c->Adjust();
}

void WidgetApplication::InternalClose()
{

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t Entering WidgetAppplication::InternalClose() \n");
       Debugger::TimerLog( "\t \t Start Killing All Widgets in the Desktop ... \n");
#endif // DEBUG_MODE

       // for each desktopfeature class
       for (auto& c : desktops)
       {
              // if we have a wallpaper, we free the associated memory


#if RENDER_WITH_SDL == 1
              if (c->background_image != nullptr)
                    SDL_FreeSurface( c->background_image );
#else
              if (c->background_image != nullptr)
              {
                     free( c->background_image->data );
                     free( c->background_image );
              }
#endif

              //for each widget in the rootwidget of the desktop feature class, we delete it to ask for the destructor
              for (auto& d : c->rootwidgets)
              {
                     delete d;
              }

              // then we clear the collection
              c->rootwidgets.clear();

              //and finally we delete the desktopfeature
              delete c;
       }

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... All Widgets in the Desktop Killed [OK] \n \n");
#endif // DEBUG_MODE


#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t Start Closing All Singletons ... \n");
#endif // DEBUG_MODE

       // Now we clean all the Singleton by calling their Close() method (no destructor available)
       MouseManager::Close();

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... 1/8 Mouse Manager Killed [OK] \n");
#endif // DEBUG_MODE

       KeyManager::Close();

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... 2/8 Keyboard Manager Killed [OK] \n");
#endif // DEBUG_MODE

       ColorEngine::Close();

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... 3/8 Color Engine Killed [OK] \n");
#endif // DEBUG_MODE

       FontEngine::Close();

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... 4/8 Font Engine Killed [OK] \n");
#endif // DEBUG_MODE

       ThemeEngine::Close();

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... 5/8 Theme Engine Killed [OK] \n");
#endif // DEBUG_MODE

       DepthBufferRenderer::Close();

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... 6/8 DepthBuffer Renderer Killed [OK] \n");
#endif // DEBUG_MODE


       ScreenRenderer::Close();

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... 7/8 Screen Renderer Killed [OK] \n");
#endif // DEBUG_MODE


       TimeManager::Close();

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... 8/8 Timer Manager Killed [OK] \n");
#endif // DEBUG_MODE

#if RENDER_WITH_SDL == 1
            SDL_Quit();
            #if DEBUG_MODE == 1
                   Debugger::TimerLog( "\t \t ... Extra : SDL_Library Killed [OK] \n");
            #endif // DEBUG_MODE
#endif

#if DEBUG_MODE == 1
       Debugger::TimerLog( "\t \t ... All Singletons Killed [OK] \n");
#endif // DEBUG_MODE

}


void WidgetApplication::InternalAddChild( Widget *root )
{
       currentdesktop->rootwidgets.push_back( root );
}


void WidgetApplication::InternalRemoveChild( Widget *root )
{
       int i=0;
       for(auto& c : currentdesktop->rootwidgets )
       {
              if (c==root)
              {
                     //delete currentdesktop->rootwidgets[i];
                     currentdesktop->rootwidgets.erase( currentdesktop->rootwidgets.begin() + i );
                     return;
              }
              i++;
       }
}

void WidgetApplication::InternalAddChildToDesktop( Widget *root, DesktopFeatures *desktop )
{
       desktop->rootwidgets.push_back( root );
}



void WidgetApplication::InternalAddDesktop( )
{
       DesktopFeatures *desktoptoadd = new DesktopFeatures;
       desktops.push_back( desktoptoadd );
       nb_desktop++;
}

void WidgetApplication::InternalSetDrawBackground( bool setter )
{
       backgroundtobedrawn = setter;
}

void WidgetApplication::InternalRemoveDesktop( DesktopFeatures *desktoptoremove )
{
       // to be coded here
       int i=0;
       for( auto& c : desktops)
       {
              if (c==desktoptoremove)
              {
                     //delete desktops[i];
                     desktops.erase( desktops.begin()+i );
                     return;
              }
              i++;
       }
}


void WidgetApplication::InternalRun( RunMode mode )
{

       if (mode == ForcedRender)
              InternalLogicWithForcedRender();
       else if (mode == Normal)
              InternalLogic();
        else
            InternalLogic();        // Can not happen, but this is here in case one would like to develop another run mechanism
}


DesktopFeatures* WidgetApplication::InternalGetCurrentDesktopPointer( void )
{
       return desktops[cur_desktop];
}

void WidgetApplication::InternalSetCurrentDesktop( unsigned int ndesk )
{
       if (ndesk < nb_desktop)
       {
              cur_desktop = ndesk;
              currentdesktop = desktops[cur_desktop];
       }
}

int WidgetApplication::InternalGetCurrentDesktop( void )
{
       return cur_desktop;
}

void WidgetApplication::InternalSetNextDesktop( void )
{
       if (cur_desktop < nb_desktop-1)
       {
              cur_desktop++;
       }
       else
       {
              cur_desktop = 0;
       }

       currentdesktop=desktops[cur_desktop];
}

void WidgetApplication::InternalSetPreviousDesktop( void )
{
       if (cur_desktop > 0)
       {
              cur_desktop--;
       }
       else
       {
              cur_desktop = nb_desktop-1;
       }

       currentdesktop=desktops[cur_desktop];
}



void WidgetApplication::InternalRenderDepth( void )
{
       // We clear the depthbuffer of the current desktop
       DepthBufferRenderer::ClearScreen( 0, 0, 0, 0 );

       // we scrutinize all the rootwidgets on the current desktop and render them in the depth buffer
       // we cannot launch a (currentdesktop->renderdepth method()) cause currentdesktop is a struct, not a widget derivative class
       // the renderdepth method is one of the widget class

       for (auto& c : currentdesktop->rootwidgets )
              if (c->IsVisible()) c->RenderDepth( );
}



void WidgetApplication::InternalRender( void )
{
       if (backgroundtobedrawn)
       {
              if (!currentdesktop->uniform_background && !currentdesktop->background_wallpaper)
              {
                     ScreenRenderer::ClearScreen( 0, 0, 0, 0 );
              }

              if (currentdesktop->uniform_background && !currentdesktop->background_wallpaper)
              {
                     ScreenRenderer::ClearScreen( currentdesktop->r_background, currentdesktop->g_background, currentdesktop->b_background, 255 );
              }

              if (!currentdesktop->uniform_background && currentdesktop->background_wallpaper)
              {
                     ScreenRenderer::DrawImageBackground(currentdesktop->background_image );
              }
       }

       for (auto& c : currentdesktop->rootwidgets )
              if (c->IsVisible()) c->Render( );

       MouseManager::Render();
       ScreenRenderer::FlipScreen();
}



void WidgetApplication::InternalLogic( void )
{

       MouseManager::Logic();
       KeyManager::Logic();

       // if an event from mouse or from keyboard is detected, we launch the render() and the children->logic() processes
       if (KeyManager::IsAnyKeyEvent() || MouseManager::IsKeyArrowEvent() || MouseManager::IsMouseEvent() )
       {
              InternalRender();
              InternalRenderDepth();

              for (auto& c : currentdesktop->rootwidgets )
                     if (c->IsVisible() && c->IsEnabled()) c->Logic( );
       }

       // This is to take a screenshot to be store in the Widget folder.
       if (KeyManager::kbCTRL() && KeyManager::kbDOT() )
       {
              ScreenRenderer::TakeScreenShot();
              DepthBufferRenderer::TakeScreenShot();
       }

       if (KeyManager::kbCTRL()  && KeyManager::kbSHIFT() && KeyManager::kbESC())
       {
              AskForClose = true;
       };

       if (KeyManager::kbCTRL()  && KeyManager::kbSHIFT() && KeyManager::kb7())
       {
              InternalSetPreviousDesktop();
              TimeManager::Delay( 250 );
       };

       if (KeyManager::kbCTRL()  && KeyManager::kbSHIFT() && KeyManager::kb9())
       {
              InternalSetNextDesktop();
              TimeManager::Delay( 250 );
       };

       if (KeyManager::kbCTRL()  && KeyManager::kbSHIFT() && KeyManager::kb8())
       {
              //To be coded : shortcut for listing all the desktops and show a thumbnail
       };
}


void WidgetApplication::InternalLogicWithForcedRender( void )
{

       MouseManager::Logic();
       KeyManager::Logic();

       InternalRender();
       InternalRenderDepth();

       for (auto& c : currentdesktop->rootwidgets )
              if (c->IsVisible() && c->IsEnabled()) c->Logic( );


       // This is to take a screenshot to be store in the Widget folder.
       if (KeyManager::kbCTRL() && KeyManager::kbDOT() )
       {
              ScreenRenderer::TakeScreenShot();
              DepthBufferRenderer::TakeScreenShot();
       }

       if (KeyManager::kbCTRL()  && KeyManager::kbSHIFT() && KeyManager::kbESC())
       {
              AskForClose = true;
       };


       if (KeyManager::kbCTRL()  && KeyManager::kbSHIFT() && KeyManager::kb7())
       {
              InternalSetPreviousDesktop();
              TimeManager::Delay( 250 );
       };

       if (KeyManager::kbCTRL()  && KeyManager::kbSHIFT() && KeyManager::kb9())
       {
              InternalSetNextDesktop();
              TimeManager::Delay( 250 );
       };

       if (KeyManager::kbCTRL()  && KeyManager::kbSHIFT() && KeyManager::kb8())
       {
              //To be coded : shortcut for listing all the desktops and show a thumbnail
       };
}

bool WidgetApplication::InternalAskForClosure( void )
{
       return AskForClose;
}

void WidgetApplication::InternalSetUniformBackgroundColor( uint8_t r, uint8_t g, uint8_t b)
{
       currentdesktop->uniform_background = true;
       currentdesktop->background_wallpaper = false;

       currentdesktop->r_background = r;
       currentdesktop->g_background = g;
       currentdesktop->b_background = b;
}

void WidgetApplication::InternalSetBackgroundPicture( std::string filename )
{
       currentdesktop->uniform_background = false;
       currentdesktop->background_wallpaper = true;

       currentdesktop->position_background.x = 0;
       currentdesktop->position_background.y = 0;
       currentdesktop->position_background.w = 320;
       currentdesktop->position_background.h = 240;


#if RENDER_WITH_SDL == 1
       currentdesktop->background_image = IMG_Load( filename.c_str() );
#else
       currentdesktop->background_image = ReadBMP( filename.c_str() );
#endif
}


void WidgetApplication::InternalInitThemeEngine( void )
{
       ThemeEngine::Initialize();
}

void WidgetApplication::InternalSetDefaultTheme( void )
{
       ThemeEngine::SetDefaultThemePreset();
}


void WidgetApplication::InternalLoadTheme( std::string filename )
{
       ThemeEngine::LoadThemeFromFile( filename );
       ThemeEngine::ApplyTheme();
}
