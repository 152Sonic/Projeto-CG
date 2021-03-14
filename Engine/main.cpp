#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <string>
#include "tinyxml2.h"
#include "Ponto.h"


using namespace tinyxml2;
using namespace std;



float alpha = 0.61547999;
float beta = 0.61547999;
float rad = 10;

vector<Ponto> shape;

void readFile(string fich) {
    ifstream file;
    file.open(fich.c_str());
    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            Ponto p = Ponto(line);
            shape.push_back(p);
        }
        file.close();
    }
    else {
        printf("NAO ABRIU O FICHEIRO\n");
    }
}

void lerXML(string ficheiro) {
    XMLDocument docxml;

    if (!(docxml.LoadFile(ficheiro.c_str()))) {
        XMLElement* root = docxml.FirstChildElement();
        for(XMLElement *elemento = root -> FirstChildElement();elemento != NULL; elemento = elemento -> NextSiblingElement()){
            string fich = elemento -> Attribute("file");
            cout << "Ficheiro: " << fich << " lido com sucesso " << endl;
            readFile(fich);
        }
    }
    else {
        cout << "Ficheiro XML não foi encontrado" << endl;
    }
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
	gluLookAt(rad*cos(beta)*sin(alpha),rad*sin(beta) , rad*cos(beta)*cos(alpha),
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

    glPolygonMode(GL_FRONT,GL_FILL);

    glBegin(GL_LINE);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    glEnd();


    for(int j = 0; j < shape.size(); j += 3){
        glBegin(GL_TRIANGLES);
        glColor3f(sin(j),1/tan(j),cos(j));
        glVertex3f(shape[j].getX(),shape[j].getY(),shape[j].getZ());
        glVertex3f(shape[j+1].getX(),shape[j+1].getY(),shape[j+1].getZ());
        glVertex3f(shape[j+2].getX(),shape[j+2].getY(),shape[j+2].getZ());
        glEnd();
    }
	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void keys(unsigned char c, int xx, int yy){
    switch (c) {
        case 'w':
            if(beta <= M_PI/2) {
                beta += M_PI / 64;
            }
            glutPostRedisplay();
            break;
        case 's':
            if(beta >= -M_PI/2){
                beta -= M_PI/64;
            }
            glutPostRedisplay();
            break;
        case 'a':
            alpha -= M_PI/64;
            glutPostRedisplay();
            break;
        case 'd':
            alpha += M_PI/64;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}



int main(int argc, char** argv) {
    if(argc < 2){
        return 0;
    }
    if(!strcmp(argv[1],"-h")){
        return 0;
    }
    char path[1024];
    strcpy(path, "../Engine/");
    strcat(path, argv[1]);
    lerXML(path);
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
	glutKeyboardFunc(keys);


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}