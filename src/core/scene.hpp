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

		public:

			///
			/// \brief Render all GameObjects in a scene
			///
			void Render();

		private:

			std::list<GameObject*> game_objects;

			void AddGameObject(GameObject* go);

		};
	}
}