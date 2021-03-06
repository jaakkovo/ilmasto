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
	edit[nro] = value[nro];
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

int SetupEdit::getValue(int nrob) {
	//printf("%d \n",value[nrob]);
	return (value[nrob]);
}
void SetupEdit::setValue(int nrob, int value1) {
	edit[nrob] = value1;
	save();
}
