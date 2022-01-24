#include "InputWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"



InputWidget::InputWidget()
{
    widgettype = "Input";
    //strcpy( widgettype, (char*) "Input");
};

InputWidget::InputWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "Input";
    //strcpy( widgettype, (char*) "Input");
};

InputWidget::~InputWidget()
{
    text.clear();
};


std::string InputWidget::GetContent()
{
    return text;
}

void InputWidget::SetContent(std::string str)
{
    text = str;
    cursor_pos = 0;
    scroll = 0;
}


void InputWidget::Logic( void )
{

    if (is_enabled && is_visible)
    {
        is_hovering = CursorOn( );
        mousex=MouseManager::GetX();
        mousey=MouseManager::GetY();
        mouses=MouseManager::GetB();

        if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        if ( is_hovering &&  (MouseManager::GetB() || KeyManager::kbSCRATCH() )  && !has_focus )
        {
            Focus( this );
        }

        if(  (MouseManager::GetB() || KeyManager::kbSCRATCH() )  && is_hovering )
        {
            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );

            unsigned int x_rel = mousex - xpos - 2;
            const char *str = text.c_str() + scroll;
            unsigned int pos = scroll;

            while(x_rel > 0 && *str)
            {
                unsigned int temp = FontEngine::GetCharWidth( (char) *str++ );
                x_rel -= temp;
                ++pos;
            }

            cursor_pos = pos;

        }

        if(!has_focus)
            return;

        char c = KeyManager::AsciiGet();
        if(c >= 0x80 || c == '\n')
            return;


        if (key_hold_down)
        {
            key_hold_down = KeyManager::IsAnyKeyPressed();
        }
        else if (KeyManager::kbCTRL() && MouseManager::kbLEFT())
        {
            cursor_pos = 0;
            UpdateScroll();
        }
        else if (KeyManager::kbCTRL() && MouseManager::kbRIGHT())
        {
            cursor_pos = text.length();
            UpdateScroll();
        }
        else if (MouseManager::kbLEFT())
        {
            if(cursor_pos > 0) --cursor_pos;
            UpdateScroll();
        }
        else if (MouseManager::kbRIGHT())
        {
            if(cursor_pos < text.length()) ++cursor_pos;
            UpdateScroll();
        }

        static char old_char = 0;
        if(c != old_char && c != 0)
        {
            if(c == '\b')
            {
                if(cursor_pos > 0)
                {
                    text.erase(text.begin() + (cursor_pos - 1));
                    --cursor_pos;

                    UpdateScroll();
                }
            }
            else
            {
                text.insert(text.begin() + cursor_pos, c);
                ++cursor_pos;

                UpdateScroll();
            }
        }

        old_char = c;

        if(!KeyManager::IsAnyKeyPressed())
        {
            old_char = 0;
        }

        for (auto& c : children ) c->Logic( );

    }
}


void InputWidget::Render( void )
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
            else
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
            }

            const char *str = text.c_str() + scroll;
            const char *cursor = text.c_str() + cursor_pos;
            unsigned int x1 = xpos + 5;

            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );

            char* tpstr = (char*) str;
            int sh = FontEngine::GetStringHeight( tpstr );

            while(*str && x1 - xpos + FontEngine::GetCharWidth( (char) *str) < width)
            {
                if(has_focus && str == cursor)
                {
                    ScreenRenderer::DrawLine(  x1, ypos + height/4, x1, ypos + 3*height/4, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                    ScreenRenderer::DrawLine(  x1+1, ypos + height/4, x1+1, ypos + 3*height/4, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                    x1+=2;
                }

                FontEngine::DrawCharLeft( *str, x1, ypos + height/2 - sh/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
                x1 +=FontEngine::GetCharWidth( (char) *str ) + FontEngine::GetCurrentHSpacing();

                ++str;
            }

            if(str == cursor)
            {
                    ScreenRenderer::DrawLine(  x1, ypos + height/4, x1, ypos + 3*height/4, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                    ScreenRenderer::DrawLine(  x1+1, ypos + height/4, x1+1, ypos + 3*height/4, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                x1+=2;
            }
        }
        else
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

            ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

            const char *str = text.c_str() + scroll;
            const char *cursor = text.c_str() + cursor_pos;
            unsigned int x1 = xpos + 5;

            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );

            char* tpstr = (char*) str;
            int sh = FontEngine::GetStringHeight( tpstr );


            while(*str && x1 - xpos + FontEngine::GetCharWidth( (char) *str) < width)
            {
                if(has_focus && str == cursor)
                {
                    ScreenRenderer::DrawLine(  x1, ypos + height/4, x1, ypos + 3*height/4, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                    ScreenRenderer::DrawLine(  x1+1, ypos + height/4, x1+1, ypos + 3*height/4, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                    x1+=2;
                }

                FontEngine::DrawCharLeft( *str, x1, ypos + height/2 - sh/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                x1 +=FontEngine::GetCharWidth( (char) *str ) + FontEngine::GetCurrentHSpacing();

                ++str;
            }

            if(str == cursor)
            {
                    ScreenRenderer::DrawLine(  x1, ypos + height/4, x1, ypos + 3*height/4, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                    ScreenRenderer::DrawLine(  x1+1, ypos + height/4, x1+1, ypos + 3*height/4, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                x1+=2;
            }


        }

        for (auto& c : children )      c->Render( );
    }
}


void InputWidget::UpdateScroll()
{
    if(scroll != 0 && cursor_pos <= scroll)
        --scroll;

    if(cursor_pos <= scroll)
        return;

    FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );

    const char *str = text.c_str() + scroll;
    unsigned int cur_x = 0;
    unsigned int len = cursor_pos - scroll;

    while(len--)
        cur_x += FontEngine::GetCharWidth( *str++ ) + FontEngine::GetCurrentHSpacing();

    if(cur_x >= width - 5)
        ++scroll;
}
