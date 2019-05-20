#include "Scene.h"

#include "Colour.h"
#include "ImageDisplay.h"
#include "utility.h"

Scene::Scene() : backgroundColour(0,0,0), ambientLight(0,0,0), maxRayDepth(3), renderWidth(800), renderHeight(600), filename("render.png"), camera_(), objects_(), lights_() {

}

Scene::~Scene() {

}

void Scene::render() const {
	ImageDisplay display("Render", renderWidth, renderHeight);
	



	const double w = double(renderWidth);
	const double h = double(renderHeight);

	for (unsigned int v = 0; v < renderHeight; ++v) {
		for (unsigned int u = 0; u < renderWidth; ++u) {
			double cu = -1 + (u + 0.5)*(2.0 / w);
			double cv = -h/w + (v + 0.5)*(2.0 / w);
			Ray ray = camera_->castRay(cu, cv);
			display.set(u, v, computeColour(ray, maxRayDepth));
		}
		display.refresh();
	}

	display.save(filename);
	display.pause(5);
}

RayIntersection Scene::intersect(const Ray& ray) const {
    RayIntersection firstHit;
    firstHit.distance = infinity;	
    for (const auto & obj : objects_) {
        for (const auto & hit : obj->intersect(ray)) {
            if (hit.distance > epsilon && hit.distance < firstHit.distance) {
                firstHit = hit;
            }
        }
    }	return firstHit;
}

Colour Scene::computeColour(const Ray& ray, unsigned int rayDepth) const {
    RayIntersection hitPoint = intersect(ray);
    if (hitPoint.distance == infinity) {
        return backgroundColour;
    }

    Colour hitColour =  ambientLight * hitPoint.material.ambientColour;
		
 
    for (const auto & light: lights_) {

        if (light->getDistanceToLight(hitPoint.point) < 0) {
   
            hitColour += light->getIlluminationAt(hitPoint.point) * hitPoint.material.ambientColour;
        } else {
            Vector angle = -light->getLightDirection(hitPoint.point);
            Vector normal = hitPoint.normal;
            Vector r = 2 * normal.dot(angle) * (normal - angle);
            Vector direction = -ray.direction;

            Colour c = light->getIlluminationAt(hitPoint.point);
            Colour diffuse = hitPoint.material.diffuseColour;
            Colour specular = hitPoint.material.specularColour;
            
            normal = normal/normal.norm();
            direction = direction/direction.norm();
            angle = angle/angle.norm();
            r = r/r.norm();
            
            double s = std::max<double>(0, r.dot(direction));
            double ld = std::max<double>(0, normal.dot(angle));
            double specE = hitPoint.material.specularExponent;

            Ray shadow;
            shadow.direction = angle;
            shadow.point = hitPoint.point;
            RayIntersection shadowIntersect = intersect(shadow);
            if (shadowIntersect.distance > light->getDistanceToLight(hitPoint.point)) {
            
                hitColour += c * (diffuse * ld + specular*pow(s, specE));
            }
        }
    }

    if (rayDepth > 0) {
    
        Vector normal = hitPoint.normal;
        Vector direction = -ray.direction;

        normal = normal/normal.norm();
        direction = direction/direction.norm();

        Ray reflection;
        reflection.direction = 2 * normal.dot(direction) * normal - direction;

        reflection.point = hitPoint.point;
        hitColour += hitPoint.material.mirrorColour * computeColour(reflection, rayDepth - 1);
    }


    hitColour.clip();
    return hitColour;
}

bool Scene::hasCamera() const {
    return bool(camera_);
}
