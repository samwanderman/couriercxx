/*
 * Callback.h
 *
 *  Created on: Nov 1, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_CALLBACK_H_
#define COURIERCXX_EVENT_CALLBACK_H_

#include <cstdint>
#include <functional>

/**
 * Callback class
 *
 * FIXME - should be this merged with Listener?
 */
template<typename T>
class Callback {
public:
	/**
	 * Constructor
	 *
	 * \param[in] T event - captured event
	 * \param[in] callback - callback
	 * \param[in] uint64_t timeout - response wait timeout
	 */
	Callback(T event, std::function<void (void*, void*, void*)> callback, uint64_t timeout) {
		this->event = event;
		this->callback = callback;
		this->timeout = timeout;
		this->permanent = false;
	}

	/**
	 * Constructor
	 *
	 * \param[in] T event - captured event
	 * \param[in] callback - callback
	 * \param[in] bool permanent - do not remove after callback call
	 */
	Callback(T event, std::function<void (void*, void*, void*)> callback, bool permanent) {
		this->event = event;
		this->callback = callback;
		this->timeout = 0;
		this->permanent = permanent;
	}

	/**
	 * Constructor
	 *
	 * \param[in] T event - captured event
	 * \param[in] callback - callback
	 * \param[in] uint64_t timeout - response wait timeout
	 * \param[in] bool permanent - do not remove after callback call
	 */
	Callback(T event, std::function<void (void*, void*, void*)> callback, uint64_t timeout, bool permanent) {
		this->event = event;
		this->callback = callback;
		this->timeout = timeout;
		this->permanent = permanent;
	}

	/**
	 * Destructor
	 */
	virtual ~Callback() {}

	/**
	 * Get event
	 *
	 * \return event
	 */
	T getEvent() {
		return event;
	}

	/**
	 * Get event timeout
	 *
	 * return event timeout
	 */
	uint64_t getTimeout() {
		return timeout;
	}

	/**
	 * Get callback
	 *
	 * \return callback
	 */
	std::function<void (void*, void*, void*)>& getCallback() {
		return callback;
	}

	/**
	 * Check if callback is permanent
	 *
	 * \return true if permanent, false otherwise
	 */
	bool isPermanent() {
		return permanent;
	}

private:
	uint64_t timeout = 0;
	T event;
	std::function<void (void*, void*, void*)> callback;
	bool permanent = false;
};

#endif /* COURIERCXX_EVENT_CALLBACK_H_ */
