//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Light::Light(const RGBSpectrum &intensity)
		: m_intensity(intensity) {}

	Light::Light(RGBSpectrum &&intensity)
		: m_intensity(std::move(intensity)) {}

	Light::Light(const Light &light) = default;
	
	Light::Light(Light &&light) = default;

	Light::~Light() = default;

	Light &Light::operator=(const Light &light) = default;
	
	Light &Light::operator=(Light &&light) = default;
}