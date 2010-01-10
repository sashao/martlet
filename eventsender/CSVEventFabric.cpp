#include "CSVEventFabric.h"
#include "CSVCommand.h"

CSVEventFabric::CSVEventFabric(QObject *parent)
	: AbstractEventFabric(parent)
{
	registerCommand( new CSVMousePressCommand(this) );
	registerCommand( new CSVMouseReleaseCommand(this) );
}

CSVEventFabric::~CSVEventFabric()
{

}
