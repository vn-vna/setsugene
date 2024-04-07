
#include <setsugen/entity.h>
#include <setsugen/mesh.h>
#include <setsugen/platform.h>
#include <setsugen/scene.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace setsugen
{

MeshData::MeshData(const std::string& file_path) : m_file_path{file_path}
{}

void
MeshData::load()
{
  Assimp::Importer importer;

  auto abs_path = get_assets_path() + m_file_path;
  auto scene    = importer.ReadFile(abs_path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    throw EngineException{"Failed to load mesh data: " + m_file_path};
  }

  // Load vertices and normals
  m_vertices = std::make_unique<VerticiesArray>();
  m_normals  = std::make_unique<NormalsArray>();
  m_indices  = std::make_unique<IndicesArray>();

  unsigned int last_vertex_index = 0;

  for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
  {
    auto mesh = scene->mMeshes[i];
    for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
    {
      const auto& [vx, vy, vz] = mesh->mVertices[j];
      m_vertices->emplace_back(vx, vy, vz);
      const auto& [nx, ny, nz] = mesh->mNormals[j];
      m_normals->emplace_back(nx, ny, nz);
    }

    for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
    {
      auto face = mesh->mFaces[j];
      for (unsigned int k = 0; k < face.mNumIndices; ++k)
      {
        m_indices->emplace_back(face.mIndices[k] + last_vertex_index);
      }
    }

    last_vertex_index += mesh->mNumVertices;
  }
}

void
MeshData::unload()
{
  m_vertices.reset();
  m_normals.reset();
  m_indices.reset();
}

const MeshData::VerticiesArray*
MeshData::get_vertices() const
{
  return m_vertices.get();
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
  return m_vertices && m_normals && m_indices;
}

} // namespace setsugen
