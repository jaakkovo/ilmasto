/*
 * OnOffEdit.cpp
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#include "OnOffEdit.h"
#include <cstdio>

OnOffEdit::OnOffEdit(LiquidCrystal& lcd_, std::string editTitle): lcd(lcd_), title(editTitle){
	value = 0;
	edit = 0;
	focus = false;
}

OnOffEdit::~OnOffEdit() {
	// TODO Auto-generated destructor stub
}

void OnOffEdit::increment() {
	if (focus) {
		if (edit == true) {
			edit = false;
		}
		else {
			edit = true;
		}
	}
}

void OnOffEdit::decrement() {
	if (focus) {
		if (edit == true) {
			edit = false;
		}
		else {
			edit = true;
		}
	}
}

void OnOffEdit::accept() {
	save();
}

void OnOffEdit::cancel() {
	edit = value;
}

void OnOffEdit::setFocus(bool focus) {
	this->focus = focus;
}

void OnOffEdit::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(title);
	lcd.setCursor(0,1);
	char s[16];
	if(focus) {
		snprintf(s, 16, "[%d]", edit);
	}
	else {
		snprintf(s, 16, "%d", edit);
	}
	lcd.print(s);
}

void OnOffEdit::save() {

	if (edit == true) {
		// PIDE��N POWERI P��LL�
	}
	if (edit == false) {
		// SAMMUTETAAN LAITE
	}
	value = edit;

}

bool OnOffEdit::getValue() {
	return (value);
}

void OnOffEdit::setValue(bool value) {
	edit = value;
	save();
}

