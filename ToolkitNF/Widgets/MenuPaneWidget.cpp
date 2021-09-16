#include "MenuPaneWidget.hpp"

#include "MenuItemWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


MenuPaneWidget::MenuPaneWidget() : ContainerVWidget ()
{
    widgettype = "MenuPane";
    this->Undrop();
};


MenuPaneWidget::MenuPaneWidget(std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ContainerVWidget( l, x, y, w, h, p )
{

    widgettype = "MenuPane";

    label = l;
    xrel=x;
    yrel=y;
    widrel=w;
    heirel=h;
    parent=p;

    if (parent)
    {
        xpos = parent->GetUseableXPos();
        ypos = parent->GetUseableYPos()+12;

        // This part may be subjected to optimisation
        // TODO
        unsigned int tempw = 0;
        unsigned int temph = 0;

        for (auto& c : children )
        {
            unsigned int currentwidgetwidth;

            if (c->GetWidgetType()=="MenuItem")
                currentwidgetwidth = dynamic_cast<MenuItemWidget*>(c)->GetFullTextWidth();
            else
                currentwidgetwidth =10;

            if ( currentwidgetwidth > tempw) tempw = currentwidgetwidth;
            //tempw = 50;
            temph += 14;
        }

        width = tempw+5;
        height = temph;

        // We check we the menu is too wide and will exceed the right border of the screen, if so, we move it to the left accordingly to its size
        if (xpos+width>=SCREEN_WIDTH_GUI)
            xpos=SCREEN_WIDTH_GUI-width-4;

        // END TODO

        parent->AddPopupChild( this );

    }
    else // Note: THIS SITUATION SHOULD NOTE APPEAR - IT IS A NON SENSE TO ADD A MENU TO NOTHING - THIS IS CODED FOR FUTURE CONTEXTUAL MENUS
    {
        xpos=xrel;
        ypos=yrel;
        width=widrel;
        height=heirel;
    }

    unsigned int i=0;
    nbchildren = children.size();

    for (auto& c : children )
    {
        c->SetDimensions( xpos+1, ypos+1 + 14*i, width-2, 12 );
        i++;
    }

    for (auto& c : children ) c->Adjust();

    this->Undrop();
};



MenuPaneWidget::~MenuPaneWidget()
{
    //dtor
}

void MenuPaneWidget::Drop( void )
{
    is_dropped = true;
    is_visible = true;
}

void MenuPaneWidget::Undrop( void )
{
    if (!has_child_menu_open)
    {
        is_dropped = false;
        is_visible = false;
    }
}

void MenuPaneWidget::SetChildDropped( void )
{
    has_child_menu_open = true;
    is_visible = true;
}

void MenuPaneWidget::UnsetChildDropped( void )
{
    has_child_menu_open = false;
}



void MenuPaneWidget::Adjust( void )
{

    if (parent)
    {
        if(parent->GetParent())
        {
            //if the parent of the parent is a MenuPane, we shift on the right of the parent menu (this is a submenu)
            if (parent->GetParent()->GetWidgetType() == "MenuPane")
            {
                if (parent->GetXPos() + parent->GetWidth() + 2 + width <= SCREEN_WIDTH_GUI) // si on ne dépasse pas le bord droit de l'écran, on met à droite
                {
                    xpos = parent->GetXPos()+parent->GetWidth() + 2;
                }
                else
                {
                    xpos = parent->GetXPos() - width - 2;    // sinon on met à gauche
                }

                ypos = parent->GetYPos() ;

            }
            else
            {
                xpos = parent->GetXPos();   // else we just put below
                ypos = parent->GetYPos() + parent->GetHeight();
            }



            // This part may be subjected to optimisation
            // TODO
            unsigned int tempw = 0;
            unsigned int temph = 0;

            for (auto& c : children )
            {
                unsigned int currentwidgetwidth;

                if (c->GetWidgetType()=="MenuItem")
                    currentwidgetwidth = dynamic_cast<MenuItemWidget*>(c)->GetFullTextWidth();
                else
                    currentwidgetwidth =10;

                if ( currentwidgetwidth > tempw) tempw = currentwidgetwidth;
                //tempw = 50;
                temph += 14;
            }

            width = tempw+5;
            height = temph;

            // We check we the menu is too wide and will exceed the right border of the screen, if so, we move it to the left accordingly to its size
            if (xpos+width>=SCREEN_WIDTH_GUI)
                xpos=SCREEN_WIDTH_GUI-width-4;

            // END TODO

        }
    }
    else
    {
        xpos=xrel;
        ypos=yrel;
        width=widrel;
        height=heirel;
    }


    int i=0;
    nbchildren = children.size();

    for (auto& c : children )
    {
        c->SetDimensions( xpos+1, ypos+1 + 14*i, width-2, 12 );
        i++;
    }

    for (auto& c : children )
        c->Adjust();

}


void MenuPaneWidget::Logic( void )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->Logic( );

        MouseManager::Logic();
        KeyManager::Logic();

        is_hovering = CursorOn(  );

        bool clickoutof = (MouseManager::GetB() || KeyManager::kbSCRATCH() ) && !is_hovering;

        if (clickoutof && !has_child_menu_open && MouseManager::IsMouseEvent &&  KeyManager::IsAnyKeyEvent() )
        {
            this->Undrop();
            if (parent)
                if (parent->GetParent())
                    if (parent->GetParent()->GetWidgetType() == "MenuPane")
                    {
                        dynamic_cast<MenuPaneWidget*>(parent->GetParent())->UnsetChildDropped();
                        dynamic_cast<MenuPaneWidget*>(parent->GetParent())->Undrop();
                    }
        }
    }
    else
    {
        // DEBUG : test to see if it actually works
        for (auto& c : children )
            c->Logic( );
    }
}



void MenuPaneWidget::Render( void )
{


    // This part may be subjected to optimisation
    // TODO
    unsigned int tempw = 0;
    unsigned int temph = 0;

    for (auto& c : children )
    {
        unsigned int currentwidgetwidth;

        if (c->GetWidgetType()=="MenuItem")
            currentwidgetwidth = dynamic_cast<MenuItemWidget*>(c)->GetFullTextWidth();
        else
            currentwidgetwidth =10;

        if ( currentwidgetwidth > tempw) tempw = currentwidgetwidth;
        //tempw = 50;
        temph += 14;
    }


    width = tempw+5;
    height = temph;

    // We check we the menu is too wide and will exceed the right border of the screen, if so, we move it to the left accordingly to its size
    if (xpos+width>=SCREEN_WIDTH_GUI)
        xpos=SCREEN_WIDTH_GUI-width-4;

    int i=0;
    nbchildren = children.size();

    for (auto& c : children )
    {
        c->SetDimensions( xpos+1, ypos+1 + 14*i, width-2, 12 );
        i++;
    }

    for (auto& c : children )
        c->Adjust();


    // END TODO

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

        }
        else
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

            ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
        }

        for (auto& c : children )
        {
            c->Render(  );
        }

    }
}
