/*
 * OnOffEdit.h
 *
 *  Created on: 18.2.2016
 *      Author: Jaakko
 */

#ifndef MANUAUTOEDIT_H_
#define MANUAUTOEDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include <string>

using namespace std;

class ManuAutoEdit : public PropertyEdit {
public:
	ManuAutoEdit(LiquidCrystal& lcd_, string editTitle);
	virtual ~ManuAutoEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	string getValue();
	void setValue(string value);

private:
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	string title;
	string value;
	string edit;
	bool focus;
};

#endif /* MANUAUTOEDIT_H_ */
