#include "MenuBarWidget.hpp"
#include "MenuItemWidget.hpp"
#include "WindowWidget.hpp"
#include "DesktopWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


MenuBarWidget::MenuBarWidget() : ContainerHWidget ()
{
       widgettype = "MenuBar";
}


MenuBarWidget::MenuBarWidget(std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ContainerHWidget( l, x, y, w, h, p )
{
       widgettype = "MenuBar";

       label = l;
       xrel=x;
       yrel=y;
       widrel=w;
       heirel=h;
       parent=p;

       if (parent)
       {
              if (parent->GetWidgetType() == "Desktop")
              {
                     dynamic_cast<DesktopWidget*>(parent)->SetMenuBar();

                     xpos = parent->GetUseableXPos();

                     if (dynamic_cast<DesktopWidget*>(parent)->GetIconBar() == true)
                     {
                            ypos = parent->GetUseableYPos()-12-20;
                     }
                     else
                     {
                            ypos = parent->GetUseableYPos()-12;
                     }

                     width = parent->GetUseableWidth();
                     height = 12;
              }
              else if (parent->GetWidgetType() == "Window" )
              {
                     dynamic_cast<WindowWidget*>(parent)->SetMenuBar();

                     xpos = parent->GetUseableXPos();

                     if (dynamic_cast<WindowWidget*>(parent)->GetIconBar() == true)
                     {
                            ypos = parent->GetUseableYPos()-12-20;
                     }
                     else
                     {
                            ypos = parent->GetUseableYPos()-12;
                     }

                     width = parent->GetUseableWidth();
                     height = 12;
              }
       }
       else
       {
              xpos=xrel;
              ypos=yrel;
              width=widrel;
              height=heirel;
       }

       nbchildren = children.size();

       unsigned int currentpositionX = xpos+1;
       unsigned int currentwidth=0;

       for (auto& c : children )   // this code has been updated to have a homogeneous spacing of MenuItemsWidgets
       {
              //c->setdimensions( xpos+1 + width/nbchildren*i, ypos, width/nbchildren-2, height );
              //i++;
              currentwidth = dynamic_cast<MenuItemWidget*>(c)->GetFullTextWidth() + 10;
              c->SetDimensions( currentpositionX, ypos, currentwidth, height );
              currentpositionX += currentwidth;
       }

       for (auto& c : children )
              c->Adjust();

}



MenuBarWidget::~MenuBarWidget()
{
       //dtor
}


void MenuBarWidget::Adjust( void )
{

       if (parent)
       {
              if (parent->GetWidgetType() == "Desktop")
              {
                     dynamic_cast<DesktopWidget*>(parent)->SetMenuBar();

                     xpos = parent->GetUseableXPos();

                     if (dynamic_cast<DesktopWidget*>(parent)->GetIconBar() == true)
                     {
                            ypos = parent->GetUseableYPos()-12-20;
                     }
                     else
                     {
                            ypos = parent->GetUseableYPos()-12;
                     }

                     width = parent->GetUseableWidth();
                     height = 12;
              }
              else if (parent->GetWidgetType() == "Window" )
              {
                     dynamic_cast<WindowWidget*>(parent)->SetMenuBar();

                     xpos = parent->GetUseableXPos();

                     if (dynamic_cast<WindowWidget*>(parent)->GetIconBar() == true)
                     {
                            ypos = parent->GetUseableYPos()-12-20;
                     }
                     else
                     {
                            ypos = parent->GetUseableYPos()-12;
                     }

                     width = parent->GetUseableWidth();
                     height = 12;
              }
       }
       else
       {
              xpos=xrel;
              ypos=yrel;
              width=widrel;
              height=heirel;
       }

       nbchildren = children.size();

       unsigned int currentpositionX = xpos+1;
       unsigned int currentwidth=0;

       for (auto& c : children )   // this code has been updated to have a homogeneous spacing of MenuItemsWidgets
       {
              //c->setdimensions( xpos+1 + width/nbchildren*i, ypos, width/nbchildren-2, height );
              //i++;
              currentwidth = dynamic_cast<MenuItemWidget*>(c)->GetFullTextWidth() + 10;
              c->SetDimensions( currentpositionX, ypos, currentwidth, height );
              currentpositionX += currentwidth;
       }

       for (auto& c : children )
              c->Adjust();
}


unsigned int MenuBarWidget::GetUseableHeight( void )
{
       return height - 2;
}


void MenuBarWidget::Logic( void )
{
       if (is_enabled && is_visible)
       {
              for (auto& c : children )
                     c->Logic( );
       }
       else
       {
              // DEBUG : test to see if it actually works
              for (auto& c : children )
                     c->Logic( );
       }

}


void MenuBarWidget::Render( void )
{
       if (is_visible)
       {
              if (is_enabled)
              {
                     ScreenRenderer::DrawFilledRectangle( xpos, ypos, xpos+width, ypos+height, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

                     if (!is_hovering)
                     {
                            ScreenRenderer::DrawLine( xpos, ypos+height-1, xpos+width, ypos+height-1, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                     }
                     else
                     {
                            ScreenRenderer::DrawLine( xpos, ypos+height-1, xpos+width, ypos+height-1, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
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
