/*
 * ConvertFailureException.cpp
 *
 *  Created on: 22 мая 2020 г.
 *      Author: user
 */

#include "ConversionErrorException.h"

const char* ConversionErrorException::what() const throw(){
	return "Conversion Error";
}
