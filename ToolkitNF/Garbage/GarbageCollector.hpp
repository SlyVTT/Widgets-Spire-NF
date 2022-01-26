#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H

#include "../Widgets/Widget.hpp"
#include <list>
#include <string>

class WidgetItem;

class GarbageCollector
{
public:

    enum StatusItem
    {
        NothingToDo = 0,
        ToBeDeleted = 1,
    };


    GarbageCollector( GarbageCollector& ) = delete;
    GarbageCollector& operator= (const GarbageCollector&) = delete;

    static GarbageCollector& Get( void );
    static void RegisterWidget( uint32_t identifier, std::string type, Widget* pointer )
    {
        Get().InternalRegisterWidget( identifier, type, pointer );
    };
    static void MarkWidgetForDeletion( uint32_t identifier )
    {
        Get().InternalMarkWidgetForDeletion( identifier );
    };

    static void Initialize( void )
    {
        Get().InternalInitialize();
    };

    static void TrashGarbage( void )
    {
        Get().InternalTrashGarbage();
    };
    static void Close( void )
    {
        Get().InternalClose();
    };


protected:

private:
    GarbageCollector();

    static GarbageCollector m_garbage;

    std::list<WidgetItem*> WidgetBucket;

    void InternalRegisterWidget( uint32_t identifier, std::string type, Widget* pointer );
    void InternalMarkWidgetForDeletion( uint32_t identifier );

    void InternalInitialize( void );

    void InternalTrashGarbage( void );
    void InternalClose( void );
};


class WidgetItem
{
public:

    WidgetItem() {};
    ~WidgetItem() {};

    uint32_t ID;
    std::string WidgetType;
    Widget* PointerToWidget;
    GarbageCollector::StatusItem Status;
};

#endif // GARBAGECOLLECTOR_H
