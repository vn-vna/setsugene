
#include <setsugen/application.h>
#include <setsugen/entity.h>
#include <setsugen/mesh.h>
#include <setsugen/scene.h>

#include <ofbx.h>

namespace setsugen
{
MeshData::
MeshData(const std::string& file_path)
    : m_file_path{file_path}
{}

void
MeshData::load()
{
  auto load_flags = ofbx::LoadFlags::IGNORE_BLEND_SHAPES | ofbx::LoadFlags::IGNORE_CAMERAS |
                    ofbx::LoadFlags::IGNORE_LIGHTS | ofbx::LoadFlags::IGNORE_SKIN | ofbx::LoadFlags::IGNORE_BONES |
                    ofbx::LoadFlags::IGNORE_PIVOTS | ofbx::LoadFlags::IGNORE_POSES | ofbx::LoadFlags::IGNORE_VIDEOS |
                    ofbx::LoadFlags::IGNORE_LIMBS | ofbx::LoadFlags::IGNORE_ANIMATIONS;

  auto abs_path = Application::get_assets_path() + m_file_path;
  auto ifs      = std::ifstream(abs_path.c_str(), std::ios::binary | std::ios::ate);
  if (!ifs.is_open())
  {
    throw FileNotFoundException(abs_path);
  }

  ifs.seekg(0, std::ios::beg);
  const std::vector<uint8_t> data(std::istreambuf_iterator<char>(ifs), {});

  // Load the file
  auto* scene = ofbx::load(data.data(), data.size(), static_cast<ofbx::u16>(load_flags));

  // Load vertices and normals
  m_positions = std::make_unique<VerticiesArray>();
  m_normals   = std::make_unique<NormalsArray>();
  m_indices   = std::make_unique<IndicesArray>();

  int indices_offset = 0;

  for (int mesh_index = 0; mesh_index < scene->getMeshCount(); ++mesh_index)
  {
    auto* mesh    = scene->getMesh(mesh_index);
    auto& geodata = mesh->getGeometryData();
    auto  pos     = geodata.getPositions();
    auto  norm    = geodata.getNormals();

    // TODO: NEED TO TRIANGULATE MESHES
    for (int i = 0; i < pos.count; ++i)
    {
      auto [px, py, pz] = pos.get(i);
      m_positions->emplace_back(px, py, pz);

      auto [nx, ny, nz] = norm.get(i);
      m_normals->emplace_back(nx, ny, nz);

      m_indices->push_back(indices_offset++);
    }
  }

  scene->destroy();
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
