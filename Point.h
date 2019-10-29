#pragma once
class Point 
{
private:
	float x;
	float y;
public:
	Point()
	{}
	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	float getX() 
	{
		return this->x;
	}
	float getY()
	{
		return this->y;
	}
	void setX(float x)
	{
		this->x = x;
	}
	void setY(float y)
	{
		this->y = y;
	}

};