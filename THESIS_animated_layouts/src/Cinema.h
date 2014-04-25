//
//  Cinema.h
//  THESIS_animated_layouts
//
//  Created by Bernardo Santos Schorr on 4/24/14.
//
//

#pragma once

#include "ofxState.h"
#include "SharedData.h"

class Cinema : public itg::ofxState<SharedData>
{
public:
	void update();
	void draw();
	string getName();
};
