/*
 * IntegerEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "IntegerEdit.h"
#include <cstdio>

IntegerEdit::IntegerEdit(LiquidCrystal& lcd_, std::string editTitle, int ilower, int iupper): lcd(lcd_), title(editTitle) {
	value = 0;
	edit = 0;
	focus = false;
	lower = ilower;
	upper = iupper;
	currentmenu = "setup_menu";
}

IntegerEdit::~IntegerEdit() {
}

void IntegerEdit::increment() {
	if (edit >= upper){
			edit = upper;
		} else{
			edit++;
		}
}

void IntegerEdit::decrement() {
	if (edit <= lower){
			edit = lower;
		} else{
			edit--;
		}
}

void IntegerEdit::accept() {
	save();
}

void IntegerEdit::cancel() {
	if(focus){
		edit = value;
	}else{
		currentmenu = "menu";
	}
}


void IntegerEdit::setFocus(bool focus) {
	this->focus = focus;
}

void IntegerEdit::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(title);
	lcd.setCursor(0,1);
	char s[16];
	if(focus) {
		snprintf(s, 16, "     [%4d]     ", edit);
	}
	else {
		snprintf(s, 16, "      %4d      ", edit);
	}
	lcd.print(s);
}


void IntegerEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}


int IntegerEdit::getValue() {
	return (value);
}
void IntegerEdit::setValue(int value) {
	edit = value;
	save();
}
string IntegerEdit::returnmenu(){
	return (currentmenu);
}

void IntegerEdit::setmenu(string menu){
	currentmenu = menu;
}
