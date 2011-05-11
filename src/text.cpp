#include "text.hpp"
#include <string>
#include "programManager.hpp"

Text::Text()
{
}

Text::Text(int x, int y, std::string input, std::string fontPath, int fontSize)
{
	w = x;
	h = y;
	font = TTF_OpenFont( fontPath.c_str(), fontSize );
	id = 0;
	glGenTextures(1, &id);
	assert(id);
	opacity = 1.0f;

	glBindTexture(GL_TEXTURE_2D, id);

	GLuint target = GL_TEXTURE_2D;

	textColor.r = 255;
	textColor.b = 255;
	textColor.g = 255;

	color1 = 1.0f;
	color2 = 1.0f;
	color3 = 1.0f;
	
	assert(font);
	surface = TTF_RenderText_Blended( font, input.c_str(), textColor );
	assert(surface);
	format = checkGenerated(surface);

	assert(surface);
	assert(surface->pixels);
	// 8 = 1 channel, alpha
	// 32 = RGBA
	assert(surface->format->BitsPerPixel == 32);
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
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	assert(surface);
}

void Text::render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, progmgr.getScreenX(), 0, progmgr.getScreenY(), -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(x, y, 0);
	glScalef(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	// SDL_Surface->glTexImage2D conversion made earlier. We have only the alpha
	// in the original surface, so we are taking the alpha, blending it to the
	// texture, then colouring the mask
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, id);
	glColor4f(color1, color2, color3, opacity);
	
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
