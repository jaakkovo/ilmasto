
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

// ADC:n määrittelyt
static volatile bool adcdone = false;
static volatile bool adcstart = false;

volatile uint32_t a0;
volatile uint32_t d0;
volatile uint32_t a3;
volatile uint32_t d3;
volatile int kalib = 50; // Määrittää kalibrointirajan +-
// ADC:n määrittelyt loppuuu


#ifdef __cplusplus
extern "C" {
#endif


void SysTick_Handler(void)
{
	systicks++;
	if(counter > 0) counter--;

	// ADC systikki::begins
	static uint32_t count;
	adcstart = true;
	count++;
	// ADC systick::ends

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

#ifdef __cplusplus
extern "C" {
#endif

// ADC -- Alkaa
void ADC0A_IRQHandler(void)
{
	uint32_t pending;

	/* Get pending interrupts */
	pending = Chip_ADC_GetFlags(LPC_ADC0);

	/* Sequence A completion interrupt */
	if (pending & ADC_FLAGS_SEQA_INT_MASK) {
		adcdone = true; }

	/* Clear any pending interrupts */
	Chip_ADC_ClearFlags(LPC_ADC0, pending);
}
// ADC -- Loppuu
#ifdef __cplusplus
}
#endif

double pressure(){
	I2C i2c = I2C(0,100000);

	uint8_t pressureData[3];
	uint8_t readPressureCmd = 0xF1;
	int16_t pressure = 0;
	i2c.transaction(0x40, &readPressureCmd, 1, pressureData, 3);
	/* Output temperature. */
	pressure = (pressureData[0] << 8) | pressureData[1];
	return pressure/24000.0;
}
float temperature (uint32_t value){
	value += 3800;
	float temp = ((float)value / 16382.0);
	temp = temp * 165.0;
	return temp-40.0;
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

	/* Set up SWO to PIO1_2 */
	Chip_SWM_MovablePortPinAssign(SWM_SWO_O, 1, 2);


	// ADC:n ALUSTUS ALKAA TÄSTÄ
	/* Setup ADC for 12-bit mode and normal power */
	Chip_ADC_Init(LPC_ADC0, 0);

	/* Setup for maximum ADC clock rate */
	Chip_ADC_SetClockRate(LPC_ADC0, ADC_MAX_SAMPLE_RATE);

	/* For ADC0, sequencer A will be used without threshold events.
			   It will be triggered manually  */
	Chip_ADC_SetupSequencer(LPC_ADC0, ADC_SEQA_IDX, (ADC_SEQ_CTRL_CHANSEL(0) | ADC_SEQ_CTRL_CHANSEL(3) | ADC_SEQ_CTRL_MODE_EOS));

	/* For ADC0, select analog input pint for channel 0 on ADC0 */
	Chip_ADC_SetADC0Input(LPC_ADC0, 0);

	/* Use higher voltage trim for both ADC */
	Chip_ADC_SetTrim(LPC_ADC0, ADC_TRIM_VRANGE_HIGHV);

	/* Assign ADC0_0 to PIO1_8 via SWM (fixed pin) and ADC0_3 to PIO0_5 */
	Chip_SWM_EnableFixedPin(SWM_FIXED_ADC0_0);
	Chip_SWM_EnableFixedPin(SWM_FIXED_ADC0_3);

	/* Need to do a calibration after initialization and trim */
	Chip_ADC_StartCalibration(LPC_ADC0);
	while (!(Chip_ADC_IsCalibrationDone(LPC_ADC0))) {}

	/* Clear all pending interrupts and status flags */
	Chip_ADC_ClearFlags(LPC_ADC0, Chip_ADC_GetFlags(LPC_ADC0));

	/* Enable sequence A completion interrupts for ADC0 */
	Chip_ADC_EnableInt(LPC_ADC0, ADC_INTEN_SEQA_ENABLE);

	/* Enable related ADC NVIC interrupts */
	NVIC_EnableIRQ(ADC0_SEQA_IRQn);

	/* Enable sequencer */
	Chip_ADC_EnableSequencer(LPC_ADC0, ADC_SEQA_IDX);

	// ADC:n ALUSTUS LOPPUU




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


	// Näytön alustus ja alkuasetukset

	LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

	lcd.begin(16,2);
	lcd.setCursor(0,0);

	// Menu

	SimpleMenu menu;

	// Alamenun otsikkonimikkeet. Rajat annetaan samassa järjestyksessä.

	// Setup-valikko
	static const string arr[] = { "Hertz", "Pressure Min", "Pressure Max", "Hertz Min", "Hertz Max", "Interval (s)" };
	vector<string> setupvalikot (arr, arr + sizeof(arr) / sizeof(arr[0]) );

	// Status-valikko
	static const string arr2[] ={ "info_System", "info_Temperature", "info_Pressure" };
	vector<string> statusvalikot (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );

	// Ylarajat
	static const int arr3[] = { 50, 135, 135, 50, 50, 3600 };
	vector<int> ylarajat (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );

	// Alarajat
	static const int arr4[] = { 0, -135, -135, 0, 0, 0 };
	vector<int> alarajat (arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]) );


	// Luodaan menun kohdat. Menuille annetaan otsikko, alamenujen otsikot, alarajat ja ylarajat.
	ManuAutoEdit mode = ManuAutoEdit(lcd, "Mode");
	SetupEdit setup = SetupEdit(lcd, "Setup", setupvalikot, alarajat, ylarajat);
	StatusEdit status = StatusEdit(lcd, "Status", statusvalikot, alarajat, ylarajat);

	// Päävalikkoon lisätään kohtia. True / False viimeisenä parametrina kertoo, onko valikolla alavalikko.
	menu.addItem(new SubMenuItem(mode, false));
	menu.addItem(new SubMenuItem(setup, true));
	menu.addItem(new SubMenuItem(status, true));

	// Display first menu item
	menu.event(SubMenuItem::show);


	int lukema = 500000;
	int mod = 0;

	int freq = 0;
	string s = "";
	string d = "";
	int hertz = 0;

	try {
		setFrequency(node, 400 * hertz);
		status.setValue(0, "OK");
	}
	catch (...) {
		status.setValue(0, "Error");
	}

	while(1){

		if (lukema > 1){
			mod++;
			lukema--;
		}
		if (lukema == 1){
			try {
				Chip_ADC_StartSequencer(LPC_ADC0, ADC_SEQA_IDX);

				// ADC alkaa!
				while (!adcdone) __WFI();
				adcdone = false;

				a0 = Chip_ADC_GetDataReg(LPC_ADC0, 0);
				d0 = ADC_DR_RESULT(a0);

				a3 = Chip_ADC_GetDataReg(LPC_ADC0, 3);
				d3 = ADC_DR_RESULT(a3);


				lukema = 0;
				lcd.clear();

				stringstream ss;

				ss.precision(3);
				ss << temperature(d0);
				ss >> s;

				lcd.setCursor(0, 0);
				lcd.print("Temp:");
				lcd.print(s);

				status.setValue(1, "OK");
			}
			catch (...) {
				status.setValue(1, "Error");
			}

			if (mode.getValue() == "Manual"){
				lcd.print(" ");
				lcd.print("Mode:M");
			}else if (mode.getValue() == "Automatic"){
				lcd.print(" ");
				lcd.print("Mode:A");
			}else if (mode.getValue() == "Idle") {
				lcd.print(" ");
				lcd.print("Mode:I");
			}


			try {
				stringstream dd;

				dd.precision(3);
				dd << pressure();
				dd >> d;
				lcd.setCursor(0, 1);

				lcd.print("Pressure:");
				lcd.print(d);

				status.setValue(2, "OK");
			}
			catch (...) {
				status.setValue(2, "Error");
			}

			if (mod > (100000 * setup.getValue(5))) {
				mod = 0;
				if (mode.getValue() == "Automatic") {

					// Tarkistukset. Mikäli hertzit on annettujen rajojen ulkopuolella, asetetaan se raja-arvoon.
					if (hertz < setup.getValue(3)) {
						hertz = setup.getValue(3);
					}

					if (hertz > setup.getValue(4)) {
						hertz = setup.getValue(4);
					}

					try {
						setFrequency(node, 400 * hertz);
						status.setValue(0, "OK");
					}
					catch (...) {
						status.setValue(0, "Error");
					}

					if (pressure() > setup.getValue(2)) {
						if (hertz > setup.getValue(3)) {
							hertz--;
						}
					}

					if (pressure() < setup.getValue(1)) {

						if (hertz < setup.getValue(4)) {
							hertz++;
						}

					}
				}
			}
			lukema = 500000;
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
			lukema = 500000;
			menu.event(SubMenuItem::up);
		}
		if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 16)) {
			while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 16)) {
			}
			lukema = 500000;
			menu.event(SubMenuItem::down);
		}
		if (Chip_GPIO_GetPinState(LPC_GPIO, 1, 3)) {
			while (Chip_GPIO_GetPinState(LPC_GPIO, 1, 3)) {
			}
			lukema = 500000;
			menu.event(SubMenuItem::ok);
		}
		if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 0)) {
			while (Chip_GPIO_GetPinState(LPC_GPIO, 0, 0)) {
			}
			lukema = 500000;
			menu.event(SubMenuItem::back);
		}



		if (mode.getValue() == "Manual" ) {
			if (setup.getValue(0) != hertz){
				hertz = setup.getValue(0);
				try {
					setFrequency(node, 400 * hertz);
					status.setValue(0, "OK");
				}
				catch (...) {
					status.setValue(0, "Error");
				}
			}
		}

		if (mode.getValue() == "Idle") {
			if (hertz != 0) {
				hertz = 0;
				try {
					setFrequency(node, 400 * hertz);
					status.setValue(0, "OK");
				}
				catch (...) {
					status.setValue(0, "Error");
				}
			}
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
