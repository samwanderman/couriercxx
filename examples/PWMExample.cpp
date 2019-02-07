#include "../couriercxx/logger/Log.h"
#include "../couriercxx/sound/PWM.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	PWM* pwm = new PWM(0, 0);
	if (pwm->open() == -1) {
		Log::error("PWM.open() error");

		delete pwm;

		return -1;
	}
	Log::debug("PWM.open() success");

	if (pwm->play(1000) == -1) {
		Log::error("PWM.play() error");
	} else {
		Log::debug("PWM.play() success");
	}

	if (pwm->close() == -1) {
		Log::error("PWM.close() error");

		delete pwm;

		return -1;
	}
	Log::debug("PWM.close() success");

	delete pwm;

	return 0;
}
