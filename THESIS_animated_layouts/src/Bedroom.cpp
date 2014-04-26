//
//  Bedroom.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Bedroom.h"

void Bedroom::setup()
{
    bedroomClock.setup( "bedroom_clock" );
    
}

void Bedroom::update()
{

}

void Bedroom::draw()
{
	ofBackground(200);
	ofDrawBitmapString("Bedroom", 30, 30);
    bedroomClock.draw(150, 150, 200, 200);
}

string Bedroom::getName()
{
	return "bedroom";
}
