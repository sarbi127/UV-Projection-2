#include "cube.hpp"

// Constructor.
qbRT::RM::Cube::Cube()
{
	// Create a function pointer for our object function.
	std::function<double(qbVector<double>*, qbVector<double>*)> f = [=](qbVector<double> *location, qbVector<double> *parms)
	{
  	return this->ObjectFcn(location, parms);
	};
	
	// Assign the object function.
	SetObjectFcn(f);

	// Modify the bounding box.
	m_boundingBox.SetTransformMatrix(qbRT::GTform { qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{1.2, 1.2, 1.2}} } );

}

// Destructor.
qbRT::RM::Cube::~Cube()
{

}

// The private object function.
double qbRT::RM::Cube::ObjectFcn(qbVector<double> *location, qbVector<double> *parms)
{	
	qbVector<double> center = std::vector<double>{0.0, 0.0, 0.0};
	qbVector<double> intParms = std::vector<double>{1.0, 1.0, 1.0};
	return qbRT::RM::SDF::Box(*location, center, intParms);		
}


