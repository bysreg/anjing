#include "shader.hpp"
#include "core/log.hpp"
#include "app/app.hpp"

#include <cstdio>

anjing::gfx::Shader * anjing::gfx::Shader::LoadShaderProgram(const std::string & vs_filepath, const std::string & fs_filepath)
{
	GLuint compiled_vs_id, compiled_fs_id, program;
	GLint link_status;

	if (CompileShader(compiled_vs_id, vs_filepath, ShaderType::Vertex) != 0)
		return nullptr;
	if (CompileShader(compiled_fs_id, fs_filepath, ShaderType::Fragment) != 0)
		return nullptr;
	
	program = glCreateProgram();
	glAttachShader(program, compiled_vs_id);
	glAttachShader(program, compiled_fs_id);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);

	if (link_status == GL_FALSE)
	{
		GLint info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

		if (info_log_length > 1)
		{
			char* info_log = Anew char[sizeof(char) * info_log_length];

			glGetProgramInfoLog(program, info_log_length, NULL, info_log);
			ANJING_LOGF_E("Error linking program : %s\n", info_log);			

			AdeleteArr(info_log);
		}

		return nullptr;
	}

	Shader* shader = Anew Shader;
	shader->vs_filepath = vs_filepath;
	shader->fs_filepath = fs_filepath;
	shader->program = program;
	shader->vertex_shader = compiled_vs_id;
	shader->fragment_shader = compiled_fs_id;

	//load all the attributes
	shader->local_pos_att = glGetAttribLocation(program, "a_posL");
	shader->color_att = glGetAttribLocation(program, "a_color");
	shader->uv_att = glGetAttribLocation(program, "a_uv");
	shader->local_normal_att = glGetAttribLocation(program, "a_normalL");

	return shader;
}

int anjing::gfx::Shader::CompileShader(GLuint& out_shader, const std::string& filepath, ShaderType shader_type)
{
	GLint compile_result;
	GLint glshader_type = 0;

	switch (shader_type)
	{
	case ShaderType::Vertex:
		glshader_type = GL_VERTEX_SHADER;
		break;
	case ShaderType::Fragment:
		glshader_type = GL_FRAGMENT_SHADER;
		break;
	}

	GLuint shader = glCreateShader(glshader_type);

	char* source = ReadSource(filepath);

	if (source == nullptr)
	{
		ANJING_LOGF_E("Cannot open the shader file : %s\n", filepath.c_str());
		return 2;
	}

	GLchar* const shader_source = static_cast<GLchar*>(source);
	glShaderSource(shader, 1, &shader_source, NULL);
	AdeleteArr(source);

	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	if (!compile_result)
	{
		GLint info_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);

		if (info_length > 1)
		{
			char* info_log = Anew char[info_length];
			glGetShaderInfoLog(shader, info_length, NULL, info_log);
			ANJING_LOGF_E("Error compiling shader %s : %s\n", filepath.c_str(), info_log);

			AdeleteArr(info_log);
		}

		return 1;
	}

	out_shader = shader;
	return 0;
}

char* anjing::gfx::Shader::ReadSource(const std::string & filepath)
{
	std::FILE* pf = anjing::app::App::GetAssets(filepath, "rb");
	
	if (pf == nullptr)
		return nullptr;
		
	std::fseek(pf, 0, SEEK_END);
	long size = std::ftell(pf);
	std::fseek(pf, 0, SEEK_SET);

	char* shader_source = Anew char[size + 1];
	std::fread(shader_source, sizeof(char), size, pf);
	shader_source[size] = '\0';
	std::fclose(pf);

	return shader_source;
}
