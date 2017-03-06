#pragma once

namespace mage {

	//-------------------------------------------------------------------------
	// ResourceFactory
	//-------------------------------------------------------------------------

	template < typename VertexT >
	SharedPtr< ModelDescriptor > ResourceFactory::CreateModelDescriptor(const wstring &fname, const RenderingDevice &device, const MeshDescriptor< VertexT > &desc) {
		SharedPtr< ModelDescriptor > resource = m_model_descriptor_resource_manager->GetResource(fname);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< ModelDescriptor >(new ModelDescriptor(device, fname, desc));
			// Store the new resource.
			m_model_descriptor_resource_manager->AddResource(resource);
		}
		return resource;
	}

	//-------------------------------------------------------------------------
	// Resource Creation
	//-------------------------------------------------------------------------

	template < typename VertexT >
	inline SharedPtr< ModelDescriptor > CreateModelDescriptor(const wstring &fname, const MeshDescriptor< VertexT > &desc) {
		const RenderingDevice device = GetRenderingDevice();
		ResourceFactory &factory = GetResourceFactory();
		return factory.CreateModelDescriptor(fname, device, desc);
	}
}