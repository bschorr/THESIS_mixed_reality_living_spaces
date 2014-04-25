//
//  Library.cpp
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#include "Library.h"

void Library::update()
{

}

void Library::draw()
{
	ofBackground(0, 255, 255);
	ofDrawBitmapString("Library", 30, 30);
}

string Library::getName()
{
	return "library";
}
