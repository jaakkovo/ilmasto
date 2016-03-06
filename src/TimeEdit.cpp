/*
* IntegerEdit.cpp
*
*  Created on: 2.2.2016
*      Author: krl
*/

#include "TimeEdit.h"
#include <cstdio>

TimeEdit::TimeEdit(LiquidCrystal& lcd_, std::string editTitle) : lcd(lcd_), title(editTitle) {
	value = 0;
	edit = 0;
	focus = false;
}

TimeEdit::~TimeEdit() {
}

void TimeEdit::increment() {

}

void TimeEdit::decrement() {

}

void TimeEdit::accept() {
	save();
}

void TimeEdit::cancel() {
	edit = value;
}


void TimeEdit::setFocus(bool focus) {
	this->focus = focus;
}

void TimeEdit::display() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(title);
	lcd.setCursor(0, 1);
	char s[16];
	if (focus) {
		snprintf(s, 16, "     [%4d]     ", edit);
	}
	else {
		snprintf(s, 16, "      %4d      ", edit);
	}
	lcd.print(s);
}


void TimeEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}


int TimeEdit::getValue() {
	return (value);
}
void TimeEdit::setValue(int value) {
	edit = value;
	save();
}
