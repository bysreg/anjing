#pragma once

namespace anjing
{
	namespace gfx
	{

		//forward declarations
		class Shader;

		class Material
		{
			
		public:

			///
			/// Default constructor for Material
			///
			Material();

			inline Shader* GetShader() const
			{
				return shader;
			}

			inline void SetShader(Shader* shader)
			{
				this->shader = shader;
			}

		private:
			Shader* shader;

		};

	}
}