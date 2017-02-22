#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_CAMERA_FOV_Y XM_PIDIV4
#define MAGE_DEFAULT_CAMERA_NEAR_Z 0.01f
#define MAGE_DEFAULT_CAMERA_FAR_Z 100.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of camera.
	 */
	class Camera {

	public:

		/**
		 Destructs this camera.
		 */
		virtual ~Camera() = default;

		/**
		 Copies the given camera to this camera.

		 @param[in]		camera
						The camera.
		 */
		Camera &operator=(const Camera &camera) {
			m_width     = camera.m_width;
			m_height    = camera.m_height;
			m_near_z    = camera.m_near_z;
			m_far_z     = camera.m_far_z;
			m_transform = SharedPtr< Transform >(new Transform(*camera.m_transform));
			return (*this);
		}

		/**
		 Clones this camera.

		 @return		A pointer to the clone of this camera.
		 */
		virtual Camera *Clone() const = 0;

		/**
		 Returns the width of this camera.

		 @return		The width of this camera.
		 */
		float GetWidth() const {
			return m_width;
		}
		
		/**
		 Sets the width of this camera to the given value.

		 @param[in]		width
						The width.
		 @return		A reference to this camera.
		 */
		Camera &SetWidth(float width) {
			m_width = width;
			return (*this);
		}
		
		/**
		 Returns the height of this camera.

		 @return		The height of this camera.
		 */
		float GetHeight() const {
			return m_height;
		}
		
		/**
		 Sets the height of this camera to the given value.

		 @param[in]		height
						The height.
		 @return		A reference to this camera.
		 */
		Camera &SetHeight(float height) {
			m_height = height;
			return (*this);
		}
		
		/**
		 Sets the width and height of this camera to the given values.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @return		A reference to this camera.
		 */
		Camera &SetWidthAndHeight(float width, float height) {
			m_width = width;
			m_height = height;
			return (*this);
		}

		/**
		 Returns the position of the near z-plane of this camera.

		 @return		The position of the near z-plane of this camera.
		 */
		float GetNearZ() const {
			return m_near_z;
		}
		
		/**
		 Sets the position of the near z-plane of this camera to the given value.

		 @param[in]		near_z
						The position of the near z-plane.
		 @return		A reference to this camera.
		 */
		Camera &SetNearZ(float near_z) {
			m_near_z = near_z;
			return (*this);
		}
		
		/**
		 Returns the position of the far z-plane of this camera.

		 @return		The position of the far z-plane of this camera.
		 */
		float GetFarZ() const {
			return m_far_z;
		}
		
		/**
		 Sets the position of the far z-plane of this camera to the given value.

		 @param[in]		far_z
						The position of the far z-plane.
		 @return		A reference to this camera.
		 */
		Camera &SetFarZ(float far_z) {
			m_far_z = far_z;
			return (*this);
		}
		
		/**
		 Sets the position of the near and far z-plane of this camera to the given values.

		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		 @return		A reference to this camera.
		 */
		Camera &SetNearAndFarZ(float near_z, float far_z) {
			m_near_z = near_z;
			m_far_z = far_z;
			return (*this);
		}

		/**
		 Returns the view-to-projection matrix of this camera.

		 @return		The view-to-projection matrix of this camera.
		 */
		virtual XMMATRIX GetViewToProjectionMatrix() const = 0;
			
		/**
		 Returns the transform of this camera.

		 @return		A reference to the transform of this camera.
		 */
		Transform &GetTransform() const {
			return *m_transform;
		}

	protected:

		/**
		 Constructs a camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		 */
		Camera(float width, float height, float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z)
			: m_width(width), m_height(height), 
			m_near_z(near_z), m_far_z(far_z), 
			m_transform(new Transform()) {}

		/**
		 Constructs a camera from the given camera.

		 @param[in]		camera
						The camera.
		 */
		Camera(const Camera &camera) 
			: m_width(camera.m_width), m_height(camera.m_height), 
			m_near_z(camera.m_near_z), m_far_z(camera.m_far_z), 
			m_transform(new Transform(*camera.m_transform)) {}

	private:

		/**
		 The width of this camera.
		 */
		float m_width;

		/**
		 The height of this camera.
		 */
		float m_height;

		/**
		 The position of the near z-plane. 
		 */
		float m_near_z;

		/**
		 The position of the far z-plane.
		 */
		float m_far_z;

		/**
		 The transform of this camera.
		 */
		SharedPtr< Transform > m_transform;
	};
}