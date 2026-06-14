#include<GL/glut.h>
#include<math.h>
#include<string.h>
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

using namespace std;

// angle of rotation for the camera direction
float angle = 0.0, yAngle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = -5.0f, z = 18.0f;
float roll = 0.0f;

//for mouse movements
float halfWidth = (float)(WINDOW_WIDTH/2.0);
float halfHeight = (float)(WINDOW_HEIGHT/2.0);
float mouseX = 0.0f, mouseY = 0.0f;

// Light on/off flag
bool lightsOn = true;

// Texture ID for walls only
GLuint wallTexture;

void display();
void reshape(int,int);
void init()

{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // Set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Ambient light
    GLfloat ambientLight[] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    // Diffuse light (bright white)
    GLfloat diffuseColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);

    // Light position (ceiling center)
    GLfloat lightPos[] = {0.0f, 6.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Create Wall Texture only
    glGenTextures(1, &wallTexture);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    unsigned char wallData[256][256][3];
    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < 256; j++) {
            wallData[i][j][0] = 237;
            wallData[i][j][1] = 235;
            wallData[i][j][2] = 213;
            if((i/40 + j/40) % 3 == 0) {
                wallData[i][j][0] = 220;
                wallData[i][j][1] = 218;
                wallData[i][j][2] = 196;
            }
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, wallData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void chair()
{
    glColor3f(0.5f, 0.5f, 0.0f);
	glBegin(GL_QUADS);

	//Front
	//
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);

	//Right
	//
	glVertex3f(2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);

	//Back
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//Left
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);

	//top
	//

	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);

	//bottom

	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//table front leg
	//front
	//
    glColor3f(.8f, .6f, 0.0f);
	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -3.0f, 1.6f);
	glVertex3f(1.8f, -3.0f, 1.6f);

	//back
	//;

	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.2f);

	//right
	//

	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.6f);

	//left

	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.6f);

	//back leg back
	//front

	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.2f);

	//back

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -3.0f, -1.6f);
	glVertex3f(1.8f, -3.0f, -1.6f);

	//right
	//

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.6f);

	//left
	//

	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.6f);

	//leg left front

	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -3.0f, 1.6f);
	glVertex3f(-1.8f, -3.0f, 1.6f);

	//back

	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -3.0f, 1.2f);
	glVertex3f(-1.8f, -3.0f, 1.2f);

	//right


	glVertex3f(-1.8f, -0.2f, 1.6f);
	glVertex3f(-1.8f, -0.2f, 1.2f);
	glVertex3f(-1.8f, -3.0f, 1.2f);
	glVertex3f(-1.8f, -3.0f, 1.6f);

	//left

	glVertex3f(-1.4f, -0.2f, 1.6f);
	glVertex3f(-1.4f, -0.2f, 1.2f);
	glVertex3f(-1.4f, -3.0f, 1.2f);
	glVertex3f(-1.4f, -3.0f, 1.6f);

	//left leg back front

	//front

	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -3.0f, -1.2f);
	glVertex3f(-1.8f, -3.0f, -1.2f);

	//back

	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -3.0f, -1.6f);
	glVertex3f(-1.8f, -3.0f, -1.6f);

	//right


	glVertex3f(-1.8f, -0.2f, -1.6f);
	glVertex3f(-1.8f, -0.2f, -1.2f);
	glVertex3f(-1.8f, -3.0f, -1.2f);
	glVertex3f(-1.8f, -3.0f, -1.6f);

	//left


	glVertex3f(-1.4f, -0.2f, -1.6f);
	glVertex3f(-1.4f, -0.2f, -1.2f);
	glVertex3f(-1.4f, -3.0f, -1.2f);
	glVertex3f(-1.4f, -3.0f, -1.6f);

	//chair back
	//front


	//chair upper part
	glColor3f(0.5,0.5,0);
	glVertex3f(-1.8f, 1.2f, -1.8f);
	glVertex3f(1.8f, 1.2f, -1.8f);
	glVertex3f(1.8f, 3.5f, -1.8f);
	glVertex3f(-1.8f, 3.5f, -1.8f);

	glVertex3f(-1.8f, 1.2f, -0.6f);
	glVertex3f(1.8f, 1.2f, -0.6f);
	glVertex3f(1.8f, 3.5f, -0.6f);
	glVertex3f(-1.8f, 3.5f, -0.6f);

	//chair upper side
	glColor3f(1, 1, 0.4);
	glVertex3f(-1.8f, 1.2f, -1.80f);
	glVertex3f(-1.8f, 1.2f, -0.6f);
	glVertex3f(-1.8f, 3.5f, -0.6f);
	glVertex3f(-1.8f, 3.5f, -1.8f);

	glVertex3f(1.8f, 1.2f, -1.80f);
	glVertex3f(1.8f, 1.2f, -0.6f);
	glVertex3f(1.8f, 3.5f, -0.6f);
	glVertex3f(1.8f, 3.5f, -1.8f);

	//chiar upper top
	glColor3f(1, 1, 0);
	glVertex3f(-1.8f, 3.5f, -1.80f);
	glVertex3f(-1.8f, 3.5f, -0.6f);
	glVertex3f(1.8f, 3.5f, -0.6f);
	glVertex3f(1.8f, 3.5f, -1.8f);

	glVertex3f(-1.8f, 1.2f, -1.80f);
	glVertex3f(-1.8f, 1.2f, -0.6f);
	glVertex3f(1.8f, 1.2f, -0.6f);
	glVertex3f(1.8f, 1.2f, -1.8f);

	// chair top legs

	glColor3f(1.0, 1.0, 0.0);
	//side walls
	glVertex3f(-1.2f, 1.2f, -1.20f);
	glVertex3f(-1.2f, 1.2f, -0.6f);
	glVertex3f(-1.2f, .2f, -0.6f);
	glVertex3f(-1.2f, .2f, -1.2f);

	glVertex3f(-.8f, 1.2f, -1.20f);
	glVertex3f(-.8f, 1.2f, -0.6f);
	glVertex3f(-.8f, .2f, -0.6f);
	glVertex3f(-.8f, .2f, -1.2f);

	//froont walls adnd back walls
	glVertex3f(-1.2f, 1.2f, -1.2f);
	glVertex3f(-0.8f, 1.2f, -1.2f);
	glVertex3f(-0.8f, .2f, -1.2f);
	glVertex3f(-1.2f, .2f, -1.2f);

	glVertex3f(-1.2f, 1.2f, -0.6f);
	glVertex3f(-0.8f, 1.2f, -0.6f);
	glVertex3f(-0.8f, .2f, -0.6f);
	glVertex3f(-1.2f, .2f, -0.6f);

	//side walls
	glVertex3f(1.2f, 1.2f, -1.20f);
	glVertex3f(1.2f, 1.2f, -0.6f);
	glVertex3f(1.2f, .2f, -0.6f);
	glVertex3f(1.2f, .2f, -1.2f);

	glVertex3f(.8f, 1.2f, -1.20f);
	glVertex3f(.8f, 1.2f, -0.6f);
	glVertex3f(.8f, .2f, -0.6f);
	glVertex3f(.8f, .2f, -1.2f);

	//front walls and back walls
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(1.2f, 1.2f, -1.2f);
	glVertex3f(0.8f, 1.2f, -1.2f);
	glVertex3f(0.8f, .2f, -1.2f);
	glVertex3f(1.2f, .2f, -1.2f);

	glVertex3f(1.2f, 1.2f, -0.6f);
	glVertex3f(0.8f, 1.2f, -0.6f);
	glVertex3f(0.8f, .2f, -0.6f);
	glVertex3f(1.2f, .2f, -0.6f);

	glEnd();
}

