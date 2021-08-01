#include "ToolkitNF/GUIToolkitNF.hpp"


int main( void )
{
       /*
           bool output = KeyManager::kbA();
           //std::cout << output << std::endl;
           printf("Before modif : %d \n", output);

           Widget *temp = new Widget();

           printf("\n");
           KeyManager::Logic();


           output = KeyManager::kbA();
           //std::cout << output << std::endl;
           printf("After modif : %d \n", output);


           printf("\n");
           KeyManager::ResetState();


           output = KeyManager::kbA();
           //std::cout << output << std::endl;
           printf("After 2nd modif : %d \n", output);


           temp->ChangeKey( true );
           temp->ChangeKey( false );
           temp->ChangeKey( true );
           temp->ChangeKey( false );

           delete temp;

           Draw();

           //std::cin.get();
           //getchar();
       */



       MouseManager::Initialize();
       KeyManager::Initialize();

       MouseManager::SetSensibility( 2.0f );

       while (!(KeyManager::kbESC_Release_Event()  && KeyManager::kbCTRL() ))
       {
              MouseManager::Logic();
              KeyManager::Logic();
              printf("Mouse position : X=%d - Y=%d - B=%d \n", MouseManager::GetX(), MouseManager::GetY(), MouseManager::GetB() );
       }


       ScreenRenderer::Initialize();
       DepthBufferRenderer::Initialize();

       //FontEngine *font = new FontEngine();

       FontEngine::Initialize();

       ScreenRenderer::DrawFilledRoundedRectangle( 20, 20, 300, 220, 10, 255, 0, 0, 255 );
       ScreenRenderer::DrawFilledRoundedRectangle( 40, 40, 280, 200, 10, 0, 255, 0, 255 );
       ScreenRenderer::DrawFilledRoundedRectangle( 60, 60, 260, 180, 10, 0, 0, 255, 255 );

       DepthBufferRenderer::DrawFilledCircle( 160, 120, 100, 255, 255, 255, 255 );

       //       ScreenRenderer::DrawCircle( 30, 30, 10, 255, 255, 0, 255);
       //       ScreenRenderer::DrawFilledCircle( 30, 210, 10, 255, 255, 0, 255);
       //       ScreenRenderer::DrawCircle( 290, 30, 10, 255, 0, 255, 255);
       //       ScreenRenderer::DrawFilledCircle( 290, 210, 10, 255, 0, 255, 255);

       ScreenRenderer::FlipScreen();

       MouseManager::SetCursorType( MouseManager::Cursor_Handfinger );

       while (!(KeyManager::kbESC()  && KeyManager::kbCTRL() && KeyManager::kbSHIFT() ))
       {
              MouseManager::Logic();
              KeyManager::Logic();

              {
                     // this is here to simulate the GUI rendering process

                     ScreenRenderer::DrawFilledRectangle( 0, 0, 320, 240, 255, 255, 255, 255 );

                     ScreenRenderer::DrawFilledRoundedRectangle( 20, 20, 300, 220, 10, 255, 0, 0, 255 );
                     ScreenRenderer::DrawFilledRoundedRectangle( 40, 40, 280, 200, 10, 0, 255, 0, 255 );
                     ScreenRenderer::DrawFilledRoundedRectangle( 60, 60, 260, 180, 10, 0, 0, 255, 255 );

                     DepthBufferRenderer::DrawFilledCircle( 160, 120, 100, 255, 255, 255, 255 );
              }


              MouseManager::Render();

              ScreenRenderer::FlipScreen();

       }

       ScreenRenderer::TakeScreenShot();
       DepthBufferRenderer::TakeScreenShot();


       FontEngine::SetCurrentSpacing(1,0);
       FontEngine::DrawStringLeft( "Hello World",10, 10, 0,0,0,255);

       ScreenRenderer::FlipScreen();

       DepthBufferRenderer::ClearScreen( 0, 0, 0, 0 );

       ScreenRenderer::TakeScreenShot();
       DepthBufferRenderer::TakeScreenShot();


       while (!KeyManager::kbMENU())
       {
              KeyManager::Logic();
       }

       while (!KeyManager::kbMENU())
       {
              KeyManager::Logic();
       }

       printf("RGB=%d - R=%d - G=%d - B=%d \n", ScreenRenderer::GetPixel(10,10), ScreenRenderer::GetPixelR(10,10), ScreenRenderer::GetPixelG(10,10), ScreenRenderer::GetPixelB(10,10) );
       printf("RGB=%d - R=%d - G=%d - B=%d \n", ScreenRenderer::GetPixel(20,20), ScreenRenderer::GetPixelR(20,20), ScreenRenderer::GetPixelG(20,20), ScreenRenderer::GetPixelB(20,20) );
       printf("RGB=%d - R=%d - G=%d - B=%d \n", ScreenRenderer::GetPixel(40,40), ScreenRenderer::GetPixelR(40,40), ScreenRenderer::GetPixelG(40,40), ScreenRenderer::GetPixelB(40,40) );
       printf("RGB=%d - R=%d - G=%d - B=%d \n", ScreenRenderer::GetPixel(60,60), ScreenRenderer::GetPixelR(60,60), ScreenRenderer::GetPixelG(60,60), ScreenRenderer::GetPixelB(60,60) );


       while (!KeyManager::kbSCRATCH())
       {
              KeyManager::Logic();
       }



       while (!(KeyManager::kbESC()  && KeyManager::kbCTRL() ))
       {
              KeyManager::Logic();

       }


       ScreenRenderer::ClearScreen( 0, 0, 0, 0 );
       DepthBufferRenderer::ClearScreen( 0, 0, 0, 0 );


       ScreenRenderer::TakeScreenShot();
       DepthBufferRenderer::TakeScreenShot();






       MouseManager::Close();
       ScreenRenderer::Close();





       return 0;
}
