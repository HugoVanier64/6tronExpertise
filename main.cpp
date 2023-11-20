/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
using namespace std::chrono;
namespace {
#define PERIOD_MS 1000ms
Ticker flipper;
InterruptIn boutonPin(BUTTON1);  // Numéro de la broche du bouton
DigitalOut ledPin(LED1);   // Numéro de la broche de la LED 
float freq = 5.0;
}

void flip()
{
    ledPin = !ledPin;
	
}

void flipBouton1()
{
    freq++;
}

void flipBouton2()
{
	if(freq >= 20.0){
		freq = 5.0;
		flipper.attach(&flip, freq); 
	}
	else{
		flipper.attach(&flip, freq);
	}
	
}



int main()
{
	ledPin = 1;
	boutonPin.rise(&flipBouton1);
	boutonPin.fall(&flipBouton2);
	flipper.attach(&flip, freq); 
	while (true) {
		
		printf("The actual frequence is %f seconds\n", freq);
		ThisThread::sleep_for(PERIOD_MS / 4);
	}
}
