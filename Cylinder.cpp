#include "Cylinder.h"

#include "utility.h"

Cylinder::Cylinder() : Object() {

}

Cylinder::Cylinder(const Cylinder& cylinder) : Object(cylinder) {

}

Cylinder::~Cylinder() {

}

const Cylinder& Cylinder::operator=(const Cylinder& cylinder) {
	if (this != &cylinder) {
		Object::operator=(cylinder);
	}
	return *this;
}

std::vector<RayIntersection> Cylinder::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;


        Ray inverseRay = transform.applyInverse(ray);
        double t;
        RayIntersection hit;
        

        const Point& p = inverseRay.point;
        const Direction& d = inverseRay.direction;

        double z0 = inverseRay.point(2);
        double dz = inverseRay.direction(2);

        Ray xyRay = inverseRay;
        xyRay.direction(2) = 0;
        xyRay.point(2) = 0;

        double a = xyRay.direction.squaredNorm();
        double b = 2 * xyRay.direction.dot(xyRay.point);
        double c = xyRay.point.squaredNorm() - 1;

        double b2_4ac = b * b - 4 * a * c;
        

        hit.material = material;

        t = (1 - z0)/dz;
        hit.point = p + t * d;

       
        if (t > 0 && (Point(p + t * d) - Point(0, 0, 1)).norm() < 1) {
            hit.point = transform.apply(hit.point);
            hit.normal = transform.apply(Normal(0, 0, 1));
            if (hit.normal.dot(ray.direction) > 0) {
                hit.normal = -hit.normal;
            }
            hit.distance = (hit.point - ray.point).norm() * sign(t);
            result.push_back(hit);
        }
        

        t = (-1 - z0)/dz;
        hit.point = p + t * d;
       
        if (t > 0 && (Point(p + t * d) - Point(0, 0, -1)).norm() < 1) {
            hit.point = transform.apply(hit.point);
            hit.normal = transform.apply(Normal(0, 0, -1));
            if (hit.normal.dot(ray.direction) > 0) {
                hit.normal = -hit.normal;
            }
            hit.distance = (hit.point - ray.point).norm() * sign(t);
            result.push_back(hit); 
        }

        

        Point point;

        
        switch(sign(b2_4ac)) {
            case -1:
                // No intersection
                break;

            case 0:
               
                
                t = -b/(2 * a);
                point = Point(p + t * d);
                
                
                if (t > 0 && point(2) < 1 && point(2) > -1) {
                    hit.point = transform.apply(point);

                    Normal normal = Normal(point - Point(0, 0, point(2)));
                    normal /= normal.norm();
                    
                    hit.normal = transform.apply(normal);
                    
                    if (hit.normal.dot(ray.direction) > 0) {
                        hit.normal = -hit.normal;
                    }
                    
                    hit.distance = (hit.point - ray.point).norm() * sign(t);
                    result.push_back(hit);
                }

                break;
                
            case 1:

                t = (-b + sqrt(b2_4ac))/(2 * a);
                point = Point(p + t * d);
                if (t > 0 && point(2) < 1 && point(2) > -1) {
                    hit.point = transform.apply(point);
                    
                    Normal normal = Normal(point - Point(0, 0, point(2)));
                    normal /= normal.norm();
                    
                    hit.normal = transform.apply(normal);
                    
                    if (hit.normal.dot(ray.direction) > 0) {
                        hit.normal = -hit.normal;
                    }
                    hit.distance = (hit.point - ray.point).norm() * sign(t);
                    result.push_back(hit);
                }
                point = Point(p + t * d);

                t = (-b + sqrt(b2_4ac))/(2 * a);
                if (t > 0 && point(2) < 1 && point(2) > -1) {
                    hit.point = transform.apply(point);
                    
                    Normal normal = Normal(point - Point(0, 0, point(2)));
                    normal /= normal.norm();
                    
                    hit.normal = transform.apply(normal);
                    if (hit.normal.dot(ray.direction) > 0) {
                        hit.normal = -hit.normal;
                    }
                    hit.distance = (hit.point - ray.point).norm() * sign(t);
                    result.push_back(hit);
                }

                break;

            default:
		// Shouldn't be possible, but just in case
		std::cerr << "Something's wrong - sign(x) should be -1, +1 or 0" << std::endl;
		exit(-1);
		break;
                
                
        } 
        
	return result;
}
