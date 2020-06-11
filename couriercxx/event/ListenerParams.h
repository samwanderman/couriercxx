/*
 * ListenerParams.h
 *
 *  Created on: 13.02.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_LISTENERPARAMS_H_
#define COURIERCXX_EVENT_LISTENERPARAMS_H_

#include <cstdint>

/**
 * Params from IListener
 */
struct ListenerParams {
	uint64_t	timeout		= ~0;
	bool		execOnce	= false;
};
typedef struct ListenerParams ListenerParams;

#endif /* COURIERCXX_EVENT_LISTENERPARAMS_H_ */