void cupboard()
{
    glColor3f(0.6f, 0.5f, 0.0f);
	glBegin(GL_QUADS);

    // Back
	glVertex3f(-1.5f, 0.5f, -1.5f);
	glVertex3f(-1.5f, 4.5f, -1.5f);
	glVertex3f(1.5, 4.5f, -1.5f);
	glVertex3f(1.5f, 0.5f, -1.5f);

    // Left Side
    glVertex3f(-1.5f, 0.5f, -1.5f);
	glVertex3f(-1.5f, 4.5f, -1.5f);
	glVertex3f(-1.5, 4.5f, 0.5f);
	glVertex3f(-1.5f, 0.5f, 0.5f);

    // Right Side
    glVertex3f(1.5f, 0.5f, -1.5f);
	glVertex3f(1.5f, 4.5f, -1.5f);
	glVertex3f(1.5, 4.5f, 0.5f);
	glVertex3f(1.5f, 0.5f, 0.5f);

    // Front
    glVertex3f(-1.5f, 0.5f, 0.5f);
	glVertex3f(-1.5f, 4.5f, 0.5f);
	glVertex3f(1.5, 4.5f, 0.5f);
	glVertex3f(1.5f, 0.5f, 0.5f);

    glColor3f(0.6f, 0.5f, 0.0f);;
    // Left Support
	glVertex3f(-1.5f, 0.0f, -1.5f);
	glVertex3f(-1.5f, 0.5f, -1.5f);
	glVertex3f(-1.2, 0.5f, -1.5f);
	glVertex3f(-1.2f, 0.0f, -1.5f);

    glVertex3f(-1.5f, 0.0f, -1.5f);
	glVertex3f(-1.5f, 0.5f, -1.5f);
	glVertex3f(-1.5, 0.5f, 0.5f);
	glVertex3f(-1.5f, 0.0f, 0.5f);

    glVertex3f(-1.2f, 0.0f, -1.5f);
	glVertex3f(-1.2f, 0.5f, -1.5f);
	glVertex3f(-1.2, 0.5f, 0.5f);
	glVertex3f(-1.2f, 0.0f, 0.5f);

    glVertex3f(-1.5f, 0.0f, 0.5f);
	glVertex3f(-1.5f, 0.5f, 0.5f);
	glVertex3f(-1.2, 0.5f, 0.5f);
	glVertex3f(-1.2f, 0.0f, 0.5f);

    // Right Support
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.5f, -1.5f);
	glVertex3f(1.2f, 0.5f, -1.5f);
	glVertex3f(1.2f, 0.0f, -1.5f);

    glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.5f, -1.5f);
	glVertex3f(1.5f, 0.5f, 0.5f);
	glVertex3f(1.5f, 0.0f, 0.5f);

    glVertex3f(1.2f, 0.0f, -1.5f);
	glVertex3f(1.2f, 0.5f, -1.5f);
	glVertex3f(1.2f, 0.5f, 0.5f);
	glVertex3f(1.2f, 0.0f, 0.5f);

    glVertex3f(1.5f, 0.0f, 0.5f);
	glVertex3f(1.5f, 0.5f, 0.5f);
	glVertex3f(1.2f, 0.5f, 0.5f);
	glVertex3f(1.2f, 0.0f, 0.5f);

    glEnd();

    //lines
    glColor3f(0.8f, 0.6f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);

    glVertex3f(-1.4f, 0.6f, 0.501f);
	glVertex3f(-1.4f, 4.4f, 0.501f);

	glVertex3f(-1.4f, 4.4f, 0.501f);
	glVertex3f(1.4f, 4.4f, 0.501f);

    glVertex3f(1.4f, 0.6f, 0.501f);
	glVertex3f(1.4f, 4.4f, 0.501f);

    glVertex3f(-1.4f, 0.6f, 0.501f);
	glVertex3f(1.4f, 0.6f, 0.501f);

    //middle line
    glVertex3f(0.0f, 0.6f, 0.501f);
	glVertex3f(0.0f, 4.4f, 0.501f);

    glEnd();

    // Handles
    glColor3f(0.8f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef( 0.1f, 2.5f, 0.5f);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glutSolidTorus(0.03f, 0.1f, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -0.1f, 2.5f, 0.5f);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glutSolidTorus(0.03f, 0.1f, 100, 100);
    glPopMatrix();
}

