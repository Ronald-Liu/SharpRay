#pragma once
#include <glm.hpp>
#include "Core\film.h"
#include "Core\world.h"
#include "Core\shader.h"

class camera
{
protected:
	vector3D axis_x, axis_y, direction;
	point3D position;
	inline point3D mapFilm2World(float x, float y){ return position+axis_x*x + axis_y*y; }
	World* currentWorld;
	Shader* shader;
	Film* lFilm;
public:
	camera(const vector3D& u, const vector3D& d, const point3D& pos, Film* f);

	virtual void shoot(World*) = 0;
	virtual ~camera();
};

class pinhole:camera
{
public:
	point3D pinholePos;
	pinhole(vector3D up, vector3D d, const point3D& pos, Film* f, float focalLength) :camera(up, d, pos, f){
		pinholePos = direction*focalLength;
	}
	void shoot(World*);
	~pinhole(){}
};

class lenCamera:camera
{
public:
	float focalLength;
	float apertureDiameter;
	lenCamera();
	void shoot(World*);
	~lenCamera(){}
};