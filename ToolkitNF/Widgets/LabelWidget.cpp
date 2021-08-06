#include "LabelWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


LabelWidget::LabelWidget()
{
    widgettype = "Label";
    //strcpy( widgettype, (char*) "Label");
};

LabelWidget::LabelWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "Label";
    //strcpy( widgettype, (char*) "Label");
};

LabelWidget::~LabelWidget()
{

};

void LabelWidget::SetAlignment( LabelWidget::AlignType type )
{
    alignment = type;
};


LabelWidget::AlignType LabelWidget::GetAlignement()
{
    return alignment;
};

void LabelWidget::Logic( void )
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


void LabelWidget::Render( void )
{
    if (is_visible)
    {

        if (is_enabled)
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
            drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

            if (drawablecharlabel!=0)
            {
                drawablelabel =  FontEngine::ReduceStringToVisible( label, width-2 -2  );

                int sl =  FontEngine::GetStringWidth( drawablelabel );
                int sh =  FontEngine::GetStringHeight( drawablelabel );

                if (alignment==Centered)  FontEngine::DrawStringLeft(  drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );

                if (alignment==Left)  FontEngine::DrawStringLeft(  drawablelabel, xpos, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );

                if (alignment==Right)  FontEngine::DrawStringLeft(  drawablelabel, xpos+(width-sl), ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
            }

        }
        else
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
            drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

            if (drawablecharlabel!=0)
            {
                drawablelabel =  FontEngine::ReduceStringToVisible( label, width-2 -2  );

                int sl =  FontEngine::GetStringWidth( drawablelabel );
                int sh =  FontEngine::GetStringHeight( drawablelabel );

                if (alignment==Centered)  FontEngine::DrawStringLeft(  drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );

                if (alignment==Left)  FontEngine::DrawStringLeft(  drawablelabel, xpos, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );

                if (alignment==Right)  FontEngine::DrawStringLeft(  drawablelabel, xpos+(width-sl), ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
            }

        }

        for (auto& c : children )
            c->Render( );

    }
}
