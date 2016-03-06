/*
 * SubEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "SetupEdit.h"

#include <cstdio>
#include <iostream>

using namespace std;

SetupEdit::~SetupEdit() {
}

void SetupEdit::increment() {
	if (kohdalla && focus) {
		if (edit[nro] >= ylarajat[nro]) {
			edit[nro] = ylarajat[nro];
		}
		else {
			edit[nro]++;
		}
	} else if (kohdalla) {
		if (nro < alamenut.size()-1) {
			nro++;
		}
	}
	
}

void SetupEdit::decrement() {
	if (kohdalla && focus) {
		if (edit[nro] <= alarajat[nro]) {
			edit[nro] = alarajat[nro];
		}
		else {
			edit[nro]--;
		}
	}
	else if (kohdalla) {
		if (nro > 0) {
			nro--;
		}
	}
}

void SetupEdit::accept() {
	save();
}

void SetupEdit::cancel() {
	edit = value;
}


void SetupEdit::setFocus(bool focus) {
	this->focus = focus;
}

void SetupEdit::setKohdalla(bool kohdalla) {
	this->kohdalla = kohdalla;
}

void SetupEdit::display() {

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
		if (focus) {
			snprintf(c, 16, "     [%4d]     ", edit);
		}
		else {
			snprintf(c, 16, "      %4d      ", edit);
		}
		lcd.print(c);
	}

}




void SetupEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}


int SetupEdit::getValue(int nro) {
	return (value[nro]);
}
void SetupEdit::setValue(int nro, int value) {
	edit[nro] = value;
	save();
}
