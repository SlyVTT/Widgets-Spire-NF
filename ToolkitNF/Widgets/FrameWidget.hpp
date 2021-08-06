#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include "Widget.hpp"


class FrameWidget : public Widget
{
public:

    FrameWidget();
    FrameWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    ~FrameWidget();


    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    // These methods must be override cause frame geometry is a bit different with the title bar
    virtual unsigned int GetUseableXPos() override;
    virtual unsigned int GetUseableYPos() override;
    virtual unsigned int GetUseableWidth() override;
    virtual unsigned int GetUseableHeight() override;

protected:
    bool is_pressed = false;

private:
};

#endif // FRAMEWIDGET_H
