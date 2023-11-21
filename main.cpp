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
InterruptIn Bouton(BUTTON1);
Thread thread;
Thread thread2;
Timer timer;
Timer timer2;
float pression = 0.0;
float humidite = 0.0;
float temperature = 0.0;
bool appuie = false;
Mutex mutex_temp;
Mutex mutex_hum;
Mutex mutex_press;
Mutex mutex_print;

BME280 CapteurBME280(&bus, BME280::I2CAddress::Address1);
}

void obtenirTemp(){

	mutex_temp.lock();
	float temperature = CapteurBME280.temperature();
	mutex_temp.unlock();
}

void obtenirHum(){

	mutex_temp.lock();
	float humidite = CapteurBME280.humidity();
	mutex_temp.unlock();
}

void threadTemp(){

	CapteurBME280.initialize();
	CapteurBME280.set_sampling();

	while(true){

		timer.start();
		printf("%f", timer.elapsed_time().count());
		if(timer.elapsed_time().count() == 2){
			mutex_print.lock();
			printf("Température: %.2f °C \n", temperature);	
			mutex_print.unlock();
			timer.reset();
		}
		ThisThread::sleep_for(PERIOD_MS);
		
	}
}

void threadHum(){

	while(true){

		timer2.start();
		if(timer2.elapsed_time().count() == 2.0){
			mutex_print.lock();
			printf("Humidite: %.2f °C \n", humidite);	
			mutex_print.unlock();
			timer2.reset();
		}
		ThisThread::sleep_for(PERIOD_MS);
		
	}
}

void obtenirPression(){
	
	appuie = true;
}

int main()
{
	CapteurBME280.initialize();
	CapteurBME280.set_sampling();

	//thread.start(threadTemp);
	//thread2.start(threadHum);

	while (true) {

		Bouton.rise(&obtenirPression);
		
		if(appuie){
			mutex_press.lock();
			float pression = CapteurBME280.pressure();
			mutex_press.unlock();
			mutex_print.lock();
        	printf("Pressure: %.2f °C \n", pression);
			mutex_print.unlock();
			appuie = false;
		}

		//thread.join();
		//thread2.join();
		ThisThread::sleep_for(PERIOD_MS);
	}
}