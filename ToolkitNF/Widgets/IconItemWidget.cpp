#include "IconItemWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


#if RENDER_WITH_SDL == 1
    #include <SDL/SDL_image.h>
#else

#endif

IconItemWidget::IconItemWidget()
{
       widgettype =  "IconItem";
       //strcpy( widgettype, (char*) "IconItem");
};

IconItemWidget::IconItemWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : ButtonWidget( l, x, y, w, h, p )
{
       widgettype = "IconItem";
       //strcpy( widgettype, (char*) "IconItem");
};

IconItemWidget::~IconItemWidget()
{
#if RENDER_WITH_SDL == 1

       if (icon)  SDL_FreeSurface( icon );

#else

       if (icon)
       {
              free( icon->data);
              free( icon );
              icon = nullptr;
       }

#endif


}


bool IconItemWidget::IsPressed( void )
{
       return is_pressed;
}

void IconItemWidget::Disable( void )
{
       is_enabled = false;

       if (icondisableset == 1)
       {
#if RENDER_WITH_SDL == 1

              if (icon)  SDL_FreeSurface( icon );
              icon = IMG_Load( iconnamedisable.c_str() );

#else

              if (icon)
              {
                     free( icon->data);
                     free( icon );
                     icon = nullptr;
              }

              icon = ReadBMP(  iconnamedisable.c_str() );

#endif

       }

       for (auto& c : children ) c->Disable( );
}


void IconItemWidget::Enable( void )
{
       is_enabled = true;

       if (iconenableset == 1)
       {

#if RENDER_WITH_SDL == 1

              if (icon)  SDL_FreeSurface( icon );
              icon = IMG_Load( iconnameenable.c_str() );

#else

              if (icon)
              {
                     free( icon->data);
                     free( icon );
                     icon = nullptr;
              }

              icon = ReadBMP(  iconnameenable.c_str() );

#endif


       }

       for (auto& c : children ) c->Enable( );
}

void IconItemWidget::AssignIconEnable( std::string filename )
{
       iconnameenable = filename;
       iconenableset = 1;

#if RENDER_WITH_SDL == 1

       if (icon)  SDL_FreeSurface( icon );
       icon = IMG_Load( iconnameenable.c_str() );

#else

       if (icon)
       {
              free( icon->data);
              free( icon );
              icon = nullptr;
       }

       icon = ReadBMP(  iconnameenable.c_str() );

#endif


}


void IconItemWidget::AssignIconDisable( std::string filename )
{
       iconnamedisable = filename;
       icondisableset = 1;
}


void IconItemWidget::Logic(  )
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
                     if (clickfunction)
                            clickfunction( (char*) "test" );

                     mouse_hold_down = true;
              }
              else if (currently_pressed && is_ticked )
              {
                     if (releasefunction)
                            releasefunction( (char*) "test" );

                     mouse_hold_down = true;
              }
              else if (is_hovering)
              {
                     if (hoverfunction)
                            hoverfunction( (char*) "test" );
              }

              is_pressed = currently_pressed;

              for (auto& c : children ) c->Logic( );
       }
}

void IconItemWidget::Render(  )
{
       if (is_visible)
       {
              if (is_enabled)
              {
                     ScreenRenderer::DrawFilledRoundedRectangle( xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

                     if (!is_hovering)
                     {
                            ScreenRenderer::DrawRoundedRectangle( xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
                     }
                     else
                     {
                            ScreenRenderer::DrawRoundedRectangle( xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
                     }
              }

              //if (icon_enable)
              if (icon)
              {
                     Rect src_rect, screen_pos;

                     src_rect.x = 0;
                     src_rect.y = 0;
                     src_rect.w = 16;
                     src_rect.h = 16;

                     screen_pos.x = xpos+2;
                     screen_pos.y = ypos+2;
                     screen_pos.w = 16;
                     screen_pos.h = 16;

                     ScreenRenderer::DrawImage (icon, src_rect, screen_pos);
              }
              else
              {
                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-2 -2  );

                            int sl =  FontEngine::GetStringWidth( drawablelabel );
                            int sh =  FontEngine::GetStringHeight( drawablelabel );

                            FontEngine::DrawStringLeft( drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
                     }
              }
       }
       else
       {
              ScreenRenderer::DrawFilledRoundedRectangle( xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );
              //Border of the button is black cause it is disabled
              ScreenRenderer::DrawRoundedRectangle( xpos+1, ypos+1, xpos+width-2, ypos+height-2, 3-1, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );
              //if (icon_disable)
              if (icon)
              {
                     Rect src_rect, screen_pos;

                     src_rect.x = 0;
                     src_rect.y = 0;
                     src_rect.w = 16;
                     src_rect.h = 16;

                     screen_pos.x = xpos+2;
                     screen_pos.y = ypos+2;
                     screen_pos.w = 16;
                     screen_pos.h = 16;

                     ScreenRenderer::DrawImage (icon, src_rect, screen_pos);
              }
              else
              {
                     // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
                     FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );
                     drawablecharlabel =  FontEngine::AssertStringLength( label, width-2-2 );

                     if (drawablecharlabel!=0)
                     {
                            drawablelabel =  FontEngine::ReduceStringToVisible( label, width-2 -2  );

                            int sl =  FontEngine::GetStringWidth( drawablelabel );
                            int sh =  FontEngine::GetStringHeight( drawablelabel );

                            FontEngine::DrawStringLeft( drawablelabel, xpos+(width-sl)/2, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
                     }
              }
       }

       for (auto& c : children ) c->Render(  );
}
