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
				return m_Shader;
			}

			inline void SetShader(Shader* shader)
			{
				m_Shader = shader;
			}

		private:
			Shader* m_Shader;

		};

	}
}