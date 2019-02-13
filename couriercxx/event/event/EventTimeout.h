/*
 * EventTimeout.h
 *
 *  Created on: 13.02.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_EVENT_EVENTTIMEOUT_H_
#define COURIERCXX_EVENT_EVENT_EVENTTIMEOUT_H_

#include "../IEvent.h"

/**
 * Timeout event
 */
class EventTimeout : public IEvent {
public:
	EventTimeout();
	virtual ~EventTimeout();
};

#endif /* COURIERCXX_EVENT_EVENT_EVENTTIMEOUT_H_ */