float rotationangle  = 0.0f;

void fan()
{
     glTranslatef(0, 5, -5.0);
    glScalef(5, 5, 5);
    //glRotatef(90, 1, 0, 0);
    //Cube
    glPushMatrix();
    glColor3f(0.8, 0.8, 0);
    glScalef(1, 1.2, 1);
    glScalef(.5, .4, .5);
    glTranslatef(0, -2.0, 0);
    glScalef(1.0f, 0.7f, 1.0f);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rotationangle, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0, -1.05, 0);
    glScalef(0.15, .15, .15);
    glTranslatef(0.0f, -2.2f, 0.0f);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 5) {
        glColor3f(0.302, 0.149, 0.0);
        glVertex3f(cos(j), +1, sin(j));
        glColor3f(0.6, 0.302, 0.0);
        glVertex3f(cos(j), -1, sin(j));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(.3, .3, .3);
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0, 1.55);
    glScalef(.25, .25, .25);
    glutSolidTorus(.1, .72, 25, 25);
    glPopMatrix();

    glPushMatrix();

    glPushMatrix();
    glColor3f(0.4, 0.4, 0.0);
    glTranslatef(-1, -1.55, 0);
    glScalef(2.5, .1, .6);
    glutSolidCube(.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.55, 0);
    glScalef(0.05, .11, .05);
    glRotatef(90, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, -5);
    glScalef(1, 1, 2.4);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 5) {
        glColor3f(.3, .3, .3);
        glVertex3f(cos(j), +1, sin(j));
        glColor3f(.7, .7, .7);
        glVertex3f(cos(j), -1, sin(j));
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glColor3f(0.4, 0.4, 0.0);
    glTranslatef(-1, -1.55, 0);
    glScalef(2.5, .1, .6);
    glutSolidCube(.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.55, 0);
    glScalef(0.05, .11, .05);
    glRotatef(90, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, -5);
    glScalef(1, 1, 2.4);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 5) {
        glColor3f(.3, .3, .3);
        glVertex3f(cos(j), +1, sin(j));
        glColor3f(.7, .7, .7);
        glVertex3f(cos(j), -1, sin(j));
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);

    glPushMatrix();
    glColor3f(0.4, 0.4, 0.0);
    glTranslatef(-1, -1.55, 0);
    glScalef(2.5, .1, .6);
    glutSolidCube(.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.55, 0);
    glScalef(0.05, .11, .05);
    glRotatef(90, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, -5);
    glScalef(1, 1, 2.4);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 5) {
        glColor3f(.3, .3, .3);
        glVertex3f(cos(j), +1, sin(j));
        glColor3f(.7, .7, .7);
        glVertex3f(cos(j), -1, sin(j));
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(270, 0, 1, 0);
    glPushMatrix();
    glColor3f(0.4, 0.4, 0.0);
    glTranslatef(-1, -1.55, 0);
    glScalef(2.5, .1, .6);
    glutSolidCube(.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.55, 0);
    glScalef(0.05, .11, .05);
    glRotatef(90, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, -5);
    glScalef(1, 1, 2.4);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 5) {
        glColor3f(.3, .3, .3);
        glVertex3f(cos(j), +1, sin(j));
        glColor3f(.7, .7, .7);
        glVertex3f(cos(j), -1, sin(j));
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
}

