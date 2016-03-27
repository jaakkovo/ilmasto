/*
 * SubEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef SETUPEDIT_H_
#define SETUPEDIT_H_

#include "LiquidCrystal.h"
#include "PropertyEdit.h"
#include <string>
#include <vector>

using namespace std;

class SetupEdit : public PropertyEdit {
public:
	// Luokan konstruktori saa otsikon, alamenun otsikot, alarajat ja ylarajat. Luokan raja-muuttujat alustetaan paaohjelmassa annetuilla arvoilla.
	SetupEdit(LiquidCrystal& lcd_, std::string editTitle, vector <string> tekstit, vector <int> ialarajat, vector <int> iylarajat) :  lcd(lcd_), title(editTitle), alamenut { tekstit }, alarajat{ ialarajat }, ylarajat{ iylarajat } {
		value = alarajat;
		edit = alarajat;
		nro = alamenut.size()-1;
		focus = false;
		kohdalla = false;
	}

	virtual ~SetupEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();

	// setFocus maarittaa, onko arvo valittu vai ei.
	void setFocus(bool focus);

	// setKohdalla maarittaa, onko Setup-valikko avattu.
	void setKohdalla(bool kohdalla);

	void display();
	int getValue(int nrob);
	void setValue(int nrob, int value1);
private:
	LiquidCrystal& lcd;

	// Itse paaotsikko ("Setup")
	string title;

	// Taulukko joka sisaltaa alamenujen otsikot.
	vector<string> alamenut;

	// Luokkamuuttujina alarajat, ylarajat, seka jokaisen kohdan arvot, seka muutettu arvo (jota ei ole viela tallennettu).
	// Kun arvo tallennetaan, value:ksi laitetaan edit:in arvo.
	vector<int> alarajat;
	vector<int> ylarajat;

	
	vector<int> value;
	vector<int> edit;

	void save();

	int nro;

	bool focus;
	bool kohdalla;

};

#endif /* SETUPEDIT_H_ */
