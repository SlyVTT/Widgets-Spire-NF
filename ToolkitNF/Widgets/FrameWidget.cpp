#include "FrameWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


FrameWidget::FrameWidget()
{
       widgettype =  "Frame";
       //strcpy( widgettype, (char*) "Frame");
};

FrameWidget::FrameWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype =  "Frame";
       //strcpy( widgettype, (char*) "Frame");
};

FrameWidget::~FrameWidget()
{
};

unsigned int FrameWidget::GetUseableXPos()
{
       return xpos + 2;
}


unsigned int FrameWidget::GetUseableYPos()
{
       return ypos + 14;
}


unsigned int FrameWidget::GetUseableWidth()
{
       return width - 4;
}


unsigned int FrameWidget::GetUseableHeight()
{
       return height - 16;
}


void FrameWidget::Logic( void )
{
       if (is_enabled && is_visible)
       {

              is_hovering = CursorOn(  );
              bool currently_pressed = (MouseManager::GetB() || KeyManager::kbSCRATCH() ) && is_hovering;


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
                     c->Logic( );
       }
}

void FrameWidget::Render( void )
{
       if (is_visible)
       {



              if (is_enabled)
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-5-5 );

                     if (drawablecharlabel!=0)
                     {
                            int sl =  FontEngine::GetStringWidth( drawablelabel );
                            int sh =  FontEngine::GetStringHeight( drawablelabel );

                            if (!is_hovering)
                            {
                                   ScreenRenderer::DrawRoundedRectangle(  xpos, ypos+sh, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                            }
                            else
                            {
                                   ScreenRenderer::DrawRoundedRectangle(  xpos, ypos+sh, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                            }

                            ScreenRenderer::DrawFilledRectangle( xpos+3, ypos, xpos+3+sl, ypos+sh, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

                            drawablelabel =  FontEngine::ReduceStringToVisible(  label, width-5 -5  );

                            FontEngine::DrawStringLeft(  drawablelabel, xpos+3, ypos+sh/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
                     }
              }
              else
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );
                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-5-5 );

                     if (drawablecharlabel!=0)
                     {
                            int sl =  FontEngine::GetStringWidth( drawablelabel );
                            int sh =  FontEngine::GetStringHeight( drawablelabel );

                            ScreenRenderer::DrawRoundedRectangle(  xpos, ypos+sh, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                            ScreenRenderer::DrawFilledRectangle( xpos+3, ypos, xpos+3+sl, ypos+sh,  ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-5-5  );

                            FontEngine::DrawStringLeft(  drawablelabel, xpos+3, ypos+sh/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                     }
              }

              for (auto& c : children )
                     c->Render( );

       }
}
