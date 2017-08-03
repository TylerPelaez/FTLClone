#include "h\WeaponSystem.h"

void WeaponSystem::setWeaponActive( int index, bool active )
{
	weapons[index]->SetActive( active );
}

 void WeaponSystem::update( float dt )
 {
	 for ( auto& weapon : weapons )
	 {
		 weapon->update(dt);
	 }
 }

 void WeaponSystem::render()
 {
	 for ( auto& weapon : weapons )
	 {
		 weapon->render();
	 }
 }


 void WeaponSystem::addWeapon( Weapon* weapon )
 {
	 if ( !weapon || weapons.size() >= maxWeapons )
		 return;

	 weapons.push_back( weapon );
	 weapon->setPos( location->ship->getPosX() + location->ship->weaponPositions[weapons.size()-1][0], location->ship->getPosY() + location->ship->weaponPositions[weapons.size() - 1][1]);
 }