#include "MiniButtonWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


MiniButtonWidget::MiniButtonWidget()
{
    widgettype = "MiniButton";
    //strcpy( widgettype, (char*) "MiniButton");
};

MiniButtonWidget::MiniButtonWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
{
    widgettype =  "MiniButton";
    //strcpy( widgettype, (char*) "MiniButton");
};

MiniButtonWidget::~MiniButtonWidget()
{

};


void MiniButtonWidget::SetType( TypeSymbol type )
{
    switch(type)
    {
    case Bottom_Arrow:
        label = "\u001f";
        //label = (char*) "\u001f";
        break;
    case Up_Arrow:
        label = "\u001e";
        //label = (char*) "\u001e";
        break;
    case Left_Arrow:
        label = "\u0011";
        //label = (char*) "\u0011";
        break;
    case Right_Arrow:
        label = "\u0010";
        //label = (char*) "\u0010";
        break;
    case Close_Symbol:
        label = "\u0009";
        //label = (char*) "\u0009";
        break;
    case Question_Symbol:
        label = "\u003f";
        //label = (char*) "\u003f";
        break;
    case Exclamation_Symbol:
        label = "\u0021";
        //label = (char*) "\u0021";
        break;
    }
}

bool MiniButtonWidget::IsTicked( void )
{
    return is_ticked;
};

void MiniButtonWidget::Invert( void )
{
    is_ticked = !is_ticked;
};


bool MiniButtonWidget::IsPressed()
{
    return is_pressed;
}

void MiniButtonWidget::Logic( void )
{
    if (is_enabled && is_visible)
    {
        is_hovering = CursorOn(  );
        bool currently_pressed = (MouseManager::GetB() || KeyManager::kbSCRATCH() ) && is_hovering;

        if(mouse_hold_down)
        {
            mouse_hold_down = currently_pressed;
        }
        else if (currently_pressed && !is_ticked )
        {
            Invert();

            if (clickfunction)
                clickfunction( (char*) "test" );

            mouse_hold_down = true;
        }
        else if (currently_pressed && is_ticked )
        {
            Invert();

            if (releasefunction)
                releasefunction( (char*) "test" );

            mouse_hold_down = true;
        }
        else if (is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        for (auto& c : children )
            c->Logic(  );
    }

}


void MiniButtonWidget::Render( void )
{
    if (is_visible)
    {

        if (is_enabled)
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

            if (!is_hovering)
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
            }
            else if (is_pressed)
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Hasfocus) );
            }
            else
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
            }

            // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
            drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

            if (drawablecharlabel!=0)
            {
                drawablelabel =  FontEngine::ReduceStringToVisible( label, width-2 -2  );

                int sl =  FontEngine::GetStringWidth( drawablelabel );
                int sh =  FontEngine::GetStringHeight( drawablelabel );

                 FontEngine::DrawStringLeft( drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
            }
        }
        else
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

            ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

            // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );
            drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

            if (drawablecharlabel!=0)
            {
                drawablelabel =  FontEngine::ReduceStringToVisible( label, width-2 -2  );

                int sl =  FontEngine::GetStringWidth( drawablelabel );
                int sh =  FontEngine::GetStringHeight( drawablelabel );

                 FontEngine::DrawStringLeft( drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
            }
        }

        for (auto& c : children) c->Render( );

    }
}
