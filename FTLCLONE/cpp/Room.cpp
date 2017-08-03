#include "h\Room.h"
#include "h\Ship.h"
#include "h\WeaponSystem.h"


Room::Room(Ship* _ship)
{
	ship = _ship;
	system = 0;
	posX = 0;
	posY = 0;
}

Room::~Room()
{
	if ( system )
		delete system;
}

void Room::doDamage( int amt )
{
	if (ship)
		ship->doDamage( amt );
	//system->DoDamage()
}

bool Room::assignSystem( ShipSystem* newSystem )
{
	if ( nullptr == newSystem )
		return false;

	if ( nullptr != system )
	{
		delete system;
		system = nullptr;
	}
	system = newSystem;

	ship->assignSystem( newSystem );
	if (system->location == nullptr )
		system->location = this;

	return true;
}

void Room::renderRoom()
{
}