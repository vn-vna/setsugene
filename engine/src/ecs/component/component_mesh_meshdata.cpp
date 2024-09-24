
#include <setsugen/application.h>
#include <setsugen/entity.h>
#include <setsugen/mesh.h>
#include <setsugen/scene.h>

namespace setsugen
{
MeshData::
MeshData(const std::string& file_path)
    : m_file_path{file_path}
{}

void
MeshData::load()
{
}

void
MeshData::unload()
{
  m_positions.reset();
  m_normals.reset();
  m_indices.reset();
}

const MeshData::VerticiesArray*
MeshData::get_positions() const
{
  return m_positions.get();
}

const MeshData::NormalsArray*
MeshData::get_normals() const
{
  return m_normals.get();
}

const MeshData::IndicesArray*
MeshData::get_indices() const
{
  return m_indices.get();
}

bool
MeshData::is_loaded() const
{
  return m_positions && m_normals && m_indices;
}
} // namespace setsugen
