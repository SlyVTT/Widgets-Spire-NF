#include "DialogBoxWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"



DialogBoxWidget::DialogBoxWidget()
{
       widgettype = "Window";
       //strcpy( widgettype, (char*) "DialogBox");
};

DialogBoxWidget::DialogBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : WindowWidget( l, x, y, w, h, p )
{
       widgettype = "Window";
       //strcpy( widgettype, (char*) "DialogBox");
       xposback = x;
       yposback = y;
       widthback = w;
       heightback = h;
};

DialogBoxWidget::~DialogBoxWidget()
{

};


unsigned int DialogBoxWidget::GetUseableXPos()
{
       return xpos + 2;
}


unsigned int DialogBoxWidget::GetUseableYPos()
{
       return ypos + 14;               // we just remove the size of the title bar (12px+2px = 14px)
}


unsigned int DialogBoxWidget::GetUseableWidth()
{
       return width - 4;
}


unsigned int DialogBoxWidget::GetUseableHeight()
{
       return height - 16;                // we just remove the size of the title bar (12px + 2px + 2px = 16px)
}


bool DialogBoxWidget::IsMouseOnTitleBar(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos+2) && ((unsigned int) MouseManager::GetY() >= ypos+2) && ((unsigned int) MouseManager::GetX() <= xpos+width-32) && ((unsigned int) MouseManager::GetY() <= ypos+12);
}


void DialogBoxWidget::Logic( void )
{
       if (is_activated)
       {

              is_hovering = CursorOn(  );

              if(is_hovering)
              {
                     if (hoverfunction)
                            hoverfunction( (char*) "test" );
              }

              bool ontitle = false;

              if (IsMouseOnTitleBar( ))
              {
                     MouseManager::SetCursorType( MouseManager::Cursor_Handfinger );
                     ontitle = true;
              }
              else
              {
                     MouseManager::SetCursorType( MouseManager::Cursor_Pointer );
              }


              if (ontitle && KeyManager::kbSCRATCH() && !startmove)
              {
                     movemode = true;
                     startmove = true;
                     clickX = MouseManager::GetX();
                     clickY = MouseManager::GetY();
              }
              else if (ontitle && KeyManager::kbSCRATCH() && startmove)
              {
                     movemode = true;
              }
              else
              {
                     movemode = false;
                     startmove = false;
              }

              // Here comes the resize Logic
              // DialopBow cannot be resized


              // Here comes the move Logic ...
              if (movemode && IsMouseOnTitleBar( ))
              {
                     MouseManager::Logic();

                     int deltax = (int) MouseManager::GetX() - (int) clickX;
                     int deltay = (int) MouseManager::GetY() - (int) clickY;

                     //we go left
                     if (deltax < 0)
                     {
                            //if ((int) xpos > (int) (-1 * deltax))   xpos += deltax;
                            if ((int) (xpos + deltax) > (int) parent->GetUseableXPos() )   xpos += deltax;
                     }
                     //we go up
                     if (deltay < 0)
                     {
                            //if ((int) ypos > (int) (-1 * deltay))   ypos += deltay;
                            if ((int) (ypos + deltay) > (int) parent->GetUseableYPos() )   ypos += deltay;
                     }

                     //we go right
                     if (deltax > 0)
                     {
                            //if ((int) (SCREEN_WIDTH - xpos - width) > (int) (deltax))   xpos += deltax;
                            if ((int) (parent->GetUseableXPos() + parent->GetUseableWidth() - xpos - width) > (int) (deltax))   xpos += deltax;
                     }
                     //we go down
                     if (deltay > 0)
                     {
                            //if ((int) (SCREEN_HEIGHT - ypos - height) > (int) (deltay))   ypos += deltay;
                            if ((int) (parent->GetUseableYPos() + parent->GetUseableHeight() - ypos - height) > (int) (deltay))   ypos += deltay;
                     }

                     Adjust();

                     clickX = MouseManager::GetX();
                     clickY = MouseManager::GetY();
              }


              for (auto& c : children )
                     c->Logic( );

              // No PopUpChild

       }
}


void DialogBoxWidget::Render( void )
{

       if (is_visible)
       {

              if (is_enabled)
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+12, 3, ColorEngine::GetColor(ColorEngine::Window_Titlebar_Enable) );

                     if (!is_hovering)
                     {
                            ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                     }
                     else
                     {
                            ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                     }

                     FontEngine::SetCurrentFontSet( FontEngine::Window_Titlebartext_Enable );

                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-5-5-30 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-5 -5 -30 );

                            //int sl = fonts->getstringwidth( drawablelabel );
                            int sh =  FontEngine::GetStringHeight( drawablelabel );
                            FontEngine::DrawStringLeft(  drawablelabel, xpos+5, ypos+sh/2, ColorEngine::GetColor(ColorEngine::Window_Titlebartext_Enable) );
                     }
              }
              else
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+12, 3, ColorEngine::GetColor(ColorEngine::Window_Titlebar_Disable) );
                     ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                     FontEngine::SetCurrentFontSet( FontEngine::Window_Titlebartext_Disable );

                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-5-5-30 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-5 -5 -30 );

                            //int sl = fonts->getstringwidth( drawablelabel );
                            int sh =  FontEngine::GetStringHeight( drawablelabel );
                            FontEngine::DrawStringLeft(  drawablelabel, xpos+5, ypos+sh/2, ColorEngine::GetColor(ColorEngine::Window_Titlebartext_Disable) );
                     }
              }


              /*
              // THIS IS FOR DEBUGGING THE DEPTH BUFFER PORTION OF THE CODE
              char* tempID;
              sprintf( tempID, "ID = %ld", WidgetID );
              fonts->setcurrentfont( THIN_FONT );
              fonts->setmodifiertypo( Bold );
              fonts->drawstringleft( screen, tempID, xpos+2, ypos+4, 255, 0, 0, 255 );
              */

              for (auto& c : children )
              {
                     if (c->IsVisible())
                     {
                            c->Render( );
                     }
              }

              // No PopUpChild to be drawn in DialogBox
       }
}
