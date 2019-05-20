#pragma once

#ifndef PARABALOID_H_INCLUDED
#define PARABALOID_H_INCLUDED

#include "Object.h"

/**
 * \file
 * \brief Cube class header file.
 */


 /**
  * \brief Class for Cube objects.
  *
  * This class provides an Object which is a Cube at the origin with "radius" 1.
  * That is, a Cube that extends from \f$-1\f$ to \f$+1\f$ along each axis.
  *
  */
class Parabaloid : public Object {

public:

	/** \brief Parabaloid default constructor.
	 *
	 * A newly constructed Parabaloid extending from \f$0\f$ to \f$+1\f$ along the \f$Z\f$ axis.
	 * It may be moved, rotated, and scaled through its transform member.
	 *
	 * \image html parabaloid.png
	 */
	Parabaloid();

	/** \brief Parabaloid copy constructor.
	 *  \param parabaloid The Parabaloid to copy.
	 */
	Parabaloid(const Parabaloid& parabaloid);

	/** \brief Parabaloid destructor. */
	~Parabaloid();

	/** \brief Parabaloid assignment operator.
	 *
	 * \param parabaloid The Parabaloid to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const Parabaloid& operator=(const Parabaloid& parabaloid);

	/** \brief Parabaloid-Ray intersection computation.
	 *
	 * \todo The Parabaloid-Ray intersection needs to be implemented as part of the assignment.
	 *
	 * Intersection with a Parabaloid is similar to that of a Sphere, but instead of
	 * \f[ x^2 + y^2 + z^2 = 1 \f]
	 * The formula for the surface is 
	 * \f[ x^2 + y^2 - z = 0 \f]
	 * As with the sphere this leads to a quadratic equation and zero, one, or two intersections.
	 *
	 * \param ray The Ray to intersect with this Parabaloid.
	 * \return A list (std::vector) of intersections, which may be empty.
	 */
	std::vector<RayIntersection> intersect(const Ray& ray) const;

};

#endif // PARABALOID_H_INCLUDED
