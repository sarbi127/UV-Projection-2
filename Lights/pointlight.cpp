#include "pointlight.hpp"

// Default constructor.
qbRT::PointLight::PointLight()
{
	m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_intensity = 1.0;
}

// Destructor.
qbRT::PointLight::~PointLight()
{

}

// Function to compute illumination.
bool qbRT::PointLight::ComputeIllumination(	const qbVector<double> &intPoint, const qbVector<double> &localNormal,
											const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
											const std::shared_ptr<qbRT::ObjectBase> &currentObject,
											qbVector<double> &color, double &intensity)
{
	// Construct a vector pointing from the intersection point to the light.
	qbVector<double> lightDir = (m_location - intPoint).Normalized();
	double lightDist = (m_location - intPoint).norm();
	
	// Compute a starting point.
	qbVector<double> startPoint = intPoint;
	
	// Construct a ray from the point of intersection to the light.
	qbRT::Ray lightRay (startPoint, startPoint + lightDir);
	
	/* Check for intersections with all of the objects
		in the scene, except for the current one. */
	qbVector<double> poi		{3};
	qbVector<double> poiNormal	{3};
	qbVector<double> poiColor	{3};
	bool validInt = false;
	for (auto sceneObject : objectList)
	{
		if (sceneObject != currentObject)
		{
			validInt = sceneObject -> TestIntersection(lightRay, poi, poiNormal, poiColor);
			//if intersation in behind dont cast the shadow
			if (validInt)
			{
				double dist = (poi - startPoint).norm();
				if (dist > lightDist)
					validInt = false;
			}
		}
		
		/* If we have an intersection, then there is no point checking further
			so we can break out of the loop. In other words, this object is
			blocking light from this light source. */
		if (validInt)
			break;
	}

	/* Only continue to compute illumination if the light ray didn't
		intersect with any objects in the scene. Ie. no objects are
		casting a shadow from this light source. */
	if (!validInt)
	{
		// Compute the angle between the local normal and the light ray.
		// Note that we assume that localNormal is a unit vector.
		double angle = acos(qbVector<double>::dot(localNormal, lightDir)); // dot between light source and normal vector
		
		// If the normal is pointing away from the light(pi/2), then we have no illumination.
		if (angle > 1.5708)
		{
			// No illumination.
			color = m_color;
			intensity = 0.0;
			return false;
		}
		else
		{
			// We do have illumination.
			color = m_color;
			intensity = m_intensity * (1.0 - (angle / 1.5708));
			return true;
		}
	}
	else
	{
		// Shadow, so no illumination.
		color = m_color;
		intensity = 0.0;
		return false;
	}	
	
}

