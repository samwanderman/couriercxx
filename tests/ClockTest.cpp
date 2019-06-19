#include "../couriercxx/util/Clock.h"

#include <cinttypes>
#include <cstdint>

#include "../couriercxx/logger/Log.h"

int main(int ac, char** av) {
	uint64_t currentTimestamp = Clock::getTimestamp();

	Log::info("Timestamp is %" PRIu64 " in milliseconds", currentTimestamp);

	uint64_t currentTimestampExt = Clock::getTimestampExt();

	Log::info("Timestamp is %" PRIu64 " in microseconds", currentTimestampExt);

	Time t = Clock::getTime();

	Log::info("Time: %04u-%02u-%02u %02u-%02u-%02u (GMT+%02u), timestamp %" PRIu64, t.year, t.month, t.date, t.hour, t.minute, t.second, t.gmt, t.getTimestamp());

	t.hour += 1;

	Clock::setTime(t);

	return 0;
}
