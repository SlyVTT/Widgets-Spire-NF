#ifndef SPLASHSCREENWIDGET_H
#define SPLASHSCREENWIDGET_H

#include "Widget.hpp"

#include "../Globals/GUIToolkitNFGlobals.hpp"
#include "../Globals/GlobalFunctions.hpp"


class SplashScreenWidget : public Widget
{
public:
    SplashScreenWidget();
    SplashScreenWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~SplashScreenWidget();

    virtual void AssignImage( std::string filename );

    virtual void Logic( void );
    virtual void Render( void );

    virtual void SetDuration( uint32_t duration );    // duration in ms
    virtual void Start( void );

protected:

    uint32_t timerstart = 0;
    uint32_t currenttimer = 0;
    uint32_t durationsplash = 0;

private:

#if RENDER_WITH_SDL == 1
    SDL_Surface *image = nullptr;
#else
    imagegc* image = nullptr;
#endif // RENDER_WITH_SDL

    std::string filereference;
};

#endif // SPLASHSCREENWIDGET_H