void projector()
{
    glTranslatef(0, 5, -5.0);
    glScalef(5, 5, 5);
    glPushMatrix();
    glColor3f(0.8, 0.8, 0);
    glScalef(1, 1.2, 1);
    glScalef(.5, .4, .5);
    glTranslatef(0, -2.0, 0);
    glScalef(1.0f, 0.5f, 1.0f);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.05, 0);
    glScalef(0.08, 0.15, 0.1);
    glTranslatef(0.0f, -2.2f, 0.0f);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 5) {
        glColor3f(0.6, 0.2, 0.0);
        glVertex3f(cos(j), +1, sin(j));
        glColor3f(0.6, 0.2, 0.0);
        glVertex3f(cos(j), -1, sin(j));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1, 0.1, 0.1);
    glScalef(1, 1.2, 1);
    glScalef(.5, .4, .5);
    glTranslatef(0, -2.0, 0);
    glScalef(1.0f, 0.5f, 2.0f);
    glTranslatef(0, -2.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0, -1.05, 0);
    glScalef(0.08, 0.1, 0.1);
    glTranslatef(0.5f, -5.2f, -5.0f);
    glRotatef(90,1,0,0);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 5) {
        glColor3f(0.01, 0.01, 0.0);
        glVertex3f(cos(j), +1, sin(j));
        glColor3f(0.01, 0.01, 0.0);
        glVertex3f(cos(j), -1, sin(j));
    }
    glEnd();
    glPopMatrix();
    glEnd();
}

void table()
{
    glBegin(GL_QUADS);

	//Front
	//
	glColor3f(.6,.2,0);
	glVertex3f(-4.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-4.0f, 0.2f, 2.0f);

	//Back
	//;
	glVertex3f(-4.0f, -0.2f, -2.0f);
	glVertex3f(-4.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//Right
	//
	glVertex3f(2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);


	//Left
	;
	glVertex3f(-4.0f, -0.2f, -2.0f);
	glVertex3f(-4.0f, -0.2f, 2.0f);
	glVertex3f(-4.0f, 0.2f, 2.0f);
	glVertex3f(-4.0f, 0.2f, -2.0f);

	//top
	//

	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-4.0f, 0.2f, 2.0f);
	glVertex3f(-4.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);

	//bottom
	;

	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(-4.0f, -0.2f, 2.0f);
	glVertex3f(-4.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//table front leg
	//front
	//
	glColor3f(.8f, .6f, 0.0f);
	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -3.0f, 1.6f);
	glVertex3f(1.8f, -3.0f, 1.6f);

	//back
	//;

	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.2f);

	//right
	//

	glVertex3f(1.8f, -0.2f, 1.6f);
	glVertex3f(1.8f, -0.2f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.2f);
	glVertex3f(1.8f, -3.0f, 1.6f);

	//left
	//;

	glVertex3f(1.4f, -0.2f, 1.6f);
	glVertex3f(1.4f, -0.2f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.2f);
	glVertex3f(1.4f, -3.0f, 1.6f);

	//back leg back
	//front
	//;
	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.2f);

	//back
	//;

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -3.0f, -1.6f);
	glVertex3f(1.8f, -3.0f, -1.6f);

	//right
	//

	glVertex3f(1.8f, -0.2f, -1.6f);
	glVertex3f(1.8f, -0.2f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.2f);
	glVertex3f(1.8f, -3.0f, -1.6f);

	//left
	//

	glVertex3f(1.4f, -0.2f, -1.6f);
	glVertex3f(1.4f, -0.2f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.2f);
	glVertex3f(1.4f, -3.0f, -1.6f);

	//leg left front
	//


	glVertex3f(-3.8f, -0.2f, 1.6f);
	glVertex3f(-3.4f, -0.2f, 1.6f);
	glVertex3f(-3.4f, -3.0f, 1.6f);
	glVertex3f(-3.8f, -3.0f, 1.6f);

	//back
	//;

	glVertex3f(-3.8f, -0.2f, 1.2f);
	glVertex3f(-3.4f, -0.2f, 1.2f);
	glVertex3f(-3.4f, -3.0f, 1.2f);
	glVertex3f(-3.8f, -3.0f, 1.2f);

	//right


	glVertex3f(-3.8f, -0.2f, 1.6f);
	glVertex3f(-3.8f, -0.2f, 1.2f);
	glVertex3f(-3.8f, -3.0f, 1.2f);
	glVertex3f(-3.8f, -3.0f, 1.6f);

	//left
	;

	glVertex3f(-3.4f, -0.2f, 1.6f);
	glVertex3f(-3.4f, -0.2f, 1.2f);
	glVertex3f(-3.4f, -3.0f, 1.2f);
	glVertex3f(-3.4f, -3.0f, 1.6f);

	//left leg back front

	//front
	;
	//glColor3f(1,1,1);
	glVertex3f(-3.8f, -0.2f, -1.2f);
	glVertex3f(-3.4f, -0.2f, -1.2f);
	glVertex3f(-3.4f, -3.0f, -1.2f);
	glVertex3f(-3.8f, -3.0f, -1.2f);

	//back
	;

	glVertex3f(-3.8f, -0.2f, -1.6f);
	glVertex3f(-3.4f, -0.2f, -1.6f);
	glVertex3f(-3.4f, -3.0f, -1.6f);
	glVertex3f(-3.8f, -3.0f, -1.6f);

	//right


	glVertex3f(-3.8f, -0.2f, -1.6f);
	glVertex3f(-3.8f, -0.2f, -1.2f);
	glVertex3f(-3.8f, -3.0f, -1.2f);
	glVertex3f(-3.8f, -3.0f, -1.6f);

	//left


	glVertex3f(-3.4f, -0.2f, -1.6f);
	glVertex3f(-3.4f, -0.2f, -1.2f);
	glVertex3f(-3.4f, -3.0f, -1.2f);
	glVertex3f(-3.4f, -3.0f, -1.6f);



	glEnd();
}


