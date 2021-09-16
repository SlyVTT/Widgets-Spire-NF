#include "CheckBoxWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


CheckBoxWidget::CheckBoxWidget()
{
       widgettype = "CheckBox";
       //strcpy( widgettype, (char*) "CheckBox");
};


CheckBoxWidget::CheckBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
{
       widgettype = "CheckBox";
       //strcpy( widgettype, (char*) "CheckBox");
};

CheckBoxWidget::~CheckBoxWidget()
{

};

void CheckBoxWidget::Invert()
{
       is_ticked = !is_ticked;
};

bool CheckBoxWidget::IsTicked( void )
{
       return is_ticked;
};

void CheckBoxWidget::SetType( Tick type )
{
       typetick = type;
};

CheckBoxWidget::Tick CheckBoxWidget::GetType( void )
{
       return typetick;
};

void CheckBoxWidget::Logic( void )
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

void CheckBoxWidget::Render( void )
{
       if (is_visible)
       {

              if (is_enabled)
              {

                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

                     if (!is_hovering)
                     {
                            ScreenRenderer::DrawRoundedRectangle( xpos, ypos+height/2-6, xpos+12, ypos+height/2+6, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                     }
                     else
                     {
                            ScreenRenderer::DrawRoundedRectangle( xpos, ypos+height/2-6, xpos+12, ypos+height/2+6, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
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


                     if (is_ticked && (typetick == Square_Tick ))
                     {
                            ScreenRenderer::DrawFilledRoundedRectangle( xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, 1, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Enable) );
                     }
                     else if (is_ticked && (typetick == Cross_Tick ))
                     {
                            ScreenRenderer::DrawLine( xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Enable) );
                            ScreenRenderer::DrawLine( xpos+4, ypos+height/2-3, xpos+9, ypos+height/2+2, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Enable) );
                            ScreenRenderer::DrawLine( xpos+3, ypos+height/2-2, xpos+8, ypos+height/2+3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Enable) );

                            ScreenRenderer::DrawLine( xpos+3, ypos+height/2+3, xpos+9, ypos+height/2-3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Enable) );
                            ScreenRenderer::DrawLine( xpos+3, ypos+height/2+2, xpos+8, ypos+height/2-3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Enable) );
                            ScreenRenderer::DrawLine( xpos+4, ypos+height/2+3, xpos+9, ypos+height/2-2, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Enable) );
                     }


              }
              else
              {


                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

                     ScreenRenderer::DrawRoundedRectangle( xpos, ypos+height/2-6, xpos+12, ypos+height/2+6, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );
                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-2 -2  );

                            int sh =  FontEngine::GetStringHeight( drawablelabel );

                            FontEngine::DrawStringLeft( drawablelabel, xpos+15, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                     }


                     if (is_ticked && (typetick == Square_Tick ))
                     {
                            ScreenRenderer::DrawFilledRoundedRectangle( xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, 1, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Disable) );
                     }
                     else if (is_ticked && (typetick == Cross_Tick ))
                     {
                            ScreenRenderer::DrawLine( xpos+3, ypos+height/2-3, xpos+9, ypos+height/2+3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Disable) );
                            ScreenRenderer::DrawLine( xpos+4, ypos+height/2-3, xpos+9, ypos+height/2+2, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Disable) );
                            ScreenRenderer::DrawLine( xpos+3, ypos+height/2-2, xpos+8, ypos+height/2+3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Disable) );

                            ScreenRenderer::DrawLine( xpos+3, ypos+height/2+3, xpos+9, ypos+height/2-3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Disable) );
                            ScreenRenderer::DrawLine( xpos+3, ypos+height/2+2, xpos+8, ypos+height/2-3, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Disable) );
                            ScreenRenderer::DrawLine( xpos+4, ypos+height/2+3, xpos+9, ypos+height/2-2, ColorEngine::GetColor(ColorEngine::Widget_Tickmark_Disable) );
                     }
              }


              for (auto& c : children )
                     c->Render(  );

       }
}
