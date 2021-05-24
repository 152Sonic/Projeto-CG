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

Ponto luz;

GLfloat pos[4] = { luz.getX(), luz.getY(), luz.getZ(), 1.0 };
GLfloat amb[4] = { 0, 0, 0,1 };
GLfloat diff[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat matt[4] = { 1, 1, 1,1 };


void spherical2Cartesian() {

        camX = radius * cos(beta) * sin(alfa);
        camY = radius * sin(beta);
        camZ = radius * cos(beta) * cos(alfa);
}


vector<Group> groups1 = vector<Group>();
vector<Ponto> shape1;

void buildRotMatrix(float *x, float *y, float *z, float *m) {

        m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
        m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
        m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(float *a, float *b, float *res) {

        res[0] = a[1]*b[2] - a[2]*b[1];
        res[1] = a[2]*b[0] - a[0]*b[2];
        res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalize(float *a) {

        float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
        a[0] = a[0]/l;
        a[1] = a[1]/l;
        a[2] = a[2]/l;
}

float length(float *v) {

        float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
        return res;

}

void multMatrixVector(float *m, float *v, float *res) {

        for (int j = 0; j < 4; ++j) {
                res[j] = 0;
                for (int k = 0; k < 4; ++k) {
                        res[j] += v[k] * m[j * 4 + k];
                }
        }

}

void renderCatmullRomCurve(vector<Ponto> curva){

  int tam = curva.size();
  int i;
  glColor3f(1,1,1);

  glBegin(GL_LINE_LOOP);
  for(i=0;i<tam;i++ ){
    glVertex3f(curva[i].getX(), curva[i].getY(), curva[i].getZ());
  }
  glEnd();
}

void direction(float* deriv, float*y, float*z, float* m){

  normalize(deriv);

  cross(deriv,y,z);
  normalize(z);
  cross(z,deriv,y);
  normalize(y);

  buildRotMatrix(deriv,y,z,m);

  glMultMatrixf(m);
}

void desenha(vector<Group> g){
  float* z = new float[3];
  float* y = new float[3]{0,1,0};
  float* m = new float[16];
  float res[3];
  float deriv[3];
  for(int j=0; j<g.size();j++){
    glPushMatrix();

    Transformation t = g[j].getTrans();
    Rotate rt = t.getRotate();
    Translate tl = t.getTranslate();

    if(tl.getTime()>0){
        float r = glutGet(GLUT_ELAPSED_TIME) % (int)(tl.getTime() * 1000);
				float gt = (float) r / (tl.getTime() * 1000);
				renderCatmullRomCurve(tl.getCurva());
				tl.getGlobalCatmullRomPoint(gt,res,deriv);
				glTranslatef(res[0],res[1],res[2]);
        direction(deriv,y,z,m);
    }
    else{
      glTranslatef(t.getTranslate().getX(),t.getTranslate().getY(),t.getTranslate().getZ());
    }
    if(rt.getTime()>0){
      float r = glutGet(GLUT_ELAPSED_TIME) % (int)(rt.getTime() * 1000);
      float ang = r *360 / (rt.getTime() * 1000);
      glRotatef(ang, rt.getX(),rt.getY(),rt.getZ());
    }
    else{
    glRotatef(t.getRotate().getAngle(), t.getRotate().getX(),t.getRotate().getY(),t.getRotate().getZ());
  }

    glScalef(t.getScale().getX(),t.getScale().getY(),t.getScale().getZ());
    //glColor3f(t.getCor().getR(),t.getCor().getG(),t.getCor().getB());

    Material m = t.getMaterial();
    m.draw();
    /*if (t.getTranslate().getTime() == 0) {
      glMaterialfv(GL_FRONT,GL_EMISSION,matt);
    }
    else{
			GLfloat matt2[3] = { 0,0,0 };
      GLfloat white[]={1.0f,1.0f,1.0f,1.0f};
      glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,white);
      //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matt2);
		}
*/
    glBindTexture(GL_TEXTURE_2D, g[j].getTexID());
    glEnable(GL_LIGHTING);
    g[j].draw();
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);


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
    // Y Axis in Gree
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

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glLightfv(GL_LIGHT0, GL_POSITION, pos); // posição da luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb); // luz ambiente
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff); // luz difusa
    glLightfv(GL_LIGHT0,GL_EMISSION,matt);

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



  glEnable(GL_LIGHT0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
	glShadeModel (GL_SMOOTH);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_CULL_FACE);

  ilInit();
  ilEnable(IL_ORIGIN_SET);
  ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

  if(argc < 2){
      return 0;
  }
  if(!strcmp(argv[1],"-h")){
      return 0;
  }
  char path[1024];
  strcpy(path, "../Engine/");
  strcat(path, argv[1]);
  groups1 = lerXML(path, &luz);

  //  OpenGL settings




  spherical2Cartesian();


	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
