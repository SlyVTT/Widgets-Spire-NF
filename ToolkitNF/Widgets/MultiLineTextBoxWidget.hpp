#ifndef MULTILINETEXTBOXWIDGET_H
#define MULTILINETEXTBOXWIDGET_H

#include "Widget.hpp"

#include <string>
#include <vector>


class MultiLineTextBoxWidget : public Widget
{
public:
    MultiLineTextBoxWidget();
    MultiLineTextBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~MultiLineTextBoxWidget();

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual void LoadContentFromFile( std::string filename );
    virtual void SaveContentToFile( std::string filename );
    virtual void Flush();

    virtual void CopySelection();
    virtual void CutSelection();
    virtual void PasteSelection();
    virtual void EraseSelection();

    virtual void SetNonEditable();
    virtual void SetEditable();

    virtual std::string GetContent();
    virtual void SetContent( std::string str );

    virtual void AppendContent(std::string str);

protected:


private:
    void UpdateScroll();

    std::vector<std::string> content;

    unsigned int selectstart;
    unsigned int selectend;
    std::string selection;
    bool isselected;

    bool iseditable = true;

    unsigned int nblinetotal = 0;
    unsigned int firstlinevisible = 0;
    unsigned int currentline = 0;

    unsigned int currentlinecursor = 0;

    unsigned int nblinevisible = 0;
    unsigned int nbcharvisibleperline = 0;

    unsigned int cursor_posX = 0;

    unsigned int scrollX = 0;

    unsigned int mousex,mousey;
    bool mouses;

    bool key_hold_down = false;
};

#endif // MULTILINETEXTBOXWIDGET_H
