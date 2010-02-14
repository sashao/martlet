#include "CSVEventFabric.h"
#include "CSVCommand.h"

CSVEventFabric::CSVEventFabric(QObject *parent)
	: AbstractEventFabric(parent)
{
	registerCommand( new CSVMousePressCommand(this) );
	registerCommand( new CSVMouseReleaseCommand(this) );
	registerCommand( new CSVMouseMoveCommand(this) );
//	registerCommand( new CSVMouseEnterCommand(this) );
//	registerCommand( new CSVMouseLeaveCommand(this) );
}

CSVEventFabric::~CSVEventFabric()
{

}