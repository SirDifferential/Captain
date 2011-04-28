#ifdef WIN32
#include <SDL_image.h>
#else
#include <SDL/SDL_image.h>
#endif
#include "sprite.hpp"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "programManager.hpp"

#define dist(a, b, c, d) sqrt(double((a - c) * (a - c) + (b - d) * (b - d)))

void Sprite::setPixel ( SDL_Surface* pSurface , int x , int y , SDL_Color color ) 
{
	// http://www.gamedev.net/reference/programming/features/sdl2/page5.asp
	
	//convert color
	Uint32 col = SDL_MapRGB ( pSurface->format , color.r , color.g , color.b ) ;
	
	//determine position
	char* pPosition = ( char* ) pSurface->pixels ;
	
	//offset by y
	pPosition += ( pSurface->pitch * y ) ;
	
	//offset by x
	pPosition += ( pSurface->format->BytesPerPixel * x ) ;
	
	//copy pixel data
	memcpy ( pPosition , &col , pSurface->format->BytesPerPixel ) ;
}

SDL_Color Sprite::getPixel ( SDL_Surface* pSurface , int x , int y ) 
{
	// http://www.gamedev.net/reference/programming/features/sdl2/page5.asp
	
	SDL_Color color ;
	Uint32 col = 0 ;
	
	//determine position
	char* pPosition = ( char* ) pSurface->pixels ;
	
	//offset by y
	pPosition += ( pSurface->pitch * y ) ;
	
	//offset by x
	pPosition += ( pSurface->format->BytesPerPixel * x ) ;
	
	//copy pixel data
	memcpy ( &col , pPosition , pSurface->format->BytesPerPixel ) ;
	
	//convert color
	SDL_GetRGB ( col , pSurface->format , &color.r , &color.g , &color.b ) ;
	return ( color ) ;
}

GLenum Sprite::check(SDL_Surface *surface, const string &filename)
{
	if (!surface) {
		std::cout << "Surface " << filename << " is empty" << std::endl;
		throw string("SDL surface error:") += filename;
	}
	
	if ((surface->w & (surface->w - 1)) != 0 ||
		(surface->h & (surface->h - 1)) != 0) {
		SDL_FreeSurface(surface);
		throw "Image size must be in power of two";
	}
	
	/* Select texture format. */
	GLenum format;
	std::cout << "Checking format" << std::endl;
	if (surface->format->BytesPerPixel == 4)
	{
		format = GL_RGBA;
		useBlend == false;
		std::cout << "GL_RGBA" << std::endl;
	}
	else if (surface->format->BytesPerPixel == 3)
	{
		format = GL_RGB;
		useBlend == false;
		std::cout << "GL_RGB" << std::endl;
	}
	else if (surface->format->BytesPerPixel == 1)
	{
		format = GL_LUMINANCE;
		useBlend == false;
		std::cout << "GL_LUMI" << std::endl;
	}
	else {
		SDL_FreeSurface(surface);
		throw "Image format must be 8, 24 or 32 bits per pixel.";
	}
	return format;
}

GLenum Sprite::checkGenerated(SDL_Surface *surface)
{	
	
	/* Select texture format. */
	GLenum format;
	if (surface->format->BytesPerPixel == 4) {
		format = GL_RGBA;
	}
	else if (surface->format->BytesPerPixel == 3)
	{
		format = GL_RGB;
	}
	else if (surface->format->BytesPerPixel == 1) {
		format = GL_LUMINANCE;
	}
	else {
		SDL_FreeSurface(surface);
		throw "Image format must be 8, 24 or 32 bits per pixel.";
	}
	return format;
}

SDL_Color Sprite::getRandomColor()
{
	int min = 1;
	int max = 255;
	SDL_Color out;
	out.r = min + (double(rand())/RAND_MAX) * ((max-min) +1);
	out.g = min + (double(rand())/RAND_MAX) * ((max-min) +1);
	out.b = min + (double(rand())/RAND_MAX) * ((max-min) +1);
	return out;
}

void Sprite::setPixels()
{

	GLuint target = GL_TEXTURE_2D;

	// Lock the surface for direct pixel acccess
	SDL_LockSurface(surface);

	SDL_Color color;
	
	color.r = 200;
	color.b = 200;
	color.g = 200;
	
	// Set all pixels to 200
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			setPixel(surface, i, j, color);
		}
	}
	
	// Done, unlock
	SDL_UnlockSurface( surface );
	glTexImage2D(target,
		0,
		format,
		surface->w,
		surface->h,
		0,
		format,
		GL_UNSIGNED_BYTE,
		surface->pixels);
	
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Sprite::Sprite()
{
}

Sprite::Sprite(int x, int y)
{
	w = x;
	h = y;
	id = 0;
	glGenTextures(1, &id);
	assert(id);
	opacity = 1.0f;
	iterations = 0.0f;
	
	glBindTexture(GL_TEXTURE_2D, id);
	
	GLuint target = GL_TEXTURE_2D;
	bool buildMipmaps = false;
	surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
	
	// Get the texture format. We will want to create it according to the SDL surface
	// to avoid the problem we had earlier: texture having pillars due to trying to
	// use a RGB format glTexture2D with a RGBA SDL surface
	format = checkGenerated(surface);
	
	if (target == GL_TEXTURE_2D) {
		
		// Lock the surface for direct pixel acccess
		SDL_LockSurface(surface);
		
		SDL_Color color;
		
		// Init the surface with random colors
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				color = getRandomColor();
				setPixel(surface, i, j, color);
			}
		}
		
		// Done, unlock
		SDL_UnlockSurface( surface );
		if (buildMipmaps) {
			gluBuild2DMipmaps(target,
			format,
			surface->w,
			surface->h,
			format,
			GL_UNSIGNED_BYTE,
			surface->pixels);
		} else {
			glTexImage2D(target,
			0,
			format,
			surface->w,
			surface->h,
			0,
			format,
			GL_UNSIGNED_BYTE,
			surface->pixels);
		}
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}

