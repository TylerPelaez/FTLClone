#pragma once
#ifndef _WEAPONSYSTEM_H
#include "ShipSystem.h"
#include "Weapon.h"
#include <array>

class WeaponSystem : public ShipSystem
{
	std::vector<Weapon*> weapons;
	int maxWeapons;
	
	int curActiveWeapons;
	int numTotalWeapons;

public:
	WeaponSystem( Room* _location = nullptr, int _maxPower = 0, int startingPower = 0, int _maxWeapons = 0)
		: ShipSystem(_location, _maxPower, startingPower)
		, maxWeapons(_maxWeapons)
		, curActiveWeapons(0)
		, numTotalWeapons(0)
	{}

	virtual void update( float dt ) override;

	void setWeaponActive(int index, bool active);

	void addWeapon( Weapon* weapon );

	void render() override;

};
#endif