#include "MenuItemWidget.hpp"
#include "MenuPaneWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


MenuItemWidget::MenuItemWidget()
{
    widgettype = "MenuItem";
};

MenuItemWidget::MenuItemWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : MiniButtonWidget( l, x, y, w, h, p )
{
    widgettype = (char*) "MenuItem";
};

MenuItemWidget::~MenuItemWidget()
{
    //dtor
}


unsigned int MenuItemWidget::GetFullTextWidth( void )
{
    return width_full_text;
}

void MenuItemWidget::Drop( void )
{
    is_dropped = true;
    is_visible = true;
    //is_pressed = false;
}

void MenuItemWidget::Undrop( void )
{
    is_dropped = false;
    is_visible = false;
    is_pressed = false;
}


bool MenuItemWidget::IsPressed( void )
{
    return is_pressed;
}

void MenuItemWidget::Logic( void  )
{
    if (is_enabled && is_visible)
    {
        is_hovering = CursorOn(  );
        bool currently_pressed = (MouseManager::GetB() || KeyManager::kbSCRATCH() ) && is_hovering;

        if(currently_pressed && !is_pressed)
        {
            if (clickfunction)
                clickfunction( (char*) "test" );
            is_pressed = true;
        }
        else if(!currently_pressed && is_pressed)
        {
            if (releasefunction)
                releasefunction( (char*) "test" );
            is_pressed = false;
        }
        else if(is_hovering)
        {
            if (hoverfunction)
                hoverfunction( (char*) "test" );
            is_pressed = false;
        }
        else
        {
            is_pressed = false;
        }
        //is_pressed = currently_pressed;

        if (is_pressed && (children.size()!=0))
        {
            for ( auto& c : children )
            {
                //TODO : working on that part of the code for correct overlapping of the menus
                if (parent)
                    if (parent->GetWidgetType() == "MenuPane")
                        dynamic_cast<MenuPaneWidget*>(parent)->SetChildDropped();

                if (c->GetWidgetType() == "MenuPane")
                {
                    c->SetVisible();
                    dynamic_cast<MenuPaneWidget*>(c)->Drop();
                }
                else
                {
                    c->SetVisible();
                }
            }
        }
        else if (is_pressed && (children.size()==0))
        {
            if (parent)
                if (parent->GetWidgetType() == "MenuPane")
                {
                    dynamic_cast<MenuPaneWidget*>(parent)->UnsetChildDropped();
                    dynamic_cast<MenuPaneWidget*>(parent)->Undrop();
                }
        }

        for (auto& c : children )
            c->Logic( );
    }
    else
    {
        // DEBUG : test to see if it actually works
        for (auto& c : children )
            c->Logic(  );

        is_pressed = false;
    }

}

void MenuItemWidget::Render( void )
{
    labelarrow = label;
    FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
    width_full_text = FontEngine::GetStringWidth(  labelarrow );

    if (is_visible)
    {

        if (is_enabled)
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height-2, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

            if (!is_hovering)
            {
                //ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
            }
            else
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height-2, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
            }

            // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
            drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

            labelarrow = label;
            width_full_text = FontEngine::GetStringWidth(  labelarrow );

            if (drawablecharlabel!=0)
            {
                drawablelabel = label; //fonts->reducestringtovisible( label, width-2 -2  );
                int sl =  FontEngine::GetStringWidth( drawablelabel );
                int sh =  FontEngine::GetStringHeight( drawablelabel );

                 FontEngine::DrawStringLeft( drawablelabel, xpos+2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );


                // create a mark to indicate that there is a submenu
                if (parent)
                {
                    // if the parent is a menubar, there is no need for the arrow indicator, it is absolutely logic to have a submenu
                    if (parent->GetWidgetType() != "MenuBar")
                    {
                        if (children.size()!=0)
                        {

                            for(auto& c : children)
                            {
                                if (c->GetWidgetType() == "MenuPane")
                                {
                                    FontEngine::DrawCharLeft(  (char) '\u0010',  xpos+sl+5, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );

                                }
                            }
                        }
                    }


                }
            }
        }
        else
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height-2, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );
            //Border of the button is black cause it is disabled
            //roundedRectangleRGBA( screen, xpos, ypos, xpos+width, ypos+height, 3, colors->widget_border_disable.R, colors->widget_border_disable.G, colors->widget_border_disable.B, colors->widget_border_disable.A);

            // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );
            drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

            labelarrow = label;
            width_full_text = FontEngine::GetStringWidth(  labelarrow );

            if (drawablecharlabel!=0)
            {
                drawablelabel = label; //fonts->reducestringtovisible( label, width-2 -2  );
                //int sl =  FontEngine::GetStringWidth( drawablelabel );
                int sh =  FontEngine::GetStringHeight( drawablelabel );

                 FontEngine::DrawStringLeft( drawablelabel, xpos+2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
            }
        }

        for (auto& c : children )
            c->Render( );
    }
}
