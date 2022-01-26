#include "GraphicContextWidget.hpp"

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

GraphicContextWidget::GraphicContextWidget() : Widget()
{
    widgettype = "GraphicContext";
    widthuseableGC = width;
    heightuseableGC = height;
    posviewX = 0;
    posviewY = 0;
    shiftposX = 0;
    shiftposY = 0;
    zoomx = 1.0f;
    zoomy = 1.0f;
    SetMode( GraphicContextWidget::Normal );
}


GraphicContextWidget::GraphicContextWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "GraphicContext";
    widthuseableGC = width;
    heightuseableGC = height;
    posviewX = 0;
    posviewY = 0;
    shiftposX = 0;
    shiftposY = 0;
    zoomx = 1.0f;
    zoomy = 1.0f;
    SetMode( GraphicContextWidget::Normal );
}


GraphicContextWidget::~GraphicContextWidget()
{
    surfacetobedrawn = nullptr;
    SDL_FreeSurface( transformedimage );
    transformedimage = nullptr;
}


void GraphicContextWidget::AssignSurface( SDL_Surface *surface )
{
    surfacetobedrawn = surface;
    //setuserzoomlevel( 1.0f );
    SetMode( GraphicContextWidget::Normal );
    Update();
}


SDL_Surface *GraphicContextWidget::CreateEmptyImage( unsigned int width, unsigned int height )
{
    SDL_Surface* surf = SDL_CreateRGBSurface(0, width, height, 16, 0, 0, 0, 0 );
    SDL_FillRect( surf, 0, 0x0000);
    SDL_Flip(surf);
    return surf;
}


SDL_Surface *GraphicContextWidget::CreateEmptyImageColor( unsigned int width, unsigned int height, unsigned short R, unsigned short G, unsigned short B, unsigned short A  )
{
    SDL_Surface* surf = SDL_CreateRGBSurface(0, width, height, 16, 0, 0, 0, 0 );
    SDL_FillRect( surf, 0, SDL_MapRGBA( surf->format, R, G, B, A));
    SDL_Flip(surf);
    return surf;
}


void GraphicContextWidget::SetMode( DrawMode mode )
{
    if (mode == GraphicContextWidget::Normal)
    {
        zoomx = 1.0;
        zoomy = 1.0;
        userzoomfactor = 1.0;
    }
    else if (mode == GraphicContextWidget::FitX)
    {
        if (surfacetobedrawn)
        {
            zoomx = (double) ((double) width / (double) surfacetobedrawn->w);
            userzoomfactor= zoomx;
            zoomy = zoomx;
        }
    }
    else if (mode == GraphicContextWidget::FitY)
    {
        if (surfacetobedrawn)
        {
            zoomy = (double) ((double) height / (double) surfacetobedrawn->h);
            userzoomfactor = zoomy;
            zoomx = zoomy;
        }
    }
    else if (mode == GraphicContextWidget::FitBest)
    {
        if (surfacetobedrawn)
        {
            zoomx = (double) ((double) width / (double) surfacetobedrawn->w);
            zoomy = (double) ((double) height / (double) surfacetobedrawn->h);
            double zoomtobeused = std::min(zoomx, zoomy);
            userzoomfactor = zoomtobeused;
            zoomx = zoomtobeused;
            zoomy = zoomtobeused;
        }
    }
    else if (mode == GraphicContextWidget::UserZoom)
    {
        zoomx = userzoomfactor;
        zoomy = userzoomfactor;
    }
    else
    {
        zoomx = 1.0;
        zoomy = 1.0;
        userzoomfactor = 1.0;
    }

    Update();
}


void GraphicContextWidget::SetUserZoomLevel( float level )
{
    userzoomfactor = level;
    SetMode( GraphicContextWidget::UserZoom );
    //update();
}


void GraphicContextWidget::Adjust( void )
{
    Update();
}