Sprite::Sprite(const std::string &filename) :
	x(0), y(0)
{
	id = 0;
	glGenTextures(1, &id);
	assert(id);
	opacity = 0.0f;
	
	glBindTexture(GL_TEXTURE_2D, id);
	
	GLuint target = GL_TEXTURE_2D;
	bool buildMipmaps = true;
	if (surface != NULL)
		SDL_FreeSurface(surface);
	else
		surface = NULL;
	std::cout << "Loading " << filename << std::endl;
	if (target == GL_TEXTURE_CUBE_MAP) {
		for (int side=0; side<6; side++) {
			ostringstream f;
			f << filename << side << ".png";
			surface = IMG_Load(f.str().c_str());
			GLenum format = check(surface, f.str()), t;
			switch (side) {
			case 0: t = GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT; break;
			case 1: t = GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT; break;
			case 2: t = GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT; break;
			case 3: t = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT; break;
			case 4: t = GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT; break;
			case 5: t = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT; break;
			}
			if (buildMipmaps)
				gluBuild2DMipmaps(t,
				format,
				surface->w,
				surface->h,
				format,
				GL_UNSIGNED_BYTE,
				surface->pixels);
			else throw "Code me.";
			}
	}
	else if (target == GL_TEXTURE_2D) {
		surface = IMG_Load(filename.c_str());
		GLenum format = check(surface, filename);
		w = surface->w;
		h = surface->h;
		
		if (buildMipmaps) {
			gluBuild2DMipmaps(target,
			format,
			surface->w,
			surface->h,
			format,
			GL_UNSIGNED_BYTE,
			surface->pixels);
		} else {
			glTexImage2D(target,
			0,
			format,
			surface->w,
			surface->h,
			0,
			format,
			GL_UNSIGNED_BYTE,
			surface->pixels);
		}
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
}

Sprite::~Sprite()
{
	std::cout << "Deleting surface" << std::endl;
	assert(surface);
	SDL_FreeSurface(surface);
}

void Sprite::change(const std::string &filename)
{
	// The surface must be reseted before IMG_Load is called again
	// Otherwise apocalypses occur. Six guineapigs died for this reason...
	if (surface != NULL)
	{
		surface = NULL;
	}

	id = 0;
	glGenTextures(1, &id);
	assert(id);
	opacity = 0.0f;
	
	glBindTexture(GL_TEXTURE_2D, id);
	
	GLuint target = GL_TEXTURE_2D;
	bool buildMipmaps = true;
	if (surface != NULL)
		SDL_FreeSurface(surface);
	else
		surface = NULL;
	std::cout << "Loading " << filename << std::endl;
	if (target == GL_TEXTURE_CUBE_MAP) {
		for (int side=0; side<6; side++) {
			ostringstream f;
			f << filename << side << ".png";
			surface = IMG_Load(f.str().c_str());
			GLenum format = check(surface, f.str()), t;
			switch (side) {
			case 0: t = GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT; break;
			case 1: t = GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT; break;
			case 2: t = GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT; break;
			case 3: t = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT; break;
			case 4: t = GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT; break;
			case 5: t = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT; break;
			}
			if (buildMipmaps)
				gluBuild2DMipmaps(t,
				format,
				surface->w,
				surface->h,
				format,
				GL_UNSIGNED_BYTE,
				surface->pixels);
			else throw "Code me.";
			}
	}
	else if (target == GL_TEXTURE_2D) {
		surface = IMG_Load(filename.c_str());
		GLenum format = check(surface, filename);
		w = surface->w;
		h = surface->h;
		
		if (buildMipmaps) {
			gluBuild2DMipmaps(target,
			format,
			surface->w,
			surface->h,
			format,
			GL_UNSIGNED_BYTE,
			surface->pixels);
		} else {
			glTexImage2D(target,
			0,
			format,
			surface->w,
			surface->h,
			0,
			format,
			GL_UNSIGNED_BYTE,
			surface->pixels);
		}
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
}

void Sprite::poke()
{
	std::cout << "Surface being poked!" << std::endl;
	assert(surface);
}

void Sprite::render()
{	
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(x, y, 0);
	glScalef(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, id);
	glColor4f(1, 1, 1, opacity);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(-w, -h);
	glTexCoord2f(1, 1); glVertex2f(w, -h);
	glTexCoord2f(1, 0); glVertex2f(w, h);
	glTexCoord2f(0, 0); glVertex2f(-w, h);
	glEnd();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Sprite::renderScale(float scale)
{	
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(x, y, 0);
	glScalef(scale, scale, scale);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	// Implement some better way for checking if the sprite has 4 colour channels
	if (this->useBlend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	} else
	{
		glDisable(GL_BLEND);
	}
	glBlendEquation(GL_ADD);
	glBindTexture(GL_TEXTURE_2D, id);
	glColor4f(1, 1, 1, opacity);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(-w, -h);
	glTexCoord2f(1, 1); glVertex2f(w, -h);
	glTexCoord2f(1, 0); glVertex2f(w, h);
	glTexCoord2f(0, 0); glVertex2f(-w, h);
	glEnd();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
