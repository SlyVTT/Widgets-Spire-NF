#include "WindowWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


WindowWidget::WindowWidget( )
{
       widgettype = "Window";
       //strcpy( widgettype, (char*) "Window");
};

WindowWidget::WindowWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "Window";
       //strcpy( widgettype, (char*) "Window");
       xposback = x;
       yposback = y;
       widthback = w;
       heightback = h;
};

WindowWidget::~WindowWidget()
{

};

void WindowWidget::SetMinimalDimensions( unsigned int widmin, unsigned int heimin)
{
       minwidth = widmin;
       minheight = heimin;
};

void WindowWidget::SetMenuBar()
{
       hasmenubar = true;
};

void WindowWidget::SetIconBar()
{
       hasiconbar = true;
};

bool WindowWidget::GetMenuBar()
{
       return hasmenubar;
};

bool WindowWidget::GetIconBar()
{
       return hasiconbar;
};


unsigned int WindowWidget::GetUseableXPos()
{
       return xpos + 2;
}


unsigned int WindowWidget::GetUseableYPos()
{
       if (!hasmenubar && !hasiconbar) return ypos + 14;               // we just remove the size of the title bar (12px+2px = 14px)
       else if (hasmenubar && !hasiconbar) return ypos + 14 + 12;            // we remove the size of the title bar and of the menu bar (14px + 12px)
       else if (hasmenubar && hasiconbar) return ypos + 14 + 12 + 20;        // we remove the size of the title bar, of the menu bar and of the icon bar (14px + 12px + 20px)
       else return ypos + 14 + 20;        // we remove the size of the title bar, of the menu bar and of the icon bar (14px + 12px + 20px)
}


unsigned int WindowWidget::GetUseableWidth()
{
       return width - 4;
}


unsigned int WindowWidget::GetUseableHeight()
{
       if (!hasmenubar && !hasiconbar) return height - 16;                // we just remove the size of the title bar (12px + 2px + 2px = 16px)
       else if (hasmenubar && !hasiconbar) return height - 16 - 12;            // we remove the size of the title bar and of the menu bar (16px + 12px)
       else if (hasmenubar && hasiconbar) return height - 16 - 12 - 20;        // we remove the size of the title bar, of the menu bar and of the icon bar (16px + 12px + 20px)
       else return height - 16 - 20;            // we remove the size of the title bar, of the menu bar and of the icon bar (16px + 12px + 20px)
}


bool WindowWidget::IsMouseAtLeftBorder(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos-2) && ((unsigned int) MouseManager::GetY() >= ypos+2) && ((unsigned int) MouseManager::GetX() <= xpos+2) && ((unsigned int) MouseManager::GetY() <= ypos+height-2);
}


bool WindowWidget::IsMouseAtRightBorder(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos+width-2) && ((unsigned int) MouseManager::GetY() >= ypos+2) && ((unsigned int) MouseManager::GetX() <= xpos+width+2) && ((unsigned int) MouseManager::GetY() <= ypos+height-2);
}


bool WindowWidget::IsMouseAtTopBorder(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos+2) && ((unsigned int) MouseManager::GetY() >= ypos-2) && ((unsigned int) MouseManager::GetX() <= xpos+width-2) && ((unsigned int) MouseManager::GetY() <= ypos+2);
}


bool WindowWidget::IsMouseAtBottomBorder(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos+2) && ((unsigned int) MouseManager::GetY() >= ypos+height-2) && ((unsigned int) MouseManager::GetX() <= xpos+width-2) && ((unsigned int) MouseManager::GetY() <= ypos+height+2);
}


bool WindowWidget::IsMouseOnTitleBar(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos+2) && ((unsigned int) MouseManager::GetY() >= ypos+2) && ((unsigned int) MouseManager::GetX() <= xpos+width-32) && ((unsigned int) MouseManager::GetY() <= ypos+12);
}


bool WindowWidget::IsMouseOnMinimiseButton(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos+width-32) && ((unsigned int) MouseManager::GetY() >= ypos+2) && ((unsigned int) MouseManager::GetX() <= xpos+width-22) && ((unsigned int) MouseManager::GetY() <= ypos+12);
}


bool WindowWidget::IsMouseOnRestoreButton(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos+width-22) && ((unsigned int) MouseManager::GetY() >= ypos+2) && ((unsigned int) MouseManager::GetX() <= xpos+width-12) && ((unsigned int) MouseManager::GetY() <= ypos+12);
}


