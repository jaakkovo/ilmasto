/*
 * SetupEdit.cpp
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#include "OnOffEdit.h"
#include <cstdio>

SetupEdit::SetupEdit(LiquidCrystal& lcd_, std::string editTitle): lcd(lcd_), title(editTitle){
	value = 0;
	edit = 0;
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
	if(focus) {
		snprintf(s, 16, "[%s]", edit);
	}
	else {
		snprintf(s, 16, "%s", edit);
	}
	lcd.print(s);
}

void SetupEdit::save() {
	value = edit;
}

bool SetupEdit::getValue() {
	return value;
}

void SetupEdit::setValue(bool value) {
	edit = value;
	save();
}

