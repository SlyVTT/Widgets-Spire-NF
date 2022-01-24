#ifndef GRAPHICCONTEXTWIDGET_H
#define GRAPHICCONTEXTWIDGET_H

#include "Widget.hpp"
#include "SDL/SDL.h"


class GraphicContextWidget : public Widget
{
public:
    GraphicContextWidget();
    GraphicContextWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~GraphicContextWidget();

    virtual void Logic(  ) override;
    virtual void Render(  ) override;

    SDL_Surface *CreateEmptyImage( unsigned int width, unsigned int height );
    SDL_Surface *CreateEmptyImageColor( unsigned int width, unsigned int height, unsigned short R, unsigned short G, unsigned short B, unsigned short A  );

    enum DrawMode
    {
        Normal = 0,              // zoomx = zoomy = 1
        FitX = 1,                     // zoomx is based on image width and widget width and applied to Y
        FitY = 2,                     // zoomy is based on image height and widget height and applied to X
        FitBest = 3,                // both zoomx and zoomy are calculated and then min (fitX, fitY)
        UserZoom = 4           // user defined zoom is applied to X and Y
    };

    virtual void AssignSurface( SDL_Surface *surface );
    virtual void SetMode( DrawMode mode );

    void SetUserZoomLevel( float level );
    void Update( void );

    void Adjust() override;

protected:
    SDL_Surface *surfacetobedrawn = nullptr;
    SDL_Surface *transformedimage = nullptr;

    DrawMode currentmode = Normal;

    unsigned int posviewX = 0;
    unsigned int posviewY = 0;

    unsigned int shiftposX = 0;
    unsigned int shiftposY = 0;

    unsigned int widthuseableGC = 0;            // this correspond to the actual width of the widget that can be used (equals width but can be reduce by 15pixels if escalators are drawn)
    unsigned int heightuseableGC = 0;         // this correspond to the actual height of the widget that can be used (equals height but can be reduce by 15pixels if escalators are drawn)

    bool escalatorH = false;
    bool escalatorV = false;

    bool scrollableX = false;
    bool scrollableY = false;

    double zoomx = 1.0f;
    double zoomy = 1.0f;

    double userzoomfactor = 1.0f;

private:


};

#endif // GRAPHICCONTEXTWIDGET_H
