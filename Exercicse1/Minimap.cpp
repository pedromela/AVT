#include "Minimap.h"

Minimap::Minimap(double x, double y, double z, MyMesh * _mesh)
{
	setPosition(x, y, z);
	setRaio((0.75*0.75) + ((0.75 / 2)*(0.75 / 2)));
	setTexMd(3);
	float amb2[4] = { 0.74f,0.74f,0.0f,1.0f };
	float diff2[4] = { 0.5f,0.5f,0.4f,1.0f };
	float spec2[4] = { 0.7f,0.7f,0.04f,1.0f };
	float emissive[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float pos[3] = { 0.0f, 0.0f, 0.0f };

	float shininess = 100.0f;
	int texcount = 3;
	mesh = _mesh;
	memcpy(mesh->mat.ambient, amb2, 4 * sizeof(float));
	memcpy(mesh->mat.diffuse, diff2, 4 * sizeof(float));
	memcpy(mesh->mat.specular, spec2, 4 * sizeof(float));
	memcpy(mesh->mat.emissive, emissive, 4 * sizeof(float));
	memcpy(mesh->position, pos, 3 * sizeof(float));
	mesh->mat.shininess = shininess;
	mesh->mat.texCount = texcount;
	createSphere(4.0f,8);
}

void Minimap::draw() {
	pushMatrix(MODEL);
	translate(MODEL, getPosition()->getX() - 0.5f, getPosition()->getZ(), getPosition()->getY() - 0.5f);
}