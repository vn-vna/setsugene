#pragma once

#include <setsugen/pch.h>

#include <setsugen/context.h>
#include <setsugen/refl.h>
#include <setsugen/version.h>

namespace setsugen
{

class ApplicationContext;

enum class PluginType : uint64_t
{
  None        = 0,
  Application = 1 << 0,
  Renderer    = 1 << 1,
  Shader      = 1 << 2,
  Input       = 1 << 3,
  Audio       = 1 << 4,
  Physics     = 1 << 5,
  Scripting   = 1 << 6,
  Networking  = 1 << 7,
  Asset       = 1 << 8,
};

struct PluginConfiguration
{
  std::string name;
  std::string identity;
  std::string entry_point;
};


class PluginManager
{
public:
  PluginManager();
  ~PluginManager();
};

class Plugin
{
public:
  using PluginTypeFlags = uint64_t;
  using PluginPriority  = uint64_t;

  virtual ~Plugin();

  PluginTypeFlags type() const;
  PluginPriority  priority() const;

protected:
  Plugin(PluginTypeFlags type, PluginPriority priority);

  PluginPriority  m_priority;
  PluginTypeFlags m_type;
};

} // namespace setsugen
