#include "renderer.hpp"
#include "opengl.hpp"
#include "manager.hpp"
#include "sprite.hpp"
#include "roommanager.hpp"

Renderer renderer;

Renderer::Renderer()
{
    fprintf(stderr, "Renderer being hammered together from an old radio and a roll of duct tape...\n");
    eye.x = 0;
    eye.y = 0;
    eye.z = 140;
    
    center.x = 0;
    center.y = 0;
    center.z = 0;
    nativeHeight = 140.0f;
    firstRun = true;
}

Renderer::~Renderer()
{
    fprintf(stderr, "Renderer rendered renderless...\n");
}

void Renderer::moveCamera(float coord_x, float coord_y, float coord_z)
{
   //eye.x = sin(manager.getTime())*150;
   //eye.y = cos(manager.getTime())*100;
    eye.x = coord_x;
    eye.y = coord_y;
    eye.z = coord_z;

    center.x = coord_x;
    center.y = coord_y;
    center.z = 0;
}

void Renderer::clearScreen()
{
    glClearColor(0.0,0.0,0.0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, manager.getOpengl()->getScreenX()/manager.getOpengl()->getScreenY(), 0.1, 1100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(	eye.x, eye.y, eye.z,
                center.x, center.y, center.z,
                0,1,0
              );
}

void Renderer::renderBackground()
{
}

void Renderer::renderMain()
{
    manager.getRoomMgr()->work();
}

void Renderer::renderForeground()
{
}

void Renderer::render()
{
    clearScreen();
    calculateLights();
    renderBackground();
    renderMain();
    renderForeground();
    manager.getOpengl()->swapBuffers();
}

void Renderer::renderObject(    GLenum primitiveType, int indiceCount, GLenum datatype,
                                std::vector<int> indices, std::vector<double> vertices,
                                std::vector<double> normals, Vector3 location,
                                float rotation, float scale
                            )
{
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glEnable(GL_NORMALIZE);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glTranslatef(location.x, location.y, location.z);
    glRotatef(rotation, 1.0f, 1.0f, 1.0f);
    
    glScalef(scale, scale, scale);
    glShadeModel(GL_FLAT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_DOUBLE, 0, &vertices[0]);
    glNormalPointer(GL_DOUBLE, 0, &normals[0]);
    glDrawElements(primitiveType, indiceCount, datatype, &indices[0]);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
    glPopMatrix();
}

void Renderer::calculateLights()
{
    glShadeModel(GL_SMOOTH);
    glColor3f(0.5, 0.5, 0.5);
    GLfloat whiteSpecularMaterial[] = {0.2, 0.2, 0.2};
    GLfloat whiteEmissiveMaterial[] = {0.2, 0.2, 0.2};
    GLfloat mShininess[] = {32};
    GLfloat white2DiffuseMaterial[] = {0.3, 0.3, 0.3};
    float mcolor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat ambientLight[] = { 0.3f, 0.4f, 0.2f, 0.7f };
    GLfloat diffuseLight[] = { 0.3f, 0.5f, 0.6f, 0.5f };
    GLfloat specularLight[] = { 0.4f, 0.4f, 0.8f, 0.7f };
    GLfloat position[] = { 0, 0, 60 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white2DiffuseMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, whiteEmissiveMaterial);
    glEnable(GL_LIGHT0);
}
