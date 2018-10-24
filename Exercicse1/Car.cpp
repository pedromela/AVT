#include "Car.h"

Car::Car() : DynamicObject(), angle(0.0), UP(0), DOWN(0), RIGHT(0), LEFT(0) {
	angle = 0;
	angle_w = 0;
	escala = 0.25;
	largura = 2.0 * escala;
	comprimento = 5.0 * escala;
	setRaio(comprimento);
	lights = false;
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	mate.defineMaterial(amb, diff, spec, shine);
}

Car::Car(double x, double y, double z) : DynamicObject() {

	setPosition(x, y, z);
	setSpeed(0, 0, 0);
	angle_w = 0;
	angle = 0;
	escala = 0.25;
	largura = 2.0 * escala;
	comprimento = 5.0 * escala;
	setRaio((comprimento / 2));
	colidiu = false;
	lights = false;
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	//mate.defineMaterial(amb, diff, spec, shine);
	//initLights();
}
Car::Car(double x, double y, double z, struct MyMesh *_mesh) : DynamicObject()
{
	setPosition(x, y, z);
	setSpeed(0, 0, 0);
	angle_w = 0;
	angle = 0;
	escala = 0.25;
	largura = 2.0 * escala;
	comprimento = 5.0 * escala;
	setRaio((comprimento / 2));
	colidiu = false;
	lights = false;
	float pos[] = { 0.0f, 0.0f, 0.0f };
	float amb[] = { 0.2f, 0.15f, 0.1f, 1.0f };
	float diff[] = { 0.2f, 0.6f, 0.4f, 1.0f };
	float spec[] = { 0.4f, 0.8f, 0.8f, 1.0f };
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
	createCone(1,0.5,10);
}
Car::~Car() {}
void Car::initLights() {
	Vector3 v = getPosCar();
	GLfloat light_pos[] = { 4,2,1, 1.0 };
	GLfloat position[] = { 1.0, 0.0, -1.0, 2.0 };
	GLfloat directional[] = { 0.5, 0.5, 0.5, 5.0 };
	glLightfv(GL_LIGHT7, GL_POSITION, light_pos);
	// directional light 
	glLightfv(GL_LIGHT7, GL_DIFFUSE, directional);
	glLightfv(GL_LIGHT7, GL_SPECULAR, directional);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, position);
	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 60); // 0~180 
	glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 0.1);
}
void Car::onLights() {
	glEnable(GL_LIGHT7);
}
void Car::offLights() {
	glDisable(GL_LIGHT7);
}
double Car::getAngle() {
	return angle;
}

void Car::setAngle(double _a) {
	angle = _a;
}

void Car::setColidiu(bool bo) {
	colidiu = bo;
}

bool Car::getColidou() {
	return colidiu;
}

int Car::getVidas() {
	return vidas;
}

void Car::setVidas(int v) {
	vidas = v;
}

float Car::getPontos() {
	return pontos;
}

void Car::setPontos(float v) {
	pontos = v;
}
void Car::update(double delta) {
	int i = 0;
	double d;
	if (HasSpeed() != 0) {
		angle_w = angle_w + 1;
		if (angle_w == 360) angle_w = 0;
	}

	if (colidiu == true) {
		setSpeed(0, 0, 0);
		setPontos(0);
	}
	if (UP == 1) {
		setSpeed(getSpeed().getX() + 0.000025, getSpeed().getY() + 0.000025, 0);
	}
	if (DOWN == 1) {
		setSpeed(getSpeed().getX() - 0.000015, getSpeed().getY() - 0.000015, 0);
	}
	if (RIGHT == 1) {
		/*if (UP == 1 || DOWN == 1) {
			angle = (angle - 1.5);
			if (angle == 360) angle = 0;
			if (angle == -360) angle = 0;
		}*/
		d = sqrt((getSpeed().getX() * getSpeed().getX()) + (getSpeed().getY() * getSpeed().getY()));
		if (d < 2.5){
			if (UP == 1)
				angle = angle - 1000 * d;
			if (DOWN == 1)
				angle = angle + 1000 * d;
		}
		else{
			if (UP == 1)
				angle = angle - 1000 * 2.5;
			if (DOWN == 1)
				angle = angle + 1000 * 2.5;
		}
	}
	if (LEFT == 1) {
		/*if (UP == 1 || DOWN == 1) {
			angle = (angle + 1.5);
			if (angle == 360) angle = 0;
			if (angle == -360) angle = 0;
		}*/
		d = sqrt((getSpeed().getX() * getSpeed().getX()) + (getSpeed().getY() * getSpeed().getY()));
		if (d < 2.5) {
			if (UP == 1)
				angle = angle + 1000 * d;
			if (DOWN == 1)
				angle = angle - 1000 * d;
		}
		else {
			if (UP == 1)
				angle = angle + 1000 * 2.5;
			if (DOWN == 1)
				angle = angle - 1000 * 2.5;
		}
	}
	setPosition(getPosition()->getX() + getSpeed().getX()*cos(angle*PI / 180)*delta, getPosition()->getY() + getSpeed().getY()*sin(angle*PI / 180)*delta, getPosition()->getZ() + getSpeed().getZ());
	setPontos(getPontos() + sqrt((getSpeed().getX() * getSpeed().getX()) + (getSpeed().getY() * getSpeed().getY()))*10);
	if (UP == 0 && DOWN == 0) {
		if (HasSpeed()) {
			setSpeed(getSpeed().getX() - getSpeed().getX()*0.05, getSpeed().getY() - getSpeed().getY()*0.05, getSpeed().getZ());
		}
		angle_w = 0;

	}
}

Vector3 Car::getPosCar() {
	Vector3 _posCar = getPosition()->operator+(Vector3(1, 0, 0));
	return _posCar;
}

void Car::setDir(int up, int down, int right, int left) {
	UP = up;
	DOWN = down;
	RIGHT = right;
	LEFT = left;
}

void Car::draw() {
	pushMatrix(MODEL);
	translate(MODEL, getPosition()->getX(), getPosition()->getZ(), getPosition()->getY());
	rotate(MODEL, -angle, 0.0, 1.0, 0.0); 

}

void Car::draw(VSShaderLib shader, GLint vm_uniformId, GLint pvm_uniformId, GLint normal_uniformId)
{
	// send the material
	GLint loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
	glUniform4fv(loc, 1, mesh->mat.ambient);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
	glUniform4fv(loc, 1, mesh->mat.diffuse);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
	glUniform4fv(loc, 1, mesh->mat.specular);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.shininess");
	glUniform1f(loc, mesh->mat.shininess);
	pushMatrix(MODEL);
	translate(MODEL, getPosition()->getX(), getPosition()->getZ(), getPosition()->getY());
	// send matrices to OGL
	//printf("%f %f %f %f\n", i, _orange_objects[i]->getPosition()->getY(), _orange_objects[i]->getPosition()->getY(), _orange_objects[i]->getPosition()->getZ());
	computeDerivedMatrix(PROJ_VIEW_MODEL);
	glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
	glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
	computeNormalMatrix3x3();
	glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

	// Render mesh
	glBindVertexArray(mesh->vao);

	if (!shader.isProgramValid()) {
		printf("Program Not Valid!\n");
		exit(1);
	}
	glDrawElements(mesh->type, mesh->numIndexes, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	popMatrix(MODEL);
}
