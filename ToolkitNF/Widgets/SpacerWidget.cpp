#include "SpacerWidget.hpp"

SpacerWidget::SpacerWidget()
{
    widgettype = "Spacer";
    //strcpy( widgettype, (char*) "Spacer");
};

SpacerWidget::SpacerWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "Spacer";
    //strcpy( widgettype, (char*) "Spacer");
};

SpacerWidget::~SpacerWidget()
{

};


void SpacerWidget::Logic( void )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->Logic( );
    }
}

void SpacerWidget::Render( void )
{
    if (is_visible)
    {
        for (auto& c : children )
            c->Render( );
    }
}
