/*
 * SetupEdit.cpp
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#include "SetupEdit.h"
#include <cstdio>
#include <string>
#include <sstream>

stringstream ss;

SetupEdit::SetupEdit(LiquidCrystal& lcd_, std::string editTitle): lcd(lcd_), title(editTitle){
	value = "Time Set";
	edit = "Time Set";
	focus = false;
}

SetupEdit::~SetupEdit() {
	// TODO Auto-generated destructor stub
}


void SetupEdit::accept() {
	save();
}

void SetupEdit::cancel() {
	edit = value;
}

void SetupEdit::increment() {
	if (value == "Boundaries"){
		edit = "Hz";
	} else{
		edit = "Time Set";
	}
}

void SetupEdit::decrement() {
	if (value == "Time Set"){
		edit = "Hz";
	} else{
		edit = "Boundaries";
	}
}

void SetupEdit::setFocus(bool focus) {
	this->focus = focus;
}

void SetupEdit::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(title);
	lcd.setCursor(0,1);
	char s[16];
	char editti[16];
	if(focus) {
		ss << edit;
		ss >> editti;

		snprintf(s, 16, "[%s]", editti);
	}
	else {
		ss << edit;
		ss >> editti;

		snprintf(s, 16, "[%s]", editti);
	}
	lcd.print(s);
}

void SetupEdit::save() {
	value = edit;
}

string SetupEdit::getValue() {
	return value;
}

void SetupEdit::setValue(string value) {
	edit = value;
	save();
}


