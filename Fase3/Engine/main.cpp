#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <string>
#include "tinyxml2.h"
#include "Ponto.h"
#include "Group.h"
#include "Parse.h"


using namespace tinyxml2;
using namespace std;

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

int timeb = 0;
float frame = 0;


void spherical2Cartesian() {

        camX = radius * cos(beta) * sin(alfa);
        camY = radius * sin(beta);
        camZ = radius * cos(beta) * cos(alfa);
}


vector<Group> groups1 = vector<Group>();
vector<Ponto> shape1;

void renderCatmullRomCurve(vector<Ponto> curva){

  int tam = curva.size();
  int i;

  glBegin(GL_LINE_LOOP);
  for(i=0;i<tam;i++ ){
    glVertex3f(curva[i].getX(), curva[i].getY(), curva[i].getZ());
  }
  glEnd();
}

void desenha(vector<Group> g){
  float res[3];
  for(int j=0; j<g.size();j++){
    glPushMatrix();
    Transformation t = g[j].getTrans();
    Rotate rt = t.getRotate();
    if(rt.getTime()>0){
      float r = glutGet(GLUT_ELAPSED_TIME) % (int)(rt.getTime() * 1000);
      float ang = r *360 / (rt.getTime() * 1000);
      glRotatef(ang, rt.getX(),rt.getY(),rt.getZ());
    }
    else{
    glRotatef(t.getRotate().getAngle(), t.getRotate().getX(),t.getRotate().getY(),t.getRotate().getZ());
  }
    Translate tl = t.getTranslate();
    if(tl.getTime()>0){
        float r = glutGet(GLUT_ELAPSED_TIME) % (int)(tl.getTime() * 1000);
				float gt = (float) r / (tl.getTime() * 1000);
				tl.desenhaCurvas();
				renderCatmullRomCurve(tl.getCurva());
				tl.getGlobalCatmullRomPoint(gt,res);
				glTranslatef(res[0],res[1],res[2]);
    }
    else{
      glTranslatef(t.getTranslate().getX(),t.getTranslate().getY(),t.getTranslate().getZ());
    }
    glScalef(t.getScale().getX(),t.getScale().getY(),t.getScale().getZ());
    glColor3f(t.getCor().getR(),t.getCor().getG(),t.getCor().getB());
    /*shape1.clear();
    shape1 = g[j].getPontos();
    glBegin(GL_TRIANGLES);


    for(int i = 0; i<shape1.size(); i++){
      glVertex3f(shape1[i].getX(), shape1[i].getY(), shape1[i].getZ());
    }
    glEnd();*/
    //g[j].prep();
    g[j].draw();

    if(g[j].getFilhos().size()!=0){
      desenha(g[j].getFilhos());
    }

    glPopMatrix();
  }
}

void fps() {
	float fpsec;
	int time;
	char sistema[64];

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timeb > 1000) {
		fpsec = frame*1000.0 / (time - timeb);
		timeb = time;
		frame = 0;
    sprintf(sistema,"FPS: %f",fpsec);
		glutSetWindowTitle(sistema);
	}
}


void drawAxis(void) {
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1000.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1000.0f);
    glEnd();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX,camY , camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

    desenha(groups1);
    fps();

	// End of frame
	glutSwapBuffers();
}




// write function to process keyboard events
void processSpecialKeys(int key, int xx, int yy) {

        switch (key) {

        case GLUT_KEY_RIGHT:
                alfa -= 0.1; break;

        case GLUT_KEY_LEFT:
                alfa += 0.1; break;

        case GLUT_KEY_UP:
                beta += 0.1f;
                if (beta > 1.5f)
                        beta = 1.5f;
                break;

        case GLUT_KEY_DOWN:
                beta -= 0.1f;
                if (beta < -1.5f)
                        beta = -1.5f;
                break;

        case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
                if (radius < 1.0f)
                        radius = 1.0f;
                break;

        case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
        }
        spherical2Cartesian();
        glutPostRedisplay();

}




int main(int argc, char** argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI");
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

	// put here the registration of the keyboard callbacks
	//glutKeyboardFunc(keys);
  glutSpecialFunc(processSpecialKeys);

  glewInit();
  if(argc < 2){
      return 0;
  }
  if(!strcmp(argv[1],"-h")){
      return 0;
  }
  char path[1024];
  strcpy(path, "../Engine/");
  strcat(path, argv[1]);
  groups1 = lerXML(path);

  //  OpenGL settings
	glEnable(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_CULL_FACE);
  spherical2Cartesian();


	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
