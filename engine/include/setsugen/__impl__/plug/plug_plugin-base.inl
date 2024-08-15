#pragma once

namespace setsugen
{

template<typename Mng>
PluginBase<Mng>::PluginBase(Mng* manager) noexcept : m_manager{manager}
{}

template<typename Mng>
PluginBase<Mng>::~PluginBase() noexcept = default;

template<typename Mng>
void
PluginBase<Mng>::on_load()
{}

template<typename Mng>
void
PluginBase<Mng>::on_enable()
{}

template<typename Mng>
void
PluginBase<Mng>::on_disable()
{}

template<typename Mng>
void
PluginBase<Mng>::on_unload()
{}

} // namespace setsugen
