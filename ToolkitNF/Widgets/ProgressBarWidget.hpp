#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include "Widget.hpp"



class ProgressBarWidget : public Widget
{
public:
    ProgressBarWidget();
    ProgressBarWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    ~ProgressBarWidget();


    enum BarStyle
    {
        Continuous = 0,
        Bricks = 1,
        Rainbow = 2,
        RainbowBrick = 3
    };


    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual void SetCurrentPercentage( float percent );
    virtual float GetCurrentPercentage( );

    virtual void SetStyle( BarStyle st );
    virtual void SetNumberBricks( int nb );
    virtual void SetPrintValue( bool setter );


protected:
    float percentfilled = 0.0;
    BarStyle style = Continuous;
    int nbbricks = 10;
    bool drawvalue = false;


private:
};

#endif // PROGRESSBARWIDGET_H
