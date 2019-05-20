#include "Parabaloid.h"

Parabaloid::Parabaloid() {

}

Parabaloid::Parabaloid(const Parabaloid& parabaloid) {

}

Parabaloid::~Parabaloid() {

}
const Parabaloid& Parabaloid::operator=(const Parabaloid& parabaloid) {
	
	if (this != &parabaloid) {
		Object::operator=(parabaloid);
	}
	
	return *this;
}

std::vector<RayIntersection> Parabaloid::intersect(const Ray& ray) const {
	std::vector<RayIntersection> result;
	
	/***********************************************************
	 * Code to compute Ray-Parabaloid intersections goes here. *
	 ***********************************************************/

	return result;
}