/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "bme280.h"
using namespace std::chrono;
using namespace sixtron;
namespace {
#define PERIOD_MS 1000ms
#define BME280_adresse 0x76 << 1
I2C bus(I2C1_SDA,I2C1_SCL); 
BME280 CapteurBME280(&bus, BME280::I2CAddress::Address1);
}

int main()
{
	CapteurBME280.initialize();
	CapteurBME280.set_sampling();

	while (true) {
		
		
		float temperature = CapteurBME280.temperature();
    	
        printf("Temperature: %.2f °C \n", temperature);
		ThisThread::sleep_for(PERIOD_MS);
	}
}
