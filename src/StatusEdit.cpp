/*
 * SubEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "StatusEdit.h"

#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;

StatusEdit::~StatusEdit() {
}

void StatusEdit::increment() {
	if (kohdalla && !focus) {
		if (nro < alamenut.size()-1) {
			nro++;
		}
	}
}

void StatusEdit::decrement() {
	if (kohdalla && !focus) {
		if (nro > 0) {
			nro--;
		}
	}
}

void StatusEdit::accept() {
}

void StatusEdit::cancel() {
}


void StatusEdit::setFocus(bool focus) {
	this->focus = focus;
}

void StatusEdit::setKohdalla(bool kohdalla) {
	this->kohdalla = kohdalla;
}

void StatusEdit::display() {

	stringstream convert;
	stringstream ss;
	lcd.clear();
	lcd.setCursor(0,0);

	if (!kohdalla) {
		lcd.print(title);
	}else {
		lcd.print(alamenut[nro]);
		lcd.setCursor(0,1);
		if (focus){
			lcd.print(tietoja[nro]);
		}else{
			lcd.print(edit[nro]);
		}
	}
}




void StatusEdit::save() {
	value = edit;
}


string StatusEdit::getValue(int nro) {
	return (value[nro]);
}
void StatusEdit::setValue(int nro, string value) {
	edit[nro] = value;
	save();
}
