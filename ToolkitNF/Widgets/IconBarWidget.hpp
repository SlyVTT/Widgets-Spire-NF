#ifndef ICONBARWIDGET_H
#define ICONBARWIDGET_H

#include "ContainerHWidget.hpp"


class IconBarWidget : public ContainerHWidget
{
public:
    IconBarWidget();
    IconBarWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    ~IconBarWidget();

    virtual void Adjust( void ) override;

    virtual void Logic( void ) override;

    virtual void Render( void ) override;

protected:

private:
};

#endif // ICONBARWIDGET_H
