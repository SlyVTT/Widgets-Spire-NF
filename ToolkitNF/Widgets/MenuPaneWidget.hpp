#ifndef MENUPANEWIDGET_H
#define MENUPANEWIDGET_H

#include "ContainerVWidget.hpp"


class MenuPaneWidget : public ContainerVWidget
{
public:
    MenuPaneWidget();
    MenuPaneWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~MenuPaneWidget();

    virtual void Adjust( void ) override;

    virtual void Logic( void ) override;

    virtual void Render( void ) override;

    virtual void Drop( void );
    virtual void Undrop( void );
    virtual void SetChildDropped( void );
    virtual void UnsetChildDropped( void );


protected:

private:
    bool is_dropped = false;
    bool has_child_menu_open = false;
};

#endif // MENUPANEWIDGET_H
