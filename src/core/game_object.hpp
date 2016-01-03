#pragma once

#include "gfx/mesh_renderer.hpp"
#include "core/component.hpp"

#include <string>
#include <type_traits>
#include <typeinfo>

// use vector list of components of a gameobject for now, probably should not use stl
#include <vector>

namespace anjing
{
	namespace core
	{
		///
		/// Basic class for all objects in the scenes
		///
		class GameObject
		{
		public:			

			///
			/// \brief Creates a new component with type T, with T child of class Component.
			///
			/// T has to be child of class Component
			/// 
			template <typename T>
			Component* AddComponent();

			///
			/// \brief Get component with type T attached to the gameobject
			///
			/// Return null if there is no such component with type T
			///
			template <typename T>
			T* GetComponent();

			///
			/// \brief Default constructor for GameObject
			///
			GameObject();
			
			///
			/// \brief Destructor for GameObject
			///
			virtual ~GameObject();

			///
			/// \brief Update will be called every frame
			///
			/// \todo call this function not-yet-written SceneManager class
			///
			virtual void Update();			

		private:
			
			anjing::gfx::MeshRenderer* mesh_renderer;			
			std::vector<Component*>* components;			

			///
			/// \brief Remove all components of gameobject
			///
			void RemoveAllComponents();

			///
			/// \brief helper function for AddComponent
			///
			/// Various specialized template function AddComponent must call this function
			/// to be able to add component properly to gameobject's internal component list
			///
			void AddComponentToGOList(Component* component);
		};


		template<typename T>
		inline Component* GameObject::AddComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "type is not a component");
			
			Component* component = Anew T;		
			
			AddComponentToGOList(component);
			return component;
		}

		template<>
		inline Component* GameObject::AddComponent<anjing::gfx::MeshRenderer>()
		{
			static_assert(std::is_base_of<Component, anjing::gfx::MeshRenderer>::value, "type is not a component");

			Component* component = Anew anjing::gfx::MeshRenderer;			
			this->mesh_renderer = static_cast<anjing::gfx::MeshRenderer*>(component);

			AddComponentToGOList(component);
			return component;
		}

		template<typename T>
		inline T* GameObject::GetComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "type is not a component");

			// TODO : is it better to do reflection here ?

			for (size_t i = 0; i < components->size(); i++)
			{
				if (typeid(*(components->at(i))) == typeid(T))
				{
					return dynamic_cast<T*>(components->at(i));
				}
			}

			return nullptr;
		}
	}
}