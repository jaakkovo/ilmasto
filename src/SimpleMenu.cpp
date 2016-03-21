/*
 * SimpleMenu.cpp
 *
 *  Created on: 3.2.2016
 *      Author: krl
 */

#include "SimpleMenu.h"
#include <iostream>
using namespace std;

SimpleMenu::SimpleMenu() {
	// Pelkkä menun luominen (kun yhtään valikkoa ei ole tehty), kohta on 0 ja menujen määrä 0.
	position = 0;
	amountofitems = 0;
}

SimpleMenu::~SimpleMenu() {
}

void SimpleMenu::addItem(MenuItem *item) {
	// Tässä items -taulukkoon lisätään menun kohta. Samalla menujen määrä kasvaa yhdellä.
	items1.push_back(item);
	amountofitems++;
}

void SimpleMenu::addItem(SubMenuItem *item) {
	// Tässä items -taulukkoon lisätään menun kohta. Samalla menujen määrä kasvaa yhdellä.
	items2.push_back(item);
	amountofitems++;
}


void SimpleMenu::event(MenuItem::menuEvent e) {
	// Jos yhtään valikon kohtaa ei ole:
	if (items1.size() <= 0) return;

	// Jos nykyisen valikon tapahtuma ei palauta mitään
	// Eli jos valikkoa ei ole valittu, eikä focusta ole,
	// Liikutaan päävalikossa. Lopussa näytetään nykyinen valikko.
	if (!items1[position]->event(e)) {
		if (e == MenuItem::down && position < (amountofitems - 1)) {
			position++;
		}
		else if (e == MenuItem::up && position > 0) {
			position--;
		}

		items1[position]->event(MenuItem::show);
	}
}


void SimpleMenu::event(SubMenuItem::menuEvent e) {
	// Jos yhtään valikon kohtaa ei ole:
	if(items2.size() <= 0) return;

	// Jos nykyisen valikon tapahtuma ei palauta mitään
	// Eli jos valikkoa ei ole valittu, eikä focusta ole,
	// Liikutaan päävalikossa. Lopussa näytetään nykyinen valikko.
	if(!items2[position]->event(e)) {
		if (e == SubMenuItem::down && position < (amountofitems-1)) {
			position++;
		}
		else if (e == SubMenuItem::up && position > 0) {
			position--;
		}

		items2[position]->event(SubMenuItem::show);
	}
}
