/*
 * IConcurrentDatasource.h
 *
 *  Created on: 13.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_ICONCURRENTDATASOURCE_H_
#define COURIERCXX_CONNECTION_ICONCURRENTDATASOURCE_H_

#include "IDatasource.h"

/**
 * Concurrent datasource interface
 */
class IConcurrentDatasource: public IDatasource {
public:
	/**
	 * Constructor
	 */
	IConcurrentDatasource() { };

	/**
	 * Destructor
	 */
	virtual ~IConcurrentDatasource() { };

	/**
	 * Lock datasource
	 */
	virtual void lock() { };

	/**
	 * Unlock datasource
	 */
	virtual void unlock() { };
};

#endif /* COURIERCXX_CONNECTION_ICONCURRENTDATASOURCE_H_ */
