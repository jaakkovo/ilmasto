/*
 * DecimalEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef DecimalEdit_H_
#define DecimalEdit_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include <string>

class DecimalEdit: public PropertyEdit {
public:
	DecimalEdit(LiquidCrystal& lcd_, std::string editTitle, float lower, float upper);
	virtual ~DecimalEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	int getValue();
	void setValue(float value);
private:
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	std::string title;
	float value;
	float edit;
	bool focus;
	float lower;
	float upper;
};

#endif /* DecimalEdit_H_ */
