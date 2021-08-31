#include "DesktopWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Renderers/DepthBufferRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"

#include <vector>


DesktopWidget::DesktopWidget()
{
    widgettype = "Desktop";
};


DesktopWidget::DesktopWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "Desktop";
};


DesktopWidget::~DesktopWidget()
{

};


void DesktopWidget::SetMenuBar()
{
    hasmenubar = true;
};


void DesktopWidget::SetIconBar()
{
    hasiconbar = true;
};


bool DesktopWidget::GetMenuBar()
{
    return hasmenubar;
};


bool DesktopWidget::GetIconBar()
{
    return hasiconbar;
};


unsigned int DesktopWidget::GetUseableXPos()
{
    return 0;
}


unsigned int DesktopWidget::GetUseableYPos()
{
    if (!hasmenubar && !hasiconbar) return 0;                    // we just remove 2px on top
    if (hasmenubar && !hasiconbar) return 0 + 12;           // we remove the 2px on top and of the menu bar (2px + 12px)
    if (hasmenubar && hasiconbar) return 0 + 12 + 20;       // we remove the 2px on top, of the menu bar and of the icon bar (2px + 12px + 20px)
    if (!hasmenubar && hasiconbar) return 0 + 20;           // we remove the 2px on top, of the menu bar and of the icon bar (2px + 12px + 20px)

    // the following return is to avoir warning, all possible cases are given above
    return 0;

}


unsigned int DesktopWidget::GetUseableWidth()
{
    return width - 0;
}


unsigned int DesktopWidget::GetUseableHeight()
{
    if (!hasmenubar && !hasiconbar) return SCREEN_HEIGHT_GUI - 0;                     // we just remove 2px on top and bottom (2px + 2px = 4px)
    if (hasmenubar && !hasiconbar) return SCREEN_HEIGHT_GUI - 0 - 12;            // we remove 2px on top and bottom and of the menu bar (4px + 12px)
    if (hasmenubar && hasiconbar) return SCREEN_HEIGHT_GUI - 0 - 12 - 20;        // we remove 2px on top and bottom, of the menu bar and of the icon bar (4px + 12px + 20px)
    if (!hasmenubar && hasiconbar) return SCREEN_HEIGHT_GUI - 0 - 20;            // we remove 2px on top and bottom, of the menu bar and of the icon bar (4px + 12px + 20px)

    // the following return is to avoir warning, all possible cases are given above
    return 0;
}



void DesktopWidget::Logic( void )
{
    unsigned int nbpopupvisible = 0;
    for (auto& d : popupchildren )
        if (d->IsVisible())
        {
            nbpopupvisible++;
            d->Logic(  );
        }


    if (nbpopupvisible==0)
    {
        if ( MouseManager::GetB() || KeyManager::kbSCRATCH() )
        {

            uint8_t r,g,b;
            uint8_t x, y;

            //SDL_LockSurface( depthbuffer);
            //SDL_GetRGB(getpixel(depthbuffer, mouse->x, mouse->y), depthbuffer->format, &r, &g, &b);
            //SDL_UnlockSurface( depthbuffer );

            x = MouseManager::GetX();
            y = MouseManager::GetY();


            r = DepthBufferRenderer::GetPixelR( x, y );
            g = DepthBufferRenderer::GetPixelG( x, y );
            b = DepthBufferRenderer::GetPixelB( x, y );

            unsigned int c = lround(((double) r )/25.0);
            unsigned int d = lround(((double) g )/25.0);
            unsigned int u = lround(((double) b )/25.0);

            unsigned int widgetIDpicked = 100*c + 10*d + u;

            /*
            //-------------
                    // THIS IS FOR DEBUGGING THE DEPTH BUFFER PORTION OF THE CODE

                    char tempID[100];
                    sprintf( tempID, "ID=%d / Color=%d / RGB=%d-%d-%d / c=%d / d=%d / u=%d", widgetIDpicked, DepthBufferRenderer::GetPixel( x, y ), r, g, b, c, d, u );
                    FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
                    unsigned int length=FontEngine::GetStringWidth( tempID );
                    ScreenRenderer::DrawFilledRectangle( x, y , x+length, y+10, 0, 0, 0, 255 );
                    FontEngine::DrawStringLeft( tempID, x, y, 0, 255, 0, 255 );

                    ScreenRenderer::FlipScreen();
           //---------

            //PutOnTop( 1 );
            */

            PutOnTop( widgetIDpicked );
        }

        for (auto& c : children )
            c->Logic( );

    }

    // PUT ON TOP TO START WITH POPUCHILD LOGIC
    //for (auto& d : popupchildren )
    //       d->logic( mouse, keyboard );
}


void DesktopWidget::Render(  )
{
    for (auto& c : children )
        c->Render(  );

    for (auto& d : popupchildren )
        d->Render(  );
}


void DesktopWidget::PutOnTop( unsigned int widgetidsearched )
{
    // we desactivate all the children

    std::list<Widget *>::iterator it=children.begin();

    for( auto& c : children )
    {

        if ((c->WidgetID==widgetidsearched) && (!c->IsLocked()))
        {
            /*
                        boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
                        fonttemp->drawstringleft( screen, (char*) "Found children", 6, 231, 0, 0, 255, 255 );
                        SDL_Flip(screen);
            */
            c->Activate();
            Widget* temp = c;

            children.erase( it );

            children.push_back( temp );
            return;

        }
        else if ((c->WidgetID==widgetidsearched) && (c->IsLocked()))
        {
            /*
                        boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
                        fonttemp->drawstringleft( screen, (char*) "Found lock", 6, 231, 0, 0, 255, 255 );
                        SDL_Flip(screen);
            */
            c->Desactivate();
        }
        else
        {
            /*
                        boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
                        fonttemp->drawstringleft( screen, (char*) "Not found children", 6, 231, 0, 0, 255, 255 );
                        SDL_Flip(screen);
            */
            c->Desactivate();
        }

        it++;
    }
}


void DesktopWidget::PutOnTop( Widget *widgetsearched )
{
    // we desactivate all the children

    std::list<Widget *>::iterator it=children.begin();

    for( auto& c : children )
    {

        if ((c==widgetsearched) && (!c->IsLocked()))
        {
            /*
                        boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
                        fonttemp->drawstringleft( screen, (char*) "Found children", 6, 231, 0, 0, 255, 255 );
                        SDL_Flip(screen);
            */
            c->Activate();
            Widget* temp = c;

            children.erase( it );

            children.push_back( temp );
            return;

        }
        else if ((c==widgetsearched) && (c->IsLocked()))
        {
            /*
                        boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
                        fonttemp->drawstringleft( screen, (char*) "Found lock", 6, 231, 0, 0, 255, 255 );
                        SDL_Flip(screen);
            */
            c->Desactivate();
        }
        else
        {
            /*
                        boxRGBA( screen, 5, 230, 150, 240, 0, 0, 0, 255 );
                        fonttemp->drawstringleft( screen, (char*) "Not found children", 6, 231, 0, 0, 255, 255 );
                        SDL_Flip(screen);
            */
            c->Desactivate();
        }

        it++;
    }
}
