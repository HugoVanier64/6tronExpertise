/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
using namespace std::chrono;
namespace {
#define PERIOD_MS 1000ms
#define BME280_adresse 0x76 << 1
I2C bus(I2C1_SDA,I2C1_SCL);  // Numéro de la broche du bouton
}


int main()
{
	
	
	while (true) {
		char tempRegMeasCtrl = 0xF4;
    	char modeNormal = 0b00100111;

    	bus.write(BME280_adresse, &tempRegMeasCtrl, 1);
    	bus.write(BME280_adresse, &modeNormal, 1);
    	
    	char tempRegAddr1 = 0xFA;
    	char msb_lsb_xlsb[3];
    	bus.write(BME280_adresse, &tempRegAddr1, 1);
    	bus.read(BME280_adresse, msb_lsb_xlsb, 3);

    	printf("MSB: %02X\n", msb_lsb_xlsb[0]);
    	printf("LSB: %02X\n", msb_lsb_xlsb[1]);
    	printf("XLSB: %02X\n", msb_lsb_xlsb[2]);


    	int temp = (msb_lsb_xlsb[0] << 12 | msb_lsb_xlsb[1] << 4 | msb_lsb_xlsb[2]);

    	printf("Temperature: %.2d °C \n", temp);
		ThisThread::sleep_for(PERIOD_MS);
	}
}
