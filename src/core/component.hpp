#pragma once

namespace anjing
{
	namespace core
	{

		// forward declarations
		class GameObject;

		///
		/// \brief Component is used to modify the appearance or behaviour of a gameobject
		///
		/// Component's constructor is intentionally written as protected. If you want to 
		/// create new component, always create it from anjing::core::GameObject::AddComponent()
		class Component
		{
			friend class anjing::core::GameObject;

		private:
			GameObject* owner;						

		protected:						

			///
			/// \brief Default constructor of Component
			///
			Component() : owner(nullptr) {}

			///
			/// \brief Default destructor of Component
			///
			virtual ~Component() {};

		public:

			///
			/// \brief Return owner of this component;
			///
			inline GameObject* GetOwner() const
			{
				return owner;
			}		
		};

	}
}