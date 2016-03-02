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
	currentmenu = "menu";
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

}

void SetupEdit::decrement() {

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

	if (focus) {
		currentmenu = "setup_menu";
	}
	else {
		currentmenu = "menu";
		ss << edit;
		ss >> editti;

		snprintf(s, 16, "%s", editti);
		lcd.print(s);
	}
}

void SetupEdit::save() {
	value = edit;
}

string SetupEdit::getValue() {
	return currentmenu;
}

void SetupEdit::setValue(string value) {
	currentmenu = value;
}


