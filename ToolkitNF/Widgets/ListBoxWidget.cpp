#include "ListBoxWidget.hpp"
#include "DropBoxWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Managers/TimeManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


ListBoxWidget::ListBoxWidget() : Widget()
{
       widgettype = "ListBox";
};

ListBoxWidget::ListBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
       widgettype = "ListBox";
};

ListBoxWidget::~ListBoxWidget()
{
       listitems.clear();
};

void ListBoxWidget::Flush( void )
{
       listitems.clear();

       nbitem = 0;
       selected = 0;
       scroll = 0;
       nbvisible = 0;
};


void ListBoxWidget::AddItem( std::string item )
{
       listitems.push_back( item);
       nbitem++;
};

unsigned int ListBoxWidget::GetNbItem( void )
{
       return listitems.size();
};

std::string ListBoxWidget::GetItem( int itemnumber )
{
       return listitems[itemnumber];
};

int ListBoxWidget::GetSelected( void )
{
       return selected;
};

std::string ListBoxWidget::GetSelectedItem( void )
{
       return listitems[selected];
};

bool ListBoxWidget::IsPressed( void )
{
       return is_pressed;
}

void ListBoxWidget::Logic( void )
{
       if (is_enabled && is_visible)
       {
              is_hovering = CursorOn(  );
              bool currently_pressed = (MouseManager::GetB() || KeyManager::kbSCRATCH() ) && is_hovering;

              if (currently_pressed)
              {
                     Focus(this);
              }

              if(currently_pressed && !is_pressed)
              {
                     if (clickfunction) clickfunction( (char*) "test" );
              }
              else if(!currently_pressed && is_pressed)
              {
                     if (releasefunction) releasefunction( (char*) "test" );
              }
              else if(is_hovering)
              {
                     if (hoverfunction) hoverfunction( (char*) "test" );
              }

              is_pressed = currently_pressed;

              if (!has_focus) return;

              if (currently_pressed)
              {
                     // Here is the code when the user click inside the listbox

                     // First we check if there is a escalator and if we clicked on the escalator
                     // as we are inside the widget (due to previous cursoron() call, we just need to check if the mouse x is > right border-15px
                     if ((nbvisible<nbitem) && ((int) MouseManager::GetX() >= ((int) xpos+ (int) width-15)) && ((int) MouseManager::GetY() > (int) ypos +6) && ((int) MouseManager::GetY() < (int) ypos+(int) height-6))
                     {
                            //so we are on the escalator
                            selected = (int) ((MouseManager::GetY() - ypos-3)*nbitem/(height-12));
                            if (selected<1)
                            {
                                   selected = 0;
                                   scroll = 0;
                            }
                            else if (selected<scroll) scroll=selected;
                            else if (selected>scroll+nbvisible) scroll=selected;
                            if (selected>nbitem) selected=nbitem;
                     }
                     else if (((int) MouseManager::GetY() > (int) ypos +3) && ((int) MouseManager::GetY() < (int) ypos+(int) height-3))
                     {
                            //we clicked on the main part of the widget and then we have to calculated which line is clicked and add the scroll to adjsut the selected line
                            int clickedline = (int) ((int)(MouseManager::GetY() - ypos-3)/ (int) heightline);
                            selected = scroll + clickedline;
                     }
              }


              if (KeyManager::kbESC())
              {
                     if(parent)
                     {
                            if (parent->GetWidgetType() == "DropBox")
                            {
                                   DropBoxWidget *temp = dynamic_cast<DropBoxWidget*>(parent);
                                   temp->Escape();
                                   is_visible = false;
                                   return;
                            }
                            else
                            {
                                   validated = false;
                                   escaped = true;
                            }
                     }
              }


              if (KeyManager::kbRET() || KeyManager::kbENTER())
              {
                     if(parent)
                     {
                            if (parent->GetWidgetType() == "DropBox")
                            {
                                   DropBoxWidget *temp = dynamic_cast<DropBoxWidget*>(parent);
                                   temp->Validate();
                                   is_visible = false;
                                   return;
                            }
                            else
                            {
                                   validated = true;
                                   escaped = false;
                            }
                     }
              }


              if (MouseManager::kbDOWN() && MouseManager::IsKeyArrowPressEvent())
              {
                     if ( selected < this->GetNbItem()-1)
                     {
                            selected++;
                     }

                     // selected is an unsigned int so always>=0
                     //if ((selected>=0) && (selected<=nbvisible-1))
                     if (selected<=nbvisible-1)
                     {
                            scroll=0;
                     }
                     else
                     {
                            scroll=selected-nbvisible+1;
                     }

                     TimeManager::Delay( 150 );
              }

              if (MouseManager::kbUP() && MouseManager::IsKeyArrowPressEvent())
              {
                     if (selected>0)
                     {
                            selected--;
                     }

                     // selected is an unsigned int so always>=0
                     //if ((selected>=0) && (selected<=nbvisible-1))
                     if (selected<=nbvisible-1)
                     {
                            scroll=0;
                     }
                     else
                     {
                            scroll=selected-nbvisible+1;
                     }

                     TimeManager::Delay( 150 );
              }

              for (auto& c : children )
                     c->Logic(  );
       }
}

