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
#include "Group.h"
#include "Parse.h"


using namespace tinyxml2;
using namespace std;


float alpha = 0.61547999;
float beta = 0.61547999;
float rad = 100;

vector<Group> groups1 = vector<Group>();
vector<Ponto> shape1;
/*
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


void parseTranslate(XMLElement* elemento, Translate *translate){
  if(elemento->Attribute("X"))
    translate->setX(stof(elemento->Attribute("X")));
  if (elemento->Attribute("Y"))
    translate->setY(stof(elemento->Attribute("Y")));
  if (elemento->Attribute("Z"))
    translate->setZ(stof(elemento->Attribute("Z")));
}

void parseRotate(XMLElement* elemento, Rotate *rotate){
  if(elemento->Attribute("X"))
    rotate->setX(stof(elemento->Attribute("X")));
  if (elemento->Attribute("Y"))
    rotate->setY(stof(elemento->Attribute("Y")));
  if (elemento->Attribute("Z"))
    rotate->setZ(stof(elemento->Attribute("Z")));
  if (elemento->Attribute("angle"))
    rotate->setAngle(stof(elemento->Attribute("angle")));
}

void parseScale(XMLElement* elemento, Scale *scale){
  if(elemento->Attribute("X"))
    scale->setX(stof(elemento->Attribute("X")));
  if (elemento->Attribute("Y"))
    scale->setY(stof(elemento->Attribute("Y")));
  if (elemento->Attribute("Z"))
    scale->setZ(stof(elemento->Attribute("Z")));
}

void parseXML(XMLElement* group, vector<Group> *g){
  Rotate rotate = Rotate();
  Scale scale = Scale();
  Translate translate = Translate();

  for(XMLElement* elemento = group->FirstChildElement();(strcmp(elemento->Name(),"models")!=0); elemento = elemento -> NextSiblingElement()){
      if(strcmp(elemento->Name(),"translate")==0){
        parseTranslate(elemento, &translate);
      }
      if(strcmp(elemento->Name(),"rotate")==0){
        parseRotate(elemento, &rotate);
      }
      if(strcmp(elemento->Name(),"scale")==0){
        parseScale(elemento, &scale);
      }
  }

  Transformation t = Transformation(rotate, scale, translate);

  for(XMLElement* model = group->FirstChildElement("models")->FirstChildElement("model"); model; model= model->NextSiblingElement()){

    readFile(model->Attribute("file"));
    vector<Ponto> p1 = shape;
    shape.clear();
    vector<Group> filhos;
    if (group->FirstChildElement("group")) {
        XMLElement *f = group->FirstChildElement("group");
        for(;f;f = f->NextSiblingElement()){
            parseXML(f, &filhos);
      }
    }
    Group pai = Group(model->Attribute("file"), t, filhos,p1);
    pai.imprime();
    g->push_back(pai);
  }
}


void lerXML(string ficheiro) {
    XMLDocument docxml;

    if (!(docxml.LoadFile(ficheiro.c_str()))) {
        XMLElement* root = docxml.FirstChildElement();
        XMLElement* group = root -> FirstChildElement();
        //vector<Group> g = vector<Group>();
        if(group->FirstChildElement("group")){
          group = group->FirstChildElement("group");
        }
        for(group;group;group = group->NextSiblingElement()){
          parseXML(group, &groups);
        }
    }
    else {
        cout << "Ficheiro XML não foi encontrado" << endl;
    }
}
*/
void desenha(vector<Group> g){
  for(int j=0; j<g.size();j++){
    glPushMatrix();
    Transformation t = g[j].getTrans();
    glRotatef(t.getRotate().getAngle(), t.getRotate().getX(),t.getRotate().getY(),t.getRotate().getZ());
    glTranslatef(t.getTranslate().getX(),t.getTranslate().getY(),t.getTranslate().getZ());
    glScalef(t.getScale().getX(),t.getScale().getY(),t.getScale().getZ());
    shape1.clear();
    shape1 = g[j].getPontos();
    glBegin(GL_TRIANGLES);
    glColor3f(sin(j),1/tan(j),cos(j));


    for(int i = 0; i<shape1.size(); i++){
      glVertex3f(shape1[i].getX(), shape1[i].getY(), shape1[i].getZ());
    }
    glEnd();

    for(int i = 0; i<g[j].getFilhos().size(); i++){
      desenha(g[j].getFilhos());
    }
    glPopMatrix();
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
	gluLookAt(rad*cos(beta)*sin(alpha),rad*sin(beta) , rad*cos(beta)*cos(alpha),
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

    drawAxis();

    desenha(groups1);

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
    groups1 = lerXML(path);
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
