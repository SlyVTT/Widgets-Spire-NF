#ifndef FILEDIALOGBOX_H
#define FILEDIALOGBOX_H

#include "DialogBoxWidget.hpp"
#include "ContainerHWidget.hpp"
#include "ContainerVWidget.hpp"
#include "ButtonWidget.hpp"
#include "InputWidget.hpp"
#include "ListBoxWidget.hpp"
#include "SpacerWidget.hpp"
#include "LabelWidget.hpp"


class FileDialogBoxWidget : public DialogBoxWidget
{
public:
    FileDialogBoxWidget();
    FileDialogBoxWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p );
    virtual ~FileDialogBoxWidget();

    virtual void Logic( void ) override;

    virtual void Render( void ) override;

    enum FileDialogType
    {
        FileOpen = 0,
        FileSaveAs = 1,
        FileSave = 2
    };

    // These methods must be override cause window geometry is a bit different with the title bar
    virtual unsigned int GetUseableXPos( void ) override;
    virtual unsigned int GetUseableYPos( void ) override;
    virtual unsigned int GetUseableWidth( void ) override;
    virtual unsigned int GetUseableHeight( void ) override;

    virtual void SetDialogType( FileDialogBoxWidget::FileDialogType type );
    virtual FileDialogBoxWidget::FileDialogType GetDialogType( void );



    bool validated = false;
    bool canceled = false;

    virtual std::string GetSelectedFilename( void );
    virtual std::string GetSelectedPath( void );
    virtual std::string GetSelectedFullname( void );

protected:
    bool IsMouseOnTitleBar(void ) override;
    std::string pathtoexplore;
    std::string fileselected;
    std::string fullname;

    ContainerVWidget *vertical_layout;
    LabelWidget *header_text;
    LabelWidget *bottom_text;
    ContainerHWidget *horizontal_split;
    InputWidget *input_name;
    ContainerHWidget *horizontal_split_button;
    ListBoxWidget *filelist;
    ListBoxWidget *folderlist;
    SpacerWidget *space;
    SpacerWidget *space2;
    ButtonWidget *okbutton;
    ButtonWidget *cancelbutton;

private:
    int ListDir(std::string path);
    FileDialogType typedialog;
};

#endif // FILEDIALOGBOX_H
