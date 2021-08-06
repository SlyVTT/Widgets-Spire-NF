#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include "Widget.hpp"
#include <string>


class InputWidget : public Widget
{
public:
    InputWidget();
    InputWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~InputWidget();

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual std::string GetContent();
    virtual void SetContent(std::string str);

private:
    void UpdateScroll();

    std::string text = "";

    unsigned int cursor_pos = 0;
    unsigned int scroll = 0;
    unsigned int mousex,mousey;
    bool mouses;

    bool key_hold_down = false;
};

#endif // INPUTWIDGET_H
