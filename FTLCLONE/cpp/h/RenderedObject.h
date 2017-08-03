#pragma once
#ifndef _RENDEREDOBJECT_H
#include "FTexture.h"

class RenderedObject
{
public:
	RenderedObject();

	virtual void render( SDL_Rect* clip = NULL );

	void setRotation( double degrees );

	bool loadIntoTexture( std::string path );

	virtual void setPos( int x, int y );

	int getPosX() { return m_Posx; }
	int getPosY() { return m_Posy; }
	int getWidth() { return m_Width; }
	int getHeight() { return m_Height; }

protected:
	FTexture m_FTexture;

	
	double angle;
	int m_Posx;
	int m_Posy;
	int m_Width;
	int m_Height;

};
#endif