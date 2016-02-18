/*
 * IntegerEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "SliderEdit.h"
#include "BarGraph.h"
#include <cstdio>

volatile double v1 = 0.0;
volatile double v2 = 0.0;
volatile double v3 = 0.0;

SliderEdit::SliderEdit(LiquidCrystal& lcd_, std::string editTitle, int ilower, int iupper): lcd(lcd_), title(editTitle), bar(lcd_, 80, false) {
	value = 0;
	edit = 0;
	focus = false;
	lower = ilower;
	upper = iupper;
}

SliderEdit::~SliderEdit() {
}

void SliderEdit::increment() {
	if (edit >= upper){
			edit = upper;
		} else{
			edit++;
		}
}

void SliderEdit::decrement() {
	if (edit <= lower){
			edit = lower;
		} else{
			edit--;
		}
}

void SliderEdit::accept() {
	save();
}

void SliderEdit::cancel() {
	edit = value;
}


void SliderEdit::setFocus(bool focus) {
	this->focus = focus;
}

void SliderEdit::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(title);
	lcd.setCursor(0,1);
	char s[16];
	if(focus) {
		//bar.draw(12);
		//snprintf(s, 16, "     [%4d]     ", edit);
		v1 = edit-lower;

		v2 = upper-lower;

		v3 = v1/v2;

		bar.draw(v3*80);
	}
	else {
		snprintf(s, 16, "      %4d      ", edit);
		lcd.print(s);
	}


}


void SliderEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}


int SliderEdit::getValue() {
	return value;
}
void SliderEdit::setValue(int value) {
	edit = value;
	save();
}
