#include "ToolkitNF/GUIToolkitNF.hpp"


int main( void )
{
       WidgetApplication::Initialize();

       DesktopWidget* desktop = new DesktopWidget( "I am a Desktop", 0, 0, SCREEN_WIDTH_GUI, SCREEN_HEIGHT_GUI, nullptr );

       ButtonWidget* button = new ButtonWidget( "Hello World !!!", 25, 25, 250, 20, desktop );

#if RENDER_WITH_SDL == 1
       ButtonWidget* button2 = new ButtonWidget( "We are rendered with SDL", 25, 50, 250, 20, desktop );
#else
       ButtonWidget* button2 = new ButtonWidget( "We are rendered with GC", 25, 50, 250, 20, desktop );
#endif
       button2->Disable();


       CheckBoxWidget* check1 = new CheckBoxWidget("Check 1",  10, 75, 100, 15, desktop );
       check1->SetType( CheckBoxWidget::Cross_Tick );

       CheckBoxWidget* check2 = new CheckBoxWidget("Check 2",  10, 95, 100, 15, desktop );
       check2->SetType( CheckBoxWidget::Cross_Tick );
       check2->Disable();

       CheckBoxWidget* check3 = new CheckBoxWidget("Check 3",  10, 115, 100, 15, desktop );
       check3->SetType( CheckBoxWidget::Square_Tick );

       CheckBoxWidget* check4 = new CheckBoxWidget("Check 4",  10, 135, 100, 15, desktop );
       check4->SetType( CheckBoxWidget::Square_Tick );
       check4->Disable();

       InputWidget* input1 = new InputWidget("Input",  10, 155, 200, 20, desktop );
       input1->SetContent( "Hello, I am an INPUTWidget" );

       InputWidget* input2 = new InputWidget("Input",  10, 185, 200, 20, desktop );
       input2->SetContent( "Hello, I am an INPUTWidget (Disabled) " );
       input2->Disable();

       /*
       #if DEBUG_MODE == 1
              Debugger::Initialize();
              Debugger::SetDebuggerMode( Debugger::MaintainFlow );
              Debugger::SetDebuggerFile( "/documents/Widget/DebugOut/Img_Blit.txt.tns" );
              Debugger::OpenMaintain();
       #endif // DEBUG_MODE
       */

       WidgetApplication::AddChild( desktop );

       //WidgetApplication::SetUniformBackgroundColor( 255, 255, 0 );
       WidgetApplication::SetBackgroundPicture( "/documents/Widget/Wallpapers/002.bmp.tns" );

       /*
       #if RENDER_WITH_SDL == 1
              SDL_Surface* tigre=IMG_Load(  "/documents/Widget/Wallpapers/tigre.bmp.tns" );
       #else
              imagegc* tigre=ReadBMP(  "/documents/Widget/Wallpapers/tigre2.bmp.tns" );
       #endif


              Rect origine, destination;

              origine.x = 0;
              origine.y = 0;
              origine.w = tigre->width;
              origine.h = tigre->height;


              destination.x = 100;
              destination.y = 100;
              destination.w = 100; // tigre->width;
              destination.h = 100; //tigre->height;
       */



       WidgetApplication::PrepareForRun();


       while (!WidgetApplication::AskForClosure() && !button->IsPressed()  )
       {
              WidgetApplication::Run( WidgetApplication::Normal );

              /*
              //ScreenRenderer::DrawImage( tigre, origine, destination );

              for (int i=0; i<tigre->width; i++)
              {
                     for( int j=0; j<tigre->height; j++)
                     {
                            ScreenRenderer::DrawPixel( 100+i, 100+j, tigre->data[j*tigre->width+i] );
                     }
              }

              ScreenRenderer::DrawRectangle( destination.x, destination.y, destination.x+destination.w, destination.y+destination.h, 255, 255, 0, 255 );
              ScreenRenderer::DrawRectangle( destination.x-1, destination.y-1, destination.x+destination.w+1, destination.y+destination.h+1, 255, 255, 0, 255 );

              ScreenRenderer::DrawRectangle( destination.x, destination.y, destination.x+origine.w-origine.x, destination.y+origine.h-origine.y, 255, 0, 255, 255 );
              ScreenRenderer::DrawRectangle( destination.x-1, destination.y-1,  destination.x+origine.w-origine.x+1, destination.y+origine.h-origine.y+1, 255, 0, 255, 255 );

              ScreenRenderer::FlipScreen();
              */
       }

       /*

       #if DEBUG_MODE == 1
              Debugger::CloseMaintain();
              Debugger::Close();
       #endif // DEBUG_MODE


       #if RENDER_WITH_SDL == 1
              SDL_FreeSurface( tigre );
       #else
              free(tigre->data);
              free(tigre);
       #endif
       */


       WidgetApplication::Close();


       return 0;
}
