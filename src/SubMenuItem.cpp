/*
 * MenuItem.cpp
 *
 *  Created on: 1.2.2016
 *      Author: krl
 */

#include "SubMenuItem.h"

SubMenuItem::SubMenuItem(PropertyEdit& property, bool alamenu): focus(false), kohdalla(false), pe(property) {
	alamenullinen = alamenu;
	// Konstruktorissa ei tapahdu muuta, kuin etta aluksi focus ja kohdalla muuttujat ovat falseja.
	// Tama siksi, etta kun paavalikko avautuu, mitaan menua ei ole valittu,
	// ja nainollen mitaan numeroarvoja ei voida muuttaa (focus = false).
}

SubMenuItem::~SubMenuItem() {

}

bool SubMenuItem::event(menuEvent e) {
	bool handled = true;
	switch(e) { // Tassa tapahtuu asioita sen mukaan, mika tapahtuma on juuri tapahtunut.
	case ok:
		// Jos painettiin ok, selvitetaan ollaanko jo jokin menu valittu.
		// Jos ei ole, valitaan menu. Focusta ei kuitenkaan viela ole.

		// Jos menu on jo valittu (kohdalla == true), 
		// Ja jos focus on true, valittu lukuarvo tulee voimaan
		// Jos focusta ei viela ole, se asetetaan true:ksi, jolloin paastaan muuttamaan lukuarvoja.

		if (kohdalla == false) {
			kohdalla = true;
			focus = false;
			if (!alamenullinen) {
				focus = true;
			}
		} else if (kohdalla == true) {
			if (focus) {
				pe.accept();
				focus = false;

				if (!alamenullinen) {
					kohdalla = false;
				}

			}
			else {
				kohdalla = true;
				focus = true;
			}
		}

		// Lopuksi seka focus, etta kohdalla, -muuttujat asetetaan.
		pe.setFocus(focus);
		pe.setKohdalla(kohdalla);
		break;

	case back:
		// Jos painettiin back,
		// Jos focus on true, lukuarvo hylataan, ja focus laitetaan falseksi.
		// Jos focusta ei ole, alavalikosta tullaan paavalikkoon.
		if(focus) {
			pe.cancel();
			focus = false;
		}
		else {
			kohdalla = false;
		}
		if (alamenullinen == false) {
			if (!focus) {
				kohdalla = false;
			}
		}
		pe.setKohdalla(kohdalla);
		pe.setFocus(focus);
		break;

	case show:
		pe.setFocus(focus);
		break;
	case up:
		// Jos ylas,
		// Jos focus, nostetaan lukuarvoa,
		// Ja jos ei focusta, liikutaan alavalikossa.
		if(focus) pe.increment();
		else if (kohdalla) pe.increment();
		// Jos mitaan ei ole valittu, liikutaan paavalikossa:
		else handled = false;
		break;
	case down:
		if(focus) pe.decrement();
		else if (kohdalla) pe.decrement();
		// Jos mitaan ei ole valittu, liikutaan paavalikossa:
		else handled = false;
		break;
	}

	if(handled) pe.display();

	return (handled);
}

