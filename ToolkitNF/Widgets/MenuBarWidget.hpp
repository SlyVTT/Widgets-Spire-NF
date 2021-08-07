#ifndef MENUBARWIDGET_H
#define MENUBARWIDGET_H

#include "ContainerHWidget.hpp"


class MenuBarWidget : public ContainerHWidget
{
public:
    MenuBarWidget();
    MenuBarWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    ~MenuBarWidget();

    virtual void  Adjust( void ) override;

    virtual unsigned int GetUseableHeight( void ) override;

    virtual void Logic( void ) override;

    virtual void Render( void ) override;


protected:

private:
    bool has_child_menu_open = false;
    int child_menu_opened = -1;
};

#endif // MENUBARWIDGET_H
