#include "MultiLineTextBoxWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"

#include <fstream>


MultiLineTextBoxWidget::MultiLineTextBoxWidget()
{
    widgettype =  "MultiLineTextBox";
    content.push_back("");
    cursor_posX = 0;
}


MultiLineTextBoxWidget::MultiLineTextBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype =  "MultiLineTextBox";
    content.push_back("");
    cursor_posX = 0;
}


MultiLineTextBoxWidget::~MultiLineTextBoxWidget()
{
    content.clear();
    selection.clear();
}


void MultiLineTextBoxWidget::Flush()
{
    content.clear();
    content.push_back("");
    cursor_posX = 0;
}

void MultiLineTextBoxWidget::SaveContentToFile( std::string filename )
{
    FILE* pFile;

    pFile = fopen (filename.c_str(), "w");
    if (pFile!=NULL)
    {
        fprintf( pFile, "%s",  content[0].c_str());
        fclose(pFile);
    }
    cursor_posX = 0;
}

void MultiLineTextBoxWidget::LoadContentFromFile( std::string filename )
{
    Flush();

    FILE* pFile;
    char c;

    std::string filecontent;

    pFile = fopen (filename.c_str(), "r");
    if (pFile!=NULL)
    {
        while (!feof(pFile))
        {
            fscanf( pFile, "%c",  &c);
            filecontent += c;
        }

        fclose(pFile);
    }

    SetContent( filecontent );
    cursor_posX = 0;
}


void MultiLineTextBoxWidget::AppendContent(std::string str)
{
    //content.push_back(str);
    content[0] += str;
}


void MultiLineTextBoxWidget::SetContent( std::string str )
{
    Flush();
    //content.push_back(str);
    content[0] += str;
}


std::string MultiLineTextBoxWidget::GetContent()
{
    return content[0];
}


void MultiLineTextBoxWidget::SetNonEditable()
{
    iseditable = false;
}

void MultiLineTextBoxWidget::SetEditable()
{
    iseditable = true;
}


void MultiLineTextBoxWidget::CopySelection()
{
    if (selectstart==selectend)
    {
        //keybclip->Flushselection();
    }
    else if (selectstart<selectend)
    {
        KeyManager::SetSelection( content[0].substr(selectstart, selectend-selectstart) );
    }
    else if (selectstart>selectend)
    {
        KeyManager::SetSelection( content[0].substr(selectend, selectstart-selectend) );
    }
    //keybclip->resetstate();
    isselected = false;
    selectend = selectstart;
}

void MultiLineTextBoxWidget::CutSelection()
{
    if (iseditable)
    {
        if (selectstart==selectend)
        {
            //keybclip->Flushselection();
        }
        else if (selectstart<selectend)
        {
            KeyManager::SetSelection( content[0].substr(selectstart, selectend-selectstart) );

            content[0].erase(selectstart, selectend-selectstart );
        }
        else if (selectstart>selectend)
        {
            KeyManager::SetSelection( content[0].substr(selectend, selectstart-selectend) );

            content[0].erase(selectend, selectstart-selectend );
        }
        //keybclip->resetstate();
        isselected = false;
        selectend = selectstart;
    }
}

void MultiLineTextBoxWidget::PasteSelection()
{
    if (iseditable)
    {
        if (KeyManager::GetSelection().size()!=0)
        {
            content[0].insert(cursor_posX, KeyManager::GetSelection() );
        }
        //keybclip->resetstate();
        isselected = false;
        selectend = selectstart;
    }
}

void MultiLineTextBoxWidget::EraseSelection()
{
    if (iseditable)
    {
        if (selectstart==selectend)
        {
            // not selection to be erased
        }
        else if (selectstart<selectend)
        {
            content[0].erase(selectstart, selectend-selectstart );
        }
        else if (selectstart>selectend)
        {
            content[0].erase(selectend, selectstart-selectend );
        }
        //keybclip->resetstate();
        isselected = false;
        selectend = selectstart;
    }
}


