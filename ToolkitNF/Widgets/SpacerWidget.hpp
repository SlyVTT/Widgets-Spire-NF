#ifndef SPACERWIDGET_H
#define SPACERWIDGET_H

#include "Widget.hpp"


class SpacerWidget : public Widget
{
public:
    SpacerWidget();
    SpacerWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~SpacerWidget();

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

protected:

private:
};

#endif // SPACERWIDGET_H
