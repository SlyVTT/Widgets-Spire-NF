#include "ButtonWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


ButtonWidget::ButtonWidget()
{
    widgettype = "Button";
};


ButtonWidget::ButtonWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "Button";
};


ButtonWidget::~ButtonWidget()
{

};


bool ButtonWidget::IsPressed()
{
    return is_pressed;
}


void ButtonWidget::Logic(  )
{
    if (is_enabled && is_visible)
    {
        is_hovering = CursorOn(  );
        bool currently_pressed = (MouseManager::GetB() || KeyManager::kbSCRATCH() ) && is_hovering;

        if(currently_pressed && !is_pressed)
        {
            if (clickfunction) clickfunction( (char*) "test" );
        }
        else if(!currently_pressed && is_pressed)
        {
            if (releasefunction) releasefunction( (char*) "test" );
        }
        else if(is_hovering)
        {
            if (hoverfunction) hoverfunction( (char*) "test" );
        }

        is_pressed = currently_pressed;

        for (auto& c : children) c->Logic( );
    }
}


void ButtonWidget::Render(  )
{
    if (is_visible)
    {
        if (is_enabled)  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE AND ENABLED
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

            if (!is_hovering)
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
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
                int sh =   FontEngine::GetStringHeight( drawablelabel );

                 FontEngine::DrawStringLeft( drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
            }
        }
        else  // CODE TO BE APPLIED WHEN THE WIDGET IS VISIBLE BUT DISABLED
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
