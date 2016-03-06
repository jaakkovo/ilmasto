/*
 * SimpleMenu.h
 *
 *  Created on: 3.2.2016
 *      Author: krl
 */

#ifndef SIMPLEMENU_H_
#define SIMPLEMENU_H_
#include <vector>
#include "MenuItem.h"
#include "SubMenuItem.h"

class SimpleMenu {
public:
	SimpleMenu();
	virtual ~SimpleMenu();
	void addItem(MenuItem *item);
	void addItem(SubMenuItem *item);
	void event(MenuItem::menuEvent e);
	void event(SubMenuItem::menuEvent e);
private:
	// Simplemenu pitää kirjaa kaikista MenuItemeistä:
	std::vector<MenuItem *> items1;
	std::vector<SubMenuItem *> items2;
	// Pitää kirjaa siitä missä kohdassa päävalikkoa tällä hetkellä ollaan:
	int position;
	// Ja montako päävalikon kohtaa yhteensä on:
	int amountofitems;
};

#endif /* SIMPLEMENU_H_ */
