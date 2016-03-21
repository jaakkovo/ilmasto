<<<<<<< HEAD
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
		nro = 0;
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
	int getValue(int nro);
	void setValue(int nro, int value);
private:
	void save();

	// Itse paaotsikko ("Setup")
	string title;

	// Luokkamuuttujina alarajat, ylarajat, seka jokaisen kohdan arvot, seka muutettu arvo (jota ei ole viela tallennettu).
	// Kun arvo tallennetaan, value:ksi laitetaan edit:in arvo.
	vector<int> alarajat;
	vector<int> ylarajat;
	vector <int> edit;
	vector<int> value;

	// Taulukko joka sisaltaa alamenujen otsikot.
	vector<string> alamenut;

	LiquidCrystal& lcd;
	int nro;

	bool focus;
	bool kohdalla;

};

#endif /* SETUPEDIT_H_ */
=======
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
		nro = 0;
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
	int getValue(int nro);
	void setValue(int nro, int value);
private:
	void save();

	// Itse paaotsikko ("Setup")
	string title;

	// Luokkamuuttujina alarajat, ylarajat, seka jokaisen kohdan arvot, seka muutettu arvo (jota ei ole viela tallennettu).
	// Kun arvo tallennetaan, value:ksi laitetaan edit:in arvo.
	vector<int> alarajat;
	vector<int> ylarajat;
	vector <int> edit;
	vector<int> value;

	// Taulukko joka sisaltaa alamenujen otsikot.
	vector<string> alamenut;

	LiquidCrystal& lcd;
	int nro;

	bool focus;
	bool kohdalla;

};

#endif /* SETUPEDIT_H_ */
>>>>>>> parent of 3a4741b... v0.91