void MultiLineTextBoxWidget::Logic( void )
{
    if (is_enabled && is_visible)
    {
        is_hovering = CursorOn( );

        mousex=MouseManager::GetX();
        mousey=MouseManager::GetY();

        if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
        }

        if ( is_hovering && ( MouseManager::GetX() || KeyManager::kbSCRATCH()) && !has_focus )
        {
            Focus( this );
        }

        if( (MouseManager::GetB() || KeyManager::kbSCRATCH()) && is_hovering )
        {

            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );

            unsigned int x_rel = mousex - xpos - 2;
            const char *str = content[0].c_str() + scrollX;
            unsigned int pos = scrollX;

            while(x_rel > 0 && *str)
            {
                unsigned int temp =  FontEngine::GetCharWidth( (char) *str++ );
                x_rel -= temp;
                ++pos;
            }

            cursor_posX = pos;

        }

        if(!has_focus)
            return;


        char c;

        if (iseditable)
        {
            c = KeyManager::AsciiGet();

            if (c>=0x80)
                return;
        }
        else return;

        if (key_hold_down)
        {
            key_hold_down = KeyManager::IsAnyKeyPressed();
        }

        // This is the behavior assigned to SHIFT + arrow keys which control the selection

        else if (KeyManager::kbSHIFT() && !KeyManager::kbCTRL() && MouseManager::kbLEFT())
        {
            if (isselected==false) selectstart=cursor_posX;
            isselected=true;

            if (cursor_posX > 0)
            {
                cursor_posX--;
            }
            else
            {
                cursor_posX=0;
            }

            selectend = cursor_posX;

            UpdateScroll();
        }
        else if (KeyManager::kbSHIFT() && !KeyManager::kbCTRL() && MouseManager::kbRIGHT())
        {
            if (isselected==false) selectstart=cursor_posX;
            isselected=true;

            if (cursor_posX < content[0].length())
            {
                cursor_posX++;
            }
            else
            {
                cursor_posX=content[0].length();
            }

            selectend = cursor_posX;

            UpdateScroll();
        }
        else if (KeyManager::kbSHIFT() && !KeyManager::kbCTRL() && MouseManager::kbUP())
        {
            if (isselected==false) selectstart=cursor_posX;
            isselected=true;

            if(cursor_posX > nbcharvisibleperline)
                cursor_posX -= nbcharvisibleperline;
            else
                cursor_posX = 0;

            selectend = cursor_posX;

            UpdateScroll();

            //if (firstlinevisible>0) firstlinevisible--;
        }
        else if (KeyManager::kbSHIFT() && !KeyManager::kbCTRL() && MouseManager::kbDOWN())
        {
            if (isselected==false) selectstart=cursor_posX;
            isselected=true;

            if(cursor_posX < content[0].length()-nbcharvisibleperline)
                cursor_posX += nbcharvisibleperline;
            else
                cursor_posX = content[0].length();

            selectend = cursor_posX;

            UpdateScroll();
            //if (firstlinevisible<nblinetotal) firstlinevisible++;
        }


        // This is the behavior assigned to CTRL + arrow keys and CTRL + X/V/C/DEL which control the scroll and copy/paste/cut/erase

        else if (KeyManager::IsKeyPressEvent() && isselected && !KeyManager::kbSHIFT() && KeyManager::kbCTRL() && KeyManager::kbC())                      // CTRL + C to copy the selection to the KeyboardTask
        {
            CopySelection();
        }
        else if (KeyManager::IsKeyPressEvent() && isselected && !KeyManager::kbSHIFT() && KeyManager::kbCTRL() && KeyManager::kbX())                      // CTRL + X to cut the selection to the KeyboardTask
        {
            CutSelection();
        }
        else if (KeyManager::IsKeyPressEvent() && isselected && !KeyManager::kbSHIFT() && KeyManager::kbCTRL() && KeyManager::kbDEL())                      // CTRL + DEL to erase the selection
        {
            EraseSelection();
        }
        else if (KeyManager::IsKeyPressEvent() && !KeyManager::kbSHIFT && KeyManager::kbCTRL && KeyManager::kbV)                      // CTRL + V to paste the selection coming from the KeyboardTask
        {
            PasteSelection();
        }
        else if (!KeyManager::kbSHIFT() && KeyManager::kbCTRL() && MouseManager::kbLEFT())
        {
            cursor_posX = 0;
            isselected = false;
            UpdateScroll();
        }
        else if (!KeyManager::kbSHIFT() && KeyManager::kbCTRL() && MouseManager::kbRIGHT())
        {
            cursor_posX = content[0].length();
            isselected = false;
            UpdateScroll();
        }
        else if (!KeyManager::kbSHIFT() && KeyManager::kbCTRL() && MouseManager::kbUP())
        {
            if(cursor_posX > nbcharvisibleperline)
                cursor_posX -= nbcharvisibleperline;
            else
                cursor_posX = 0;

            if (currentlinecursor<=firstlinevisible) firstlinevisible=currentlinecursor;

            isselected = false;
            UpdateScroll();
        }
        else if (!KeyManager::kbSHIFT() && KeyManager::kbCTRL() && MouseManager::kbDOWN())
        {
            if(cursor_posX < content[0].length()-nbcharvisibleperline)
                cursor_posX += nbcharvisibleperline;
            else
                cursor_posX = content[0].length();

            if (currentlinecursor>firstlinevisible+nblinevisible) firstlinevisible=currentlinecursor;

            isselected = false;
            UpdateScroll();
        }


        // This is the behavior assigned to arrow keys which control the movement of the cursor

        else if (!KeyManager::kbSHIFT() && !KeyManager::kbCTRL() && MouseManager::kbLEFT())
        {
            if(cursor_posX > 0)
                --cursor_posX;
            isselected = false;
            UpdateScroll();
        }
        else if (!KeyManager::kbSHIFT() && !KeyManager::kbCTRL() && MouseManager::kbRIGHT())
        {
            if(cursor_posX < content[0].length())
                ++cursor_posX;
            isselected = false;
            UpdateScroll();
        }
        else if (!KeyManager::kbSHIFT() && !KeyManager::kbCTRL() && MouseManager::kbDOWN())
        {
            if(cursor_posX < content[0].length()-nbcharvisibleperline)
                cursor_posX += nbcharvisibleperline;
            else
                cursor_posX = content[0].length();

            if (currentlinecursor>firstlinevisible+nblinevisible) firstlinevisible=currentlinecursor;

            isselected = false;
            UpdateScroll();
        }
        else if (!KeyManager::kbSHIFT() && !KeyManager::kbCTRL() && MouseManager::kbUP())
        {
            if(cursor_posX > nbcharvisibleperline)
                cursor_posX -= nbcharvisibleperline;
            else
                cursor_posX = 0;

            if (currentlinecursor<=firstlinevisible) firstlinevisible=currentlinecursor;

            isselected = false;
            UpdateScroll();
        }

        static char old_char = 0;

        if (iseditable)
        {

            if(c != old_char && c != 0)
            {
                if(c == '\b')
                {
                    if(cursor_posX > 0)
                    {
                        content[0].erase(content[0].begin() + (cursor_posX - 1));
                        --cursor_posX;

                        UpdateScroll();
                    }
                }
                else
                {
                    content[0].insert(content[0].begin() + cursor_posX, c);
                    ++cursor_posX;

                    UpdateScroll();
                }
            }

            old_char = c;

            if(!KeyManager::IsAnyKeyPressed())
            {
                old_char = 0;
            }

        }
        for (auto& c : children ) c->Logic( );

    }
}


