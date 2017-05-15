#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename LightT >
	DerivedLightNode< LightT >::DerivedLightNode(const string &name)
		: LightNode(name, std::make_unique< LightT >()) {}

	template< typename LightT >
	DerivedLightNode< LightT >::DerivedLightNode(const string &name, UniquePtr< LightT > &&light)
		: LightNode(name, std::move(light)) {}

	template< typename LightT >
	DerivedLightNode< LightT >::DerivedLightNode(const DerivedLightNode &light_node) = default;

	template< typename LightT >
	DerivedLightNode< LightT >::DerivedLightNode(DerivedLightNode &&light_node) = default;

	template< typename LightT >
	DerivedLightNode< LightT >::~DerivedLightNode() = default;

	template< typename LightT >
	UniquePtr< Node > DerivedLightNode< LightT >::CloneImplementation() const {
		return std::make_unique< DerivedLightNode >(*this);
	}
}