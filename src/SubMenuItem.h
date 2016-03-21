/*
 * MenuItem.h
 *
 *  Created on: 1.2.2016
 *      Author: krl
 */

#ifndef SUBMENUITEM_H_
#define SUBMENUITEM_H_

#include "PropertyEdit.h"


class SubMenuItem {
public:
	// Mita tapahtumia MenuItem:illa on. Ylos, alas, ok, back, ja nayta.
	enum menuEvent {
		up,
		down,
		ok,
		back,
		show
	};
	SubMenuItem(PropertyEdit& property, bool alamenu);
	virtual ~SubMenuItem();
	virtual bool event(menuEvent e);
private:
	// Jokaisella MenuItemilla on siis omat focus, kohdalla ja pointteri joka osoittaa propertyedit-ylaluokkaan.
	bool focus;
	bool kohdalla;
	bool alamenullinen;
	PropertyEdit& pe;
};

#endif /* SUBMENUITEM_H_ */
