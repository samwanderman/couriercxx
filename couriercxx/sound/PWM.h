/*
 * PWM.h
 *
 *  Created on: Oct 17, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_SOUND_PWM_H_
#define COURIERCXX_SOUND_PWM_H_

#include <cstdint>

/**
 * Play sound through pwm system
 */
class PWM {
public:
	/**
	 * Constructor
	 *
	 * \param[in] uint8_t chipId - chip identificator
	 * \param[in] uint16_t channelId - channel identificator
	 */
	PWM(uint8_t chipId, uint16_t channelId);

	/**
	 * Destructor
	 */
	virtual ~PWM();

	/**
	 * Open device
	 *
	 * \return -1 if error, 0 if success
	 */
	int open();

	/**
	 * Close device
	 *
	 * \return -1 if error, 0 if success
	 */
	int close();

	/**
	 * Play sound [duration] msec
	 *
	 * \param[in] uint32_t duration - sound duration in msec
	 *
	 * \return 0 if success, -1 if error
	 */
	int play(uint32_t duration);

private:
	uint8_t chipId = 0;
	uint16_t channelId = 0;
};

#endif /* COURIERCXX_SOUND_PWM_H_ */
