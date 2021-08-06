#ifndef MINIBUTTONWIDGET_H
#define MINIBUTTONWIDGET_H

#include "ButtonWidget.hpp"



class MiniButtonWidget : public ButtonWidget
{
public:
    MiniButtonWidget();
    MiniButtonWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~MiniButtonWidget();


    enum TypeSymbol
    {
        Bottom_Arrow = 0,
        Up_Arrow = 1,
        Left_Arrow = 2,
        Right_Arrow = 3,
        Close_Symbol = 4,
        Question_Symbol = 5,
        Exclamation_Symbol = 6
    };

    virtual bool IsPressed() override;
    virtual bool IsTicked( void );
    virtual void Invert( void );

    virtual void Logic( void ) override;
    virtual void Render( void ) override;

    virtual void SetType( TypeSymbol type );



protected:

private:

    friend class DropBoxWidget;

    bool is_ticked = false;
    bool mouse_hold_down = false;

};

#endif // MINIBUTTONWIDGET_H
