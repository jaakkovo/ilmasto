/*
 * ManuAutoEdit.cpp
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#include "OnOffEdit.h"
#include <cstdio>

ManuAutoEdit::ManuAutoEdit(LiquidCrystal& lcd_, std::string editTitle): lcd(lcd_), title(editTitle){
	value = 0;
	edit = 0;
	focus = false;
}

ManuAutoEdit::~ManuAutoEdit() {
	// TODO Auto-generated destructor stub
}

void ManuAutoEdit::increment() {
	if (value == "Automatic"){
		edit = "Manual";
	} else{
		edit = "Automatic";
	}
}

void ManuAutoEdit::decrement() {
	if (value == "Automatic"){
		edit = "Manual";
	} else{
		edit = "Automatic";
	}
}

void ManuAutoEdit::accept() {
	save();
}

void ManuAutoEdit::cancel() {
	edit = value;
}

void ManuAutoEdit::setFocus(bool focus) {
	this->focus = focus;
}

void ManuAutoEdit::display() {
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

void ManuAutoEdit::save() {
	value = edit;
}

bool ManuAutoEdit::getValue() {
	return value;
}

void ManuAutoEdit::setValue(bool value) {
	edit = value;
	save();
}

