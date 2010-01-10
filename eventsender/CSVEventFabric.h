#ifndef CSVEVENTFABRIC_H
#define CSVEVENTFABRIC_H

#include "AbstractEventFabric.h"

class CSVEventFabric : public AbstractEventFabric
{
	Q_OBJECT

public:
	CSVEventFabric(QObject *parent);
	~CSVEventFabric();

private:
	
};

#endif // CSVEVENTFABRIC_H
