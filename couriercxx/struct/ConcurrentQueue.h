/*
 * ConcurrentQueue.h
 *
 *  Created on: 7.07.2020
 *      Author: Potapov Sergei
 *       Email: potapov.sa@carddex.ru
 */

#ifndef COURIERCXX_STRUCT_CONCURRENTQUEUE_H_
#define COURIERCXX_STRUCT_CONCURRENTQUEUE_H_

#include <memory>
#include <mutex>
#include <queue>

/**
 * Concurrent queue class
 */
template <typename T>
class ConcurrentQueue {
public:
	/**
	 * Constructor
	 */
	ConcurrentQueue() { }

	/**
	 * Destructor
	 */
	virtual ~ConcurrentQueue() { }

	/**
	 * Get size
	 *
	 * \return size
	 */
	int size() {
		std::lock_guard lock(mutex);

		return container.size();
	}

	/**
	 * Push item to queue
	 *
	 * \param[in] item - item to push
	 */
	void push(T& item) {
		std::lock_guard lock(mutex);

		container.push(item);
	}

	/**
	 * Get element from queue
	 *
	 * \return
	 * 		- shared pointer to item if success
	 * 		- nullptr if error
	 */
	std::shared_ptr<T> pop() {
		std::lock_guard lock(mutex);

		if (container.size() > 0) {
			auto it = std::make_shared<T>(std::move(container.front()));

			container.pop();

			return it;
		}

		return nullptr;
	}

private:
	std::queue<T>			container;
	std::mutex				mutex;
};

#endif /* COURIERCXX_STRUCT_CONCURRENTQUEUE_H_ */
