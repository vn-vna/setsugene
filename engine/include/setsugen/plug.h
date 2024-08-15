#pragma once

#include <setsugen/pch.h>

#include <setsugen/context.h>
#include <setsugen/version.h>

namespace setsugen
{

template<typename Ctx, typename Plugin>
class PluginManager;

template<typename Mng>
class PluginBase;

class ApplicationPluginManager;
class ApplicationPlugin;

struct PluginManagerConfiguration
{
  std::string plugin_folder      = "plugins";
  std::size_t max_active_plugins = 1024;
};

struct PluginConfiguration
{
  std::string plugin_name;
};

template<typename Ctx, typename Plugin>
class PluginManager
{
public:
  using ContextType = Ctx;
  using PluginType  = Plugin;

  PluginManager(const PluginManagerConfiguration& configuration, ContextType* context) noexcept;

  virtual ~PluginManager() noexcept;

  ContextType* get_context() const;

protected:
  PluginManagerConfiguration m_configuration;
  ContextType*               m_context;
  std::vector<PluginType>    m_plugins;
  PluginType**               m_active_plugin;

  friend PluginType;
};

template<typename Mng>
class PluginBase
{
public:
  using ManagerType = Mng;
  using ContextType = typename Mng::ContextType;

  PluginBase(Mng* manager) noexcept;

  virtual ~PluginBase() noexcept;

  virtual std::string get_name()     = 0;
  virtual int         get_priority() = 0;
  virtual Version     get_version()  = 0;

  virtual void on_load();
  virtual void on_enable();
  virtual void on_disable();
  virtual void on_unload();

protected:
  ManagerType* m_manager;
};


enum class ApplicationPluginAssignment : std::size_t
{
  Unassingnable = 0,
  ApplicationPlugin
};

class ApplicationPluginManager : PluginManager<ApplicationContext, ApplicationPlugin>
{
public:
};


class ApplicationPlugin : PluginBase<ApplicationPluginManager>
{};

} // namespace setsugen

#include "./__impl__/plug/plug_plugin-base.inl"
#include "./__impl__/plug/plug_plugin-manager.inl"
