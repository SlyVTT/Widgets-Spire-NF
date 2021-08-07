#ifndef LISTBOXWIDGET_H
#define LISTBOXWIDGET_H

#include "Widget.hpp"
#include <vector>
#include <string>


class ListBoxWidget : public Widget
{
public:
    ListBoxWidget();
    ListBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~ListBoxWidget();

    virtual void Flush( void );
    virtual bool IsPressed( void );

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual void AddItem( std::string item );
    virtual unsigned int GetNbItem( void );
    virtual std::string GetItem( int itemnumber );
    virtual int GetSelected( void );
    virtual std::string GetSelectedItem( void );

    bool validated = false;
    bool escaped = false;

protected:

    unsigned int nbitem = 0;
    std::vector<std::string> listitems;
    unsigned int selected = 0;


private:
    unsigned int scroll = 0;
    unsigned int nbvisible = 0;
    unsigned int heightline = 0;
    bool is_pressed = false;
};

#endif // LISTBOXWIDGET_H
