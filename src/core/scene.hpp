#pragma once

#include "core/singleton.hpp"

#include <list>

// forward declarations
namespace anjing
{
	namespace core
	{
		class GameObject;
	}

	namespace gfx
	{
		class Camera;
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

		public:

			///
			/// \brief Render all GameObjects in a scene
			///
			void Render();

		private:

			std::list<anjing::core::GameObject*> game_objects;
			anjing::gfx::Camera* camera;

			uint32 width;
			uint32 height;

			///
			/// Set the screen size
			///
			inline void SetScreenSize(uint32 width, uint32 height) { this->width = width; this->height = height; }

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
			inline void SetCamera(anjing::gfx::Camera* camera) { this->camera = camera; }
		};
	}
}