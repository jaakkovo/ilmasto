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

	if (focus) {
		currentmenu = "setup_menu";
	}
}

void SetupEdit::save() {
}

string SetupEdit::getValue() {
	return currentmenu;
}

void SetupEdit::setValue(string value) {
	currentmenu = value;
}


