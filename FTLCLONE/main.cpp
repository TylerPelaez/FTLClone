#include "cpp\h\Globals.h"
#include <Windows.h>
#include <stdio.h>
#include <string>
#include "cpp\h\RenderedObject.h"
#include "cpp\h\Ship.h"
#include "cpp\h\WeaponSystem.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

bool quit = false;


Ship* playerShip = nullptr;
Ship* enemyShip = nullptr;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "FTL Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if ( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if ( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if ( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if ( !playerShip->loadIntoTexture( "assets/goodship.png" ) )
	{
		printf( "ERROR loading from file\n" );
		success = false;
	}
	else
	{
		playerShip->setPos( 100, 100 );
	}
	if ( !enemyShip->loadIntoTexture( "assets/ftilenemy.png" ) )
	{
		printf( "ERROR loading from file\n" );
		success = false;
	}
	else
	{
		enemyShip->setPos( 800, 100 );
	}


	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void render()
{
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	playerShip->render();
	enemyShip->render();

	//Update screen
	SDL_RenderPresent( gRenderer );
}

void update( float dt )
{
	playerShip->update( dt );
	enemyShip->update( dt );
}

int main( int argc, char* args[] )
{


	//Start up SDL and create window
	if ( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		playerShip = new Ship(4,5, ALLEGIANCE::FEDERATION, "Kestrel", 10, 0, 0, 40, WEAPON_ORIENTATION::RIGHT);
		enemyShip = new Ship(2,5, ALLEGIANCE::REBEL, "Federation Scout", 35, 20, 5, 10, WEAPON_ORIENTATION::UP);
		playerShip->weaponPositions[0].push_back( 411 );
		playerShip->weaponPositions[0].push_back( 111 );

		enemyShip->weaponPositions[0].push_back( 52 );
		enemyShip->weaponPositions[0].push_back( 91 );

		//Load media
		if ( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{

			Room* weaponRoom = new Room( playerShip );
			weaponRoom->posX = 173;
			weaponRoom->posY = 155;

			ShipSystem* weapons = new WeaponSystem( weaponRoom, 10, 3, playerShip->maxWeapons );
			Weapon* weaponToAdd = new Weapon( 10.0, 5, playerShip->weaponOrientation );
			weaponToAdd->loadSprite( "assets/Basic_Laser.png" );

			( (WeaponSystem*)weapons )->addWeapon( weaponToAdd );

			weaponRoom->assignSystem( weapons );
			playerShip->assignRoom( weaponRoom );

			weaponRoom = new Room( enemyShip );
			weaponRoom->posX = 92;
			weaponRoom->posY = 144;


			weapons = new WeaponSystem( weaponRoom, 10, 3, enemyShip->maxWeapons );
			weaponToAdd = new Weapon( 5.0, 1, enemyShip->weaponOrientation );
			weaponToAdd->loadSprite( "assets/Basic_Laser.png" );

			( (WeaponSystem*)weapons )->addWeapon( weaponToAdd );

			weaponRoom->assignSystem( weapons );
			enemyShip->assignRoom( weaponRoom );

			//Main loop flag
			quit = false;

			//Event handler
			SDL_Event e;

			double t = 0.0;
			const double dt = 1.0 / 60.0;  // delta time for 60 FPS

			double currentTime = SDL_GetTicks();
			double accumulator = 0.0;


			//While application is running
			while ( !quit )
			{
				//Handle events on queue
				while ( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if ( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				double newTime = SDL_GetTicks();
				double frameTime = newTime - currentTime;

				currentTime = newTime;

				accumulator += frameTime;

				while ( accumulator >= dt )
				{
					update( (float)dt );

					accumulator -= dt;
					t += dt;
				}
				render();
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}