
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

#include "ModbusMaster.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include "lcd_port.h"
#include "BarGraph.h"
#include "LiquidCrystal.h"
#include "SimpleMenu.h"
#include "SubMenuItem.h"
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
#include "I2C.h"
#include "SetupEdit.h"

#include <sstream>

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



/* this function is required by the modbus library */
uint32_t millis() {
	return (systicks);
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

	return (atSetpoint);
}

void Sleep(int ms)
{
	counter = ms;
	while(counter > 0) {
		__WFI();
	}
}


double pressure(){
	I2C i2c = I2C(0,100000);

	uint8_t pressureData[3];
	uint8_t readPressureCmd = 0xF1;
	int16_t pressure = 0;
	i2c.transaction(0x40, &readPressureCmd, 1, pressureData, 3);
	/* Output temperature. */
	pressure = (pressureData[0] << 8) | pressureData[1];
	return pressure/240.0;
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


	Chip_RIT_Init(LPC_RITIMER);
	NVIC_EnableIRQ(RITIMER_IRQn);

	SysTick_Config(Chip_Clock_GetSysTickClockRate() / 1000);

	Chip_SWM_MovablePortPinAssign(SWM_SWO_O, 1, 2);


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

	// Näytön alustus ja alkuasetukset

	LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

	lcd.begin(16,2);
	lcd.setCursor(0,0);

	// Menu

	SimpleMenu menu;

	// Alamenun otsikkonimikkeet. Rajat annetaan samassa järjestyksessä.

	// Setup-valikko
	static const string arr[] = { "Min", "Max", "Hertz", "Time set" };
	vector<string> setupvalikot (arr, arr + sizeof(arr) / sizeof(arr[0]) );

	// Status-valikko
	static const string arr2[] ={ "info_System", "info_ModBus", "info_Pressure_sensor"};
	vector<string> statusvalikot (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );

	// Ylarajat
	static const int arr3[] = { 10, 5, 2, 50 };
	vector<int> ylarajat (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );

	// Alarajat
	static const int arr4[] = { 0, 0, 0, 0 };
	vector<int> alarajat (arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]) );


	// Luodaan menun kohdat. Menuille annetaan otsikko, alamenujen otsikot, alarajat ja ylarajat.
	OnOffEdit power = OnOffEdit(lcd, "Power");
	ManuAutoEdit mode = ManuAutoEdit(lcd, "Mode");
	SetupEdit setup = SetupEdit(lcd, "Setup", setupvalikot, alarajat, ylarajat);
	StatusEdit status = StatusEdit(lcd, "Status", statusvalikot, alarajat, ylarajat);

	// Päävalikkoon lisätään kohtia. True / False viimeisenä parametrina kertoo, onko valikolla alavalikko.
	menu.addItem(new SubMenuItem(power, false));
	menu.addItem(new SubMenuItem(mode, false));
	menu.addItem(new SubMenuItem(setup, true));
	menu.addItem(new SubMenuItem(status, true));

	// Display first menu item
	menu.event(SubMenuItem::show);


	int lukema = 1000000;
	int freq = 10000;
	stringstream ss;
	string s = "";

	while(1){
		if (lukema > 1){
			lukema--;
		}
		if (lukema == 1){
			lukema = 0;
			lcd.clear();


		    ss << pressure();
		    ss >> s;

			lcd.print(s);
		}
			/*  TAAJUUDEN VAIHTELU KOMMENTOITU
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
			 */

			// VALIKKO
			if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 10)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 10)) {
				}
				menu.event(SubMenuItem::up);
			}
			if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 16)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 16)) {
				}
				menu.event(SubMenuItem::down);
			}
			if (Chip_GPIO_GetPinState(LPC_GPIO, 1, 3)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 1, 3)) {
				}
				lukema = 1000000;
				menu.event(SubMenuItem::ok);
			}
			if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 0)) {
				while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 0)) {
				}
				menu.event(SubMenuItem::back);
			}

			if (mode.getValue() == "Automatic" ) {
				// TÄHÄN AUTOMAATTIOHJAUS

					printf("Pressure read over I2C is %.1f Pa\r\n",	pressure());
					if(pressure()>1.0){
						if(freq>0){
						//	setFrequency(node,freq-400);
						}
					}
					if(pressure()<1.0){
						if(freq<20000){
						//   setFrequency(node,freq+400);
						}
					}
			}

			if (mode.getValue() == "Manual"){
				// Manuaaliohjaus
			}

			// Näin muutetaan statuksen arvoja:
			// Ensimmäinen parametri määrittää monesko valikon kohta on kyseessä. Alkaen nollasta.
			// 0 = info_System, 1 = info_ModBus, 2 = info_Pressure_sensor
			//	if (jotain){
			//		status.setValue[0, "Running OK"]
			//	}

			//	if (jotain){
			//	status.setValue[1, "Connected"]
			//	}

			// Näin tarkastetaan asetettuja arvoja:
			// Tällä voisi tarkistaa, onko ala-arvo muuttunut nykyisestä.
			//	if(setup.getValue(0) != asetettu_ala_arvo){
			// Mitä tapahtuu jos arvo on muuttunut
			//	}
	}
	return (0);
}
