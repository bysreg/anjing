#pragma once

#include "core/singleton.hpp"

#include <list>

// forward declarations
namespace anjing
{
	namespace gfx
	{
		class Camera;
	}

	namespace core
	{
		class GameObject;
	}

	namespace app
	{
		class App;
	}
}

namespace anjing
{
	namespace core
	{
		class Scene
		{

			ANJING_SINGLETON(Scene)

			friend class anjing::core::GameObject;
			friend class anjing::gfx::Camera;
			friend class anjing::app::App;

		public:

			///
			/// \brief Render all GameObjects in a scene
			///
			void Render();

		private:

			std::list<anjing::core::GameObject*> gameobjects;
			anjing::gfx::Camera* camera;

			uint32 width;
			uint32 height;

			///
			/// Set the screen size
			///
			void SetScreenSize(uint32 new_width, uint32 new_height) { width = new_width; height = new_height; }

			///
			/// \brief Adds a GameObject to the scene
			///
			void AddGameObject(anjing::core::GameObject* go);

			///
			/// \brief Removes a GameObject from the scene
			///
			void RemoveGameObject(anjing::core::GameObject* go);

			///
			/// \brief Set the main camera of the scene 
			///
			inline void SetCamera(anjing::gfx::Camera* new_camera) { camera = new_camera; }
		};
	}
}