/*
 * lcd_port.cpp
 *
 *  Created on: 26.1.2016
 *      Author: krl
 */
/* compatibility layer */
#include "board.h"
#include "lcd_port.h"

volatile bool flag = false;

extern "C" {
void RIT_IRQHandler(void)
{
	// todo: implement RIT ISR that signals main task that timer has expired

	Chip_RIT_ClearIntStatus(LPC_RITIMER);
	Chip_RIT_Disable(LPC_RITIMER);

	flag = true;
}
}

static const int dPort[] = { 1, 1, 0, 0, 0, 0, 1, 0,  0, 1, 0, 0, 0, 0 };
static const int dPin[] = { 10, 9, 29, 9, 10, 16, 3, 0, 24, 0, 27, 28, 12, 14 };

void digitalWrite(uint8_t pin, uint8_t val)
{
	if(pin > 13) return;
	Chip_GPIO_SetPinState(LPC_GPIO, dPort[pin], dPin[pin], val);
}

void pinMode(uint8_t pin, uint8_t mode)
{
	if(mode == OUTPUT) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, dPort[pin], dPin[pin], (IOCON_DIGMODE_EN));
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, dPort[pin], dPin[pin]);
	}
	else {
		Chip_IOCON_PinMuxSet(LPC_IOCON, dPort[pin], dPin[pin], (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN));
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, dPort[pin], dPin[pin]);
	}
}

void delayMicroseconds(int us)
{
	uint64_t i = Chip_Clock_GetSysTickClockRate() / 1000000 * us;

	Chip_RIT_Disable(LPC_RITIMER);

	flag = false;

	Chip_RIT_SetCompareValue(LPC_RITIMER, i);

	Chip_RIT_SetCounter(LPC_RITIMER,0);

	Chip_RIT_Enable(LPC_RITIMER);

	while (!flag){
	}

}
