#pragma once
#include "Cell.h"
class SquareCell:public Cell //inheritance
{
public:
	SquareCell(ofVec2f pos, ofVec2f vel) :Cell(pos, vel), seed(ofRandom(10000)){}
	void draw() override
	{
		ofNoFill();
		float size = 15;
		ofSetHexColor(0x1FE816);
		ofDrawRectangle(_pos.x - 0.5*size, _pos.y-0.5*size, 0, size, size);
	}
protected:
	void update() override
	{
		float t = ofGetElapsedTimef() * 0.5f;
		ofVec2f noise(ofSignedNoise(seed, t), ofSignedNoise(t, seed));
		_vel = ofVec2f::zero();
		float step = 4;		
		if (noise.x <  0)
		{
			if(noise.y <0 )
				_vel.x = step;
			else
				_vel.x =-step;
		}
		else
		{			
			if (noise.y < 0)
				_vel.y = step;
			else
				_vel.y = -step;
		}		
	}
private:
	float seed;
};