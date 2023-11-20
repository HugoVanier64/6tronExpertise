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
}



void flip()
{
    ledPin = !ledPin;
	
}

int main()
{
	ledPin = 1;
	flipper.attach(&flip, 1.0); 
	while (true) {
		
		ThisThread::sleep_for(PERIOD_MS / 4);
	}
}
