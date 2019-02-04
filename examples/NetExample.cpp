#include "../couriercxx/logger/Log.h"
#include "../couriercxx/net/Net.h"

int main(int c, char** av) {
	Log::setAppName(&av[0][2]);

	Net::Addr addr;
	if (Net::get(addr) == -1) {
		Log::error("Net.get() error");

		return -1;
	}
	Log::info("Net.get() success");
	Log::info("ip: %u.%u.%u.%u\r\nmask: %u.%u.%u.%u\r\ngateway: %u.%u.%u.%u", addr.ip[0], addr.ip[1], addr.ip[2], addr.ip[3], addr.mask[0], addr.mask[1], addr.mask[2], addr.mask[3], addr.gateway[0], addr.gateway[1], addr.gateway[2], addr.gateway[3]);

	return 0;
}
