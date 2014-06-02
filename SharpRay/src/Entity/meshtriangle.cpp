#include "meshtriangle.h"
#include <Util/mesh.h>
#include <Core/ray.h>

normal3D MeshTriangle::normalAt(const point3D& pos)
{
    point3D& v0 = mesh->vertices[vertexIdx[0]];
    point3D& v1 = mesh->vertices[vertexIdx[1]];
    point3D& v2 = mesh->vertices[vertexIdx[2]];


    return normalize(cross(v0-v1, v0-v2));
}

bool MeshTriangle::firstHit(const Ray* ray, CoordFloat& t)
{
    point3D& v0 = mesh->vertices[vertexIdx[0]];
    point3D& v1 = mesh->vertices[vertexIdx[1]];
    point3D& v2 = mesh->vertices[vertexIdx[2]];

    CoordFloat a = v0.x-v1.x, b = v0.x-v2.x, c = ray->direction.x, d = v0.x-ray->origin.x;
    CoordFloat e = v0.y-v1.y, f = v0.y-v2.y, g = ray->direction.y, h = v0.y-ray->origin.y;
    CoordFloat i = v0.z-v1.z, j = v0.z-v2.z, k = ray->direction.z, l = v0.z-ray->origin.z;

    CoordFloat m = f*k-g*j, n = h*k-g*l, p = f*l-h*j;
    CoordFloat q = g*i-e*k,s=e*j-f*i, r = e*l-h*i;

    CoordFloat invD = 1.0f/(a*m+b*q+c*s);

    CoordFloat ek = d*m-b*n-c*p;
    CoordFloat beta = ek*invD;
    if (beta <0 || beta > 1.f)
        return false;

    ek = a*n+d*q+c*r;
    CoordFloat gamma = ek*invD;
    if (gamma<0 || gamma > 1.f)
        return false;

    if (gamma + beta > 1.f)
        return false;

    ek = a*p-b*r+d*s;
    t = ek*invD;
    return true;
}
