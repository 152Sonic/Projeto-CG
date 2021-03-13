
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "tinyxml2.h"
#include "Ponto.h"
#include "Shape.h"

using namespace tinyxml2;
using namespace std;


Shape shape;
int linha = GL_LINE;
float alpha = 0.61547999;
float beta = 0.61547999;
float rad = 10;

void lerFile(char* FILENAME) {
    ifstream file(FILENAME);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            Ponto p = Ponto(line);
            shape.inserePonto(p);
        }
        file.close();
    }
    else {
        printf("NAO ABRIU O FICHEIRO\n");
    }
}

void lerXML(char * path){
    XMLDocument doc;
    XMLElement *element;
    tinyxml2::XMLError eResult = doc.LoadFile(path);// path2
    if(!eResult){
        element = doc.FirstChildElement()->FirstChildElement(); //<scene><model>
        for (; element; element = element->NextSiblingElement()) { // itera por os model
            string ficheiro = element->Attribute("file"); // pega no valor do atributo file  em cada  Model
            char * aux = const_cast<char *>(ficheiro.c_str());
            lerFile(aux); // Gets model's vertexes
        }
    }
    else {
        cout << "o ficheiro nao foi carregado" << endl;
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
	gluLookAt(rad*cos(beta),rad*sin(beta) , rad*cos(beta)*sin(alpha),
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

    glPolygonMode(GL_FRONT,linha);


    glColor3f(0,0.5,1);

    for(int j = 0; j < shape.getSize(); j += 3){
        glBegin(GL_TRIANGLES);
            glVertex3f(shape.getPonto(j).getX(),shape.getPonto(j).getY(),shape.getPonto(j).getZ());
            glVertex3f(shape.getPonto(j+1).getX(),shape.getPonto(j+1).getY(),shape.getPonto(j+1).getZ());
            glVertex3f(shape.getPonto(j+2).getX(),shape.getPonto(j+2).getY(),shape.getPonto(j+2).getZ());
        glEnd();
    }
	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events




int main(int argc, char** argv) {
    if(argc < 2){
        return 0;
    }

    if(strcmp(argv[1],"-h")){
        return 0;
    }
    lerXML(argv[1]);
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


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}