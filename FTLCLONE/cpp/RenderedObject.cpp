#include "h\RenderedObject.h"

RenderedObject::RenderedObject()
{
	m_FTexture = FTexture();
	m_Posx = 0;
	m_Posy = 0;
	m_Width = 0;
	m_Height = 0;
	angle = 0;
}

bool RenderedObject::loadIntoTexture( std::string path )
{
	bool ret = m_FTexture.loadFromFile( path );
	m_Width = m_FTexture.getWidth();
	m_Height = m_FTexture.getHeight();
	return ret;
}

void RenderedObject::render( SDL_Rect* clip )
{
	SDL_Rect renderQuad = { m_Posx, m_Posy, m_Width, m_Height };

	if ( NULL != clip )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	m_FTexture.render( clip, renderQuad, angle );
}

void RenderedObject::setRotation( double degrees )
{
	angle = degrees;
}


void RenderedObject::setPos( int x, int y )
{
	m_Posx = x;
	m_Posy = y;
}