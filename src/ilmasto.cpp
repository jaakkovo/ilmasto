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
#include <cstdio>
#include <iostream>

#endif
#endif
#include "lcd_port.h"
#include "BarGraph.h"
#include "LiquidCrystal.h"
#include "SimpleMenu.h"
#include "MenuItem.h"
#include "IntegerEdit.h"
#include "SliderEdit.h"

#include "DecimalEdit.h"
#include "PropertyEdit.h"
#include <cr_section_macros.h>

extern "C"
{
void SysTick_Handler(void)
{

}
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
	Board_LED_Set(2, true);
#endif
#endif



	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / 1000);

	// TODO: insert code here
	NVIC_EnableIRQ(RITIMER_IRQn);
	Chip_RIT_Init(LPC_RITIMER);


	LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

	lcd.begin(16,2);
	lcd.setCursor(0,0);

	SimpleMenu menu;
	//DecimalEdit dectemperature(lcd, std::string("decTemperature"), 10.0, 50.0);
	//DecimalEdit dechumidity(lcd, std::string("decHumidity"), 10.0, 100.0);

	//SliderEdit intage(lcd, std::string("intAge"), 10, 20);
	//SliderEdit intyear(lcd, std::string("intYear"), 2010, 2150);

	OnOffEdit power(lcd, std::string("Power"));
	ManuAutoEdit mode(lcd, std::string("Mode"));
	StatusEdit status(lcd, std::string("Status"));
	SetupEdit setup(lcd, std::string("Setup"));

	menu.addItem(new MenuItem(power));
	menu.addItem(new MenuItem(mode));
	menu.addItem(new MenuItem(status));
	menu.addItem(new MenuItem(setup));

	//menu.addItem(new MenuItem(dectemperature));
	//menu.addItem(new MenuItem(dechumidity));
	//menu.addItem(new MenuItem(intage));
	//menu.addItem(new MenuItem(intyear));


	//dectemperature.setValue(10.5);
	//dechumidity.setValue(99.5);
	//intage.setValue(11);
	//intyear.setValue(2016);

	menu.event(MenuItem::show); // display first menu item

	while(1){

		if (Chip_GPIO_GetPinState(LPC_GPIO, 0,10)) {
			while(Chip_GPIO_GetPinState(LPC_GPIO, 0,10)) {
			}
			menu.event(MenuItem::up);
		}
		if (Chip_GPIO_GetPinState(LPC_GPIO, 0,16)) {
			while(Chip_GPIO_GetPinState(LPC_GPIO, 0,16)) {
			}
			menu.event(MenuItem::down);
		}
		if (Chip_GPIO_GetPinState(LPC_GPIO, 1,3)) {
			while(Chip_GPIO_GetPinState(LPC_GPIO, 1,3)) {
			}
			menu.event(MenuItem::ok);
		}
		if (Chip_GPIO_GetPinState(LPC_GPIO, 0,0)) {
			while(Chip_GPIO_GetPinState(LPC_GPIO, 0,0)) {
			}
			menu.event(MenuItem::back);
		}
	}

	return 0;
}
