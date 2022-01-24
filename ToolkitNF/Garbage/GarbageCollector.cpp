#include "GarbageCollector.hpp"

GarbageCollector::GarbageCollector()
{
    //ctor
}

GarbageCollector& GarbageCollector::Get( void )
{
       static GarbageCollector m_garbage;
       return m_garbage;
}

void GarbageCollector::InternalInitialize( void )
{

}

void GarbageCollector::InternalRegisterWidget( uint32_t identifier, std::string type, Widget* pointer )
{

    WidgetItem *temp = new WidgetItem;

    temp->ID = identifier;
    temp->WidgetType = type;
    temp->PointerToWidget = pointer;
    temp->Status = GarbageCollector::NothingToDo;

    WidgetBucket.push_back( temp );

}

void GarbageCollector::InternalMarkWidgetForDeletion( uint32_t identifier )
{
    // TO DO : We need to run through the collection and search for the Widget to be unregister.
    // when found, we need to mark the status as for deletion
    for( auto &c: WidgetBucket )
    {
        if (c->ID == identifier )
        {
            c->Status = GarbageCollector::ToBeDeleted;
        }
    }
}


bool _mustBeDeleted( GarbageCollector::WidgetItem* item )
{
    return (item->Status == GarbageCollector::ToBeDeleted);
}

void GarbageCollector::InternalTrashGarbage( void )
{
    for( auto &c: WidgetBucket )
    {
        if (c->Status == GarbageCollector::ToBeDeleted )
        {
            delete( c->PointerToWidget );
        }
    }
    WidgetBucket.remove_if( _mustBeDeleted );
}

void GarbageCollector::InternalClose( void )
{
    for( auto &c: WidgetBucket )
    {
        c->Status = GarbageCollector::ToBeDeleted;
        delete( c->PointerToWidget );
    }
    WidgetBucket.remove_if( _mustBeDeleted );
}
