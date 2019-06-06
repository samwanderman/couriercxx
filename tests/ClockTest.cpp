#include "../couriercxx/util/Clock.h"

#include <cinttypes>
#include <cstdint>

#include "../couriercxx/logger/Log.h"

int main(int ac, char** av) {
	uint64_t currentTimestamp = Clock::getTimestamp();

	Log::info("Timestamp is %" PRIu64, currentTimestamp);

	return 0;
}
