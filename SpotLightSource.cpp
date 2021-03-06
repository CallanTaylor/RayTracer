#include "SpotLightSource.h"

#include "utility.h"

SpotLightSource::SpotLightSource(const Colour& colour, const Point& location, const Direction& direction, double angle) :
	LightSource(colour), location_(location), direction_(direction), angle_(angle) {

}




SpotLightSource::SpotLightSource(const SpotLightSource& lightSource) :
LightSource(lightSource),  location_(lightSource.location_), direction_(lightSource.direction_), angle_(lightSource.angle_) {

}


SpotLightSource::~SpotLightSource() {

}

const SpotLightSource& SpotLightSource::operator=(const SpotLightSource& lightSource) {
	if (this != &lightSource) {
		LightSource::operator=(lightSource);
		location_ = lightSource.location_;
		direction_ = lightSource.direction_;
		angle_ = lightSource.angle_;
	}
	return *this;
}

Colour SpotLightSource::getIlluminationAt(const Point& point) const {

    Colour colour = colour_;

    colour = colour/getDistanceToLight(point);
    
    return colour;
}

double SpotLightSource::getDistanceToLight(const Point& point) const {
    double distance = (this->location_ - point).norm();
    if (distance < epsilon) {
        distance = epsilon;
    }

    return distance;
}

Direction SpotLightSource::getLightDirection(const Point& point) const {

    Direction lightDirection = point - location_;

    return lightDirection;
}
