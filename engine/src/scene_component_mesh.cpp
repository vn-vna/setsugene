#include <setsugen/scene.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "setsugen/platform.h"

constexpr auto assimp_load_flag = aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType |
                                  aiProcess_OptimizeMeshes;

namespace setsugen
{
Mesh::Mesh(Observer<Entity> entity, const String& file_path)
  : Component{entity},
    m_path{file_path}
{}
}
