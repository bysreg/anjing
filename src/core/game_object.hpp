#pragma once

#include "gfx/mesh_renderer.hpp"
#include "core/component.hpp"

#include <string>
#include <type_traits>
#include <typeinfo>

// use vector list of components of a gameobject for now, probably should not use stl
#include <vector>

// forward declaration
namespace anjing 
{
	namespace gfx
	{
		class Camera;
	}

	namespace core
	{
		class Scene;
		class Transform;
	}
}

namespace anjing
{
	namespace core
	{
		///
		/// Basic class for all objects in the scenes
		///
		class GameObject
		{
			friend class anjing::core::Scene;
			friend class anjing::core::Transform;
			friend class anjing::gfx::Camera;

		public:			

			///
			/// \brief Creates a new component with type T, with T child of class Component.
			///
			/// T has to be child of class Component
			/// 
			template <typename T>
			Component* AddComponent();

			///
			/// \brief Removes a component
			/// \todo This function should also can be used to remove a \a GameObject from the Scene
			///
			template <typename T>
			static void Destroy(T* t);

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

			inline anjing::core::Transform* GetTransform() { return transform; }

		private:
			
			anjing::gfx::MeshRenderer* mesh_renderer;			
			anjing::core::Transform* transform;
			std::vector<Component*>* components;			

			///
			/// \brief Remove a component from gameobject. Returns true if such component is successfully being removed from the GameObject
			///
			bool RemoveComponent(anjing::core::Component* component);

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

			///
			/// \brief Return MeshRenderer component, nullptr if it doesn't exist in this GameObject
			///
			anjing::gfx::MeshRenderer* GetMeshRenderer() const
			{
				return mesh_renderer;
			}

			///
			/// \brief set transform to \a value. This should only be called by anjing::core::Component
			///
			inline void SetTransform(anjing::core::Transform* value) { transform = value; }
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
			// is it better to store the component in a hash map or something if it exceeds certain size?

			for (size_t i = 0; i < components->size(); i++)
			{
				if (typeid(*(components->at(i))) == typeid(T))
				{
					return dynamic_cast<T*>(components->at(i));
				}
			}

			return nullptr;
		}

		template<typename T>
		inline void GameObject::Destroy(T* t)
		{
			// check if t is derived from anjing::core::Component
			static_assert(std::is_base_of<anjing::core::Component, T>::value, "T must derive from anjing::core::Component");

			anjing::core::Component* component = t;
			component->GetOwner()->RemoveComponent(component);
		}
	}
}