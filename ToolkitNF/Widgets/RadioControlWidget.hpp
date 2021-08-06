#ifndef RADIOCONTROLWIDGET_H
#define RADIOCONTROLWIDGET_H

#include "ButtonWidget.hpp"


class RadioControlWidget : public ButtonWidget
{
public:
    RadioControlWidget();
    RadioControlWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~RadioControlWidget();

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual void Invert();
    virtual bool IsTicked( void );

protected:

private:

    bool is_ticked = false;

    bool mouse_hold_down = false;

};

#endif // RADIOCONTROLWIDGET_H
