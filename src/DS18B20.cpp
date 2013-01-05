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
 * Name        : DS18B20.cpp
 * Author      : Georgi Todorov <terahz@geodar.com>
 * Version     : 
 * Created on  : Jan 3, 2013
 *
 * Copyright © 2013 Georgi Todorov <terahz@geodar.com>
 */

#include "DS18B20.h"

DS18B20::DS18B20(char* address) {
	address_ = strdup(address);
	unit_ = CELCIUS;
	char path[47]; // path should be 46 chars
	snprintf(path, 46, "%s%s%s", BUS, address_, TEMPFILE);
	devFile = fopen(path, "r");
	if (devFile == NULL) {
		printf("Count not open %s\n", path);
		throw errno;
	}
}

DS18B20::~DS18B20() {
	fclose(devFile);
}

float DS18B20::getTemp() {
	float temp = -1;
	if (devFile != NULL) {
		fseek(devFile, 0, SEEK_END);
		if (!ferror(devFile)) {
			size_t size = ftell(devFile);
			char *filecontents = (char*) malloc(sizeof(char) * size);
			rewind(devFile);
			fread(filecontents, sizeof(char), size, devFile);

			//here we depend on the file contents format
			//This will likely break when/if they make a change
			char* pch = strtok(filecontents, "\n"); // get first line
			if (pch != NULL) {
				if (strstr(pch, "YES") != NULL) { // if we have a YES in the crc proceed
					pch = strtok(NULL, "\n"); // get second line
					if (pch != NULL) {
						char * dpch = strstr(pch, "="); // get the location of the temperature, probably constant but still...
						if (dpch != NULL) {
							char tmp[] = "00000";
							strncpy(tmp, dpch + 1, 5); // store 5 digit temperature
							temp = (float) atoi(tmp) / 1000.0; // we made it!
						}
					}
				}
			}
			//cleanup
			delete[] filecontents;
		}
	}
	if (unit_ == CELCIUS) {
		return temp;
	} else
		return CtoF(temp);
}

uint8_t DS18B20::getUnits() {
	return unit_;
}

void DS18B20::setUnits(uint8_t u) {
	unit_ = u;
}

float DS18B20::CtoF(float temp) {
	return temp * 1.8 + 32;
}
