#pragma once
#include <iostream>

class GameObject{
public:
	GameObject(){};
	GameObject(int x, int y):x(x),y(y){};
	GameObject(int x, int y, char* image):x(x), y(y), image(image){};
	~GameObject(){}
	int Get_X() const { return x;}
	int Get_Y() const { return y;}
	int Get_Width() const { return width;}
	int Get_Height() const { return height;}
	char* Get_Image() const { return image; }
	void Set_X(int value) { x = value; }
	void Set_Y(int value) { y = value; }
	void Set_Image(char* value) { image = value; }

private:
	int x, y;

protected:
	char* image;
	int width, height;
};