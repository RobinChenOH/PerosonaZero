#include "stdafx.h"

Scene::Scene() :MyObject(scene1, 0, 0), serial(-1) {}


Scene::~Scene(){
}

void Scene::MoveLeft(const int &distance){
	x -= distance;
}

void Scene::MoveRight(const int &distance){
	x += distance;
}

void Scene::Switch(){
	serial++;
	Reload();//重新载入场景
}

void Scene::Reload(){
	switch (serial) {
	case 0:
		SetAttribute(scene1, MOTIONLESS, false, true); x = 0; y = 0; break;
	case 1:
		SetAttribute(scene2, MOTIONLESS, false, true); x = 0; y = 0; break;
	case 2:
		SetAttribute(scene3, MOTIONLESS, false, true); x = 0; y = 0; break;
	default:break;
	}
}

void Scene::Clear(){
	serial -= 1;
}

const int & Scene::Serial(){
	return serial;
}
