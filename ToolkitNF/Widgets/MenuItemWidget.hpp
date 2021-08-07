#ifndef MENUITEMWIDGET_H
#define MENUITEMWIDGET_H

#include "MiniButtonWidget.hpp"


class MenuItemWidget : public MiniButtonWidget
{
public:

    MenuItemWidget();
    MenuItemWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~MenuItemWidget();

    virtual bool IsPressed( void );

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual unsigned int GetFullTextWidth();
    virtual void Drop( void );
    virtual void Undrop( void );

protected:

private:
    std::string labelarrow;
    bool is_pressed = false;
    bool is_dropped = false;
    bool has_child_menu_open = false;
    unsigned int width_full_text = 0;
};

#endif // MENUITEMWIDGET_H
