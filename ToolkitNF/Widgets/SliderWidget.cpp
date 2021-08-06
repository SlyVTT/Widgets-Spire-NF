#include "SliderWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


SliderWidget::SliderWidget()
{
    widgettype =  "Slider";
    //strcpy( widgettype, (char*) "Slider");
};

SliderWidget::SliderWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    length_pixels = w-8;
    widgettype =  "Slider";
    //strcpy( widgettype, (char*) "Slider");
};

SliderWidget::~SliderWidget()
{

};


void SliderWidget::SetRangeInt( int minvalue, int maxvalue)
{
    intmin = minvalue;
    intmax=maxvalue;
};


void SliderWidget::SetRangeFloat( float minvalue, float maxvalue )
{
    floatmin = minvalue;
    floatmax=maxvalue;
};


int SliderWidget::GetValueInt()
{
    int temp = (int) (intmin + (intmax-intmin)*position_cursor_pixels/length_pixels);
    return temp;
}


float SliderWidget::GetValueFloat()
{
    float temp = (float) (floatmin + (floatmax-floatmin)*position_cursor_pixels/length_pixels);
    return temp;
}



void SliderWidget::Logic( void )
{
    if (is_enabled && is_visible)
    {

        is_hovering = CursorOn(  );
        bool currently_pressed = (MouseManager::GetB() || KeyManager::kbSCRATCH() ) && is_hovering;

        length_pixels = width - 10;
        if (currently_pressed)
        {
            unsigned int x=MouseManager::GetX();
            if ((x>=xpos+5) && (x<=xpos+width-5))
            {
                position_cursor_pixels = x-(xpos+5);
            }
            else if ((x>=xpos) && (x<=xpos+5))
            {
                position_cursor_pixels = 0;
            }
            else if ((x>=xpos+width-5) && (x<=xpos+width))
            {
                position_cursor_pixels = length_pixels;
            }
        }

        if(currently_pressed && !is_pressed)
        {
            if (clickfunction)
                clickfunction( (char*) "test" );
        }
        else if(!currently_pressed && is_pressed)
        {
            if (releasefunction)
                releasefunction( (char*) "test" );
        }
        else if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        is_pressed = currently_pressed;

        for (auto& c : children )
            c->Logic(  );
    }
}

void SliderWidget::Render( void )
{
    if (is_visible)
    {

        if (is_enabled)
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

            if (!is_hovering)
            {
                ScreenRenderer::DrawRoundedRectangle( xpos+5, ypos+height/2-2, xpos+width-5, ypos+height/2+2, 2,  ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                ScreenRenderer::DrawFilledCircle( xpos+5+position_cursor_pixels, ypos+height/2, 5, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );
                ScreenRenderer::DrawCircle( xpos+5+position_cursor_pixels, ypos+height/2, 5,  ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
            }
            else
            {
                ScreenRenderer::DrawRoundedRectangle( xpos+5, ypos+height/2-2, xpos+width-5, ypos+height/2+2, 2,  ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                ScreenRenderer::DrawFilledCircle( xpos+5+position_cursor_pixels, ypos+height/2, 5, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );
                ScreenRenderer::DrawCircle( xpos+5+position_cursor_pixels, ypos+height/2, 5, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
            }

        }
        else
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

                ScreenRenderer::DrawRoundedRectangle( xpos+5, ypos+height/2-2, xpos+width-5, ypos+height/2+2, 2,  ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                ScreenRenderer::DrawFilledCircle( xpos+5+position_cursor_pixels, ypos+height/2, 5, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );
                ScreenRenderer::DrawCircle( xpos+5+position_cursor_pixels, ypos+height/2, 5,  ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
        }

        for (auto& c : children )
            c->Render(  );

    }
}
