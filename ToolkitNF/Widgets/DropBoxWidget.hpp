#ifndef DROPBOXWIDGET_H
#define DROPBOXWIDGET_H

#include "Widget.hpp"
#include "ListBoxWidget.hpp"
#include "MiniButtonWidget.hpp"


class DropBoxWidget : public Widget
{
public:

    DropBoxWidget();
    DropBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~DropBoxWidget();


    virtual void Adjust( void ) override;

    virtual bool IsPressed( void );

    virtual void Drop( void );

    virtual void Undrop( void );

    virtual void Logic( void ) override;

    virtual void Render( void ) override;

    virtual void AddItem( std::string item );

    virtual int GetNbItem( void );

    virtual std::string GetItem( int itemnumber );

    virtual int GetSelected( void );

    virtual std::string GetSelectedItem( void );

    virtual void Validate( void );

    virtual void Escape( void );

    virtual bool IsUpdated( void );

protected:

    MiniButtonWidget *dropbutton;
    ListBoxWidget *listbox;

    int selected_item = -1;     // -1 means no selection have been made yet
    std::string selected_item_value;

private:

    bool is_pressed = false;
    bool is_dropped = false;
    bool has_been_updated = false;

};

#endif // DROPBOXWIDGET_H
