/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "jotainshittii.h"
#include "chip.h"
#include "gpio.h"
#else
#include "board.h"
#define MAXLEDS 7
#endif
#endif
#define TICKRATE_HZ1 (1000)	/* 1 tick per second */
#include <cr_section_macros.h>

volatile int calc = 1;

class Dice {
	public:
		Dice();
		Dice(int diceValue);
		virtual ~Dice(){};
		void SetValue(int number);
		int GetValue();

	private:
		// Jos static, niin luokkamuuttuja. Älä käytä sitä.
		int DiceValue;
};

/* you need to figure out yourself the private members that you need */
// TODO: insert other include files here

// TODO: insert other definitions and declarations here
Dice :: Dice(){
}

int Dice :: GetValue() {
	return DiceValue;
}

void Dice :: SetValue(int number) {
	//Digital inputs with pull ups and inverting input
	// Set Port0.Pin8 as a digital input with pull up

	static const uint8_t diceport[] = { 0, 1, 0, 0, 0, 0, 1 };
	static const uint8_t dicepins[] = { 0, 3, 16, 10, 9, 29, 9 };


	DiceValue = number;
	// alla olevat olisi voinut laittaa constructoriin
	if (number == 1){
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 10);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 3);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 3, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 16);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 29);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, false);
	}

	if (number == 2){
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 10);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 3);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 3, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 16);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 29);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, false);
	}

	if (number == 3){
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 10);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 3);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 3, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 16);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 29);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, false);
	}

	if (number == 4){
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 10);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 3);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 3, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 16);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 29);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, false);
	}

	if (number == 5){
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 10);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 3);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 3, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 16);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 29);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, false);
	}

	if (number == 6){
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 10);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, false);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 3);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 3, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 16);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 29);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, true);
	}

	if (number == 7){
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 10);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 3);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 3, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 16);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 9);
		Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 29);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, true);
	}

	if (number == 0){
		int idx;
		for (idx = 0; idx < MAXLEDS; idx++) {
		/* Set the GPIO as output with initial state off (low) */
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, diceport[idx], dicepins[idx]);
		Chip_GPIO_SetPinState(LPC_GPIO, diceport[idx], dicepins[idx], false);
		}
	}

}

extern "C" {

	void SysTick_Handler(void) {
		if(Chip_GPIO_GetPinState(LPC_GPIO, 1,0)) {
			calc++;
			if (calc > 6){
				calc = 1;
			}
		}
	}
}

int main(void) {
	Dice noppa;
	uint32_t sysTickRate;

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);


#endif
#endif

	sysTickRate = Chip_Clock_GetSysTickClockRate();


	// Määritellään nappi PB1 toimimaan inputtina
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 0, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 0);

	// Määritellään nappi PC0 toimimaan inputtina
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 8, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 8);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(sysTickRate / TICKRATE_HZ1);

	noppa.SetValue(0);

	while(1) {

		if (Chip_GPIO_GetPinState(LPC_GPIO, 1,0)) {
			noppa.SetValue(0);
			while(Chip_GPIO_GetPinState(LPC_GPIO, 1,0)) {
    		}

	   		if(!Chip_GPIO_GetPinState(LPC_GPIO, 1,0)) {
	   			noppa.SetValue(calc);
	    	}
		}

   		// Testinappi, kaikki ledit syttyy
   		if (Chip_GPIO_GetPinState(LPC_GPIO, 0,8)) {
   			while(Chip_GPIO_GetPinState(LPC_GPIO, 0,8)) {
   				noppa.SetValue(7);
   			}
   			noppa.SetValue(0);
   		}
    }
   	return 0;
}
