#ifndef DIALOGBOXWIDGET_H
#define DIALOGBOXWIDGET_H

#include "WindowWidget.hpp"


class DialogBoxWidget : public WindowWidget
{
public:
    DialogBoxWidget();
    DialogBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~DialogBoxWidget();

    virtual void Logic( void ) override;
    virtual void Render( void ) override;


    // These methods must be override cause window geometry is a bit different with the title bar
    virtual unsigned int GetUseableXPos( void ) override;
    virtual unsigned int GetUseableYPos( void ) override;
    virtual unsigned int GetUseableWidth( void ) override;
    virtual unsigned int GetUseableHeight( void ) override;

protected:
    bool IsMouseOnTitleBar( void ) override;

private:
};

#endif // DIALOGBOXWIDGET_H
