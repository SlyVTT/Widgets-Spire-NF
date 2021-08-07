#include "IconBarWidget.hpp"
#include "WindowWidget.hpp"
#include "DesktopWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


IconBarWidget::IconBarWidget() : ContainerHWidget ()
{
    widgettype =  "IconBar";
};


IconBarWidget::IconBarWidget(std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ContainerHWidget( l, x, y, w, h, p )
{
    widgettype = "IconBar";

    label = l;
    xrel=x;
    yrel=y;
    widrel=w;
    heirel=h;
    parent=p;

    if (parent)
    {
        if (parent->GetWidgetType() == "Desktop" )
        {
            dynamic_cast<DesktopWidget*>(parent)->SetIconBar();

            xpos = parent->GetUseableXPos();

            if (dynamic_cast<DesktopWidget*>(parent)->GetMenuBar() == true)
            {
                ypos = parent->GetUseableYPos()-20; //-12-20
            }
            else
            {
                ypos = parent->GetUseableYPos()-20; //-20
            }

            width = parent->GetUseableWidth();
            height = 20;
        }
        else if (parent->GetWidgetType() == "Window" )
        {
            dynamic_cast<WindowWidget*>(parent)->SetIconBar();

            xpos = parent->GetUseableXPos();

            if (dynamic_cast<WindowWidget*>(parent)->GetMenuBar() == true)
            {
                ypos = parent->GetUseableYPos()-20; //-12-20
            }
            else
            {
                ypos = parent->GetUseableYPos()-20; //-20
            }

            width = parent->GetUseableWidth();
            height = 20;
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
        c->SetDimensions( xpos+1 + 22*i, ypos, 20, 20 );
        i++;
    }

    for (auto& c : children )
        c->Adjust();

};

IconBarWidget::~IconBarWidget()
{
    //dtor
}




void IconBarWidget::Adjust( void )
{

    if (parent)
    {
        if (parent->GetWidgetType() == "Desktop" )
        {
            xpos = parent->GetUseableXPos();

            if (dynamic_cast<DesktopWidget*>(parent)->GetMenuBar() == true)
            {
                ypos = parent->GetUseableYPos()-20;  // -12-20
            }
            else
            {
                ypos = parent->GetUseableYPos()-20; //-20
            }

            width = parent->GetUseableWidth();
            height = 20;
        }
        else if (parent->GetWidgetType() == "Window" )
        {
            xpos = parent->GetUseableXPos();

            if (dynamic_cast<WindowWidget*>(parent)->GetMenuBar() == true)
            {
                ypos = parent->GetUseableYPos()-20; //-12-20
            }
            else
            {
                ypos = parent->GetUseableYPos()-20; //-20
            }
            width = parent->GetUseableWidth();
            height = 20;
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
        c->SetDimensions( xpos+1 + 22*i, ypos, 20, 20 );
        i++;
    }

    for (auto& c : children )
        c->Adjust();

}



void IconBarWidget::Logic( void )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->Logic(  );
    }
}



void IconBarWidget::Render( void  )
{
    if (is_visible)
    {
        if (is_enabled)
        {
            ScreenRenderer::DrawFilledRectangle( xpos, ypos, xpos+width, ypos+height, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

            if (!is_hovering)
            {
               ScreenRenderer::DrawLine(  xpos, ypos+height, xpos+width, ypos+height,  ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
            }
            else
            {
                ScreenRenderer::DrawLine(   xpos, ypos+height, xpos+width, ypos+height,  ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
            }
        }
        else
        {
            ScreenRenderer::DrawFilledRectangle( xpos, ypos, xpos+width, ypos+height, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );
            ScreenRenderer::DrawLine( xpos, ypos+height-1, xpos+width, ypos+height-1, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
        }

        for (auto& c : children )
            c->Render(  );
    }
}
