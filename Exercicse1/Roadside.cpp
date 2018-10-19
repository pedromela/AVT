#include "Roadside.h"

Roadside::Roadside(double comp) {

	comprimento = comp;
	comp_pist_out = comp;
	comp_pist_in = (comp / 2) + 1;
	n_cheer_out = comp_pist_out * 4;
	n_cheer_in = comp_pist_in * 4;
	i = 0;
	inc = 1;

	inicializarCheerios();

	//mate.defineMaterial(amb, diff, spec, shine);
	//tex.loadTextureFromFile("./plank01.bmp");
}

Roadside::Roadside(double comp, MyMesh *_mesh, int _start, std::vector<GameObject*> *_game_objects)
{
	comprimento = comp;
	comp_pist_out = comp;
	comp_pist_in = (comp / 2) + 1;
	n_cheer_out = comp_pist_out * 4;
	n_cheer_in = comp_pist_in * 4;
	i = 0;
	inc = 1;
	start = _start;
	mesh = _mesh;
	game_objects = _game_objects;
	inicializarCheerios();

}
Roadside::Roadside(double comp, MyMesh * _mesh)
{
	comprimento = comp;
	comp_pist_out = comp;
	comp_pist_in = (comp / 2) + 1;
	n_cheer_out = comp_pist_out * 4;
	n_cheer_in = comp_pist_in * 4;
	i = 0;
	inc = 1;
	setPosition(0, 0, 0);
	mesh = _mesh;
	//inicializarCheerios();
	float pos[] = { 0.0f, 0.0f, 0.0f };
	float amb[] = { 0.2f, 0.15f, 0.1f, 1.0f };
	float diff[] = { 0.8f, 0.6f, 0.4f, 1.0f };
	float spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shininess = 100.0f;
	int texcount = 0;
	mesh = _mesh;
	memcpy(mesh->mat.ambient, amb, 4 * sizeof(float));
	memcpy(mesh->mat.diffuse, diff, 4 * sizeof(float));
	memcpy(mesh->mat.specular, spec, 4 * sizeof(float));
	memcpy(mesh->mat.emissive, emissive, 4 * sizeof(float));
	memcpy(mesh->position, pos, 3 * sizeof(float));
	mesh->mat.shininess = shininess;
	mesh->mat.texCount = texcount;
	createCone(10, 5, 5);
}
double Roadside::getN_Cheerios_In() {
	return n_cheer_in;
}

double Roadside::getN_Cheerios_Out() {
	return n_cheer_out;
}

Cheerios* Roadside::getCheerio_In(int i) {
	return c_in[i];
}
Cheerios* Roadside::getCheerio_Out(int i) {
	return c_out[i];
}

void Roadside::update(unsigned long delta) {

	for (i = 0; i < c_in.size(); i++) {
		c_in[i]->update(delta);
	}
	for (i = 0; i < c_out.size(); i++) {
		c_out[i]->update(delta);
	}

}

void Roadside::draw() {
	pushMatrix(MODEL);
	translate(MODEL, getPosition()->getX(), getPosition()->getZ(), getPosition()->getY());
}


void Roadside::inicializarCheerios() {

	float	ini_out = 0, ini_in = ini_out + 4, position_x = 0, position_y = 0, z = 0.15;
	int START = start+1;
	/*Cheerios Outside*/
	for (i = 1; i <= n_cheer_out;) {
		printf("start %d\n", START);
		if (i != (n_cheer_out)) {
			game_objects->push_back(new Cheerios(position_x, ini_out, z, &mesh[START++]));
			i++;
		}
		if (i > 2 && i != (n_cheer_out)) {
			game_objects->push_back(new Cheerios(ini_out, position_y, z, &mesh[START++]));
			i++;
		}
		if (i != (n_cheer_out)) {
			game_objects->push_back(new Cheerios(position_x, comp_pist_out, z, &mesh[START++]));
			i++;
		}
		if (i != (n_cheer_out)) {
			game_objects->push_back(new Cheerios(comp_pist_out, position_y, z, &mesh[START++]));
			i++;
		}
		if (i == (n_cheer_out)) {
			game_objects->push_back(new Cheerios(comp_pist_out, comp_pist_out, z, &mesh[START++]));
			i++;
		}
		START++;
		position_x = position_x + inc;
		position_y = position_y + inc;
	}

	/*Cheerios Inside*/
	position_x = ini_in;
	position_y = ini_in;

	for (i = 1; i <= n_cheer_in;) {
		printf("start %d\n", START);
		if (i != (n_cheer_in)) {
			game_objects->push_back(new Cheerios(position_x, ini_in, z, &mesh[START++]));
			i++;
		}
		if (i > 2 && i != (n_cheer_in)) {
			game_objects->push_back(new Cheerios(ini_in, position_y, z, &mesh[START++]));
			i++;
		}
		if (i != (n_cheer_in)) {
			game_objects->push_back(new Cheerios(position_x, comp_pist_in + ini_in, z, &mesh[START++]));
			i++;
		}
		if (i != (n_cheer_in)) {
			game_objects->push_back(new Cheerios(comp_pist_in + ini_in, position_y, z, &mesh[START++]));
			i++;
		}
		if (i == (n_cheer_in)) {
			game_objects->push_back(new Cheerios(comp_pist_in + ini_in, comp_pist_in + ini_in, z, &mesh[START++]));
			i++;
		}
		position_x = position_x + inc;
		position_y = position_y + inc;
	}
}
