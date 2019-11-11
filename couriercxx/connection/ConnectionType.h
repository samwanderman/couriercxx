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

static const uint8_t TYPE_SERIAL_PORT			= 1;
static const uint8_t TYPE_I2C					= 2;
static const uint8_t TYPE_GPIO					= 3;
static const uint8_t TYPE_DOOR_CONTROLLER_BUS	= 4;

#endif /* COURIERCXX_CONNECTION_CONNECTIONTYPE_H_ */
