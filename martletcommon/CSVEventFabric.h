#ifndef CSVEVENTFABRIC_H
#define CSVEVENTFABRIC_H

#include "AbstractEventFabric.h"

class CSVEventFabric : public AbstractEventFabric
{
	Q_OBJECT

public:
	CSVEventFabric(QObject *parent = 0);
	~CSVEventFabric();

private:
	
};

#endif // CSVEVENTFABRIC_H