void ListBoxWidget::Render( void )
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

                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );

                     int sh =  FontEngine::GetStringHeight( label );
                     heightline = sh*2;

                     nbvisible = (unsigned int) ((height-0) / (sh*2));

                     for(unsigned int i=scroll; i<=scroll+nbvisible-1; i++)
                     {
                            //Ongoing - to be optimised
                            if(i<nbitem)
                            {
                                   if (i!=selected)
                                   {
                                          FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );

                                          //We check if the titel can be written in the titlebar (with 5px on each side of the title
                                          if (nbvisible>=nbitem) drawablecharlabel = FontEngine::AssertStringLength( GetItem(i), width-5-25 );
                                          if (nbvisible<nbitem) drawablecharlabel = FontEngine::AssertStringLength( GetItem(i), width-5-25 );

                                          if (drawablecharlabel!=0)
                                          {
                                                 drawablelabel =  FontEngine::ReduceStringToVisible( GetItem(i), width-5 -25  );
                                                 int sh =  FontEngine::GetStringHeight( drawablelabel );
                                                 FontEngine::DrawStringLeft(  drawablelabel, xpos+8, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
                                          }
                                   }
                                   else
                                   {
                                          FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Selected );

                                          //We check if the titel can be written in the titlebar (with 5px on each side of the title
                                          if (nbvisible>=nbitem) drawablecharlabel = FontEngine::AssertStringLength( GetItem(i), width-5-25 );
                                          if (nbvisible<nbitem) drawablecharlabel = FontEngine::AssertStringLength( GetItem(i), width-5-25 );

                                          if (drawablecharlabel!=0)
                                          {
                                                 drawablelabel =  FontEngine::ReduceStringToVisible( GetItem(i), width-5 -25  );
                                                 int sh =  FontEngine::GetStringHeight( drawablelabel );

                                                 // if we can see all the item, no need for space for the escalator on the right
                                                 if (nbvisible>=nbitem) ScreenRenderer::DrawFilledRoundedRectangle(  xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-3, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, ColorEngine::GetColor(ColorEngine::Widget_Selection) );
                                                 //else we draw the selection line a bit shorter not to cover the escalator
                                                 if (nbvisible<nbitem) ScreenRenderer::DrawFilledRoundedRectangle(  xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-18, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, ColorEngine::GetColor(ColorEngine::Widget_Selection) );

                                                 FontEngine::DrawStringLeft( drawablelabel, xpos+8, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), ColorEngine::GetColor(ColorEngine::Widget_Text_Selected) );
                                          }
                                   }
                            }
                     }

                     if (nbvisible<nbitem)
                     {
                            unsigned int escalator = (height-12)*selected/nbitem;

                            if (!is_hovering)
                            {
                                   ScreenRenderer::DrawRoundedRectangle( xpos+width-15, ypos+3, xpos+width-3, ypos+height-3, 3,  ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                                   ScreenRenderer::DrawFilledCircle( xpos+width-9, ypos+9+escalator, 4,  ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                            }
                            else
                            {
                                   ScreenRenderer::DrawRoundedRectangle( xpos+width-15, ypos+3, xpos+width-3, ypos+height-3, 3,  ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                                   ScreenRenderer::DrawFilledCircle( xpos+width-9, ypos+9+escalator, 4,  ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                            }
                     }
              }
              else
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

                     ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );

                     int sh =  FontEngine::GetStringHeight( label );
                     heightline = sh*2;

                     nbvisible = (unsigned int) ((height-0) / (sh*2));

                     for(unsigned int i=scroll; i<=scroll+nbvisible-1; i++)
                     {
                            //Ongoing - to be optimised
                            if(i<nbitem)
                            {
                                   if (i!=selected)
                                   {
                                          FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );

                                          //We check if the titel can be written in the titlebar (with 5px on each side of the title
                                          if (nbvisible>=nbitem) drawablecharlabel = FontEngine::AssertStringLength( GetItem(i), width-5-25 );
                                          if (nbvisible<nbitem) drawablecharlabel = FontEngine::AssertStringLength( GetItem(i), width-5-25 );

                                          if (drawablecharlabel!=0)
                                          {
                                                 drawablelabel =  FontEngine::ReduceStringToVisible( GetItem(i), width-5 -25  );
                                                 int sh =  FontEngine::GetStringHeight( drawablelabel );
                                                 FontEngine::DrawStringLeft(  drawablelabel, xpos+8, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                                          }
                                   }
                                   else
                                   {
                                          FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );

                                          //We check if the titel can be written in the titlebar (with 5px on each side of the title
                                          if (nbvisible>=nbitem) drawablecharlabel = FontEngine::AssertStringLength( GetItem(i), width-5-25 );
                                          if (nbvisible<nbitem) drawablecharlabel = FontEngine::AssertStringLength( GetItem(i), width-5-25 );

                                          if (drawablecharlabel!=0)
                                          {
                                                 drawablelabel =  FontEngine::ReduceStringToVisible( GetItem(i), width-5 -25  );
                                                 int sh =  FontEngine::GetStringHeight( drawablelabel );

                                                 // if we can see all the item, no need for space for the escalator on the right
                                                 if (nbvisible>=nbitem) ScreenRenderer::DrawRoundedRectangle(  xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-3, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                                                 //else we draw the selection line a bit shorter not to cover the escalator
                                                 if (nbvisible<nbitem) ScreenRenderer::DrawRoundedRectangle(  xpos+3, ypos+3+(unsigned int) ((i-scroll)*(sh*2)), xpos+width-18, ypos+15+(unsigned int) ((i-scroll)*(sh*2)), 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

                                                 FontEngine::DrawStringLeft( drawablelabel, xpos+8, ypos+5+(unsigned int) ((i-scroll)*(sh*2)), ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                                          }
                                   }
                            }
                     }

                     if (nbvisible<nbitem)
                     {
                            unsigned int escalator = (height-12)*selected/nbitem;

                            ScreenRenderer::DrawRoundedRectangle( xpos+width-15, ypos+3, xpos+width-3, ypos+height-3, 3,  ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                            ScreenRenderer::DrawFilledCircle( xpos+width-9, ypos+9+escalator, 4,  ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
                     }

              }

              for (auto& c : children )
                     c->Render( );

       }
}
