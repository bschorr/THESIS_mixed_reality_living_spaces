//
//  dining.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Dining.h"

void Dining::update()
{

}

void Dining::draw()
{
	ofBackground(255, 0, 0);
	ofDrawBitmapString("Dining", 30, 30);
}

string Dining::getName()
{
	return "dining";
}
