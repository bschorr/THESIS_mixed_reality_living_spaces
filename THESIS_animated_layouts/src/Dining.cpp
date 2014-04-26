//
//  dining.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Dining.h"

void Dining::setup() {
    
    diningClock.setup ("dining_clock");
    
}

void Dining::update()
{

}

void Dining::draw()
{
	ofBackground(255, 0, 0);
	ofDrawBitmapString("Dining", 30, 30);
    diningClock.draw(100, 100, 200, 200);
}

string Dining::getName()
{
	return "dining";
}