void window1()
{
    glColor3f(0.6f, 0.7333f, 1.0f);
glBegin(GL_QUADS);
glVertex3f(-9.99f, 2.0f, 6.0f);
glVertex3f(-9.99f, 5.0f, 6.0f);
glVertex3f(-9.99f, 5.0f, 2.0f);
glVertex3f(-9.99f, 2.0f, 2.0f);
glEnd();

glColor3f(0.149f, 0.149f, 0.149f);
glLineWidth(10.0f);
glBegin(GL_LINES);
//left
glVertex3f(-9.98f, 2.0f, 6.0f);
glVertex3f(-9.98f, 5.0f, 6.0f);
//top
glVertex3f(-9.98f, 5.0f, 6.0f);
glVertex3f(-9.98f, 5.0f, 2.0f);
//right
glVertex3f(-9.98f, 2.0f, 2.0f);
glVertex3f(-9.98f, 5.0f, 2.0f);
//bottom
glVertex3f(-9.98f, 2.0f, 6.0f);
glVertex3f(-9.98f, 2.0f, 2.0f);
glEnd();

//Cross
glLineWidth(3.0f);
glBegin(GL_LINES);
glVertex3f(-9.98f, 2.0f, 4.0f);
glVertex3f(-9.98f, 5.0f, 4.0f);

glVertex3f(-9.98f, 3.5f, 6.0f);
glVertex3f(-9.98f, 3.5f, 2.0f);
glEnd();
}

void window2()
{
    glColor3f(0.6f, 0.7333f, 1.0f);
glBegin(GL_QUADS);
glVertex3f(-9.99f, 2.0f, -6.0f);
glVertex3f(-9.99f, 5.0f, -6.0f);
glVertex3f(-9.99f, 5.0f, -2.0f);
glVertex3f(-9.99f, 2.0f, -2.0f);
glEnd();

glColor3f(0.149f, 0.149f, 0.149f);
glLineWidth(10.0f);
glBegin(GL_LINES);
//left
glVertex3f(-9.98f, 2.0f, -6.0f);
glVertex3f(-9.98f, 5.0f, -6.0f);
//top
glVertex3f(-9.98f, 5.0f, -6.0f);
glVertex3f(-9.98f, 5.0f, -2.0f);
//right
glVertex3f(-9.98f, 2.0f, -2.0f);
glVertex3f(-9.98f, 5.0f, -2.0f);
//bottom
glVertex3f(-9.98f, 2.0f, -6.0f);
glVertex3f(-9.98f, 2.0f, -2.0f);
glEnd();

//Cross
glLineWidth(3.0f);
glBegin(GL_LINES);
glVertex3f(-9.98f, 2.0f, -4.0f);
glVertex3f(-9.98f, 5.0f, -4.0f);

glVertex3f(-9.98f, 3.5f, -6.0f);
glVertex3f(-9.98f, 3.5f, -2.0f);
glEnd();
}

void windowsill()
{
    glColor3f(0.149f, 0.149f, 0.149f);
glBegin(GL_QUADS);
glVertex3f(-9.99f, 2.0f, -6.0f);
glVertex3f(-9.99f, 2.0f, -2.0f);
glVertex3f(-9.5f, 2.0f, -2.0f);
glVertex3f(-9.5f, 2.0f, -6.0f);

glColor3f(0.2f, 0.2f, 0.2f);
glVertex3f(-9.5f, 2.0f, -6.0f);
glVertex3f(-9.5f, 2.0f, -2.0f);
glVertex3f(-9.5f, 1.8f, -2.0f);
glVertex3f(-9.5f, 1.8f, -6.0f);

glColor3f(0.24f, 0.24f, 0.24f);
glVertex3f(-9.99f, 2.0f, -6.0f);
glVertex3f(-9.5f, 2.0f, -6.0f);
glVertex3f(-9.5f, 1.8f, -6.0f);
glVertex3f(-9.99f, 1.8f, -6.0f);

glVertex3f(-9.99f, 2.0f, -2.0f);
glVertex3f(-9.5f, 2.0f, -2.0f);
glVertex3f(-9.5f, 1.8f, -2.0f);
glVertex3f(-9.99f, 1.8f, -2.0f);

glEnd();
}

