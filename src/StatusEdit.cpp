/*
 * StatusEdit.cpp
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#include "StatusEdit.h"
#include <cstdio>
#include <string>
#include <sstream>

stringstream ss;

StatusEdit::StatusEdit(LiquidCrystal& lcd_, std::string editTitle): lcd(lcd_), title(editTitle){
	value = "RUNNING";
	edit = "RUNNING";
	focus = false;
}

StatusEdit::~StatusEdit() {
	// TODO Auto-generated destructor stub
}

void StatusEdit::increment() {

}
void StatusEdit::decrement() {

}

void StatusEdit::accept() {
	save();
}

void StatusEdit::cancel() {
	edit = value;
}

void StatusEdit::setFocus(bool focus) {
	//Statusta ei voida Focusaa.
}

void StatusEdit::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(title);
	lcd.setCursor(0,1);
	char s[16];
	char editti[16];

	if(focus) {
		ss << edit;
		ss >> editti;

		snprintf(s, 16, "%s", editti);
	}
	else {
		ss << edit;
		ss >> editti;

		snprintf(s, 16, "%s", editti);
	}
	lcd.print(s);
}

void StatusEdit::save() {
	value = edit;
}

string StatusEdit::getValue() {
	return value;
}

void StatusEdit::setValue(string value) {
	edit = value;
	save();
}

