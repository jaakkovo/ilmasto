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
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cstdio>
#include <cstring>
#include <iostream>
#include "lcd_port.h"
#include "BarGraph.h"
#include "LiquidCrystal.h"
#include "SimpleMenu.h"
#include "MenuItem.h"
#include "IntegerEdit.h"
#include "SliderEdit.h"
#include "StatusEdit.h"
#include "SetupEdit.h"
#include "ManuAutoEdit.h"
#include "OnOffEdit.h"
#include "TimeEdit.h"
#include "DecimalEdit.h"
#include "PropertyEdit.h"
#include <cr_section_macros.h>

#include "ModbusMaster.h"

static volatile int counter;
static volatile uint32_t systicks;

#ifdef __cplusplus
extern "C" {
#endif

void SysTick_Handler(void)
{
	systicks++;
	if(counter > 0) counter--;
}

#ifdef __cplusplus
}
#endif

void Sleep(int ms)
{
	counter = ms;
	while(counter > 0) {
		__WFI();
	}
}

/* this function is required by the modbus library */
uint32_t millis() {
	return systicks;
}

void printRegister(ModbusMaster& node, uint16_t reg) {
	uint8_t result;
	// slave: read 16-bit registers starting at reg to RX buffer
	result = node.readHoldingRegisters(reg, 1);

	// do something with data if read is successful
	if (result == node.ku8MBSuccess)
	{
		printf("R%d=%04X\n", reg, node.getResponseBuffer(0));
	}
	else {
		printf("R%d=???\n", reg);
	}
}

bool setFrequency(ModbusMaster& node, uint16_t freq) {
	uint8_t result;
	int ctr;
	bool atSetpoint;
	const int delay = 500;

	node.writeSingleRegister(1, freq); // set motor frequency

	printf("Set freq = %d\n", freq/40); // for debugging

	// wait until we reach set point or timeout occurs
	ctr = 0;
	atSetpoint = false;
	do {
		Sleep(delay);
		// read status word
		result = node.readHoldingRegisters(3, 1);
		// check if we are at setpoint
		if (result == node.ku8MBSuccess) {
			if(node.getResponseBuffer(0) & 0x0100) atSetpoint = true;
		}
		ctr++;
	} while(ctr < 20 && !atSetpoint);

	printf("Elapsed: %d\n", ctr * delay); // for debugging

	return atSetpoint;
}

int main(void) {

	// Alustetaan nappi up
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 10, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 10);

	// Alustetaan nappi down
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 16, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 16);

	// Alustetaan nappi ok
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 3, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 3);

	// Alustetaan nappi back
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 0, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 0);

#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	// Set the LED to the state of "On"
	Board_LED_Set(1, true);
