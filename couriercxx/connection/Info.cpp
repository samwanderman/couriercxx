/*
 * Info.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Info.h"

namespace Connection {

Info::Info(int32_t id_, std::string name_, Timeout commandTimeout_, bool reconnectOnErrors_, Timeout reconnectTimeout_) : id(id_), name(name_), commandTimeout(commandTimeout_), reconnectOnErrors(reconnectOnErrors_), reconnectTimeout(reconnectTimeout_) { }

Info::Info(int32_t id, std::string name, Timeout commandTimeout) : Info(id, name, commandTimeout, false, -1) { }

Info::Info(int32_t id) : Info(id, "", -1, false, -1) { }

Info::Info() { }

}
