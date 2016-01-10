#pragma once

#include "core/singleton.hpp"

#include <list>

namespace anjing
{
	namespace core
	{

		//forward declarations
		class GameObject;

		class Scene
		{

			ANJING_SINGLETON(Scene)

			friend class GameObject;

		public:

			///
			/// \brief Render all GameObjects in a scene
			///
			void Render();

		private:

			std::list<GameObject*> game_objects;

			///
			/// \brief Adds a GameObject to the scene
			///
			void AddGameObject(GameObject* go);

			///
			/// \brief Removes a GameObject from the scene
			///
			void RemoveGameObject(GameObject* go);
		};
	}
}