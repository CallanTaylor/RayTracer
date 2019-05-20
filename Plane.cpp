#include "Plane.h"

#include "utility.h"

Plane::Plane() : Object() {

}

Plane::Plane(const Plane& plane) : Object(plane) {

}

Plane::~Plane() {

}

const Plane& Plane::operator=(const Plane& plane) {
	if (this != &plane) {
		Object::operator=(plane);
	}
	return *this;
}

std::vector<RayIntersection> Plane::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;

        Ray inverseRay = transform.applyInverse(ray);

        const Point& p = inverseRay.point;
        const Direction& d = inverseRay.direction;


        double z0 = inverseRay.point(2);
        double dz = inverseRay.direction(2);
        double t = -z0/dz;

        if (std::abs(dz) > epsilon) {
            RayIntersection hit;
            hit.point = p + t * d;
            if (std::abs(inverseRay.point(0) + t * inverseRay.direction(0)) <= 1
                && std::abs(inverseRay.point(1) + t * inverseRay.direction(1)) <= 1) {
                hit.material = material;
                hit.normal = transform.apply(Normal(0, 0, 1));
                hit.point = transform.apply(Point(p + t * d));
                hit.distance = (hit.point - ray.point).norm() * sign(t);
                result.push_back(hit);
            }
        }
        
	return result;
}
