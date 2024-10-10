#pragma once

#include "format_fwd.inl"

namespace setsugen
{

class ArgDescription
{
public:
  friend class FormatArgsStore;

  using FormatCallback = std::function<Void(StringStream&, const Void*, const FormatPlaceholder&)>;
  using Deleter        = std::function<Void(Void*)>;

  template<typename T>
  ArgDescription(const T& value);

  template<typename T>
  ArgDescription(const FormatIndex& index, const T& value);

  ArgDescription(const ArgDescription& other);

  ArgDescription(ArgDescription&& other) noexcept;

  ~ArgDescription() noexcept;

  constexpr Void operator()(StringStream& ss, const FormatPlaceholder& placeholder) const;

private:
  template<typename T>
  constexpr auto get_callback() const;

  const Void* m_data;
  FormatIndex mutable m_index;
  FormatCallback m_callback;
};

} // namespace setsugen
