/* $Rev: 250 $ */
#include "Cube.h"

#include "utility.h"

Cube::Cube() : Object() {

}

Cube::Cube(const Cube& cube) : Object(cube) {

}

Cube::~Cube() {

}

const Cube& Cube::operator=(const Cube& cube) {
	if (this != &cube) {
		Object::operator=(cube);
	}
	return *this;
}

std::vector<RayIntersection> Cube::intersect(const Ray& ray) const {

    std::vector<RayIntersection> result;

    Ray inverseRay = transform.applyInverse(ray);

    const Point& p = inverseRay.point;
    const Direction& d = inverseRay.direction;

    double z0 = inverseRay.point(2);
    double dz = inverseRay.direction(2);
    double y0 = inverseRay.point(1);
    double dy = inverseRay.direction(1);
    double x0 = inverseRay.point(0);
    double dx = inverseRay.direction(0);

    double t;
    RayIntersection hit;
    hit.material = material;


    if (std::abs(dz) > epsilon) {
        t = (-1 - z0)/ dz;
        hit.point = p + t * d;
        if (std::abs(x0 + t * dx) <= 1 && std::abs(y0 + t * dy) <= 1) {
            hit.normal = transform.apply(Normal(0, 0, -1));
            hit.point = transform.apply(Point(p + t * d));
            hit.distance = (hit.point - ray.point).norm() * sign(t);
            result.push_back(hit);
        }

        t = (1 - z0)/ dz;
        hit.point = p + t * d;
        if (std::abs(x0 + t * dx) <= 1 && std::abs(y0 + t * dy) <= 1) {
            hit.normal = transform.apply(Normal(0, 1, 0));
            hit.point = transform.apply(Point(p + t * d));
            hit.distance = (hit.point - ray.point).norm() * sign(t);
            result.push_back(hit);       
        }
    }


    if (std::abs(dy) > epsilon) {
        t = (-1 - y0)/ dy;
        hit.point = p + t * d;
        if (std::abs(x0 + t * dx) <= 1 && std::abs(z0 + t * dz) <= 1) {
            hit.normal = transform.apply(Normal(0, -1, 0));
            hit.point = transform.apply(Point(p + t * d));
            hit.distance = (hit.point - ray.point).norm() * sign(t);
            result.push_back(hit);
        }

        t = (1 - y0)/ dy;
        hit.point = p + t * d;
        if (std::abs(x0 + t * dx) <= 1 && std::abs(z0 + t * dz) <= 1) {
            hit.normal = transform.apply(Normal(0, 1, 0));
            hit.point = transform.apply(Point(p + t * d));
            hit.distance = (hit.point - ray.point).norm() * sign(t);
            result.push_back(hit);
        }
    }

    if (std::abs(dx) > epsilon) {
        t = (-1 - x0)/ dx;
        hit.point = p + t * d;
        if (std::abs(y0 + t * dy) <= 1 && std::abs(z0 + t * dz) <= 1) {
            hit.normal = transform.apply(Normal(-1, 0, 0));
            hit.point = transform.apply(Point(p + t * d));
            hit.distance = (hit.point - ray.point).norm() * sign(t);
            result.push_back(hit);
        }

        t = (1 - x0)/ dx;
        hit.point = p + t * d;
        if (std::abs(y0 + t * dy) <= 1 && std::abs(z0 + t * dz) <= 1) {
            hit.normal = transform.apply(Normal(0, 1, 0));
            hit.point = transform.apply(Point(p + t * d));
            hit.distance = (hit.point - ray.point).norm() * sign(t);
            result.push_back(hit);
        }
    }

        
    return result;
}
