/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "bme280.h"
using namespace std::chrono;
namespace {
#define PERIOD_MS 1000ms
#define BME280_adresse 0x76 << 1
I2C bus(I2C1_SDA,I2C1_SCL);  // Numéro de la broche du bouton
}


int main()
{
		// 0xF5
		char config[2] = {0xF5,0b10110100 };
    	bus.write(BME280_adresse, config, 2);	

		//0xF4
		char ctrl_meas[2] = {0xF4,0b00100111 };
		bus.write(BME280_adresse, ctrl_meas, 2);


	while (true) {
		
		
		//0xF3
		char status = 0b11110011;
		char update[1]; 
		bus.write(BME280_adresse, &status, 1);
		bus.read(BME280_adresse, update, 1);
		

    	char tempRegAddr1 = 0xFA;
    	char msb_lsb_xlsb[3];
    	bus.write(BME280_adresse, &tempRegAddr1, 1);
    	bus.read(BME280_adresse, msb_lsb_xlsb, 3);

    	printf("MSB: %X\n", msb_lsb_xlsb[0]);
    	printf("LSB: %X\n", msb_lsb_xlsb[1]);
    	printf("XLSB: %X\n", msb_lsb_xlsb[2]);
		printf("update: %X\n", update[0]);
		

    	int temp = (msb_lsb_xlsb[0] << 12 | msb_lsb_xlsb[1] << 4 | msb_lsb_xlsb[2]);

    	printf("Temperature: %.2d °C \n", temp);
		ThisThread::sleep_for(PERIOD_MS);
	}

}
