/*
* IntegerEdit.h
*
*  Created on: 2.2.2016
*      Author: krl
*/

#ifndef TIMEEDIT_H_
#define TIMEEDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include <string>

class TimeEdit : public PropertyEdit {
public:
	TimeEdit(LiquidCrystal& lcd_, std::string editTitle);
	virtual ~TimeEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	int getValue();
	void setValue(int value);
private:
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	std::string title;
	int value;
	int edit;
	bool focus;

};

#endif /* TIMEEDIT_H_ */
