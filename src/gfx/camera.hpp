#pragma once

#include "core/component.hpp"
#include "math/tmat4.hpp"

namespace anjing
{
	namespace gfx
	{

		class Camera : public anjing::core::Component
		{

		public:

			///
			/// Default Constructor
			///
			Camera();

			///
			/// \brief This function will render what the camera views to the screen
			///
			void Render();

			///
			/// \brief Set the camera's near clip
			///
			inline void SetNearClip(float value) { near_clip = value; }
			
			///
			/// \brief Set the camera's far clip
			///
			inline void SetFarClip(float value) { far_clip = value; }

			///
			/// \brief Set the camera's aspect ratio
			///
			inline void SetAspectRatio(float value) { aspect_ratio = value; }

			///
			/// \brief Set the camera's fov (field of view)
			///
			void SetFov(float value) { fovy = value; }

			///
			/// \brief Get the camera's direction vector
			///
			anjing::math::Vec3f GetDirection() const;

			///
			/// \brief Get camera's up direction vector
			///
			anjing::math::Vec3f GetUp() const;

			///
			/// \brief Update the camera's projection matrix
			///
			void UpdateProj();

			///
			/// \brief Update the camera's view matrix
			///
			void UpdateView();

			/// \brief Returns the camera's projection matrix
			anjing::math::Mat4f GetProjMat() const { return proj_mat; }

			/// \brief Returns the camera's view matrix
			anjing::math::Mat4f GetViewMat() const { return view_mat; }

		protected:

			virtual void OnAdded() override;
			virtual void OnRemoved() override;

		private:

			float fovy; // in radians
			float aspect_ratio;
			float near_clip;
			float far_clip;

			anjing::math::Mat4f proj_mat;
			anjing::math::Mat4f view_mat;

			///
			/// \brief Called when OnAdded is called
			///
			void Init();

		};

	}
}