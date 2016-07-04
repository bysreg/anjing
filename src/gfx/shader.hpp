#pragma once

#include "core/noncopyable.hpp"

#include <string>
#include <GL/glew.h>

// forward declaration
namespace anjing
{
	namespace gfx
	{
		class MeshRenderer;
	}
}

namespace anjing
{
	namespace gfx
	{

		///
		/// \brief Class to contain shader's information
		///
		/// This class cannot be directly constructed. To make an instance of this class, use \a LoadShaderProgram function
		/// This class is also Noncopyable
		///
		class Shader : private anjing::core::Noncopyable
		{			

			friend class anjing::gfx::MeshRenderer;

		public:

			///
			/// \brief Creates Shader object with specified Vertex Shader source and Fragment Shader source file
			///			
			/// Returns nullptr, if either vertex or fragment shader has compile error
			/// Returns nullptr, if there is linker error 			
			static Shader* LoadShaderProgram(const std::string& vs_filepath, const std::string& fs_filepath);			

			///
			/// \brief Set this shader as the active shader for rendering
			///
			inline void SetActive() { glUseProgram(program); }

		private:

			std::string vs_filepath;
			std::string fs_filepath;

			//attribute
			GLint local_pos_att;
			GLint color_att;
			GLint uv_att;
			GLint local_normal_att;

			GLuint program, vertex_shader, fragment_shader;

			enum class ShaderType
			{
				Vertex,
				Fragment
			};

			// ensure class cannot be constructed directly
			Shader() = default;

			///
			/// \brief Returns openGL local position attribute index
			///
			inline GLint GetLocalPositionId() const
			{
				return local_pos_att;
			}
			
			///
			/// \brief Returns color attribute index
			///
			inline GLint GetColorId() const
			{
				return color_att;
			}

			///
			/// \brief Returns Uv attribute index
			///
			inline GLint GetUvId() const
			{
				return uv_att;
			}

			///
			/// \brief Returns OpenGL local normal attribute index
			///
			inline GLint GetLocalNormalId() const
			{
				return local_normal_att;
			}			

			///
			/// \brief Compile shader in \a filepath with type \a shader_type. On success, out_shader contains the OpenGl index for the compiled shader
			///
			/// Returns 0 on success. 
			/// Returns 1 when shader is failed to compile
			/// Returns 2 when shader file cannot be read
			/// Returns 3 when ANJING__OPENGL_VERSION is set to something other than 300 or 330
			///
			static int CompileShader(GLuint& out_shader, const std::string& filepath, ShaderType shader_type);

			///
			/// \brief Returns text from the file in \a filepath
			///
			static char* ReadSource(const std::string& filepath);
		};

	}
}