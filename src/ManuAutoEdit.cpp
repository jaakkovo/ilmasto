/*
 * ManuAutoEdit.cpp
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#include "ManuAutoEdit.h"

#include <cstdio>
#include <string>
#include <sstream>


using namespace std;

ManuAutoEdit::ManuAutoEdit(LiquidCrystal& lcd_, std::string editTitle): lcd(lcd_), title(editTitle){
	value = "Automatic";
	edit = "Automatic";
	focus = false;
}

ManuAutoEdit::~ManuAutoEdit() {
	// TODO Auto-generated destructor stub
}

void ManuAutoEdit::increment() {
	if (value.compare("Automatic")){
		edit = "Manual";
	} else{
		edit = "Automatic";
	}
}

void ManuAutoEdit::decrement() {
	if (value.compare("Automatic")){
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
	stringstream ss;
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

void ManuAutoEdit::save() {
	value = edit;
}

string ManuAutoEdit::getValue() {
	return value;
}

void ManuAutoEdit::setValue(string value) {
	edit = value;
	save();
}

