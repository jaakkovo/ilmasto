/*
 * SubEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "StatusEdit.h"

#include <cstdio>
#include <iostream>

using namespace std;

StatusEdit::~StatusEdit() {
}

void StatusEdit::increment() {
	// Status asetetaan itsestään, sitä ei voi muuttaa.
}

void StatusEdit::decrement() {
	// Status asetetaan itsestään, sitä ei voi muuttaa.
}

void StatusEdit::accept() {
}

void StatusEdit::cancel() {
}


void StatusEdit::setFocus(bool focus) {
	// Statusta ei voida myöskään focusata.
}

void StatusEdit::setKohdalla(bool kohdalla) {
	this->kohdalla = kohdalla;
}

void StatusEdit::display() {

	if (!kohdalla) {
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print(title);
	}else if (kohdalla) {
		lcd.clear();
		lcd.setCursor(0,0);

		// TESTAA TÄMÄ LÄPI
		std::string s;
		for (const auto &piece : alamenut[nro]) s += piece;
		lcd.print(s);

		lcd.setCursor(0,1);
		char c[16];
		snprintf(c, 16, "      %4d      ", edit);
		lcd.print(c);
	}

}




void StatusEdit::save() {
	value = edit;
}


int StatusEdit::getValue(int nro) {
	return (value[nro]);
}
void StatusEdit::setValue(int nro, string value) {
	edit[nro] = value;
	save();
}
