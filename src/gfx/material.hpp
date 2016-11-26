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

			Shader* GetShader() const { return shader; }

			void SetShader(Shader* new_shader) { shader = new_shader; }

		private:
			Shader* shader;

		};

	}
}