#pragma once
#include "GameObject.h"

class Enemy{
public:
	Enemy(int x, int y);

	int Get_HP() const { return HP; }

	void Set_HP(int value) { HP = value; }
private:
	int HP;
};