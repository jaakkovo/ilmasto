/*
 * SubEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "SetupEdit.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

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

	lcd.clear();
	lcd.setCursor(0,0);

	if (!kohdalla) {
		lcd.print(title);
	} else {
		lcd.print(alamenut[nro]);

		lcd.setCursor(0,1);
		if (focus) {
			lcd.print("[");
			lcd.print(edit[nro]);
			lcd.print("]");
		}
		else {
			lcd.print(edit[nro]);
		}
	}

}




void SetupEdit::save() {
	// set current value to be same as edit value
	value = edit;
}


int SetupEdit::getValue(int nro) {
	int palautus = value[nro];
	return palautus;
}
void SetupEdit::setValue(int nro, int value1) {
	edit[nro] = value1;
	save();
}
