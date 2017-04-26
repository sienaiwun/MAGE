#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	__declspec(align(16)) struct TransformBuffer final : public AlignedData< TransformBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit TransformBuffer(const XMMATRIX &world_to_view, 
			const XMMATRIX &view_to_projection);
		TransformBuffer(const TransformBuffer &buffer) = default;
		TransformBuffer(TransformBuffer &&buffer) = default;
		~TransformBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		TransformBuffer &operator=(const TransformBuffer &buffer) = default;
		TransformBuffer &operator=(TransformBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const XMMATRIX GetWorldToViewMatrix() const {
			return XMMatrixTranspose(m_world_to_view);
		}
		const XMMATRIX GetWorldToViewInverseTransposeMatrix() const {
			return XMMatrixTranspose(m_world_to_view_inverse_transpose);
		}
		const XMMATRIX GetViewToProjectionMatrix() const {
			return XMMatrixTranspose(m_view_to_projection);
		}
		void SetModelToWorld(const XMMATRIX &model_to_world) const {
			m_model_to_world = XMMatrixTranspose(model_to_world);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		mutable XMMATRIX m_model_to_world;
		XMMATRIX m_world_to_view;
		XMMATRIX m_world_to_view_inverse_transpose;
		XMMATRIX m_view_to_projection;
	};

	static_assert(sizeof(TransformBuffer) == 256, "CPU/GPU struct mismatch");
}