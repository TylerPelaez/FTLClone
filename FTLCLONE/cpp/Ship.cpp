#include "h\Ship.h"

void Ship::update( float dt )
{
	updateSystems( dt );
	/* updateSubsystems( dt );
	updateCrewMembers( dt );
	updateRooms( dt );*/
}

void Ship::doDamage( int amt )
{
	health -= amt;
	if ( health <= 0 )
	{
		gameOver();
	}
}

void Ship::updateSystems( float dt )
{
	for ( size_t i = 0; i < Systems.size(); i++ )
	{
		Systems[i]->update( dt );
	}
}

bool Ship::assignSystem( ShipSystem* system )
{
	if ( system == nullptr )
		return false;

	if ( Systems.size() < maxSystems )
	{
		Systems.push_back( system );
		return true;
	}

	return false;
}


void Ship::gameOver()
{
	printf( "YOU LOSE" );
	quit = true;
}

void Ship::assignRoom( Room* newRoom )
{
	Rooms.push_back( newRoom );
}

