/*
 * OnOffEdit.h
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#ifndef ONOFFEDIT_H_
#define ONOFFEDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include <string>

class OnOffEdit : public PropertyEdit {
public:
	OnOffEdit(LiquidCrystal& lcd_, std::string editTitle);
	virtual ~OnOffEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	bool getValue();
	void setValue(bool value);

private:
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	std::string title;
	bool value;
	bool edit;
	bool focus;
};

#endif /* ONOFFEDIT_H_ */
