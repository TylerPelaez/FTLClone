#pragma once
#ifndef _ROOM_H
class Ship;
class ShipSystem;

class Room
{
public:
	int posX;
	int posY;

	int width;
	int height;

	Ship* ship;
	ShipSystem* system;
	
	void renderRoom();

	bool assignSystem(ShipSystem* newSystem);


	Room(Ship* _ship);
	~Room();

	void doDamage( int amt );
};
#endif