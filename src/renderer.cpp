#include "renderer.hpp"
#include <GL/glew.h>
#include "vector3.hpp"
#include "programManager.hpp"
#include "objectManager.hpp"
#include "stars.hpp"

typedef boost::shared_ptr<Text> TextPtr;
typedef boost::shared_ptr<Sprite> SpritePtr;

Renderer renderer;

namespace {
	Vector3 eye;
	Vector3 center;
}

Renderer::Renderer()
{
	eye.x = 0;
	eye.y = 0;
	eye.z = 50;
	
	center.x = 0;
	center.y = 0;
	center.z = 0;
}

Renderer::~Renderer()
{
}

void Renderer::renderBase()
{
	glClearColor(0.0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(65, progmgr.getScreenX()/progmgr.getScreenY(), 0.1, 150);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(eye.x, eye.y, eye.z,
              center.x, center.y, center.z,
              0, 1, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, progmgr.getScreenX(), 0, progmgr.getScreenY(), -1, 1);
}

void Renderer::renderBackground()
{
	objectmgr.renderBackground();
}

void Renderer::renderObjects()
{
	objectmgr.render();
}

void Renderer::renderForeground()
{
}

void Renderer::render()
{
	renderBase();
	renderBackground();
	renderObjects();
	renderForeground();
}

void Renderer::renderTriangle(float *v1, float *v2, float *v3) 
{
	glBegin(GL_POLYGON);
		glNormal3fv(v1); glVertex3fv(v1);
		glNormal3fv(v2); glVertex3fv(v2);
		glNormal3fv(v3); glVertex3fv(v3);
	glEnd(); 
}

void Renderer::normalize(float v[3])
{
	GLfloat d = sqrt(v[0]*v[1]+v[1]*v[1]+v[2]*v[2]);
	if (d = 0.0)
	{
		return;
	}
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}


void normcrossprod(float v1[3], float v2[3], float out[3]) 
{ 
   GLint i, j; 
   GLfloat length;

   out[0] = v1[1]*v2[2] - v1[2]*v2[1]; 
   out[1] = v1[2]*v2[0] - v1[0]*v2[2]; 
   out[2] = v1[0]*v2[1] - v1[1]*v2[0]; 
   normalize(out); 
}

void Renderer::normcrossprod(float v1[3], float v2[3], float out[3])
{
	GLint i, j;
	GLfloat length;

	out[0] = v1[1]*v2[2] - v1[2]*v2[1];
	out[1] = v1[2]*v2[0] - v1[0]*v2[2];
	out[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

void Renderer::renderVertexArray(GLfloat vertices[], GLubyte indices[], GLfloat normals[], GLfloat colors[], float rotation, int numberOfVertices)
{
	glShadeModel(GL_SMOOTH);
	glColor3f(0.1, 0.5, 0.3);

    // enable and specify pointers to vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normals);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glLoadIdentity();
	glScalef(0.3, 0.3, 0.3);
    glTranslatef(0.0f, 0.0f, -1.0f);
    glRotatef(rotation, 3.0f, 0.0f, 1.0f);
	
    glDrawArrays(GL_QUADS, 0, numberOfVertices);
	
    glPopMatrix();
	
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat ambientLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	float colorBlue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	float mcolor[] = { 1.0f, 0.3f, 0.9f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glEnable(GL_LIGHT0);
}