void GraphicContextWidget::Update( void )
{
    shiftposX = shiftposY = 0;

    if (transformedimage)
    {
        SDL_FreeSurface( transformedimage);
        transformedimage = rotozoomSurfaceXY( surfacetobedrawn, 0, zoomx, zoomy, 0);
    }
    else
    {
        transformedimage = rotozoomSurfaceXY( surfacetobedrawn, 0, zoomx, zoomy, 0);
    }

    if (transformedimage)
    {
        if ((unsigned int) transformedimage->w <= width )
        {
            shiftposX = (widthuseableGC - transformedimage->w) /2;
            posviewX = 0;
            escalatorH = false;
            scrollableX = false;
            heightuseableGC = height;
        }
        else
        {
            shiftposX = 0;
            posviewX = 0;
            escalatorH = true;
            scrollableX = true;
            heightuseableGC = height - 15;
        }


        if ((unsigned int) transformedimage->h <= height )
        {
            shiftposY = (heightuseableGC - transformedimage->h) /2;
            posviewY = 0;
            escalatorV = false;
            scrollableY = false;
            widthuseableGC = width;
        }
        else
        {
            shiftposY = 0;
            posviewY = 0;
            escalatorV = true;
            scrollableY = true;
            widthuseableGC = width - 15;
        }
    }
}


void GraphicContextWidget::Logic(  )
{
    if (is_enabled && is_visible)
    {
        is_hovering = CursorOn(  );
        bool currently_pressed = (MouseManager::GetB() || KeyManager::kbSCRATCH() ) && is_hovering;

        if(currently_pressed)
        {
            if (clickfunction) clickfunction( (char*) "test" );
        }
        else if(is_hovering)
        {
            if (hoverfunction) hoverfunction( (char*) "test" );
        }

        if (currently_pressed &&!has_focus)
            Focus( this );

        // if the picture to be displayed is smaller than the size of the widget, we need to compute the centered position
        if (transformedimage)
        {
            if ((unsigned int) transformedimage->w <= width )
            {
                shiftposX = (widthuseableGC - transformedimage->w) /2;
                posviewX = 0;
                escalatorH = false;
                scrollableX = false;
                heightuseableGC = height;
            }
            else
            {
                shiftposX=0;
                escalatorH = true;
                scrollableX = true;
                heightuseableGC = height - 15;
            }

            if ((unsigned int) transformedimage->h <= height )
            {
                shiftposY = (heightuseableGC - transformedimage->h) /2;
                posviewY = 0;
                escalatorV = false;
                scrollableY = false;
                widthuseableGC = width;
            }
            else
            {
                shiftposY=0;
                escalatorV = true;
                scrollableY = true;
                widthuseableGC = width - 15;
            }

            if (!has_focus)
                return;

            if (KeyManager::kbPLUS() && (userzoomfactor <= 5.0f))
            {
                userzoomfactor += 0.1f;
                zoomx += 0.1f;
                zoomy += 0.1f;
                Update();
            }

            if (KeyManager::kbMINUS() && (userzoomfactor >= 0.1f))
            {
                userzoomfactor -= 0.1f;
                zoomx -= 0.1f;
                zoomy -= 0.1f;
                Update();
            }



            if (scrollableX && MouseManager::kbLEFT())
            {
                if (posviewX > 5) posviewX -= 5;
                else posviewX = 0;
            }

            if (scrollableX && MouseManager::kbRIGHT())
            {
                if (posviewX < transformedimage->w - widthuseableGC - 5) posviewX += 5;
                else posviewX = transformedimage->w - widthuseableGC;
            }

            if (scrollableY && MouseManager::kbUP())
            {
                if (posviewY > 5) posviewY -= 5;
                else posviewY = 0;
            }

            if (scrollableY && MouseManager::kbDOWN())
            {
                if (posviewY < transformedimage->h - heightuseableGC - 5) posviewY += 5;
                else posviewY = transformedimage->h - heightuseableGC;
            }


            if (posviewX<=0) posviewX=0;

            if (posviewY<=0) posviewY=0;

            if (posviewX>transformedimage->w-widthuseableGC)    posviewX=transformedimage->w-widthuseableGC;

            if (posviewY>transformedimage->h-heightuseableGC)    posviewY=transformedimage->w-heightuseableGC;

        }

        for (auto& c : children) c->Logic(  );
    }
}



