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

// Reset the viewing position so that we are watching directly down
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

// Render the basic stuff that is needed for establishing a work space for
// other rendering. In short, clear screen
void Renderer::renderBase()
{
	glClearColor(0.0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(65, progmgr.getScreenX()/progmgr.getScreenY(), 0.1, 50);

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

// Ask the Object Manager to render our current main background. Also, lights
void Renderer::renderBackground()
{
	renderLamps();
	objectmgr.renderBackground();
}

// Ask the Object Manager to render all its objects. This can be a BIG list
void Renderer::renderObjects()
{
	objectmgr.render();
}

// Render whatever comes on top of everything. HUD is one, possibly some
// effects go here as well, such as blur and glow? Who knows, gotta study
void Renderer::renderForeground()
{
	objectmgr.renderHUD();
}

// Call the above functions in the correct order
void Renderer::render()
{
	renderBase();
	renderBackground();
	renderObjects();
	renderForeground();
}

// Render a single triangle
void Renderer::renderTriangle(float *v1, float *v2, float *v3) 
{
	glBegin(GL_POLYGON);
		glNormal3fv(v1); glVertex3fv(v1);
		glNormal3fv(v2); glVertex3fv(v2);
		glNormal3fv(v3); glVertex3fv(v3);
	glEnd();
}

// Normalize a vertice
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

// Calculate the normal cross product for 2 vertices
void Renderer::normcrossprod(float v1[3], float v2[3], float out[3])
{
	GLint i, j;
	GLfloat length;

	out[0] = v1[1]*v2[2] - v1[2]*v2[1];
	out[1] = v1[2]*v2[0] - v1[0]*v2[2];
	out[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

// Render all ours lamps. This function is a STUB right now.
void Renderer::renderLamps()
{
        glShadeModel(GL_SMOOTH);
        //glColor3f(0.5, 0.9, 0.9);
        GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
        GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};
        GLfloat mShininess[] = {128};
        GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0};
        float mcolor[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
        GLfloat diffuseLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
        GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        GLfloat position[] = { 0, 0, 0 };
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
	
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mcolor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
        glEnable(GL_LIGHT0);

}

// An obsolete function, please don't use this
void Renderer::renderVertexArray(GLfloat vertices[], GLubyte indices[], GLfloat normals[], GLfloat colors[],
								 float rotation, int numberOfVertices, float scale, Vector3 trans, Vector3 colour)
{
	glShadeModel(GL_SMOOTH);
	/*
	//glColor3f(0.5, 0.9, 0.9);
	GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
	GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};
	GLfloat mShininess[] = {128};
	GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0};
	float mcolor[] = { colour.x, colour.y, colour.z, 1.0f };
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat ambientLight[] = { colour.x, colour.y, colour.z, 1.0f };
	GLfloat diffuseLight[] = { colour.x, colour.y, colour.z, 1.0f };
	GLfloat specularLight[] = { colour.x, colour.y, colour.z, 1.0f };
	GLfloat position[] = { trans.x, trans.y, trans.z };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mcolor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
	glEnable(GL_LIGHT0);
	*/
	// enable and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glLoadIdentity();
	glScalef(scale, scale, scale);
	glTranslatef(trans.x, trans.y, trans.z);
	glRotatef(rotation, 3.0f, 0.0f, 1.0f);
	
	glDrawArrays(GL_QUADS, 0, numberOfVertices);
	
	glPopMatrix();
	
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

// An obsolete function, please don't use this either
void Renderer::renderVertexArray(std::vector<double> vertices, std::vector<double> normals, std::vector<double> indices, int numberOfVertices)
{
        glShadeModel(GL_SMOOTH);
        //glColor3f(0.5, 0.9, 0.9);
	/*
        GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
        GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};
        GLfloat mShininess[] = {128};
        GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0};
        float mcolor[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
        GLfloat diffuseLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
        GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        GLfloat position[] = { 0, 0, 0 };
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
	
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mcolor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
        glEnable(GL_LIGHT0);
	*/
	// enable and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	
        glLoadIdentity();
        glScalef(1.0f, 1.0f, 1.0f);
	//glTranslatef(trans.x, trans.y, trans.z);
	//glRotatef(rotation, 3.0f, 0.0f, 1.0f);
	
	glDrawArrays(GL_QUADS, 0, numberOfVertices);
	
	glPopMatrix();
	
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

// A good function, use this.
// Renders an object using its vertice, normal and indice arrays by sending the
// data via glDrawElements. Params are pretty much the same as for glDrawElements, except for some slight modifications and additions.
void Renderer::renderObject(GLenum primitiveType, int indiceCount, GLenum datatype, std::vector<int> indices, std::vector<double> vertices, std::vector<double> normals, Vector3 location, float rotation, float scale)
{
	//glLoadIdentity();
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_LIGHTING);
	
	glColor4f(1,1,1,1);
	
	//glScalef(scale, scale, scale);
	glTranslatef(location.x, location.y, location.z);
	glRotatef(rotation, rotation, rotation, 1.0f);
	
	glScalef(1.0f, 1.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glVertexPointer(3, GL_DOUBLE, 0, &vertices[0]);
	glNormalPointer(GL_DOUBLE, 0, &normals[0]);
	glDrawElements(primitiveType, indiceCount, datatype, &indices[0]);
	glPopMatrix();
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

