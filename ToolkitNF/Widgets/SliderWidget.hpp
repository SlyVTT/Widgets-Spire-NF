#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include "Widget.hpp"


class SliderWidget : public Widget
{
public:
    SliderWidget();
    SliderWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    ~SliderWidget();

    int GetValueInt();
    float GetValueFloat();
    void SetRangeInt( int minvalue, int maxvalue);
    void SetRangeFloat( float minvalue, float maxvalue );

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

protected:
    bool is_pressed = false;
    int length_pixels = 0;
    int position_cursor_pixels = 0;

    int intmin=0;
    int intmax=100;

    float floatmin=0.0;
    float floatmax=1.0;

};

#endif // SLIDERWIDGET_H
