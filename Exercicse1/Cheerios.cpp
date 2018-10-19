#include "Cheerios.h"


Cheerios::Cheerios() {
	setPosition(0, 0, 0);
	setRaio(0.15);
	setSpeed(0, 0, 0);
	mate.defineMaterial(amb, diff, spec, shine);
}

Cheerios::Cheerios(double x, double y, double z) {
	setPosition(x, y, z);
	setRaio(0.15);
	setSpeed(0, 0, 0);
	mate.defineMaterial(amb, diff, spec, shine);
}

Cheerios::Cheerios(double x, double y, double z, struct MyMesh * _mesh)
{
	setPosition(x, y, z);
	setRaio(0.15);
	setSpeed(0, 0, 0);
	mesh = _mesh;
	float amb2[4] = { 0.74f,0.74f,0.0f,1.0f };
	float diff2[4] = { 0.5f,0.5f,0.4f,1.0f };
	float spec2[4] = { 0.7f,0.7f,0.04f,1.0f };
	float emissive[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float pos[3] = { 0.0f, 0.0f, 0.0f };

	float shininess = 100.0f;
	int texcount = 0;
	mesh = _mesh;
	//printf("CHEERIOS \n");
	memcpy(mesh->mat.ambient, amb2, 4 * sizeof(float));
	memcpy(mesh->mat.diffuse, diff2, 4 * sizeof(float));
	memcpy(mesh->mat.specular, spec2, 4 * sizeof(float));
	memcpy(mesh->mat.emissive, emissive, 4 * sizeof(float));
	memcpy(mesh->position, pos, 3 * sizeof(float));
	mesh->mat.shininess = shininess;
	mesh->mat.texCount = texcount;
	createTorus(0.25,0.5,10,5);
}

void Cheerios::update(double delta) {
	double x = getPosition()->getX(), y = getPosition()->getY(), z = getPosition()->getZ();
	if (HasSpeed()) {
		setPosition(x + getSpeed().getX()*cos(getCollisionAngle()*PI / 180)*delta, y + getSpeed().getY()*sin(getCollisionAngle()*PI / 180)*delta, z);
		setSpeed(getSpeed().getX() - 0.3*getSpeed().getX(), getSpeed().getX() - 0.3*getSpeed().getX(), 0);
	}
}



void Cheerios::draw() {
	pushMatrix(MODEL);
	translate(MODEL, getPosition()->getX(), getPosition()->getZ(), getPosition()->getY());
}
