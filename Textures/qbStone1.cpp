#include "qbStone1.hpp"
#include <algorithm>

// Constructor / destructor.
qbRT::Texture::qbStone1::qbStone1()
{
	// Initial configuration.
	m_amplitude1 = 1.0;
	m_amplitude2 = 1.0;
	m_scale1 = 32;
	m_scale2 = 64;
	m_minValue = -2.0;
	m_maxValue = 2.0;

	// Configure the noise generators.
	m_noiseGenerator1.SetupGrid(m_scale1);
	m_noiseGenerator2.SetupGrid(m_scale2);
	
	// Configure the color map.
	auto stoneMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	stoneMap -> SetStop(0.0, qbVector<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}});
	stoneMap -> SetStop(0.25, qbVector<double>{std::vector<double>{0.8, 0.8, 0.8, 1.0}});
	stoneMap -> SetStop(0.5, qbVector<double>{std::vector<double>{0.5, 0.5, 0.5, 1.0}});
	stoneMap -> SetStop(0.75, qbVector<double>{std::vector<double>{0.1, 0.1, 0.1, 1.0}});
	stoneMap -> SetStop(1.0, qbVector<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}});
	SetColorMap(stoneMap);	
	
}

qbRT::Texture::qbStone1::~qbStone1()
{

}

// Function to return the color.
qbVector<double> qbRT::Texture::qbStone1::GetColor(const qbVector<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector<double> inputLoc = uvCoords;
	qbVector<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);
	
	qbVector<double> localColor {4};
	/* If no color map has been provided, then output purple. This should be
		easily recognizable in the scene, indicating that something is wrong. */
	if (!m_haveColorMap)
	{
		localColor = qbVector<double>{std::vector<double>{1.0, 0.0, 1.0, 1.0}};
	}
	else
	{
		// Generate the base function.
		double mapPosition = 	m_noiseGenerator1.GetValue(newU, newV) * m_amplitude1 + 
													m_noiseGenerator2.GetValue(newU, newV) * m_amplitude2;
													
		mapPosition = std::clamp((mapPosition - m_minValue) / (m_maxValue - m_minValue), 0.0, 1.0);
		localColor = m_colorMap -> GetColor(mapPosition);
	}
	
	return localColor;
}

// Function to return the value.
double qbRT::Texture::qbStone1::GetValue(const qbVector<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector<double> inputLoc = uvCoords;
	qbVector<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);
	
	double mapPosition = 	m_noiseGenerator1.GetValue(newU, newV) * m_amplitude1 + 
												m_noiseGenerator2.GetValue(newU, newV) * m_amplitude2;
										
	mapPosition = std::clamp((mapPosition - m_minValue) / (m_maxValue - m_minValue), 0.0, 1.0);
	return mapPosition;
}

// Function to set the color map.
void qbRT::Texture::qbStone1::SetColorMap(const std::shared_ptr<qbRT::Texture::ColorMap> &colorMap)
{
	m_colorMap = colorMap;
	m_haveColorMap = true;
}

// Function to set the ammplitude.
void qbRT::Texture::qbStone1::SetAmplitude(double amplitude)
{
	m_amplitude1 = amplitude;
}

// Function to set the scale.
void qbRT::Texture::qbStone1::SetScale(int scale)
{
	m_scale1 = scale;
	m_noiseGenerator1.SetupGrid(m_scale1);
}
