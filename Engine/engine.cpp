
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

struct Ponto {
	float x;
	float y;
	float z;
};

void plane(float side, string nome) {
	ofstream file(nome);

	float x, y, z;

	x = side / 2;
	z = side / 2;
	y = 0;

//Triangulo 1
	file << x << "," << y << "," << z << endl;
	file << x << "," << y << "," << -z << endl;
	file << -x << "," << y << "," << z << endl;

//Triangulo 2
	file << -x << "," << y << "," << -z << endl;
	file << -x << "," << y << "," << z << endl;
	file << x << "," << y << "," << -z << endl;

	file.close();
}

void cube(double comp, double alt, double larg, double div, string nome) {
	double x, y, z, xx, yy, zz;

	ofstream file(nome);
	double espcx = comp / div;
	double espcy = alt / div;
	double espcz = larg / div;

	// Frente e Tras

	z = larg / 2; zz = -z;
	y = -(alt / 2);
	for (int i = 0; i < div; i++) {
		x = -(comp / 2);
		xx = x + espcx;
		yy = y + espcy;
		for (int j = 0; j < div; j++) {

			file << x << "," << y << "," << z << endl;
			file << xx << "," << y << "," << z << endl;
			file << x << "," << yy << "," << z << endl;

			file << xx << "," << y << "," << z << endl;
			file << xx << "," << yy << "," << z << endl;
			file << x << "," << yy << "," << z << endl;

			file << x << "," << y << "," << zz << endl;
			file << x << "," << yy << "," << zz << endl;
			file << xx << "," << y << "," << zz << endl;

			file << xx << "," << y << "," << zz << endl;
			file << x << "," << yy << "," << zz << endl;
			file << xx << "," << yy << "," << zz << endl;

			x += espcx;
			xx += espcx;
		}

		y += espcy;
	}

	// Cima  e Baixo

	y = alt / 2; yy = -y;
	z = larg / 2;
	for (int i = 0; i < div; i++) {
		x = -(comp / 2);
		xx = x + espcx;
		zz = z - espcz;
		for (int j = 0; j < div; j++) {

			file << x << "," << y << "," << z << endl;
			file << xx << "," << y << "," << z << endl;
			file << x << "," << y << "," << zz << endl;

			file << xx << "," << y << "," << z << endl;
			file << xx << "," << y << "," << zz << endl;
			file << x << "," << y << "," << zz << endl;

			file << x << "," << yy << "," << z << endl;
			file << x << "," << yy << "," << zz << endl;
			file << xx << "," << yy << "," << z << endl;

			file << xx << "," << yy << "," << z << endl;
			file << x << "," << yy << "," << zz << endl;
			file << xx << "," << yy << "," << zz << endl;

			x += espcx;
			xx += espcx;
		}
		z -= espcz;
	}

	// Direita e Esquerda

	x = -(comp / 2); xx = -x;
	y = -(alt / 2);
	for (int i = 0; i < div; i++) {
		z = larg / 2;
		zz = z - espcz;
		yy = y + espcy;
		for (int j = 0; j < div; j++) {

			file << x << "," << y << "," << z << endl;
			file << x << "," << yy << "," << z << endl;
			file << x << "," << y << "," << zz << endl;

			file << x << "," << y << "," << zz << endl;
			file << x << "," << yy << "," << z << endl;
			file << x << "," << yy << "," << zz << endl;

			file << xx << "," << y << "," << z << endl;
			file << xx << "," << y << "," << zz << endl;
			file << xx << "," << yy << "," << z << endl;

			file << xx << "," << yy << "," << z << endl;
			file << xx << "," << y << "," << zz << endl;
			file << xx << "," << yy << "," << zz << endl;

			z -= espcz;
			zz -= espcz;
		}
		y += espcy;
	}
	file.close();
}

void cone(double raio, double h, double divb, double divh, string nome) {
	
	ofstream file(nome);
	double angle = (2 * M_PI) / divb;
	double espch = h / divh;
	double alt = -(h / 2);

	for (int i = 0; i < 2 * M_PI; i += angle) {

		float x1 = 0;
		float y1 = alt;
		float z1 = 0;

		float x2 = raio * sin(i + angle);
		float y2 = alt;
		float z2 = raio * cos(i + angle);

		float x3 = raio * sin(i);
		float y3 = alt;
		float z3 = raio * cos(i);

		file << x1 << "," << y1 << "," << z1 << endl;
		file << x2 << "," << y2 << "," << z2 << endl;
		file << x3 << "," << y3 << "," << z3 << endl;
	}

	for (int i = 0; i < divh; i++) {

		for (int j = 0; j < divb; j+= angle) {

		
			float x5 = (raio - (raio*i)/divh) * sin(j);
			float y5 = alt + i*espch;
			float z5 = raio * cos(j);

			float x4 = (raio - (raio * (i + 1)) / divh) * sin(j);
			float y4 = alt + (i + 1) * espch;
			float z4 = (raio - (raio * (i + 1)) / divh) * cos(j);

			float x6 = (raio - (raio * (i + 1)) / divh) * sin(j + angle);
			float y6 = alt + (i + 1) * espch;
			float z6 = (raio - (raio * (i + 1)) / divh) * cos(j + angle);

			float x7 = (raio - (raio * i) / divh) * sin(j + angle);
			float y7 = alt + i * espch;
			float z7 = (raio - (raio * i) / divh) * cos(j + angle);

			file << x5 << "," << y5 << "," << z5 << endl;
			file << x4 << "," << y4 << "," << z4 << endl;
			file << x6 << "," << y6 << "," << z6 << endl;

			file << x5 << "," << y5 << "," << z5 << endl;
			file << x7 << "," << y7 << "," << z7 << endl;
			file << x6 << "," << y6 << "," << z6 << endl;
		}

	}
	file.close();
}

