#ifndef WIDGET_H
#define WIDGET_H


#include <list>
#include <string>


class Widget
{
public:
    Widget( );
    Widget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~Widget();

    uint32_t WidgetID = -1;

    //virtual void DEBUG_draw_widget_tree_structure( int level, char* filename );

    virtual void Logic( void );

    virtual void Focus( Widget *emitter );
    virtual void UnfocusUp( Widget *emitter );
    virtual void UnfocusDown( Widget *emitter );

    virtual void Render( void );
    virtual void RenderDepth( void );

    virtual void AddChild( Widget *child );
    virtual void AddPopupChild( Widget *child );


    virtual Widget* GetClosestMainParent( void );
    virtual Widget* GetWidgetByID( uint32_t IDsearched );

    virtual void Activate();
    virtual void Desactivate();
    virtual bool IsActivated();

    virtual void Lock();
    virtual void Unlock();
    virtual bool IsLocked();

    //SETTERs
    virtual void SetDimensions( unsigned int mx, unsigned int my, unsigned int mw, unsigned int mh );
    virtual void SetXPos( unsigned int mx );
    virtual void SetYPos( unsigned int my );
    virtual void SetWidth( unsigned int mw );
    virtual void SetHeight( unsigned int mh );
    virtual void SetLabel(std::string l);
    virtual void SetContainerStatus( bool status );
    virtual void SetParent( Widget *p );
    virtual void SetVisible();
    virtual void SetInvisible();
    virtual void Enable();
    virtual void Disable();
    virtual void Adjust();

    //GETTERs
    virtual unsigned int GetXPos();
    virtual unsigned int GetYPos();
    virtual unsigned int GetWidth();
    virtual unsigned int GetHeight();

    virtual unsigned int GetUseableXPos();
    virtual unsigned int GetUseableYPos();
    virtual unsigned int GetUseableWidth();
    virtual unsigned int GetUseableHeight();

    virtual std::string GetLabel();
    virtual bool GetContainerStatus();
    virtual Widget* GetParent();
    virtual bool IsEnabled();
    virtual bool IsVisible();
    virtual std::string GetWidgetType();

    //ACTION Linker
    virtual void LinkOnClick( void(*func)(char*) );
    virtual void LinkOnRelease( void(*func)(char*) );
    virtual void LinkOnHover( void(*func)(char*) );


protected:
    bool has_focus = false;
    bool is_enabled = true;
    bool is_visible = true;
    bool is_activated = false;
    bool is_locked = false;

    std::string widgettype;

    std::string label;                // text content of the label
    std::string drawablelabel;    // text content that can be drawn (may be shorter that full label depending on size of the widget and on the used font
    unsigned int drawablecharlabel;

    unsigned int xpos; // absolute coordinate vs screen
    unsigned int xrel; // relative coodinate to parent

    unsigned int ypos; // absolute coordinate vs screen
    unsigned int yrel; // relative coodinate to parent

    unsigned int width;
    unsigned int widrel;

    unsigned int height;
    unsigned int heirel;

    bool is_container = false;
    bool is_hovering = false;

    Widget *parent = nullptr;
    int nbchildren;
    std::list< Widget* > children;
    std::list< Widget* > popupchildren;

    void(*clickfunction)(char*) = nullptr;
    void(*releasefunction)(char*) = nullptr;
    void(*hoverfunction)(char*) = nullptr;

    virtual bool CursorOn( void  );
};

#endif // WIDGET_H
