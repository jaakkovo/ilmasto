/*
 * StatusEdit.h
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#ifndef STATUSEDIT_H_
#define STATUSEDIT_H_

#include "PropertyEdit.h"
#include "BarGraph.h"
#include "LiquidCrystal.h"

class StatusEdit : public PropertyEdit {
public:
	StatusEdit(LiquidCrystal& lcd_, std::string editTitle);
	virtual ~StatusEdit();
	void accept();
	void cancel();
	void increment();
	void decrement();
	void setFocus(bool focus);
	void display();
	string getValue();
	void setValue(string value);

private:
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	std::string title;
	string value;
	string edit;
	bool focus;
};

#endif /* STATUSEDIT_H_ */
