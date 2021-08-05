#ifndef WIDGETAPPLICATION_H
#define WIDGETAPPLICATION_H

#include "Widget.hpp"

#include "../Globals/GlobalFunctions.hpp"
#include "../Globals/GUIToolkitNFGlobals.hpp"


#if RENDER_WITH_SDL == 1
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>
#endif // RENDER_WITH_SDL


#include <vector>


struct DesktopFeatures
{
       bool uniform_background = false;
       bool background_wallpaper = false;

       uint8_t r_background = 0;
       uint8_t g_background = 0;
       uint8_t b_background = 0;

#if RENDER_WITH_SDL == 1
       SDL_Surface* background_image=nullptr;
#else
      imagegc* background_image=nullptr;
#endif

       Rect position_background;

       // This allows having multiple desktops/screens in future revisions
       std::vector< Widget* > rootwidgets;
};


class WidgetApplication
{
public:

    enum RunMode
    {
        ForcedRender = 1,
        Normal = 2
    };

       //virtual void DEBUG_draw_widget_tree_structure( char* filename );

       WidgetApplication(WidgetApplication&) = delete;
       WidgetApplication& operator= (const WidgetApplication&) = delete;

       static WidgetApplication& Get( void );

       static bool AskForClosure( void ) { return Get().InternalAskForClosure( ); };

       static void AddChild( Widget *root ) { Get().InternalAddChild( root ); };
       static void RemoveChild( Widget *root ) { Get().InternalRemoveChild( root ); };

       static void AddChildToDesktop( Widget *root, DesktopFeatures *desktop ) { Get().InternalAddChildToDesktop( root, desktop ); };

       static void AddDesktop( void ) { Get().InternalAddDesktop(); };
       static void RemoveDesktop( DesktopFeatures *desktoptoremove) { Get().InternalRemoveDesktop( desktoptoremove ); };
       static DesktopFeatures* GetCurrentDesktopPointer( void ) { return Get().InternalGetCurrentDesktopPointer(); };
       static void SetCurrentDesktop( unsigned int ndesk ) { Get().InternalSetCurrentDesktop( ndesk );  };
       static int GetCurrentDesktop( void ) { return Get().InternalGetCurrentDesktop(); };
       static void SetNextDesktop( void ) { Get().InternalSetNextDesktop();  };
       static void SetPreviousDesktop( void ) { Get().InternalSetPreviousDesktop(); };

       static void Initialize( void ) { Get().InternalInitialize(); };
       static void PrepareForRun( void ) { Get().InternalPrepareForRun( ); };
       static void Run( RunMode mode ) { Get().InternalRun( mode ); };
       static void Close (void ) { Get().InternalClose(); };

       static void Render( void ) { Get().InternalRender(); };
       static void RenderDepth( void ) { Get().InternalRenderDepth(); };

       static void PutOnTop( Widget *widgetsearched ) { Get().InternalPutOnTop( widgetsearched ); };

       static void Logic( void ) { Get().InternalLogic(); };
       static void LogicWithForcedRender( void ) { Get().InternalLogicWithForcedRender(); };

       static void SetUniformBackgroundColor( uint8_t r, uint8_t g, uint8_t b) { Get().InternalSetUniformBackgroundColor( r, g, b); };
       static void SetBackgroundPicture( std::string filename ) { Get().InternalSetBackgroundPicture( filename ); };
       static void SetDrawBackground( bool setter ) { Get().InternalSetDrawBackground( setter ); };

       static void InitThemeEngine( void ) { Get().InternalInitThemeEngine(); };
       static void SetDefaultTheme( void ) { Get().InternalSetDefaultTheme(); };
       static void LoadTheme( std::string filename ) { Get().InternalLoadTheme( filename ); };



private:

       WidgetApplication();

       static WidgetApplication m_application;

       unsigned int cur_desktop = 0;
       unsigned int nb_desktop = 1;
       std::vector< DesktopFeatures* > desktops;

       DesktopFeatures* currentdesktop;

       bool backgroundtobedrawn = true;

       bool AskForClose = false;

       bool InternalAskForClosure( void );

       void InternalAddChild( Widget *root );
       void InternalRemoveChild( Widget *root );

       void InternalAddChildToDesktop( Widget *root, DesktopFeatures *desktop );

       void InternalAddDesktop( );
       void InternalRemoveDesktop( DesktopFeatures *desktoptoremove);
       DesktopFeatures* InternalGetCurrentDesktopPointer();
       void InternalSetCurrentDesktop( unsigned int ndesk );
       int InternalGetCurrentDesktop();
       void InternalSetNextDesktop();
       void InternalSetPreviousDesktop();

       void InternalInitialize( void );
       void InternalRun( RunMode mode );
       void InternalClose (void );
       void InternalPrepareForRun( void );

       void InternalRender( void );
       void InternalRenderDepth( void );

       void InternalPutOnTop( Widget *widgetsearched );

       void InternalLogic( void );
       void InternalLogicWithForcedRender( void );

       void InternalSetUniformBackgroundColor( uint8_t r, uint8_t g, uint8_t b);
       void InternalSetBackgroundPicture( std::string filename );
       void InternalSetDrawBackground( bool setter );

       void InternalInitThemeEngine();
       void InternalSetDefaultTheme();
       void InternalLoadTheme( std::string filename );
};

#endif // WIDGETAPPLICATION_H
