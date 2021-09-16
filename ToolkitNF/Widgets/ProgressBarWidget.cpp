#include "ProgressBarWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


ProgressBarWidget::ProgressBarWidget()
{
       widgettype = "ProgressBar";
       //strcpy( widgettype, (char*) "ProgressBar");
};

ProgressBarWidget::ProgressBarWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "ProgressBar";
       //strcpy( widgettype, (char*) "ProgressBar");
};

ProgressBarWidget::~ProgressBarWidget()
{

};


void ProgressBarWidget::SetCurrentPercentage( float percent )
{
       percentfilled = percent;
};

float ProgressBarWidget::GetCurrentPercentage( )
{
       return percentfilled;
};

void ProgressBarWidget::SetStyle( BarStyle st )
{
       style = st;
};

void ProgressBarWidget::SetNumberBricks( int nb )
{
       nbbricks = nb;
};

void ProgressBarWidget::SetPrintValue( bool setter )
{
       drawvalue = setter;
};


void ProgressBarWidget::Logic( void )
{
       if (is_enabled && is_visible)
       {
              is_hovering = CursorOn(  );

              if(is_hovering)
              {
                     if (hoverfunction)
                            hoverfunction( (char*) "test" );
              }

              for (auto& c : children )
                     c->Logic( );
       }
}

