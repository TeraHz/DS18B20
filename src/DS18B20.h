/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Name        : DS18B20.h
 * Author      : Georgi Todorov <terahz@geodar.com>
 * Version     : 
 * Created on  : Jan 3, 2013
 *
 * Copyright © 2013 Georgi Todorov <terahz@geodar.com>
 */

#ifndef DS18B20_H_
#define DS18B20_H_
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define CELCIUS 0
#define FAHRENHEIT 1
#define BUS "/sys/bus/w1/devices/"
#define TEMPFILE "/w1_slave"

class DS18B20 {
public:
	DS18B20(const char* address);
	virtual ~DS18B20();
	uint8_t getUnits();
	void setUnits(uint8_t);
	float getTemp();
	float CtoF(float);
private:
	uint8_t unit_;
	char* address_;
	char path[47]; // path should be 46 chars

};

#endif /* DS18B20_H_ */
