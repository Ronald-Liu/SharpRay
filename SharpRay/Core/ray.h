#ifndef _RAY_H_
#define _RAY_H_


#include <Core/fmath.h>
#include <Core/Color.h>
class Film;
struct Pixel;
class Entity;
class World;

struct ShadeInfo
{
	float transferFactor;
	float firstHitT;
	point3D firstHitPoint;
	vector3D hitNormal;
	Entity* firstHitEntity;
	RColor Lo;
};

struct Ray
{
	point3D origin;
	vector3D direction;
	Film* currentFilm;
	union{
		Pixel* orgPixel;
		Ray* orgRay;
	}parent;
	ShadeInfo shadeInfo;
	
	/**
	 * @brief Return whether this ray will hit any entity before hit a giving point.
	 * @details Ray may hit the entity which the giving point belong to.
	 * shadeInfo.firstHitT should be set to specify the point origin + direction * shadeInfo.firstHitT 
	 * This function are often used to check whether a point is in the shadow of other object
	 * @return True if this ray hit an entity before hit the giving point.
	 */
	bool hasHit() const;

	/**
	 * @brief Trace this ray
	 * @details
	 *  1. Find the nearest surface the ray may hit in the world
	 *  2. Calculate and set shadeInfo
	 */
	void trace();

	Ray(const point3D& o, const vector3D& d, Film* cf, Pixel* p) :origin(o), direction(normalize(d)), currentFilm(cf){ 
		parent.orgPixel = p;
	}
	Ray(const point3D& o, const vector3D& d, Film* cf, Ray* p) :origin(o), direction(normalize(d)), currentFilm(cf){ 
		parent.orgRay = p;
	}
	Ray(const point3D& o, const vector3D& d) :origin(o), direction(normalize(d)){ }
};
#endif