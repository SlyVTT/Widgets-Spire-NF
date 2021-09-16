#include "RadioControlWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


RadioControlWidget::RadioControlWidget()
{
       widgettype =  "RadioControl";
       //strcpy( widgettype, (char*) "RadioControl");
};


RadioControlWidget::RadioControlWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
{
       widgettype = "RadioControl";
       //strcpy( widgettype, (char*) "RadioControl");
};

RadioControlWidget::~RadioControlWidget()
{

};


void  RadioControlWidget::Invert()
{
       is_ticked = !is_ticked;
};

bool  RadioControlWidget::IsTicked( void )
{
       return is_ticked;
};



void RadioControlWidget::Logic( void  )
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

              for (auto& c : children ) c->Logic( );
       }
}

void RadioControlWidget::Render( void )
{
       if (is_visible)
       {

              if (is_enabled)
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

                     if (!is_hovering)
                     {
                            ScreenRenderer::DrawCircle( xpos+6, ypos+height/2, 6, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                     }
                     else
                     {
                            ScreenRenderer::DrawCircle( xpos+6, ypos+height/2, 6, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                     }


                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-2 -2  );

                            int sh =  FontEngine::GetStringHeight( drawablelabel );

                            FontEngine::DrawStringLeft( drawablelabel, xpos+15, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
                     }

                     if (is_ticked)
                     {
                            ScreenRenderer::DrawFilledCircle( xpos+6, ypos+height/2, 3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Enable) );
                     }

              }
              else
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

                     ScreenRenderer::DrawCircle( xpos+6, ypos+height/2, 6, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );
                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-2 -2  );

                            int sh =  FontEngine::GetStringHeight( drawablelabel );

                            FontEngine::DrawStringLeft( drawablelabel, xpos+15, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                     }

                     if (is_ticked)
                     {
                            ScreenRenderer::DrawFilledCircle( xpos+6, ypos+height/2, 3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Disable) );
                     }

              }


              for (auto& c : children )
                     c->Render(  );

       }
}
