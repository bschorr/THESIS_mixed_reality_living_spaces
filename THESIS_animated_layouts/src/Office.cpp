//
//  Office.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Office.h"

void Office::update()
{
    officeClock.setup("office_clock");
}

void Office::draw()
{
	ofBackground(0, 0, 255);
	ofDrawBitmapString("Office", 30, 30);
    officeClock.draw(200, 200, 200, 200);
}

string Office::getName()
{
	return "office";
}
