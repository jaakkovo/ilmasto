/*
 * DecimalEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "DecimalEdit.h"
#include <cstdio>

DecimalEdit::DecimalEdit(LiquidCrystal& lcd_, std::string editTitle, float flower, float fupper): lcd(lcd_), title(editTitle) {
	value = 1.0;
	edit = 0.1;
	focus = false;
	lower = flower;
	upper = fupper;

}

DecimalEdit::~DecimalEdit() {
}

void DecimalEdit::increment() {

	if (edit >= upper-0.09){
		edit = upper;
	} else{
		edit = edit+0.1;
	}

}

void DecimalEdit::decrement() {
	if (edit <= lower+0.09){
			edit = lower;
		} else{
			edit = edit-0.1;
	}
}

void DecimalEdit::accept() {
	save();
}

void DecimalEdit::cancel() {
	edit = value;
}


void DecimalEdit::setFocus(bool focus) {
	this->focus = focus;
}

void DecimalEdit::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(title);
	lcd.setCursor(0,1);
	char s[16];
	if(focus) {
		snprintf(s, 16, "     [%.1f]     ", edit);
	}
	else {
		snprintf(s, 16, "      %.1f      ", edit);
	}
	lcd.print(s);
}

void DecimalEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}

int DecimalEdit::getValue() {
	return value;
}
void DecimalEdit::setValue(float value) {
	edit = value;
	save();

}
