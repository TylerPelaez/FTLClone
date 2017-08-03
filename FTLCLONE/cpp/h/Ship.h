#pragma once
#ifndef _SHIP_H
#include "RenderedObject.h"
#include "Crew.h"
#include "Room.h"
#include "ShipSystem.h"
#include <vector>
#include <tuple>

class WeaponSystem;

enum ALLEGIANCE
{
	FEDERATION,
	REBEL,
	PIRATE,
	NEUTRAL,
	FRIENDLY
};

enum WEAPON_ORIENTATION
{
	LEFT,
	RIGHT,
	UP
};

class Ship : public RenderedObject
{
private:
	void updateSystems( float dt );
	/*
	void updateSubsystems( double dt );
	void updateCrewMembers( double dt );
	*/

	void gameOver();

public: 

	Ship( int _maxWeapons, int _maxSystems, int _team = ALLEGIANCE::FEDERATION, std::string _name = "", int startingScrap = 0, int startingMissiles = 0, int startingDrones = 0, int _maxHealth = 0, int _orientation = WEAPON_ORIENTATION::LEFT )
		: maxWeapons( _maxWeapons )
		, team( _team )
		, name( _name )
		, scrap( startingScrap )
		, missiles( startingMissiles )
		, droneParts( startingDrones )
		, maxHealth( _maxHealth )
		, maxSystems( _maxSystems )
		, weaponOrientation( _orientation )
	{
		weaponPositions = std::vector<std::vector<int> >();
		for ( int i = 0; i < maxWeapons; i++ )
		{
			weaponPositions.push_back( std::vector<int>() );
		}
	}

	~Ship()
	{
		for ( size_t i = 0; i < CrewMembers.size(); i++ )
		{
			if ( CrewMembers[i] )
			{
				delete CrewMembers[i];
				CrewMembers[i] = nullptr;
			}
		}
		for ( size_t i = 0; i < Rooms.size(); i++ )
		{
			if ( Rooms[i] )
			{ 
				delete Rooms[i];
				Rooms[i] = nullptr;
			}
		}
	}
	
	int maxHealth;
	int health;
	int team;
	std::vector<Room*> Rooms;
	std::vector<ShipSystem*> Systems;
	std::vector<ShipSystem*> Subsystems;

	std::vector<Crew*> CrewMembers;
	std::string name;

	std::vector<std::vector<int> > weaponPositions;
	int weaponOrientation;

	const int maxWeapons;
	const int maxSystems;

	int scrap;
	int missiles;
	int droneParts;

	void assignRoom( Room* newRoom );

	void doDamage( int amt );

	void update( float dt );

	bool assignSystem( ShipSystem* system );

};
#endif