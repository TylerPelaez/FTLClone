#pragma once
#ifndef _WEAPON_H
#include "Room.h"
#include "Ship.h"

class Weapon
{
	float maxCharge;
	float curCharge;
	bool active;
	Room* currentTarget;
	bool autoFire;
	RenderedObject sprite;
	int payloadDamage;
	int posX;
	int posY;
	int orientation;

public:
	Weapon( float _max, int _damage, int _orientation)
		: maxCharge(_max)
		, payloadDamage(_damage)
		, curCharge(0)
		, active(false)
		, currentTarget(nullptr)
		, autoFire(false)
		, posX(0)
		, posY(0)
		, orientation(_orientation)
	{}

	~Weapon() 
	{ 
		currentTarget = nullptr; 
	}

	virtual bool fire();

	void loadSprite(std::string path);

	void SetActive( bool on ) { active = on; }

	void update( float dt );

	void setPos( int x, int y );

	void render();
};
#endif