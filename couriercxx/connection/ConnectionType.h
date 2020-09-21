/*
 * ConnectionType.h
 *
 *  Created on: 11.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_CONNECTIONTYPE_H_
#define COURIERCXX_CONNECTION_CONNECTIONTYPE_H_

#include <cstdint>

typedef uint8_t ConnectionType;

static const ConnectionType CONNECTION_TYPE_UNDEFINED	= 0;
static const ConnectionType CONNECTION_TYPE_SERIAL		= 1;
static const ConnectionType CONNECTION_TYPE_I2C			= 2;
static const ConnectionType CONNECTION_TYPE_GPIO		= 3;
static const ConnectionType CONNECTION_TYPE_SERIAL_BUS	= 4;
static const ConnectionType CONNECTION_TYPE_ETHERNET	= 5;

#endif /* COURIERCXX_CONNECTION_CONNECTIONTYPE_H_ */
