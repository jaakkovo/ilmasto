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

	if (!kohdalla) {
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print(title);
	}else if (kohdalla) {
		lcd.clear();
		lcd.setCursor(0,0);
		std::string s;

		ss << alamenut[nro];
		s = ss.str();
		lcd.print(s);
		lcd.setCursor(0,1);
		if (focus){
			convert << tietoja[nro];
			s = convert.str();
			lcd.print(s);
		}else{
			convert << edit[nro];
			s = convert.str();
			lcd.print(s);
		}


	}

}




void StatusEdit::save() {
	value = edit;
}


string StatusEdit::getValue(int nro) {
	std::string s;
	s = value[nro];

	return (s);
}
void StatusEdit::setValue(int nro, string value) {
	edit[nro] = value;
	save();
}
