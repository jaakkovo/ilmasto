/*
 * SubEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef STATUSEDIT_H_
#define STATUSEDIT_H_

#include "PropertyEdit.h"
#include <string>
#include <vector>

using namespace std;

class StatusEdit : public PropertyEdit {
public:
	// Luokan konstruktori saa otsikon, alamenun otsikot, alarajat ja ylarajat. Luokan raja-muuttujat alustetaan paaohjelmassa annetuilla arvoilla.
	StatusEdit(LiquidCrystal& lcd_, std::string editTitle, vector <string> tekstit, vector <int> ialarajat, vector <int> iylarajat) :  lcd(lcd_), title(editTitle), alamenut { tekstit }, alarajat{ ialarajat }, ylarajat{ iylarajat } {
		value = alarajat;
		edit = alarajat;
		nro = 0;
		focus = false;
		kohdalla = false;
	}

	virtual ~StatusEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();

	// setFocus maarittaa, onko arvo valittu vai ei.
	void setFocus(bool focus);

	// setKohdalla maarittaa, onko Setup-valikko avattu.
	void setKohdalla(bool kohdalla);

	void display();
	int getValue(int nro);
	void setValue(int nro, string value);
private:
	void save();

	// Itse paaotsikko (Setup)
	string title;

	// Luokkamuuttujina alarajat, ylarajat, seka jokaisen kohdan arvot, seka muutettu arvo (jota ei ole viela tallennettu).
	// Kun arvo tallennetaan, value:ksi laitetaan edit:in arvo.
	vector<int> alarajat;
	vector<int> ylarajat;
	vector <string> edit;
	vector<string> value;

	// Taulukko joka sisaltaa alamenujen otsikot.
	vector<string> alamenut;

	LiquidCrystal& lcd;
	int nro;

	bool focus;
	bool kohdalla;

};

#endif /* STATUSEDIT_H_ */