void wall(double thickness)
{
    glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void shelf_cb()
{
    glPushMatrix();

	glBegin(GL_QUADS);


	glColor3f(1, 0.7647, 0.302);
	glVertex3f(-4.0f, 0.0f, -4.0f);
	glVertex3f(0.0f, 0.0f, -4.0f);
	glVertex3f(0.0f, 4.0f, -4.0f);
	glVertex3f(-4.0f, 4.0f, -4.0f);


	glColor3f(0.302, 0.2, 0);
	glVertex3f(-4.0f, 0.0f, -4.0f);
	glVertex3f(-4.0f, 0.0f, -0.0f);
	glVertex3f(-4.0f, 4.0f, -0.0f);
	glVertex3f(-4.0f, 4.0f, -4.0f);

	glVertex3f(0.0f, 0.0f, -4.00f);
	glVertex3f(0.0f, 0.0f, -0.0f);
	glVertex3f(0.0f, 4.0f, -0.0f);
	glVertex3f(0.0f, 4.0f, -4.0f);

	glColor3f(0.302, 0.2, 0);
	glVertex3f(-4.0f, 4.0f, -4.00f);
	glVertex3f(-4.0f, 4.0f, -0.0f);
	glVertex3f(0.0f, 4.0f, -0.0f);
	glVertex3f(0.0f, 4.0f, -4.0f);

	glVertex3f(-4.0f, 0.0f, -4.00f);
	glVertex3f(-4.0f, 0.0f, -0.0f);
	glVertex3f(0.0f, 0.0f, -0.0f);
	glVertex3f(0.0f, 0.0f, -4.0f);

	glVertex3f(-4.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(-4.0f, 0.2f, 0.0f);



	glEnd();

	glPopMatrix();
}

void shelf()
{
    shelf_cb();

	glPushMatrix();

	glTranslatef(4, -4, 0);
	shelf_cb();
	glPopMatrix();



	glPushMatrix();
	glTranslatef(2.5, -3, -1.2);
	glRotatef(-90, 0, 1, 0);
	glPushMatrix();

	glPopMatrix();
	glPopMatrix();
}

void book1()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);

	//Right
	//
	glColor3f(1,1,1);
	glVertex3f(2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);

	//Back
	//;
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//Left
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);

	//top
	//
    glColor3f(1,0,0);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);

	//bottom
	;

	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	glEnd();
	glPopMatrix();
}

void book2()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0,1,0);
    glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);

	//Right
	//
	glColor3f(1,1,1);
	glVertex3f(2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);

	//Back
	//;
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//Left
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);

	//top
	//
    glColor3f(0,1,0);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);

	//bottom
	;

	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	glEnd();
	glPopMatrix();
}

void book3()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0,0,1);
    glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);

	//Right
	//
	glColor3f(1,1,1);
	glVertex3f(2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(2.0f, -0.2f, 2.0f);

	//Back
	//;
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	//Left
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);

	//top
	//
    glColor3f(0,0,1);
	glVertex3f(2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, 2.0f);
	glVertex3f(-2.0f, 0.2f, -2.0f);
	glVertex3f(2.0f, 0.2f, -2.0f);

	//bottom
	;

	glVertex3f(2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, 2.0f);
	glVertex3f(-2.0f, -0.2f, -2.0f);
	glVertex3f(2.0f, -0.2f, -2.0f);

	glEnd();
	glPopMatrix();
}

void books()
{
    glPushMatrix();
	glTranslatef(8.4f, 2.6f, -8.99f);
	glScalef(0.2f, 0.25f, 0.15f);
	book1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.4f, 2.7f, -8.99f);
	glScalef(0.2f, 0.25f, 0.15f);
	book2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.4f, 2.8f, -8.99f);
	glScalef(0.2f, 0.25f, 0.15f);
	book3();
	glPopMatrix();

}

void computer()
{
    // Monitor
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.1);
    glScalef(1, 1.2, 1);
    glScalef(.5, .4, .5);
    glTranslatef(0, -1.6, 0);
    glScalef(1.7f, 1.5f, 0.2f);
    glTranslatef(0, -2.1, 0);
    glutSolidCube(1);
    glPopMatrix();

    // Stand
    glPushMatrix();
    glTranslatef(0, -2.4, 0);
    glScalef(0.08, 0.15, 0.1);
    glTranslatef(0.0f, -2.5f, 0.0f);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 5) {
        glColor3f(0.1, 0.1, 0.1);
        glVertex3f(cos(j), +1, sin(j));
        glColor3f(0.1, 0.1, 0.1);
        glVertex3f(cos(j), -1, sin(j));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -2.7, 0);
    glScalef(0.27, 0.1, 0.1);
    glTranslatef(0.0f, -2.4f, 0.0f);
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= 360; j += 5) {
        glColor3f(0.1, 0.1, 0.1);
        glVertex3f(cos(j), +1, sin(j));
        glColor3f(0.1, 0.1, 0.1);
        glVertex3f(cos(j), -1, sin(j));
    }
    glEnd();
    glPopMatrix();

    // Screen
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(-0.39,-2.65,0.057);
     glScalef(1,1.3,1);
    glBegin(GL_POLYGON);
    glVertex2f(0.1f,0.1f);
    glVertex2f(0.1f,0.5f);
    glVertex2f(0.7f,0.5f);
    glVertex2f(0.7f,0.1f);
    glEnd();
    glPopMatrix();
}

