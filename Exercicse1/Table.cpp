#include "Table.h"



Table::Table()
{
}

Table::Table(double x, double y, double z)
{
}

Table::Table(double x, double y, double z, MyMesh * _mesh)
{
	setPosition(x, y, z);
	tamanho = 0.75;
	setRaio((tamanho*tamanho) + ((tamanho / 2)*(tamanho / 2)));
	setSpeed(0, 0, 0);
	setTexMd(0);
	float amb2[4] = { 0.7f,0.0f,0.00f,1.0f };
	float diff2[4] = { 0.5f,0.5f,0.4f,1.0f };
	float spec2[4] = { 0.7f,0.7f,0.04f,1.0f };
	float emissive[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float pos[3] = { 0.0f, 0.0f, 0.0f };

	float shininess = 100.0f;
	int texcount = 0;
	mesh = _mesh;
	memcpy(mesh->mat.ambient, amb2, 4 * sizeof(float));
	memcpy(mesh->mat.diffuse, diff2, 4 * sizeof(float));
	memcpy(mesh->mat.specular, spec2, 4 * sizeof(float));
	memcpy(mesh->mat.emissive, emissive, 4 * sizeof(float));
	memcpy(mesh->position, pos, 3 * sizeof(float));
	mesh->mat.shininess = shininess;
	mesh->mat.texCount = texcount;
	createCube();
}


Table::~Table()
{
}

void Table::draw()
{
	pushMatrix(MODEL);
	translate(MODEL, getPosition()->getX(), getPosition()->getZ(), getPosition()->getY());
	scale(MODEL, 20, 20, 20);
}

void Table::update(double delta)
{
}
