//
//  Bedroom.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Bedroom.h"

void Bedroom::update()
{

}

void Bedroom::draw()
{
	ofBackground(0, 255, 0);
	ofDrawBitmapString("Bedroom", 30, 30);
}

string Bedroom::getName()
{
	return "bedroom";
}
