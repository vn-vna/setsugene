#include <setsugen/entity.h>
#include <setsugen/mesh.h>
#include <setsugen/scene.h>

namespace setsugen
{

Mesh::Mesh(Entity* entity, const std::string& file_path) : Component{entity}
{
  m_entity->get_scene()->add_meshdata(file_path);
  m_data = entity->get_scene()->get_meshdata(file_path);
}

Mesh::~Mesh() = default;

const char*
Mesh::get_type()
{
  return "Mesh";
}

MeshData*
Mesh::get_meshdata() const
{
  return m_data;
}

} // namespace setsugen