bool WindowWidget::IsMouseOnMaximiseButton(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos+width-12) && ((unsigned int) MouseManager::GetY() >= ypos+2) && ((unsigned int) MouseManager::GetX() <= xpos+width-2) && ((unsigned int) MouseManager::GetY() <= ypos+12);
}



void WindowWidget::Maximize()
{
       if (ismaximized)
       {
              xpos = xposback;
              ypos = yposback;
              width = widthback;
              height = heightback;

              for (auto& c : children )
                     c->SetVisible();

              ismaximized = false;
              isminimized = false;

              Adjust();
       }
       else if (isminimized)
       {
              Restore();
       }
       else
       {
              xposback = xpos;
              yposback = ypos;
              widthback = width;
              heightback = height;

              //xpos = 0;
              //ypos = 0;
              //width = SCREEN_WIDTH;
              //height = SCREEN_HEIGHT;

              xpos = parent->GetUseableXPos();
              ypos = parent->GetUseableYPos();
              width = parent->GetUseableWidth();
              height = parent->GetUseableHeight();


              for (auto& c : children )
                     c->SetVisible();

              ismaximized = true;
              isminimized = false;

              Adjust();
       }
}

void WindowWidget::Minimize()
{
       if (isminimized)
       {
              xpos = xposback;
              ypos = yposback;
              width = widthback;
              height = heightback;

              for (auto& c : children )
                     c->SetVisible();

              ismaximized = false;
              isminimized = false;

              Adjust();
       }
       else if (ismaximized)
       {
              Restore();
       }
       else
       {
              xposback = xpos;
              yposback = ypos;
              widthback = width;
              heightback = height;

              //xpos = 0;
              //ypos = 0;
              //width = SCREEN_WIDTH;
              //height = 12;

              xpos = parent->GetUseableXPos();
              ypos = parent->GetUseableYPos();
              width = parent->GetUseableWidth();
              height = 12;

              for (auto& c : children )
                     c->SetInvisible();

              ismaximized = false;
              isminimized = true;

              Adjust();
       }
}

void WindowWidget::Restore()
{
       if (!ismaximized && !isminimized)
       {
              xposback = xpos;
              yposback = ypos;
              widthback = width;
              heightback = height;
       }
       else
       {
              xpos = xposback;
              ypos = yposback;
              width = widthback;
              height = heightback;

              for (auto& c : children )
                     c->SetVisible();

              ismaximized = false;
              isminimized = false;

              Adjust();
       }
}