// Function to toggle lights
void toggleLights() {
    lightsOn = !lightsOn;
    if(lightsOn) {
        // Turn lights ON - enable lighting
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    } else {
        // Turn lights OFF - disable lighting completely to show original colors
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
}

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 2.5f, z,
		x + lx, 2.5f + ly, z + lz,
		roll + 0.0f, 2.5f, 0.0f);

	// Draw floor (no texture, just color)
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();

    //walls WITH texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glColor3f(0.9294f, 0.9216f, 0.8353f);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-10.0f, 0.0f, -10.0f);
	glTexCoord2f(0,7); glVertex3f(-10.0f, 7.0f, -10.0f);
	glTexCoord2f(10,7); glVertex3f(10.0f, 7.0f, -10.0f);
	glTexCoord2f(10,0); glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();

	//wall
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-10.0f, 0.0f, -10.0f);
	glTexCoord2f(0,7); glVertex3f(-10.0f, 7.0f, -10.0f);
	glTexCoord2f(10,7); glVertex3f(-10.0f, 7.0f, 10.0f);
	glTexCoord2f(10,0); glVertex3f(-10.0f, 0.0f, 10.0f);
	glEnd();

	//wall with door
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-10.0f, 0.0f, 10.0f);
	glTexCoord2f(0,7); glVertex3f(-10.0f, 7.0f, 10.0f);
	glTexCoord2f(2,7); glVertex3f(-6.0f, 7.0f, 10.0f);
	glTexCoord2f(2,0); glVertex3f(-6.0f, 0.0f, 10.0f);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-3.0f, 0.0f, 10.0f);
	glTexCoord2f(0,7); glVertex3f(-3.0f, 7.0f, 10.0f);
	glTexCoord2f(10,7); glVertex3f(10.0f, 7.0f, 10.0f);
	glTexCoord2f(10,0); glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-6.0f, 7.0f, 10.0f);
	glTexCoord2f(0,2); glVertex3f(-6.0f, 5.0f, 10.0f);
	glTexCoord2f(3,2); glVertex3f(-3.0f, 5.0f, 10.0f);
	glTexCoord2f(3,0); glVertex3f(-3.0f, 7.0f, 10.0f);
	glEnd();

	glColor3f(0.4f, 0.2f, 0.0f);
	glLineWidth(30.0f);
	glBegin(GL_LINES);
    glVertex3f(-6.0f, 5.0f, 10.01f);
	glVertex3f(-3.0f, 5.0f, 10.01f);
	glEnd();

	glBegin(GL_LINES);
    glVertex3f(-6.0f, 5.0f, 10.01f);
	glVertex3f(-6.0f, 0.0f, 10.01f);
	glEnd();

	glBegin(GL_LINES);
    glVertex3f(-3.0f, 0.0f, 10.01f);
	glVertex3f(-3.0f, 5.0f, 10.01f);
	glEnd();


	//wall
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(0,7); glVertex3f(10.0f, 7.0f, -10.0f);
	glTexCoord2f(10,7); glVertex3f(10.0f, 7.0f, 10.0f);
	glTexCoord2f(10,0); glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	//ceiling
	glColor3f(0.95f, 0.95f, 0.95f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glEnd();

	// Draw prof's chair
	glPushMatrix();
	glTranslatef( 6.0f, 1.0f, -9.0f);
	glScalef(0.32f, 0.32f, 0.32f);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	chair();
	glPopMatrix();


	// Draw prof's table
	glPushMatrix();
	glTranslatef( 6.0f, 1.4f, -7.6f);
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	table();
	glPopMatrix();

	// Computer
	glPushMatrix();
	glTranslatef( 5.3f, 4.5f, -7.6f);
	//glScalef(0.32f, 0.32f, 0.32f);
	glRotatef(150, 0.0, 1.0, 0.0);
	computer();
	glPopMatrix();

	// Draw student chairs
	for (int i = -3; i <= 3; i+=2){
		for (int j = -3; j <= 3; j+=2) {
			glPushMatrix();
			glTranslatef(i*2.0, 0.8f, j * 2.0 + 2.2f);
			glScalef(0.25f, 0.25f, 0.25f);
			glRotatef(180.0, 0.0, 1.0, 0.0);
			chair();
			glPopMatrix();
		}
	}

	// Draw student tables
	for (int i = -3; i <= 3; i+=2){
		for (int j = -3; j <= 3; j+=2) {
			glPushMatrix();
			glTranslatef(i*2.0 + 0.3f, 1.2f, j * 2.0 + 1.2f);
			glScalef(0.4f, 0.4f, 0.4f);
			table();
			glPopMatrix();
		}
	}

	// Draw cupboard
	glPushMatrix();
	glTranslatef( 8.49f, 0.0f, -3.5f);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	cupboard();
	glPopMatrix();

	// Draw blackboard
	glColor3f(0.4f, 0.2f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-6.0f, 2.0f, -9.99f);
	glVertex3f(-6.0f, 5.5f, -9.99f);
	glVertex3f(6.0f, 5.5f, -9.99f);
	glVertex3f(6.0f, 2.0f, -9.99f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(-5.8f, 2.2f, -9.98f);
	glVertex3f(-5.8f, 5.3f, -9.98f);
	glVertex3f(5.8f, 5.3f, -9.98f);
	glVertex3f(5.8f, 2.2f, -9.98f);
	glEnd();

	glPushMatrix();
	glTranslatef(7.99f, 3.5f, -8.99f);
	glScalef(0.25f, 0.25f, 0.25f);
	shelf();
	glPopMatrix();

	books();

    /*char str1[] = "WELCOME TO OUR LECTURE HALL";
	int l1 = strlen(str1);
	glPushMatrix();

	glColor3f(0.1f, 0.1f, 0.1f);

	glRasterPos3f(-5.0f, 3.75f, -9.98f);
	for( int i=0; i < l1; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str1[i]);
	}
	glPopMatrix(); */


	//Floor pattern
	glColor3f(0.149f, 0.149f, 0.149f);
	glLineWidth(3.0f);
	for(int i = 0; i < 20; i += 2)
	{
		glBegin(GL_LINES);
		glVertex3f(-10.0f + i, 0.001f, -10.01f);
		glVertex3f(-10.0f + i, 0.001f, 10.01f);
		glEnd();
	}
	for(int i = 0; i < 20; i += 2)
	{
		glBegin(GL_LINES);
		glVertex3f(-10.0f, 0.001f, -10.01f + i);
		glVertex3f(10.0f, 0.001f, -10.01f + i);
		glEnd();
	}

	//windows
	window1();
	window2();
	windowsill();
	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, 8.0f);
	windowsill();
	glPopMatrix();

    glPushMatrix();
	glTranslatef(0.0f, 6.0f, 4.1f);
	glScalef(0.3f, 0.3f, 0.3f);
	fan();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	glScalef(0.3f, 0.3f, 0.3f);
	projector();
	glPopMatrix();


	if(abs(mouseX) > 0.3){
		angle -= (0.004f * mouseX);
		lx = sin(angle);
		lz = -cos(angle);
	}
	if(abs(mouseY) > 0.3){
		if(abs(yAngle) < (M_PI/2)){
			yAngle += (0.002f * mouseY);
		}
		ly = sin(yAngle);
	}

	glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		x += sin(angle - M_PI/2.0) * fraction;
		z += -cos(angle - M_PI/2.0) * fraction;
		break;
	case GLUT_KEY_RIGHT:
		x += sin(M_PI/2.0 + angle) * fraction;
		z += -cos(M_PI/2.0 + angle) * fraction;
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}

