/*
 * SetupEdit.h
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#ifndef SETUPEDIT_H_
#define SETUPEDIT_H_

#include "PropertyEdit.h"
#include "BarGraph.h"
#include "LiquidCrystal.h"

class SetupEdit : public PropertyEdit {
public:
	SetupEdit(LiquidCrystal& lcd_, std::string editTitle);
	virtual ~SetupEdit();
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

#endif /* SETUPEDIT_H_ */