void WindowWidget::Logic( void )
{
       unsigned int nbpopupvisible = 0;
       for (auto& d : popupchildren )
              if (d->IsVisible())
              {
                     nbpopupvisible++;
                     d->Logic( );
              }

       if (nbpopupvisible==0)
       {
              if (is_activated)
              {

                     is_hovering = CursorOn(  );

                     if(is_hovering)
                     {
                            if (hoverfunction)
                                   hoverfunction( (char*) "test" );
                     }

                     bool atborder = false;
                     bool ontitle = false;
                     bool onmax = false;
                     bool onmin = false;
                     bool onres = false;

                     if (IsMouseAtLeftBorder(  ))
                     {
                            MouseManager::SetCursorType( MouseManager::Cursor_Leftrightresize );
                            atborder = true;
                     }
                     else if (IsMouseAtRightBorder(  ))
                     {
                            MouseManager::SetCursorType( MouseManager::Cursor_Leftrightresize );
                            atborder = true;
                     }
                     else if (IsMouseAtTopBorder(  ))
                     {
                            MouseManager::SetCursorType( MouseManager::Cursor_Topbottomresize );
                            atborder = true;
                     }
                     else if (IsMouseAtBottomBorder(  ))
                     {
                            MouseManager::SetCursorType( MouseManager::Cursor_Topbottomresize );
                            atborder = true;
                     }
                     else if (IsMouseOnTitleBar(  ))
                     {
                            MouseManager::SetCursorType( MouseManager::Cursor_Handfinger );
                            ontitle = true;
                     }
                     else if (IsMouseOnMaximiseButton(  ))
                     {
                            MouseManager::SetCursorType( MouseManager::Cursor_Triangle );
                            onmax = true;
                     }
                     else if (IsMouseOnMinimiseButton(  ))
                     {
                            MouseManager::SetCursorType( MouseManager::Cursor_Triangle );
                            onmin = true;
                     }
                     else if (IsMouseOnRestoreButton(  ))
                     {
                            MouseManager::SetCursorType( MouseManager::Cursor_Triangle );
                            onres = true;
                     }
                     else
                     {
                            MouseManager::SetCursorType( MouseManager::Cursor_Pointer );
                     }


                     if (atborder && KeyManager::kbSCRATCH())
                     {
                            resizemode = true;
                     }
                     else
                     {
                            resizemode = false;
                     }

                     if (onmax && KeyManager::kbSCRATCH())
                     {
                            Maximize();
                            onmax = false;
                     }

                     if (onmin && KeyManager::kbSCRATCH())
                     {
                            Minimize();
                            onmin = false;
                     }

                     if (onres && KeyManager::kbSCRATCH())
                     {
                            Restore();
                            onres = false;
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
                     if (resizemode && IsMouseAtLeftBorder( ))
                     {
                            unsigned int xposold = xpos;
                            MouseManager::Logic();
                            //if ((MouseManager::GetX() > 2) && (width + xposold - MouseManager::GetX() >= minwidth)) xpos = MouseManager::GetX();
                            if (((unsigned int) MouseManager::GetX() > parent->GetUseableXPos()) && (width + xposold - MouseManager::GetX() >= minwidth)) xpos = MouseManager::GetX();
                            width += (xposold - xpos);
                            Adjust();
                     }

                     if (resizemode && IsMouseAtRightBorder( ))
                     {
                            MouseManager::Logic();
                            //if ((MouseManager::GetX() < SCREEN_WIDTH-2) && (MouseManager::GetX() - xpos >= minwidth)) width = MouseManager::GetX() - xpos;
                            if (((unsigned int) MouseManager::GetX() < parent->GetUseableXPos()+parent->GetUseableWidth()) && (MouseManager::GetX() - xpos >= minwidth)) width = MouseManager::GetX() - xpos;
                            Adjust();
                     }

                     if (resizemode && IsMouseAtTopBorder( ))
                     {
                            unsigned int yposold = ypos;
                            MouseManager::Logic();
                            //if ((MouseManager::GetY() > 2) && (height + yposold - MouseManager::GetY() >= minheight)) ypos = MouseManager::GetY();
                            if (((unsigned int) MouseManager::GetY() > parent->GetUseableYPos()) && (height + yposold - MouseManager::GetY() >= minheight)) ypos = MouseManager::GetY();
                            height += (yposold - ypos);
                            Adjust();
                     }

                     if (resizemode && IsMouseAtBottomBorder( ))
                     {
                            MouseManager::Logic();
                            //if ((MouseManager::GetY() < SCREEN_HEIGHT-2) && (MouseManager::GetY() - ypos >= minheight)) height = MouseManager::GetY() - ypos;
                            if (((unsigned int) MouseManager::GetY() < parent->GetUseableYPos()+parent->GetUseableHeight()) && (MouseManager::GetY() - ypos >= minheight)) height = MouseManager::GetY() - ypos;
                            Adjust();
                     }

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
              }

              //PUT ON TOP TO START WITH POPUPCHILD LOGIC
              //for (auto& d : popupchildren )
              //              d->Logic( );

       }
}


void WindowWidget::Render( void )
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

                     // Draw the Minimize round button
                     ScreenRenderer::DrawFilledCircle( xpos+width-27, ypos+6, 3, ColorEngine::GetColor(ColorEngine::Window_Titlebar_Minimize) );
                     // Draw the Restore round button
                     ScreenRenderer::DrawFilledCircle( xpos+width-17, ypos+6, 3, ColorEngine::GetColor(ColorEngine::Window_Titlebar_Restore) );
                     // Draw the Maximize round button
                     ScreenRenderer::DrawFilledCircle( xpos+width-7, ypos+6, 3, ColorEngine::GetColor(ColorEngine::Window_Titlebar_Maximize) );

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

              for (auto& d : popupchildren )
              {
                     //if (d->isvisible())
                     {
                            d->Render( );
                     }
              }
       }

}

/*
bool WindowWidget::cursoron( void  )
{
    return (MouseManager::GetX() >= xpos) && (MouseManager::GetY() >= ypos) && (MouseManager::GetX() <= xpos+width) && (MouseManager::GetY() <= ypos+height);
}
*/
