#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include "Widget.hpp"


class WindowWidget : public Widget
{
public:
    WindowWidget( );
    WindowWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~WindowWidget();

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual void Maximize( void );
    virtual void Minimize( void );
    virtual void Restore( void );

    virtual void SetMinimalDimensions( unsigned int widmin, unsigned int heimin);
    virtual void SetMenuBar( void );
    virtual void SetIconBar( void );
    virtual bool GetMenuBar( void );
    virtual bool GetIconBar( void );

    // These methods must be overriden cause window geometry is a bit different with the title bar
    virtual unsigned int GetUseableXPos( void ) override;
    virtual unsigned int GetUseableYPos( void ) override;
    virtual unsigned int GetUseableWidth( void ) override;
    virtual unsigned int GetUseableHeight( void ) override;

protected:
    //virtual bool cursoron(  void  ) override;
    bool is_developped = true;

    virtual bool IsMouseAtLeftBorder( void );
    virtual bool IsMouseAtRightBorder( void );
    virtual bool IsMouseAtTopBorder( void );
    virtual bool IsMouseAtBottomBorder( void );
    virtual bool IsMouseOnTitleBar( void );
    virtual bool IsMouseOnMaximiseButton( void );
    virtual bool IsMouseOnMinimiseButton( void );
    virtual bool IsMouseOnRestoreButton( void );

    bool hasmenubar=false;
    bool hasiconbar=false;

    int clickX = 0;
    int clickY = 0;

    bool resizemode = false;
    bool movemode = false;
    bool startmove = false;

    bool isminimized = false;
    bool ismaximized = false;

    unsigned int xposback = 0;
    unsigned int yposback = 0;
    unsigned int widthback = 0;
    unsigned int heightback = 0;

    unsigned int minwidth;
    unsigned int minheight;

};

#endif // WINDOWWIDGET_H
