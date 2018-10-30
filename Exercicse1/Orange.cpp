#include "Orange.h"

Orange::Orange() : Obstacle(), angle(rand() % 360), angleZ(0), fall(-1) {
	setSpeed(0.002, 0.002, getSpeed().getZ());
	setRaio(0.5);
}

Orange::Orange(double x, double y, double z) : Obstacle(), angle(rand() % 360), angleZ(0), fall(-1) {
	setPosition(x, y, z);
	setSpeed(0.002, 0.002, getSpeed().getZ());
	setRaio(0.5);
//	mate.defineMaterial(amb, diff, spec, shine);
//	quad = gluNewQuadric();
	//memcpy(mesh->mat.ambient, amb, 4 * sizeof(float));
	//memcpy(mesh->mat.diffuse, diff, 4 * sizeof(float));
	//memcpy(mesh->mat.specular, spec, 4 * sizeof(float));
	//memcpy(mesh->mat.emissive, emissive, 4 * sizeof(float));
	//memcpy(mesh->position, pos, 3 * sizeof(float));
	//mesh->mat.shininess = shininess;
	//mesh->mat.texCount = texcount;
	//createSphere(1.0f, 20);
}

Orange::Orange(double x, double y, double z, struct MyMesh *_mesh) : Obstacle(), angle(rand() % 360), angleZ(0), fall(-1) {
	setPosition(x, y, z);
	setSpeed(0.002, 0.002, getSpeed().getZ());
	setRaio(0.5);
	setTexMd(1);
	mesh = _mesh;
	memcpy(mesh->mat.ambient, amb, 4 * sizeof(float));
	memcpy(mesh->mat.diffuse, diff, 4 * sizeof(float));
	memcpy(mesh->mat.specular, spec, 4 * sizeof(float));
	memcpy(mesh->mat.emissive, emissive, 4 * sizeof(float));
	memcpy(mesh->position, pos, 3 * sizeof(float));
	mesh->mat.shininess = shininess;
	mesh->mat.texCount = texcount;
	createSphere(1.0f, 8);
	//createCube();
}
Orange::~Orange() {}

void Orange::update(double delta) {
	double x = getPosition()->getX(), y = getPosition()->getY(), z = getPosition()->getZ();
	//printf("%f %f %f\n", x, y, z);
	
	if (x >= -3.0 && y >= -3.0 && x <= 20.0 && y <= 20.0) {
		if (x >= -1.0 && y >= -1.0 && x <= 19.0 && y <= 19.0) {
			setPosition(x + getSpeed().getX()*sin(PI*angle / 180)*delta, y + getSpeed().getY()*cos(PI*angle / 180)*delta, z);
		}
		else {
			setPosition(x + getSpeed().getX()*sin(PI*angle / 180)*delta/3, y + getSpeed().getY()*cos(PI*angle / 180)*delta/3, z - 0.1);
		}
	}
	else {
		z = 0.5;
		angle = rand() % 360;
		x = rand() % 29;
		i = rand() % 2;
		setSpeed(getSpeed().getX() * 1.1, getSpeed().getX()  * 1.1, getSpeed().getZ());
		if (i == 0 && angle > 0 && angle < 180) {
			setPosition(x, 0.0, z);
			angle = -angle;
		}
		if (i == 1 && angle > 0 && angle < 180) {
			setPosition(0, x , z);
		}
		if (i == 0 && angle >= 180 && angle <= 360) {
			setSpeed(getSpeed().getX(), -getSpeed().getX(), getSpeed().getZ());
			setPosition(x, 20.0, z);
			//angle = -angle;
		}
		if (i == 1 && angle >= 180 && angle <= 360) {
			setSpeed(getSpeed().getX(), -getSpeed().getX(), getSpeed().getZ());
			setPosition(20.0, x, z);
		}
	}
}

void Orange::draw() {
	pushMatrix(MODEL);
	translate(MODEL, getPosition()->getX(), getPosition()->getZ(), getPosition()->getY());
	//if (i == 0 && angle > 0 && angle < 180) {
	//	rotate(MODEL, angle, 0, 1, 0);
	//	rotate(MODEL, angleZ++, 1, 0, 0);

	//}
	if (angle > 0 && angle < 180) {
		rotate(MODEL, angle, 0, 1, 0);
		rotate(MODEL, angleZ++, 1, 0, 0);

	}
	if (angle >= 180 && angle <= 360) {
		rotate(MODEL, angle, 0, -1, 0);
		rotate(MODEL, angleZ++, -1, 0, 0);
	}
	angleZ++;
}