//
//  Cinema.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Cinema.h"

void Cinema::update()
{

}

void Cinema::draw()
{
	ofBackground(255, 255, 0);
	ofDrawBitmapString("Cinema", 30, 30);
}

string Cinema::getName()
{
	return "cinema";
}
