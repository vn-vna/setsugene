#pragma once

#include <setsugen/component.h>
#include <setsugen/math.h>
#include <setsugen/pch.h>

namespace setsugen
{

class MeshData
{
public:
  using IndicesArray   = std::vector<unsigned int>;
  using VerticiesArray = std::vector<Vec3F>;
  using NormalsArray   = std::vector<Vec3F>;

   MeshData(const std::string& file_path);
  ~MeshData() = default;

  void load();
  void unload();

  const VerticiesArray* get_positions() const;
  const NormalsArray*   get_normals() const;
  const IndicesArray*   get_indices() const;

  bool is_loaded() const;

private:
  std::unique_ptr<VerticiesArray> m_positions;
  std::unique_ptr<NormalsArray>   m_normals;
  std::unique_ptr<IndicesArray>   m_indices;
  std::string                     m_file_path;
};

class Mesh : public Component
{
public:
   Mesh(Entity* entity, const std::string& file_path);
  ~Mesh() override;

  MeshData*   get_meshdata() const;
  const char* get_type() override;

private:
  MeshData* m_data;
};
} // namespace setsugen
