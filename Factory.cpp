/*
 * Factory.cpp
 *
 *  Created on: 30 nov 2015
 *      Author: valerio
 */

#include <iostream>

#include "Factory.h"
#include "BasicFactory.h"

Factory* Factory::getFactory(int typecode) {
	switch (typecode) {
		case 1:
			return new BasicFactory;
			break;
		default:
			return nullptr;
			break;
	}
}

Factory::~Factory() {}
