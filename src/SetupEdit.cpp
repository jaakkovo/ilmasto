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


SetupEdit::SetupEdit(LiquidCrystal& lcd_, std::string editTitle): lcd(lcd_), title(editTitle){
	focus = false;
	currentmenu = "menu";
}

SetupEdit::~SetupEdit() {
	// TODO Auto-generated destructor stub
}


void SetupEdit::accept() {
	focus = true;
	currentmenu = "setup_menu";
}

void SetupEdit::cancel() {
	focus = false;
	currentmenu = "menu";
}

void SetupEdit::increment() {

}

void SetupEdit::decrement() {

}

void SetupEdit::setFocus(bool focus) {
	this->focus = focus;
	if (focus == true){
		currentmenu = "setup_menu";
	}else if (focus == false){
		currentmenu = "menu";
	}
}

void SetupEdit::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(title);
	lcd.setCursor(0,1);
}

void SetupEdit::save() {
}

string SetupEdit::getValue() {
	return currentmenu;
}

void SetupEdit::setValue(string value) {
	currentmenu = value;
}


