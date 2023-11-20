/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
using namespace std::chrono;
namespace {
#define PERIOD_MS 1000ms
InterruptIn boutonPin(BUTTON1);  // Numéro de la broche du bouton
DigitalOut ledPin(LED1);   // Numéro de la broche de la LED 
Timer t;
}



void flipAllumage()
{
    ledPin = 1;
	t.start();
}

void flipEteindre()
{
    ledPin = 0;
	t.stop();
}

int main()
{
	boutonPin.rise(&flipAllumage);
	boutonPin.fall(&flipEteindre);
	while (true) {
		
		 printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
		ThisThread::sleep_for(PERIOD_MS / 8);
	}
}
