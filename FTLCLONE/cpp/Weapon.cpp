#include "h\Weapon.h"

void Weapon::update( float dt )
{
	if (active && curCharge <= maxCharge )
		curCharge += dt;
	if ( curCharge >= maxCharge  && currentTarget != nullptr )
	{
		fire();
	}
	// do things
}

bool Weapon::fire()
{
	bool ret = 1;

	if ( !active || !currentTarget )
	{
		ret = 0;
	}
	else
	{
		if ( curCharge < maxCharge )
		{
			ret = 0;
		}
		else
		{ // FIRST COMMENT COMING UP
			currentTarget->doDamage(payloadDamage); // Placeholder - this fire function probably wont ever get used anyway
			
			printf( "Weapon Fires!\n" );

			curCharge = 0.0;
			ret = 1;
		}
	}
	return ret;
}

void Weapon::loadSprite( std::string path )
{
	sprite.loadIntoTexture( path );
	
}

void Weapon::setPos( int x, int y )
{
	posX = x;
	posY = y;
	sprite.setPos( posX, posY );
}

void Weapon::render()
{
	sprite.render();
}


