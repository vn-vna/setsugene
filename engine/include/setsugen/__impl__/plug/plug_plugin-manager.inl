#pragma once

namespace setsugen
{

template<typename Ctx, typename Plugin>
PluginManager<Ctx, Plugin>::PluginManager(const PluginManagerConfiguration& configuration,
                                          ContextType*                      context) noexcept
    : m_configuration{configuration}, m_context{context}
{}

template<typename Ctx, typename Plugin>
PluginManager<Ctx, Plugin>::~PluginManager() noexcept = default;

template<typename Ctx, typename Plugin>
auto
PluginManager<Ctx, Plugin>::get_context() const -> ContextType*
{
  return m_context;
}

} // namespace setsugen
