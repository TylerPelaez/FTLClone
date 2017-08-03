#pragma once
#ifndef _SYSTEM_H
#include "Room.h"
#include "RenderedObject.h"

class ShipSystem 
{
public:
	Room* location;

	int maxPower;
	int currentMaxPower;
	int currentPower;

	bool manned;

	ShipSystem(Room* _location = nullptr, int _maxPower = 0, int startingPower = 0)
		: location(_location)
		, maxPower(_maxPower)
		, currentMaxPower(startingPower)
		, currentPower(0)
		, manned(false)
	{}


	~ShipSystem()
	{
		location = nullptr;
	}

	virtual void update( float dt );

	virtual void render() { return; }


};
#endif