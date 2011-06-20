#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
#include <GL/glew.h>
#include "vector3.hpp"
#ifdef WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#endif


class Sprite
{
public:
	Sprite();
	Sprite(int x, int y);
	Sprite(const std::string &filename);
	virtual ~Sprite();
	
	virtual void render();
	void poke();
	void renderScale(float scale);
	void setPixels();
	void setPixel ( SDL_Surface* pSurface , int x , int y , SDL_Color color );
	void change(const std::string &filename);
	SDL_Color getPixel ( SDL_Surface* pSurface , int x , int y );
	GLenum check(SDL_Surface *surface, const string &filename);
	GLenum checkGenerated(SDL_Surface *surface);
	SDL_Color getRandomColor();
	float x, y;
	float w, h;
	float iterations;
	bool useBlend;
	GLenum format;
	GLuint id;
	float opacity;
	SDL_Surface *surface;
	std::string path;
};

#endif
