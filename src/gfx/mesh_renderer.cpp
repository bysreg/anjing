#include "mesh_renderer.hpp"

using namespace anjing::gfx;

void MeshRenderer::Render()
{
	/// \todo not implemented	
}

void anjing::gfx::MeshRenderer::SetMesh(Mesh const * const mesh)
{
	this->mesh = mesh;
}
