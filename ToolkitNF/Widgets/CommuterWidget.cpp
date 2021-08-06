#include "CommuterWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


CommuterWidget::CommuterWidget()
{
       widgettype = "Commuter";
       //strcpy( widgettype, (char*) "Commuter");
};


CommuterWidget::CommuterWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
{
       widgettype = "Commuter";
       //strcpy( widgettype, (char*) "Commuter");
};


CommuterWidget::~CommuterWidget()
{
};


void CommuterWidget::Invert( void )
{
       is_ticked = !is_ticked;
};


bool CommuterWidget::IsTicked( void )
{
       return is_ticked;
};


void CommuterWidget::SetType( CommuterType type )
{
       typetick = type;
};


CommuterWidget::CommuterType CommuterWidget::GetType( void )
{
       return typetick;
};


void CommuterWidget::SetNormal( void )
{
       is_reversed = false;
};


void CommuterWidget::SetReversed( void )
{
       is_reversed = true;
};


bool CommuterWidget::IsReversed( void )
{
       return is_reversed;
};


void CommuterWidget::Logic( void )
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

void CommuterWidget::Render( void )
{

       ColorEngine::ColorRGBA color, colorg;

       if (is_ticked && (typetick == Style1 ))
       {
              color = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Active_Filling_Style1);
              colorg = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Active_Cursor_Style1);
       }
       if (!is_ticked && (typetick == Style1 ))
       {
              color = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Inactive_Filling_Style1);
              colorg = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Inactive_Cursor_Style1);
       }

       if (is_ticked && (typetick == Style2 ))
       {
              color = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Active_Filling_Style2);
              colorg = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Active_Cursor_Style2);
       }
       if (!is_ticked && (typetick == Style2 ))
       {
              color = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Inactive_Filling_Style2);
              colorg = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Inactive_Cursor_Style2);
       }

       if (is_ticked && (typetick == Style3 ))
       {
              color = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Active_Filling_Style3);
              colorg = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Active_Cursor_Style3);
       }
       if (!is_ticked && (typetick == Style3 ))
       {
              color = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Inactive_Filling_Style3);
              colorg = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Inactive_Cursor_Style3);
       }

       if (is_ticked && (typetick == Style4 ))
       {
              color = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Active_Filling_Style3);
              colorg = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Active_Cursor_Style3);
       }
       if (!is_ticked && (typetick == Style4 ))
       {
              color = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Inactive_Filling_Style3);
              colorg = ColorEngine::GetColor(ColorEngine::Widget_Commuter_Inactive_Cursor_Style3);
       }


       if (is_visible)
       {

              if (is_enabled)
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 6, color );
                     if (!is_hovering)
                     {
                            ScreenRenderer::DrawRoundedRectangle( xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 6, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                     }
                     else
                     {
                            ScreenRenderer::DrawRoundedRectangle( xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 6, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                     }

                     if ((is_ticked && !is_reversed) || (!is_ticked && is_reversed))
                     {
                            ScreenRenderer::DrawFilledCircle( xpos+12, ypos+height/2, 4, colorg );
                            if (!is_hovering)
                            {
                                   ScreenRenderer::DrawCircle(  xpos+12, ypos+height/2, 4, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                            }
                            else
                            {
                                   ScreenRenderer::DrawCircle(  xpos+12, ypos+height/2, 4, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                            }
                     }
                     else
                     {
                            ScreenRenderer::DrawFilledCircle( xpos+24, ypos+height/2, 4, colorg );
                            if (!is_hovering)
                            {
                                   ScreenRenderer::DrawCircle(  xpos+24, ypos+height/2, 4, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                            }
                            else
                            {
                                   ScreenRenderer::DrawCircle(  xpos+24, ypos+height/2, 4, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                            }
                     }

                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-17-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-17 -2  );

                            int sh =FontEngine::GetStringHeight( drawablelabel );
                            FontEngine::DrawStringLeft(  drawablelabel, xpos+35, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
                     }
              }
              else
              {

                     ScreenRenderer::DrawFilledRoundedRectangle( xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 6, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

                     ScreenRenderer::DrawRoundedRectangle(  xpos+6, ypos+height/2-6, xpos+30, ypos+height/2+6, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );


                     if ((is_ticked && !is_reversed) || (!is_ticked && is_reversed))
                     {
                            ScreenRenderer::DrawFilledCircle( xpos+12, ypos+height/2, 4, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );
                           ScreenRenderer::DrawCircle( xpos+12, ypos+height/2, 4, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                     }
                     else
                     {
                           ScreenRenderer::DrawFilledCircle( xpos+24, ypos+height/2, 4, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );
                            ScreenRenderer::DrawCircle( xpos+24, ypos+height/2, 4, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                     }

                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );
                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-17-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-17 -2  );

                            int sh =FontEngine::GetStringHeight( drawablelabel );
                            FontEngine::DrawStringLeft(  drawablelabel, xpos+35, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                     }

              }


              for (auto& c : children )
                     c->Render(  );

       }
}
