#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	Vector2(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_) {}

	~Vector2() 
	{ 
		x = 0.0f;
		y = 0.0f;
	}

	float x, y;
};

#endif