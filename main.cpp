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



//       MouseManager::Initialize();
       KeyManager::Initialize();

/*       MouseManager::SetSensibility( 8.0f );

       while (!(KeyManager::kbESC_Release_Event()  && KeyManager::kbCTRL() ))
       {
              MouseManager::Logic();
              KeyManager::Logic();
              printf("Mouse position : X=%d - Y=%d - B=%d \n", MouseManager::GetX(), MouseManager::GetY(), MouseManager::GetB() );
       }
*/

       Renderer::Initialize();

       FontEngine *font = new FontEngine();

       Renderer::DrawFilledRoundedRectangle( 20, 20, 300, 220, 10, 255, 0, 0, 255 );
       Renderer::DrawFilledRoundedRectangle( 40, 40, 280, 200, 10, 0, 255, 0, 255 );
       Renderer::DrawFilledRoundedRectangle( 60, 60, 260, 180, 10, 0, 0, 255, 255 );

//       Renderer::DrawCircle( 30, 30, 10, 255, 255, 0, 255);
//       Renderer::DrawFilledCircle( 30, 210, 10, 255, 255, 0, 255);
//       Renderer::DrawCircle( 290, 30, 10, 255, 0, 255, 255);
//       Renderer::DrawFilledCircle( 290, 210, 10, 255, 0, 255, 255);

        font->SetSpacing(1,0);
        font->DrawStringLeft( "Hello World" ,10, 10, 0,0,0,255);

        Renderer::FlipScreen();

               while (!KeyManager::kbMENU())
       {
              KeyManager::Logic();
       }

/*               while (!KeyManager::kbMENU())
       {
              KeyManager::Logic();
       }

        printf("RGB=%d - R=%d - G=%d - B=%d \n", Renderer::GetPixel(10,10), Renderer::GetPixelR(10,10), Renderer::GetPixelG(10,10), Renderer::GetPixelB(10,10) );
        printf("RGB=%d - R=%d - G=%d - B=%d \n", Renderer::GetPixel(20,20), Renderer::GetPixelR(20,20), Renderer::GetPixelG(20,20), Renderer::GetPixelB(20,20) );
        printf("RGB=%d - R=%d - G=%d - B=%d \n", Renderer::GetPixel(40,40), Renderer::GetPixelR(40,40), Renderer::GetPixelG(40,40), Renderer::GetPixelB(40,40) );
        printf("RGB=%d - R=%d - G=%d - B=%d \n", Renderer::GetPixel(60,60), Renderer::GetPixelR(60,60), Renderer::GetPixelG(60,60), Renderer::GetPixelB(60,60) );


       while (!KeyManager::kbSCRATCH())
       {
              KeyManager::Logic();
       }
*/
       while (!(KeyManager::kbESC()  && KeyManager::kbCTRL() ))
       {
              KeyManager::Logic();
       }


           Renderer::ClearScreen( 0, 0, 0, 0 );

/*
       while (!KeyManager::kbMENU())
       {
              KeyManager::Logic();
       }
*/

       Renderer::Close();





       return 0;
}
