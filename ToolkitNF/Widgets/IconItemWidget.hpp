#ifndef ICONITEMWIDGET_H
#define ICONITEMWIDGET_H

#include "ButtonWidget.hpp"

#include "../Globals/GUIToolkitNFGlobals.hpp"
#include "../Globals/GlobalFunctions.hpp"


class IconItemWidget : public ButtonWidget
{
public:

    IconItemWidget();
    IconItemWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~IconItemWidget();

    void Disable( void ) override;
    void Enable(void ) override;

    virtual bool IsPressed() override;

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual void AssignIconEnable( std::string filename );
    virtual void AssignIconDisable( std::string filename );

protected:

    std::string iconnameenable;
    int iconenableset = -1;
    std::string iconnamedisable;
    int icondisableset = -1;


#if RENDER_WITH_SDL == 1
    SDL_Surface *icon = nullptr;
#else
    imagegc *icon = nullptr;
#endif


private:
    bool is_ticked = false;
    bool mouse_hold_down = false;
};

#endif // ICONITEMWIDGET_H
