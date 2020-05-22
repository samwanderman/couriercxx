/*
 * ConversionErrorException.h
 *
 *  Created on: 22.05.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef COURIERCXX_EXCEPTION_CONVERSIONERROREXCEPTION_H_
#define COURIERCXX_EXCEPTION_CONVERSIONERROREXCEPTION_H_

#include <exception>

/**
 * Conversion error exception
 */
struct ConversionErrorException : public std::exception {
	/**
	 * Error description
	 */
	const char* what() const throw();
};

#endif /* COURIERCXX_EXCEPTION_CONVERSIONERROREXCEPTION_H_ */
