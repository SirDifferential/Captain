/*SDL_Collide.h by Amir 'Genjix' Taaki released under GNU GPL
				genjix@gmail.com
	so far only been used on Linux :D*/

/*To use this function simply call, does a pixel perfect check on 2 surfaces
	
	SDL_Collide( SurfaceA , Ax , Ay , SurfaceB , Bx , By );
	
where SurfaceA and SurfaceB are 2 surfaces you want to test for collision
and x and y are both their x and y values

	SDL_BoundingCollide( SurfaceA , Ax , Ay , SurfaceB , Bx , By );
	
uses exactly the same syntax, except that it's
a million times faster and should be used when prefferable
(such as on small objects), as it only checks the surfaces bounding box

	SDL_BoundingCollide(RectA , RectB);

does the same except variables are conveniently loaded into SDL_Rect's
and passed to function*/

/*if this header is not supported on your system comment out
the assert function call in SDL_TransparentPixel*/
#include "assert.h"

/*returns maximum or minimum of number*/
#define SDL_COLLIDE_MAX(a,b)	((a > b) ? a : b)
#define SDL_COLLIDE_MIN(a,b)	((a < b) ? a : b)

/*
	returns 1 if offsets are a transparent pixel
*/
bool SDL_TransparentPixel(SDL_Surface *surface , int u , int v)
{
	/*assert that (u,v) offsets lie within surface*/
	assert( !((u < surface->w) || (v < surface->h)) );

	int bpp = surface->format->BytesPerPixel;
	/*here p is the address to the pixel we want to retrieve*/
	Uint8 *p = (Uint8 *)surface->pixels + v * surface->pitch + u * bpp;

	Uint32 pixelcolor;

	switch(bpp)
	{
		case(1):
			pixelcolor = *p;
		break;

		case(2):
			pixelcolor = *(Uint16 *)p;
		break;

		case(3):
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				pixelcolor = p[0] << 16 | p[1] << 8 | p[2];
			else
				pixelcolor = p[0] | p[1] << 8 | p[2] << 16;
		break;

		case(4):
			pixelcolor = *(Uint32 *)p;
		break;
	}

	/*test whether pixels color == color of transparent pixels for that surface*/
	return (pixelcolor == surface->format->colorkey);
}

/*
	SDL pixel perfect collision test
*/
int SDL_Collide(SDL_Surface *as , int ax , int ay , SDL_Surface *bs , int bx , int by)
{
	/*Box A;
	Box B;*/

	/*a - bottom right co-ordinates*/
	int ax1 = ax + as->w - 1;
	int ay1 = ay + as->h - 1;
	
	/*b - bottom right co-ordinates*/
	int bx1 = bx + bs->w - 1;
	int by1 = by + bs->h - 1;

	/*check if bounding boxes intersect*/
	if((bx1 < ax) || (ax1 < bx))
		return 0;
	if((by1 < ay) || (ay1 < by))
		return 0;


/*Now lets make the bouding box for which we check for a pixel collision*/

	/*To get the bounding box we do
	    Ax1,Ay1_____________
		|		|
		|		|
		|		|
		|    Bx1,By1_____________
		|	|	|	|
		|	|	|	|
		|_______|_______|	|
			|    Ax2,Ay2	|
			|		|
			|		|
			|____________Bx2,By2

	To find that overlap we find the biggest left hand cordinate
	AND the smallest right hand co-ordinate

	To find it for y we do the biggest top y value
	AND the smallest bottom y value

	Therefore the overlap here is Bx1,By1 --> Ax2,Ay2

	Remember	Ax2 = Ax1 + SA->w
			Bx2 = Bx1 + SB->w

			Ay2 = Ay1 + SA->h
			By2 = By1 + SB->h
	*/

	/*now we loop round every pixel in area of
	intersection
		if 2 pixels alpha values on 2 surfaces at the
		same place != 0 then we have a collision*/
	int inter_x0 = SDL_COLLIDE_MAX(ax,bx);
	int inter_x1 = SDL_COLLIDE_MIN(ax1,bx1);

	int inter_y0 = SDL_COLLIDE_MAX(ay,by);
	int inter_y1 = SDL_COLLIDE_MIN(ay1,by1);

	for(int y = inter_y0 ; y <= inter_y1 ; y++)
	{
		for(int x = inter_x0 ; x <= inter_x1 ; x++)
		{
			if((SDL_TransparentPixel(as , x-ax , y-ay))/*compute offsets for surface*/
			&& (SDL_TransparentPixel(bs , x-bx , y-by)))/*before pass to SDL_TransparentPixel*/
				return 1;
		}
	}
}

/*
	SDL bounding box collision test
*/
int SDL_BoundingCollide(SDL_Surface *sa , int ax , int ay , SDL_Surface *sb , int bx , int by)
{
	if(bx + sb->w < ax)	return 0;	/*Just checking if their*/
	if(bx > ax + sa->w)	return 0;	/*Bounding boxes even touch*/
						/*Write down on paper if*/
	if(by + sb->h < ay)	return 0;	/*Don't make sense*/
	if(by > ay + sa->h)	return 0;

	return 1;				/*Bouding boxes intersect*/
}

/*
	SDL bounding box collision tests (works on SDL_Rect's)
*/
int SDL_BoudingCollide(SDL_Rect a , SDL_Rect b)
{
	if(b.x + b.w < a.x)	return 0;	/*Just checking if their*/
	if(b.x > a.x + a.w)	return 0;	/*Bounding boxes even touch*/
						/*Write down on paper if*/
	if(b.y + b.h < a.y)	return 0;	/*Don't make sense*/
	if(b.y > a.y + a.h)	return 0;

	return 1;				/*Bouding boxes intersect*/
}


