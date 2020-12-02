/*
 * ConcurrentMap.h
 *
 *  Created on: 23.06.2020
 *      Author: Potapov Sergei
 *       Email: potapov.sa@carddex.ru
 */

#ifndef COURIERCXX_STRUCT_CONCURRENTMAP_H_
#define COURIERCXX_STRUCT_CONCURRENTMAP_H_

#include <functional>
#include <map>
#include <mutex>
#include <utility>

/**
 * Concurrent map
 */
template<typename K, typename V>
class ConcurrentMap {
public:
	/**
	 * Empty constructor
	 */
	ConcurrentMap() { }

	/**
	 * Destructor
	 */
	virtual ~ConcurrentMap() { }

	/**
	 * Insert key-value pair
	 *
	 * \param[in] key	- key
	 * \param[in] value - value
	 */
	void insert(K key, V value) {
		std::lock_guard lock(mutex);
		container.insert(std::pair<K, V>(key, value));
	}

	/**
	 * Operator []
	 *
	 * \return found element
	 */
	V& operator[](int idx) {
		return container[idx];
	}

	/**
	 * Emplace element
	 *
	 * \param[in] key	- key
	 * \param[in] value - value
	 */
	template<typename ... Args>
	void emplace(Args&&... args) {
		std::lock_guard lock(mutex);
		container.emplace(args...);
	}

	/**
	 * Erase element
	 *
	 * \param[in] key
	 */
	void erase(K key) {
		std::lock_guard lock(mutex);
		container.erase(key);
	}

	/**
	 * Execute for each element
	 *
	 * \param[in] func - function to execute
	 */
	void forEach(std::function<void(const K& key, V& value)> func) {
		std::lock_guard lock(mutex);
		auto it = container.begin();
		while (it != container.end()) {
			func(it->first, it->second);
			it++;
		}
	}

	/**
	 * Get size
	 *
	 * \return size
	 */
	int size() {
		std::lock_guard lock(mutex);

		return container.size();
	}

private:
	std::map<K, V>	container;
	std::mutex		mutex;
};

#endif /* COURIERCXX_STRUCT_CONCURRENTMAP_H_ */
