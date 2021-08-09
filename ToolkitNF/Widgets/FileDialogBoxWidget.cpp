#include "FileDialogBoxWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"

#include <stdio.h>
#include <dirent.h>
#include <string.h>


std::string simplify(std::string path)
{
       // using vector in place of stack
       std::vector<std::string> v;
       int n = path.length();
       std::string ans;
       for (int i = 0; i < n; i++)
       {
              std::string dir = "";
              // forming the current directory.
              while (i < n && path[i] != '/')
              {
                     dir += path[i];
                     i++;
              }

              // if ".." , we pop.
              if (dir == "..")
              {
                     if (!v.empty())
                            v.pop_back();
              }
              else if (dir == "." || dir == "")
              {
                     // do nothing (added for better understanding.)
              }
              else
              {
                     // push the current directory into the vector.
                     v.push_back(dir);
              }
       }

       // forming the ans
       for (auto i : v)
       {
              ans += "/" + i;
       }

       // vector is empty
       if (ans == "")
              return  std::string("/");

       return ans;
}


FileDialogBoxWidget::FileDialogBoxWidget()
{
       widgettype = "FileDialogBox";
       typedialog = FileOpen;
}

FileDialogBoxWidget::~FileDialogBoxWidget()
{
       //dtor
}


void FileDialogBoxWidget::SetDialogType( FileDialogBoxWidget::FileDialogType type )
{
       typedialog = type;
       if (type==FileOpen)
       {
              this->SetLabel( "File Open ...");
              header_text->SetLabel("Pick a folder and a file to open :");
              filelist->Enable();
              bottom_text->SetLabel("The selected file is :");
       }
       else  if (type==FileSaveAs)
       {
              this->SetLabel( "File Save As ...");
              header_text->SetLabel("Pick a folder for save location :");
              filelist->Disable();
              bottom_text->SetLabel("Name of the file (ending with .tns) :");
       }
       else  if (type==FileSave)
       {
              this->SetLabel( "File Save ...");
              header_text->SetLabel("Pick a folder for save location :");
              filelist->Disable();
              bottom_text->SetLabel("Name of the file (ending with .tns) :");
       }
}


FileDialogBoxWidget::FileDialogType FileDialogBoxWidget::GetDialogType( void )
{
       return typedialog;
}


std::string FileDialogBoxWidget::GetSelectedFilename()
{
       return fileselected;
};


std::string FileDialogBoxWidget::GetSelectedPath()
{
       return pathtoexplore;
};

std::string FileDialogBoxWidget::GetSelectedFullname()
{
       return fullname;
};


int FileDialogBoxWidget::ListDir( std::string path)
{
       std::string name;
       struct dirent *ent;
       DIR *dir = opendir(path.c_str());
       while((ent = readdir(dir)))
       {
              //Test whether it's a directory
              name = path+"/"+std::string(ent->d_name);
              DIR *test = opendir( name.c_str() );
              if(test)    // This is a directory and we add to the folder list widget
              {
                     closedir(test);
                     std::string temp(ent->d_name);
                     folderlist->AddItem( (char*) temp.c_str() );
              }
              else    // this is a file and we add to the file list widget
              {
                     std::string temp(ent->d_name);
                     filelist->AddItem( (char*) temp.c_str() );
              }
       }
       closedir(dir);
       return 0;
}


