#pragma once
class Cell
{
protected:
	ofVec2f _pos;
	ofVec2f _vel;
public:
	Cell(ofVec2f pos = {0,0}, ofVec2f vel = {0,0}) :_pos(pos), _vel(vel) {}
	void move()
	{
		update();				
		bounce();
		_pos += _vel;
	}	
	virtual void draw()   = 0; //add virtual to support dynamic binding
protected:
	virtual void update() = 0; // " = 0 " means pure virtual(abstract)
private:
	void bounce()
	{
		if ((_pos.x > ofGetWidth() - 1 && _vel.x > 0
			|| _pos.x < 0 && _vel.x < 0)
			)
			_vel.x *= -1;

		if ((_pos.y > ofGetHeight() - 1 && _vel.y > 0
			|| _pos.y < 0 && _vel.y < 0)
			)
			_vel.y *= -1;
	}
};