void ProgressBarWidget::Render(  )
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

                     if (percentfilled<=0.0) percentfilled=0.0;

                     if (percentfilled>0)
                     {
                            if (percentfilled>100.0) percentfilled=100.0;

                            float length;


                            if (style == Continuous)
                            {
                                   length = (percentfilled/100.0 * (width-2));
                                   ScreenRenderer::DrawFilledRoundedRectangle( xpos+2, ypos+2, xpos+((int) length), ypos+height-2, 2, ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Enable_Filling) );
                            }
                            else if (style == Bricks)
                            {
                                   length = width;
                                   float bricklength = length / nbbricks;
                                   int dx = 0;
                                   for( int u=0; u<nbbricks; u++)
                                   {
                                          if ((u+1)*100/nbbricks <= percentfilled)
                                          {
                                                 ScreenRenderer::DrawFilledRoundedRectangle(  xpos+3+dx, ypos+2, xpos+dx+bricklength+2, ypos+height-2, 2, ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Enable_Filling) );
                                                 dx += (int) bricklength;
                                          }
                                          else
                                          {
                                                 float remain = percentfilled-u*100/nbbricks;
                                                 if (remain >= 0)
                                                 {
                                                        int extralength = (int) (remain/100*width);
                                                        ScreenRenderer::DrawFilledRoundedRectangle( xpos+3+dx, ypos+2, xpos+dx+extralength+2, ypos+height-2, 2, ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Enable_Filling) );
                                                 }
                                          }
                                   }
                            }
                            else if (style == Rainbow)
                            {
                                   unsigned short R, G, B, A;
                                   ColorEngine::ColorRGBA colorempty = ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Rainbow_Empty);
                                   ColorEngine::ColorRGBA colorfull = ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Rainbow_Full);

                                   R = (unsigned int) (colorempty.R + percentfilled/100 * (colorfull.R - colorempty.R));
                                   G = (unsigned int) (colorempty.G + percentfilled/100 * (colorfull.G - colorempty.G));
                                   B = (unsigned int) (colorempty.B + percentfilled/100 * (colorfull.B - colorempty.B));
                                   A = (unsigned int) (colorempty.A + percentfilled/100 * (colorfull.A - colorempty.A));
                                   length = (percentfilled/100.0 * (width-2));
                                   ScreenRenderer::DrawFilledRoundedRectangle( xpos+2, ypos+2, xpos+((int) length), ypos+height-2, 2, R, G, B, A);
                            }
                            else if (style == RainbowBrick)
                            {
                                   unsigned short R, G, B, A;
                                   ColorEngine::ColorRGBA colorempty, colorfull;

                                   R = (unsigned int) (colorempty.R + percentfilled/100 * (colorfull.R - colorempty.R));
                                   G = (unsigned int) (colorempty.G + percentfilled/100 * (colorfull.G - colorempty.G));
                                   B = (unsigned int) (colorempty.B + percentfilled/100 * (colorfull.B - colorempty.B));
                                   A = (unsigned int) (colorempty.A + percentfilled/100 * (colorfull.A - colorempty.A));
                                   length = width;
                                   float bricklength = length / nbbricks;
                                   int dx = 0;
                                   for( int u=0; u<nbbricks; u++)
                                   {
                                          if ((u+1)*100/nbbricks <= percentfilled)
                                          {
                                                 ScreenRenderer::DrawFilledRoundedRectangle( xpos+3+dx, ypos+2, xpos+dx+bricklength+2, ypos+height-2, 2, R, G, B, A);
                                                 dx += (int) bricklength;
                                          }
                                          else
                                          {
                                                 float remain = percentfilled-u*100/nbbricks;
                                                 if (remain >= 0)
                                                 {
                                                        int extralength = (int) (remain/100*width);
                                                        ScreenRenderer::DrawFilledRoundedRectangle( xpos+3+dx, ypos+2, xpos+dx+extralength+2, ypos+height-2, 2, R, G, B, A);
                                                 }
                                          }
                                   }
                            }
                     }


                     if (drawvalue)
                     {
                            char value[10];

                            sprintf( value, "%d", (int) percentfilled);

                            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );

                            int sl = FontEngine::GetStringWidth( value );
                            int sh = FontEngine::GetStringHeight(  value );

                            if (sl<=(int) width-15)  ScreenRenderer::DrawFilledRectangle( xpos+(width-sl)/2-2, ypos+2, xpos+(width+sl)/2+2, ypos+height-2, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );
                            if (sl<=(int) width-15) FontEngine::DrawStringLeft(  value, xpos+(width-sl)/2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
                     }
              }
              else
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

                     ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );


                     if (percentfilled<=0.0) percentfilled=0.0;

                     if (percentfilled>0)
                     {
                            if (percentfilled>100.0) percentfilled=100.0;

                            float length;


                            if (style == Continuous)
                            {
                                   length = (percentfilled/100.0 * (width-2));
                                   ScreenRenderer::DrawRoundedRectangle( xpos+2, ypos+2, xpos+((int) length), ypos+height-2, 2, ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Disable_Filling) );
                            }
                            else if (style == Bricks)
                            {
                                   length = width;
                                   float bricklength = length / nbbricks;
                                   int dx = 0;
                                   for( int u=0; u<nbbricks; u++)
                                   {
                                          if ((u+1)*100/nbbricks <= percentfilled)
                                          {
                                                 ScreenRenderer::DrawRoundedRectangle( xpos+3+dx, ypos+2, xpos+dx+bricklength+2, ypos+height-2, 2, ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Disable_Filling) );
                                                 dx += (int) bricklength;
                                          }
                                          else
                                          {
                                                 float remain = percentfilled-u*100/nbbricks;
                                                 if (remain >= 0)
                                                 {
                                                        int extralength = (int) (remain/100*width);
                                                        ScreenRenderer::DrawRoundedRectangle( xpos+3+dx, ypos+2, xpos+dx+extralength+2, ypos+height-2, 2, ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Disable_Filling) );
                                                 }
                                          }
                                   }
                            }
                            else if (style == Rainbow)
                            {
                                   length = (percentfilled/100.0 * (width-2));
                                   ScreenRenderer::DrawRoundedRectangle( xpos+2, ypos+2, xpos+((int) length), ypos+height-2, 2, ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Disable_Filling) );
                            }
                            else if (style == RainbowBrick)
                            {
                                   length = width;
                                   float bricklength = length / nbbricks;
                                   int dx = 0;
                                   for( int u=0; u<nbbricks; u++)
                                   {
                                          if ((u+1)*100/nbbricks <= percentfilled)
                                          {
                                                 ScreenRenderer::DrawRoundedRectangle( xpos+3+dx, ypos+2, xpos+dx+bricklength+2, ypos+height-2, 2, ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Disable_Filling) );
                                                 dx += (int) bricklength;
                                          }
                                          else
                                          {
                                                 float remain = percentfilled-u*100/nbbricks;
                                                 if (remain >= 0)
                                                 {
                                                        int extralength = (int) (remain/100*width);

                                                        ScreenRenderer::DrawRoundedRectangle( xpos+3+dx, ypos+2, xpos+dx+extralength+2, ypos+height-2, 2, ColorEngine::GetColor(ColorEngine::Widget_Progressbar_Disable_Filling) );
                                                 }
                                          }
                                   }
                            }
                     }


                     if (drawvalue)
                     {
                            char value[10];

                            sprintf( value, "%d", (int) percentfilled);

                            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );

                            int sl = FontEngine::GetStringWidth( value );
                            int sh = FontEngine::GetStringHeight(  value );

                            if (sl<=(int) width-15)  ScreenRenderer::DrawFilledRectangle( xpos+(width-sl)/2-2, ypos+2, xpos+(width+sl)/2+2, ypos+height-2, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );
                            if (sl<=(int) width-15) FontEngine::DrawStringLeft(  value, xpos+(width-sl)/2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                     }
              }

              for (auto& c : children )
                     c->Render(  );

       }
}
