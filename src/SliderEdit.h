/*
 * SliderEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef SliderEdit_H_
#define SliderEdit_H_

#include "PropertyEdit.h"
#include "BarGraph.h"
#include "LiquidCrystal.h"
#include <string>
#include "perkele.h"

class SliderEdit: public PropertyEdit {
public:
	SliderEdit(LiquidCrystal& lcd_, std::string editTitle, int ilower, int iupper);
	virtual ~SliderEdit();
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
	BarGraph bar;
	LiquidCrystal& lcd;
	std::string title;
	int value;
	int edit;
	bool focus;
	int lower;
	int upper;

};

#endif /* SliderEdit_H_ */