void MultiLineTextBoxWidget::Render( void )
{
    FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
    nblinevisible = (height-5) /  (FontEngine::GetCharHeight( 'O' )+ FontEngine::GetCurrentVSpacing());

    bool escalator = false;

    if (nblinetotal>nblinevisible)
    {
        escalator = true;
        nbcharvisibleperline = (width - 25) / (FontEngine::GetCharWidth( 'O' )+ FontEngine::GetCurrentHSpacing()) -1 ;
    }
    else
    {
        escalator = false;
        nbcharvisibleperline = (width - 10) / (FontEngine::GetCharWidth( 'O' )+ FontEngine::GetCurrentHSpacing()) - 1 ;
    }

    unsigned int currentnblinetotal = 0;


    if (is_visible)
    {
        if (is_enabled)
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

            if (!is_hovering)
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );

                if (escalator==true)
                {
                    ScreenRenderer::DrawRoundedRectangle(xpos+width-12, ypos+4, xpos+width-4, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                    unsigned int y = ((height-7-7)*firstlinevisible / nblinetotal);
                    ScreenRenderer::DrawFilledCircle( xpos+width-8, ypos+7+y, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                }

            }
            else
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );

                if (escalator==true)
                {
                    ScreenRenderer::DrawRoundedRectangle(xpos+width-12, ypos+4, xpos+width-4, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                    unsigned int y = ((height-7-7)*firstlinevisible / nblinetotal);
                    ScreenRenderer::DrawFilledCircle( xpos+width-8, ypos+7+y, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                }

            }



            const char *str = content[0].c_str() + scrollX;
            const char *cursor = content[0].c_str() + cursor_posX;
            unsigned int x1 = xpos + 2;

            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );

            char* tpstr = (char*) str;
            int sh =FontEngine::GetStringHeight( tpstr );
            int sp = FontEngine::GetCurrentVSpacing();

            unsigned int currentpositioniinstring = 0;
            bool selected = false;

            unsigned int selend=selectend;
            unsigned int selsta=selectstart;

            if (selend<selectstart)
            {
                selend = selectstart;
                selsta = selectend;
            }

            currentline = 0;
            //while(*str && x1 - xpos + fonts->getcharwidth( (char) *str) < width)
            while (*str)
            {

                if (isselected && (currentpositioniinstring>=selsta) && (currentpositioniinstring<selend))
                    selected = true;
                else
                    selected = false;

                // TO BE TESTED
                if (str == cursor)
                {
                    currentlinecursor = currentline;
                }
                // END TO BE TESTED

                if(has_focus && (str == cursor) &&  (currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                {
                    ScreenRenderer::DrawLine(  x1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), x1, ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                    ScreenRenderer::DrawLine(  x1+1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), x1-1, ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                    x1+=2;
                }

                if (*str == '\n' )
                {
                    // if the current char is "RETURN" we go to the next line
                    x1 = xpos + 2;
                    currentline++;
                }
                else if (*str == '\t')
                {
                    // if the current char is a "TAB", we replace it with 5 SPACES
                    for(unsigned int u=0; u<5; u++)
                    {
                        if ((currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                        {
                            FontEngine::DrawCharLeft( ' ', x1, ypos + 2 + (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
                        }
                        x1 += FontEngine::GetCharWidth( ' ' ) + FontEngine::GetCurrentHSpacing();
                    }
                }
                else
                {
                    if ((currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                    {
                        if (!selected)
                        {
                            FontEngine::DrawCharLeft( *str, x1, ypos + 2 + (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
                        }
                        else
                        {
                            ScreenRenderer::DrawFilledRectangle( x1, ypos+2+(currentline-firstlinevisible) * (sh+sp), x1+FontEngine::GetCharWidth( (char) *str ), ypos+2+(currentline-firstlinevisible) * (sh+sp) + sh, ColorEngine::GetColor(ColorEngine::Widget_Selection) );
                            FontEngine::DrawCharLeft( *str, x1, ypos + 2 + (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Text_Selected) );
                        }
                    }
                    x1 += FontEngine::GetCharWidth( (char) *str ) + FontEngine::GetCurrentHSpacing();
                }

                if ((escalator==false) && (x1-xpos > width-10))
                {
                    x1 = xpos + 2;
                    currentline++;
                    if (currentline>currentnblinetotal) currentnblinetotal=currentline;
                }

                if ((escalator==true) && (x1-xpos > width-25))
                {
                    x1 = xpos + 2;
                    currentline++;
                    if (currentline>currentnblinetotal) currentnblinetotal=currentline;
                }


                ++str;
                currentpositioniinstring++;
            }

            // TO BE TESTED
            if (str == cursor)
            {
                currentlinecursor = currentline;
            }
            // END TO BE TESTED

            if(has_focus && (str == cursor) && (currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
            {
                ScreenRenderer::DrawLine(  x1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), x1, ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                ScreenRenderer::DrawLine(  x1+1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), x1+1, ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                x1+=2;
            }

        }
        else
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

            ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

            if (escalator==true)
            {
                ScreenRenderer::DrawRoundedRectangle(xpos+width-12, ypos+4, xpos+width-4, ypos+height-4, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                unsigned int y = ((height-7-7)*firstlinevisible / nblinetotal);
                ScreenRenderer::DrawFilledCircle( xpos+width-8, ypos+7+y, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
            }

            const char *str = content[0].c_str() + scrollX;
            const char *cursor = content[0].c_str() + cursor_posX;
            unsigned int x1 = xpos + 2;

            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );

            char* tpstr = (char*) str;
            int sh =FontEngine::GetStringHeight( tpstr );
            int sp = FontEngine::GetCurrentVSpacing();
            //while(*str && x1 - xpos + fonts->getcharwidth( (char) *str) < width)
            while (*str)
            {

                // TO BE TESTED
                if (str == cursor)
                {
                    currentlinecursor = currentline;
                }
                // END TO BE TESTED

                if(has_focus && str == cursor &&  (currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                {
                    ScreenRenderer::DrawLine(  x1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), x1, ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                    ScreenRenderer::DrawLine(  x1+1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), x1+1, ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                    x1+=2;
                }

                if (*str == '\n' )
                {
                    // if the current char is "RETURN" we go to the next line
                    x1 = xpos + 2;
                    currentline++;
                }
                else if (*str == '\t')
                {
                    // if the current char is a "TAB", we replace it with 5 SPACES
                    for(unsigned int u=0; u<5; u++)
                    {
                        //fonts->drawcharleft( screen, ' ', x1, ypos + 2 + currentline * (sh+sp),colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A);

                        if ((currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                        {
                            FontEngine::DrawCharLeft( ' ', x1, ypos + 2 + (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                        }

                        x1 += FontEngine::GetCharWidth( ' ' ) + FontEngine::GetCurrentHSpacing();
                    }
                }
                else
                {
                    //fonts->drawcharleft( screen, *str, x1, ypos + 2+ currentline * (sh+sp), colors->widget_text_enable.R, colors->widget_text_enable.G, colors->widget_text_enable.B, colors->widget_text_enable.A);

                    if ((currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
                    {
                        FontEngine::DrawCharLeft( *str, x1, ypos + 2 + (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                    }

                    x1 += FontEngine::GetCharWidth( (char) *str ) + FontEngine::GetCurrentHSpacing();
                }

                if ((escalator==false) && (x1-xpos > width-10))
                {
                    x1 = xpos + 2;
                    currentline++;
                    if (currentline>currentnblinetotal) currentnblinetotal=currentline;
                }

                if ((escalator==true) && (x1-xpos > width-25))
                {
                    x1 = xpos + 2;
                    currentline++;
                    if (currentline>currentnblinetotal) currentnblinetotal=currentline;
                }

                ++str;
            }

            // TO BE TESTED
            if (str == cursor)
            {
                currentlinecursor = currentline;
            }
            // END TO BE TESTED

            if((str == cursor) && (currentline>=firstlinevisible) && (currentline<firstlinevisible+nblinevisible))
            {
                ScreenRenderer::DrawLine(  x1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), x1, ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                ScreenRenderer::DrawLine(  x1+1, ypos + 1+ (currentline-firstlinevisible) * (sh+sp), x1+1, ypos + sh + 1+ (currentline-firstlinevisible) * (sh+sp), ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                x1+=2;
            }


        }

        for (auto& c : children )
            c->Render( );
    }

    nblinetotal = currentnblinetotal;
}

void MultiLineTextBoxWidget::UpdateScroll()
{

}
