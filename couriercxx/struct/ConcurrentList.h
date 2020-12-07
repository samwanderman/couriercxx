/*
 * ConcurrentList.h
 *
 *  Created on: 23.06.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef COURIERCXX_STRUCT_CONCURRENTLIST_H_
#define COURIERCXX_STRUCT_CONCURRENTLIST_H_

#include <functional>
#include <list>
#include <mutex>

/**
 * Concurrent list
 */
template<typename T>
class ConcurrentList {
public:
	/**
	 * Empty constructor
	 */
	ConcurrentList() { }

	/**
	 * Destructor
	 */
	virtual ~ConcurrentList() { }

	/**
	 * Get vector size
	 *
	 * \return vector size
	 */
	int size() {
		std::lock_guard<decltype(mutex)> lock(mutex);

		return container.size();
	}

	/**
	 * Push element in the end of vector
	 *
	 * \param[in] value - value
	 */
	void pushBack(T& value) {
		std::lock_guard<decltype(mutex)> lock(mutex);

		container.push_back(value);
	}

	/**
	 * Remove element by value
	 *
	 * \param[in] value - value
	 */
	void remove(T& value) {
		std::lock_guard<decltype(mutex)> lock(mutex);

		auto it = container.begin();
		while (it != container.end()) {
			if (*it == value) {
				auto tmp = it;
				it++;
				container.erase(tmp);

				continue;
			}

			it++;
		}
	}

	/**
	 * Execute function for each element
	 *
	 * \param[in] func - function to execute
	 */
	void forEach(std::function<void(T& value)> func) {
		std::lock_guard<decltype(mutex)> lock(mutex);

		auto it = container.begin();
		while (it != container.end()) {
			func(*it);

			it++;
		}
	}

private:
	std::list<T>	container;
	std::mutex		mutex;
};

#endif /* COURIERCXX_STRUCT_CONCURRENTLIST_H_ */
