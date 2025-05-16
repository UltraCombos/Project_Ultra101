#pragma once
#include "Cell.h"
class DotCell : public Cell //inheritance
{
public:
	DotCell(ofVec2f pos, ofVec2f vel) :Cell(pos, vel) {}
	void draw() override
	{
		ofFill();
		ofSetHexColor(0xDE3245);
		ofDrawCircle(_pos, 3);
	}
protected:
	void update() override
	{
		ofVec2f p = _pos*10;
		float t = ofGetElapsedTimef() * 0.1f;
		_vel += ofVec2f(ofSignedNoise(p.x, p.y, t), ofSignedNoise(p.x, t, p.y));
		_vel.normalize();
		_vel *= 2;
	}	
};