void GraphicContextWidget::Render(  )
{
    if (is_visible)
    {
        if (is_enabled)  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE AND ENABLED
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

            if (!is_hovering)
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );

                if (transformedimage)
                {
                    Rect src_rect, screen_pos;

                    src_rect.x = posviewX;
                    src_rect.y = posviewY;

                    src_rect.w = widthuseableGC;
                    src_rect.h = heightuseableGC;

                    if (escalatorV)
                    {
                        ScreenRenderer::DrawRoundedRectangle( xpos+width-12, ypos+4, xpos+width-4, ypos+height-12, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                        ScreenRenderer::DrawRoundedRectangle( xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );

                        unsigned int y = ((height-7-15)*posviewY / (transformedimage->h - heightuseableGC));

                        ScreenRenderer::DrawFilledCircle( xpos+width-8, ypos+7+y, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                    }

                    if (escalatorH)
                    {
                        ScreenRenderer::DrawRoundedRectangle( xpos+4, ypos+height-12, xpos+width-12, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                        ScreenRenderer::DrawRoundedRectangle( xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );

                        unsigned int x = ((width-7-15)*posviewX / (transformedimage->w - widthuseableGC));

                        ScreenRenderer::DrawFilledCircle( xpos+7+x, ypos+height-8, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                    }

                    screen_pos.x = xpos+shiftposX;
                    screen_pos.y = ypos+shiftposY;

                    ScreenRenderer::DrawImage( transformedimage, src_rect, screen_pos);
                }
            }
            else
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );


                // TO BE UPDATED WITH THE RIGHT COLORS
                if (transformedimage)
                {
                    Rect src_rect, screen_pos;

                    src_rect.x = posviewX;
                    src_rect.y = posviewY;

                    src_rect.w = widthuseableGC;
                    src_rect.h = heightuseableGC;

                    if (escalatorV)
                    {
                        ScreenRenderer::DrawRoundedRectangle( xpos+width-12, ypos+4, xpos+width-4, ypos+height-12, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                        ScreenRenderer::DrawRoundedRectangle( xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );

                        unsigned int y = ((height-7-15)*posviewY / (transformedimage->h - heightuseableGC));

                        ScreenRenderer::DrawFilledCircle( xpos+width-8, ypos+7+y, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                    }

                    if (escalatorH)
                    {
                        ScreenRenderer::DrawRoundedRectangle( xpos+4, ypos+height-12, xpos+width-12, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                        ScreenRenderer::DrawRoundedRectangle( xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );

                        unsigned int x = ((width-7-15)*posviewX / (transformedimage->w - widthuseableGC));

                        ScreenRenderer::DrawFilledCircle( xpos+7+x, ypos+height-8, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                    }

                    screen_pos.x = xpos+shiftposX;
                    screen_pos.y = ypos+shiftposY;

                    ScreenRenderer::DrawImage( transformedimage, src_rect, screen_pos);

                }

            }
        }
        else  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE BUT DISABLED
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

            ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

            // TO BE UPDATED WITH THE RIGHT COLORS
            if (transformedimage)
            {
                Rect src_rect, screen_pos;

                src_rect.x = posviewX;
                src_rect.y = posviewY;

                src_rect.w = widthuseableGC;
                src_rect.h = heightuseableGC;

                if (escalatorV)
                {
                    ScreenRenderer::DrawRoundedRectangle( xpos+width-12, ypos+4, xpos+width-4, ypos+height-12, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                    ScreenRenderer::DrawRoundedRectangle( xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );


                    unsigned int y = ((height-7-15)*posviewY / (transformedimage->h - heightuseableGC));

                    ScreenRenderer::DrawFilledCircle( xpos+width-8, ypos+7+y, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                }

                if (escalatorH)
                {
                    ScreenRenderer::DrawRoundedRectangle( xpos+4, ypos+height-12, xpos+width-12, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                    ScreenRenderer::DrawRoundedRectangle( xpos+width-12, ypos+height-12, xpos+width-4, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );


                    unsigned int x = ((width-7-15)*posviewX / (transformedimage->w - widthuseableGC));

                    ScreenRenderer::DrawFilledCircle( xpos+7+x, ypos+height-8, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                }

                screen_pos.x = xpos+shiftposX;
                screen_pos.y = ypos+shiftposY;

                ScreenRenderer::DrawImage( transformedimage, src_rect, screen_pos);

            }

        }

        for (auto& c : children) c->Render( );
    }
}
