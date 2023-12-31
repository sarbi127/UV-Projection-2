#include "objectbase.hpp"
#include <math.h>

//#define EPSILON 1e-21f;

#define EPSILON 1e-6f;

// Default constructor.
qbRT::ObjectBase::ObjectBase()
{

}

// The destructor.
qbRT::ObjectBase::~ObjectBase()
{

}

// Function to test for intersections.
//bool qbRT::ObjectBase::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
bool qbRT::ObjectBase::TestIntersection(const Ray &castRay, qbRT::DATA::hitData &hitData)
{
	return false;
}

void qbRT::ObjectBase::SetTransformMatrix(const qbRT::GTform &transformMatrix)
{
	m_transformMatrix = transformMatrix;
}

qbRT::GTform qbRT::ObjectBase::GetTransformMatrix()
{
	return m_transformMatrix;
}

// Function to assign a material.
bool qbRT::ObjectBase::AssignMaterial(const std::shared_ptr<qbRT::MaterialBase> &objectMaterial)
{
	m_pMaterial = objectMaterial;
	m_hasMaterial = true;
	return m_hasMaterial;
}

// Function to test whether two floating-point numbers are close to being equal.
bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2)
{
	return fabs(f1-f2) < EPSILON;
}

// Function to perform UV mapping.
void qbRT::ObjectBase::ComputeUV(const qbVector<double> &localPOI, qbVector<double> &uvCoords)
{
	switch (m_uvMapType)
	{
		case qbRT::uvSPHERE:
			{
				// Spherical projection.
				double x = localPOI.GetElement(0);
				double y = localPOI.GetElement(1);
				double z = localPOI.GetElement(2);
				double u = atan2(y, x) / M_PI;
				double v = 2.0 * (atan2(sqrtf(pow(x, 2.0) + pow(y, 2.0)), z) / M_PI) - 1.0;				
				uvCoords.SetElement(0, u);
				uvCoords.SetElement(1, v);
				break;
			}
		case qbRT::uvPLANE:
			{
				// Plane projection.
				uvCoords.SetElement(0, localPOI.GetElement(0));
				uvCoords.SetElement(1, localPOI.GetElement(1));
				break;
			}
		case qbRT::uvCYLINDER:
			{
				// Cylinder projection.
				double x = localPOI.GetElement(0);
				double y = localPOI.GetElement(1);
				double z = localPOI.GetElement(2);				
				double u = atan2(y, x) / M_PI;
				double v = -z;
				uvCoords.SetElement(0, u);
				uvCoords.SetElement(1, v);
				break;
			}
		case qbRT::uvBOX:
			{
				// Box projection.
				double x = localPOI.GetElement(0);
				double y = localPOI.GetElement(1);
				double z = localPOI.GetElement(2);
				double u = 0.0;
				double v = 0.0;
				
				// Define default UV transform matrix.
				qbMatrix2<double> uvTransform {3,3};
				uvTransform.SetToIdentity();
				
				if (CloseEnough(x, -1.0))
				{
					// Left face.
					u = -(y * 0.25) - 0.75;
					v = -z * 0.25;
					
				}
				else if (CloseEnough(x, 1.0))
				{
					// Right face.
					u = (y * 0.25) + 0.25;
					v = -z * 0.25;
					
				}
				else if (CloseEnough(y, -1.0))
				{
					// Front face.
					u = (x * 0.25) - 0.25;
					v = (-z * 0.25) - 0.5;
					
				}
				else if (CloseEnough(y, 1.0))
				{
					// Back face.
					u = -(x * 0.25) - 0.25;;
					v = (-z * 0.25) + 0.5;
					
				}
				else if (CloseEnough(z, -1.0))
				{
					// Top face.
					u = (x * 0.25) + 0.75;
					v = y * 0.25;
					
				}
				else if (CloseEnough(z, 1.0))
				{
					// Bottom face.
					u = (x * 0.25) - 0.25;
					v = y * 0.25;
					
				}
				else
				{
					// The object isn't a box...
					
				}
				
				uvCoords.SetElement(0, u);
				uvCoords.SetElement(1, v);
				
				break;
			}
	}
	
	// Apply the transform to the UV coordinates.
	// *** TO BE IMPLEMENTED ***
	//uvCoords = ApplyUVTransform(uvCoords);
	
}
