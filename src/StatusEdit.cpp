/*
 * StatusEdit.cpp
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#include "OnOffEdit.h"
#include <cstdio>

StatusEdit::StatusEdit(LiquidCrystal& lcd_, std::string editTitle): lcd(lcd_), title(editTitle){
	value = 0;
	edit = 0;
	focus = false;
}

StatusEdit::~StatusEdit() {
	// TODO Auto-generated destructor stub
}


void StatusEdit::accept() {
	save();
}

void StatusEdit::cancel() {
	edit = value;
}

void StatusEdit::setFocus(bool focus) {
	this->focus = focus;
}

void StatusEdit::display() {
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

void StatusEdit::save() {
	value = edit;
}

bool StatusEdit::getValue() {
	return value;
}

void StatusEdit::setValue(bool value) {
	edit = value;
	save();
}

