#ifndef LABELWIDGET_H
#define LABELWIDGET_H

#include "Widget.hpp"





class LabelWidget : public Widget
{
public:
    LabelWidget();
    LabelWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~LabelWidget();

    enum AlignType
    {
        Centered = 0,
        Left = 1,
        Right = 2
    };

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual void SetAlignment( AlignType type );

    virtual AlignType GetAlignement();

protected:
    bool is_pressed = false;
    AlignType alignment = Centered;

private:
};

#endif // LABELWIDGET_H