void processNormalKeys(unsigned char key, int xx, int yy) {
    float fraction = 0.1f;
    if(key == 'w'){
        x += lx * fraction;
		z += lz * fraction;
    } else if(key == 'a'){
        x += sin(angle - M_PI/2.0) * fraction;
		z += -cos(angle - M_PI/2.0) * fraction;
    } else if(key == 's'){
        x -= lx * fraction;
		z -= lz * fraction;
    } else if(key == 'd'){
        x += sin(M_PI/2.0 + angle) * fraction;
		z += -cos(M_PI/2.0 + angle) * fraction;
    } else if (key == 'x') {
		roll += 0.5f;
	} else if (key == 'z') {
		roll -= 0.5f;
	} else if (key == 'l' || key == 'L') {
		toggleLights();
	}

	if (key == 27)
		exit(0);
}

void processMouseMovement(int xx, int yy){

	mouseX = (float)(halfWidth - xx)/halfWidth;
	mouseY = (float)(halfHeight - yy)/halfHeight;
	angle -= (0.005f * mouseX);
	lx = sin(angle);
	lz = -cos(angle);

	if(abs(yAngle) < (M_PI/2)){
		yAngle += (0.005f * mouseY);
	}
	ly = sin(yAngle);

}

void changeSize(int w, int h) {

	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);
	halfWidth = (float)(w/2.0);
	halfHeight = (float)(h/2.0);

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

void animate () {

    rotationangle+=1.5f;

    glutPostRedisplay();
}



int main(int argc,char**argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Classroom - Press L to toggle lights");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(animate);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
    glutPassiveMotionFunc(processMouseMovement);

	init();
	glEnable(GL_DEPTH_TEST);

	// Start with lights ON
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutMainLoop();

}
