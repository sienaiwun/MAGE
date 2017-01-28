#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of orthographic cameras.
	 */
	class OrthographicCamera : public Camera {

		/**
		 Constructs an orthographic camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		 */
		OrthographicCamera(float width, float height,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z)
			: Camera(width, height, near_z, far_z) {}
		
		/**
		 Constructs an orthographic camera from the given orthographic camera.

		 @param[in]		camera
						A reference to the orthographic camera.
		 */
		OrthographicCamera(const OrthographicCamera &camera)
			: Camera(camera) {}

		/**
		 Destructs this orthographic camera.
		 */
		virtual ~OrthographicCamera() {}
		
		/**
		 Clones this orthographic camera.

		 @return		A pointer to the clone of this orthographic camera.
		 */
		virtual Camera *Clone() const {
			return new OrthographicCamera(*this);
		}

		/**
		 Returns the view-to-projection matrix of this orthographic camera.

		 @return		The view-to-projection matrix of this orthographic camera.
		 */
		virtual XMMATRIX GetViewToProjectionMatrix() const override {
			return XMMatrixOrthographicLH(GetWidth(), GetHeight(), GetNearZ(), GetFarZ());
		}

		/**
		 Sets the view-to-projection matrix of this orthographic camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		*/
		void SetViewToProjectionMatrix(float width, float height,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z) {
			
			SetWidthAndHeight(width, height);
			SetNearAndFarZ(near_z, far_z);
		}

	private:

		/**
		 Copies the given orthographic camera to this orthographic camera.

		 @param[in]		orthographic_camera
						The orthographic camera.
		 */
		OrthographicCamera &operator=(const OrthographicCamera &orthographic_camera) = delete;
	};
}