FileDialogBoxWidget::FileDialogBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ): DialogBoxWidget( l, x, y, w, h, p )
{
       widgettype = "FileDialogBox";
       typedialog = FileOpen;
       pathtoexplore = std::string( "/documents/Widget/" );

       vertical_layout = new ContainerVWidget( "ContainerV", 1, 1, 1, 1, this );

       header_text = new LabelWidget( "Pick a file",1,1,1,1, vertical_layout );
       header_text->SetAlignment( LabelWidget::Left );
       vertical_layout->AddConstraint( 10, (char*) "px" );

       horizontal_split = new ContainerHWidget( "ContainerH", 1, 1, 1, 1, vertical_layout );
       vertical_layout->AddConstraint( 100, (char*) "%" );

       folderlist = new ListBoxWidget( "Folder List",1,1,1,1, horizontal_split );
       horizontal_split->AddConstraint( 50, (char*) "%" );

       space = new SpacerWidget( "Spacer",1,1,1,1, horizontal_split );
       horizontal_split->AddConstraint( 5, (char*) "px" );

       filelist = new ListBoxWidget( "File List",1,1,1,1, horizontal_split );
       horizontal_split->AddConstraint( 50, (char*) "%" );

       bottom_text = new LabelWidget( "Selected file",1,1,1,1, vertical_layout );
       bottom_text->SetAlignment( LabelWidget::Left );
       vertical_layout->AddConstraint( 10, (char*) "px" );

       input_name = new InputWidget( ".",1,1,1,1, vertical_layout );
       input_name->SetContent( (char *) pathtoexplore.c_str() );
       vertical_layout->AddConstraint( 15, (char*) "px" );


       //TO BE REMOVED - JUST FOR TESTING
       //space = new SpacerWidget( (char*) "Spacer",1,1,1,1, vertical_layout );
       //vertical_layout->AddConstraint( 100, (char*) "%" );


       horizontal_split_button = new ContainerHWidget( "ContainerH", 1, 1, 1, 1, vertical_layout );
       vertical_layout->AddConstraint( 15, (char*) "px" );

       space2 = new SpacerWidget( "Spacer",1,1,1,1, horizontal_split_button );
       horizontal_split_button->AddConstraint( 100, (char*) "%" );

       okbutton = new ButtonWidget( "OK",1,1,1,1, horizontal_split_button );;
       horizontal_split_button->AddConstraint( 70, (char*) "px" );

       cancelbutton = new ButtonWidget( "Cancel",1,1,1,1, horizontal_split_button );;
       horizontal_split_button->AddConstraint( 70, (char*) "px" );

       ListDir( (char *) pathtoexplore.c_str() );

       this->Adjust();

}


unsigned int FileDialogBoxWidget::GetUseableXPos()
{
       return xpos + 2;
}


unsigned int FileDialogBoxWidget::GetUseableYPos()
{
       return ypos + 14;               // we just remove the size of the title bar (12px+2px = 14px)
}


unsigned int FileDialogBoxWidget::GetUseableWidth()
{
       return width - 4;
}


unsigned int FileDialogBoxWidget::GetUseableHeight()
{
       return height - 16;                // we just remove the size of the title bar (12px + 2px + 2px = 16px)
}


bool FileDialogBoxWidget::IsMouseOnTitleBar(void )
{
       return ((unsigned int) MouseManager::GetX() >= xpos+2) && ((unsigned int) MouseManager::GetY() >= ypos+2) && ((unsigned int) MouseManager::GetX() <= xpos+width-32) && ((unsigned int) MouseManager::GetY() <= ypos+12);
}


void FileDialogBoxWidget::Logic( void )
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

              if (IsMouseOnTitleBar(  ))
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


              if (folderlist->validated)
              {
                     //strcat( pathtoexplore, folderlist->getselecteditem() );
                     //strcpy(pathtoexplore, simplify(pathtoexplore) );
                     //strcat( pathtoexplore, "/" );

                     pathtoexplore = simplify(pathtoexplore+std::string(folderlist->GetSelectedItem()) )+"/";

                     folderlist->Flush();
                     filelist->Flush();
                     folderlist->validated = false;
                     ListDir( pathtoexplore );
                     input_name->SetContent( pathtoexplore.c_str() );
              }

              if (filelist->validated)
              {
                     fileselected = std::string( filelist->GetSelectedItem() );

                     filelist->validated = false;

                     fullname = pathtoexplore+fileselected;

                     input_name->SetContent( fullname.c_str() );
              }



              if (okbutton->IsPressed())
              {
                     validated = true;
                     canceled = false;
                     this->SetInvisible();
              }


              if (cancelbutton->IsPressed())
              {
                     validated = false;
                     canceled = true;
                     this->SetInvisible();
              }

              // No PopUpChild

       }
}


void FileDialogBoxWidget::Render( void )
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

