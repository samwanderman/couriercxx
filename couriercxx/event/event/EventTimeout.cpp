/*
 * EventTimeout.cpp
 *
 *  Created on: 13.02.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "EventTimeout.h"

#include "../IEvent.h"

EventTimeout::EventTimeout() : IEvent(IEvent::EVENT_TIMEOUT) { }

EventTimeout::~EventTimeout() { }