#endif
#endif

	/* Enable and setup SysTick Timer at a periodic rate */
	// SysTick_Config(SystemCoreClock / 1000);

	//NVIC_EnableIRQ(RITIMER_IRQn);
	//Chip_RIT_Init(LPC_RITIMER);

	ModbusMaster node(2); // Create modbus object that connects to slave id 2

	node.begin(9600); // set transmission rate - other parameters are set inside the object and can't be changed here
	printRegister(node, 3); // for debugging
	node.writeSingleRegister(0, 0x0406); // prepare for starting
	printRegister(node, 3); // for debugging

	Sleep(1000); // give converter some time to set up
	// note: we should have a startup state machine that check converter status and acts per current status
	//       but we take the easy way out and just wait a while and hope that everything goes well

	printRegister(node, 3); // for debugging
	node.writeSingleRegister(0, 0x047F); // set drive to start mode
	printRegister(node, 3); // for debugging

	Sleep(1000); // give converter some time to set up
	// note: we should have a startup state machine that check converter status and acts per current status
	//       but we take the easy way out and just wait a while and hope that everything goes well

	printRegister(node, 3); // for debugging

	int i = 0;
	int j = 0;
	const uint16_t fa[20] = { 1000, 2000, 3000, 3500, 4000, 5000, 7000, 8000, 8300, 10000, 10000, 9000, 8000, 7000, 6000, 5000, 4000, 3000, 2000, 1000 };

	LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

	lcd.begin(16,2);
	lcd.setCursor(0,0);

	SimpleMenu menu;
	SimpleMenu setup_menu;

	//Setup-valikko
	TimeEdit time(lcd, std::string("Time Set"));
	IntegerEdit hertz(lcd, std::string("Hertz"), 0, 10);
	IntegerEdit min(lcd, std::string("Min"), 0, 10);
	IntegerEdit max(lcd, std::string("Max"), 0, 10);

	setup_menu.addItem(new MenuItem(time));
	setup_menu.addItem(new MenuItem(hertz));
	setup_menu.addItem(new MenuItem(min));
	setup_menu.addItem(new MenuItem(max));

	//Paavalikko
	OnOffEdit power(lcd, std::string("Power"));
	ManuAutoEdit mode(lcd, std::string("Mode"));
	SetupEdit setup(lcd, std::string("Setup"));
	StatusEdit status(lcd, std::string("Status"));

	menu.addItem(new MenuItem(power));
	menu.addItem(new MenuItem(mode));
	menu.addItem(new MenuItem(setup));
	menu.addItem(new MenuItem(status));

	// Display first menu item
	menu.event(MenuItem::show);

	int valikko = 1;

	while(1){
		uint8_t result;

		// slave: read (2) 16-bit registers starting at register 102 to RX buffer
		j = 0;
		do {
			result = node.readHoldingRegisters(102, 2);
			j++;
		} while(j < 3 && result != node.ku8MBSuccess);

		if (result == node.ku8MBSuccess) {
			printf("F=%4d, I=%4d  (ctr=%d)\n", node.getResponseBuffer(0), node.getResponseBuffer(1),j);
		}
		else {
			printf("ctr=%d\n",j);
		}

		Sleep(3000);
		i++;
		if(i >= 20) {
			i=0;
		}

		// frequency is scaled:
		// 20000 = 50 Hz, 0 = 0 Hz, linear scale 400 units/Hz
		setFrequency(node, fa[i]);


		// VALIKKO

		if (setup.getValue == "menu") {

			if (valikko != 1) {
				valikko = 1;
				menu.event(MenuItem::show);
			}

			if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 10)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 10)) {
				}
				menu.event(MenuItem::up);
			}
			if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 16)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 16)) {
				}
				menu.event(MenuItem::down);
			}
			if (Chip_GPIO_GetPinState(LPC_GPIO, 1, 3)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 1, 3)) {
				}
				menu.event(MenuItem::ok);
			}
			if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 0)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 0)) {
				}
				menu.event(MenuItem::back);
			}
		}

		if (setup.getValue == "setup_menu") {

			if (valikko != 2) {
				valikko = 2;
				setup_menu.event(MenuItem::show);
			}

			if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 10)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 10)) {
				}
				setup_menu.event(MenuItem::up);
			}
			if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 16)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 16)) {
				}
				setup_menu.event(MenuItem::down);
			}
			if (Chip_GPIO_GetPinState(LPC_GPIO, 1, 3)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 1, 3)) {
				}
				setup_menu.event(MenuItem::ok);
			}
			if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 0)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 0)) {
				}
				setup_menu.event(MenuItem::back);
			}
		}


		if (mode.getValue() == "Automatic" ) {
			// TAHAN AUTOMAATTIOHJAUS
		}

		// JOS PAALLA
		if ("jotain") {
			status.setValue("RUNNING");
		}

		// JOS POIS PAALTA
		if ("jotain") {
			status.setValue("STOPPED");
		}

		// JOS VIRHE
		if ("jotain") {
			status.setValue("ERROR");
		}
	}

	return 0;
}
