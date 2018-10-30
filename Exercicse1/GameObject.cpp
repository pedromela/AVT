#include "GameObject.h"

GameObject::GameObject() : Entity() {}
GameObject::~GameObject() {}
void GameObject::draw(double angle, double px, double py) {}
void GameObject::update(double delta) {}
void GameObject::draw(double angle) {}
void GameObject::draw() {}

void GameObject::draw(VSShaderLib shader, GLint vm_uniformId, GLint pvm_uniformId, GLint normal_uniformId){}

bool GameObject::Colision(GameObject* obj, double angle, double _obj_angle) {
	double x = getPosition()->getX();
	double y = getPosition()->getY();
	double r = sqrt(getRaio());

	double x_obj = obj->getPosition()->getX();
	double y_obj = obj->getPosition()->getY();
	double r_obj = obj->getRaio();

	double d = sqrt((x - x_obj)*(x - x_obj) + (y - y_obj)*(y - y_obj));

	double sum_r_r_obj = sqrt(r*r + r_obj * r_obj);

	if (d <= sum_r_r_obj)
		return true;
	else
		return false;


}

bool GameObject::Colision(GameObject* obj) {
	double x = getPosition()->getX();
	double y = getPosition()->getY();
	double r = sqrt(getRaio());

	double x_obj = obj->getPosition()->getX();
	double y_obj = obj->getPosition()->getY();
	double r_obj = obj->getRaio();

	double d = sqrt((x - x_obj)*(x - x_obj) + (y - y_obj)*(y - y_obj));

	double sum_r_r_obj = sqrt(r*r + r_obj * r_obj);

	if (d <= sum_r_r_obj)
		return true;
	else
		return false;


}

int GameObject::getTex() {
	return _tex;
}
void GameObject::setTex(int tex) {
	_tex = tex;
}

int GameObject::getTexMd() {
	return texMd;
}
void GameObject::setTexMd(int t) {
	texMd = t;
}
void GameObject::setCollisionAngle(double _a) {
	collision_agle = _a;
}
double GameObject::getCollisionAngle() {
	return collision_agle;
}



void GameObject::setBox(double xm, double xM, double ym, double yM) {
	_xm = xm;
	_xM = xM;
	_ym = ym;
	_yM = yM;
}
double GameObject::getXm() {
	return _xm;
}
double GameObject::getXM() {
	return _xM;
}
double GameObject::getYm() {
	return _ym;
}
double GameObject::getYM() {
	return _yM;
}
