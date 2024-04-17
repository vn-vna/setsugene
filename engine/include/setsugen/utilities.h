#include <atomic>
#include <memory>
#include <setsugen/pch.h>
#include <type_traits>

namespace setsugen
{

template<typename... Ts>
struct TupleHash : std::function<size_t(const std::tuple<Ts...>&)>
{
  size_t operator()(const std::tuple<Ts...>& t) const
  {
    return hash_combine<0>(t);
  }

  template<size_t I, typename... Tys>
  size_t hash_combine(const std::tuple<Tys...>& t) const
  {
    if constexpr (I >= sizeof...(Tys))
    {
      return 0;
    }
    else
    {
      auto next = hash_combine<I + 1>(t);
      return std::hash<std::tuple_element_t<I, std::tuple<Ts...>>>()(std::get<I>(t)) ^ next ^ (next << 6) ^ (next >> 2);
    }
  }
};

/**
 * @brief A simple class to trace the value of a variable, This class is useful to avoid unnecessary computation
 * during the execution of a program. It provide a method called `has_changed` that return true if the value of the
 * variable has changed since the last call to `has_changed`. Newly created objects are considered as changed.
 * @tparam T The type of the variable to trace
 * @tparam Atomicly A boolean value that indicate if the value of the variable should be traced atomically
 */
template<typename T, bool Atomicly = true>
struct ValueTracer
{
public:
  using SmartPointerType = std::unique_ptr<T>;
  using TracerType       = std::conditional_t<Atomicly, std::atomic<bool>, bool>;

  ValueTracer() : m_current{nullptr}, m_changed{true}
  {}

  /**
   * @brief Construct a new Value Tracer object
   * @param value The value to trace
   */
  ValueTracer(const T& value) : m_current{new T{value}}, m_changed{true}
  {}

  /**
   * @brief Copy constructor
   * @param other The other ValueTracer object to copy
   */
  ValueTracer(const ValueTracer& other) : m_current{new T{*other.m_current}}, m_changed{other.m_changed.load()}
  {}

  /**
   * @brief Move constructor
   * @param other The other ValueTracer object to move
   */
  ValueTracer(ValueTracer&& other) noexcept : m_current{other.m_current}, m_changed{other.m_changed.load()}
  {
    other.m_current = nullptr;
  }

  /**
   * @brief Destroy the Value Tracer object
   */
  ~ValueTracer() noexcept = default;

  /**
   * @brief Copy assignment operator
   * @param other The other ValueTracer object to copy
   * @return ValueTracer& A reference to this object
   */
  ValueTracer& operator=(const ValueTracer& other)
  {
    if (this != &other)
    {
      m_current = new T{*other.m_current};
      m_changed.store(other.m_changed.load());
    }
    return *this;
  }

  /**
   * @brief Move assignment operator
   * @param other The other ValueTracer object to move
   * @return ValueTracer& A reference to this object
   */
  ValueTracer& operator=(ValueTracer&& other) noexcept
  {
    if (this != &other)
    {
      m_current = other.m_current;
      m_changed.store(other.m_changed.load());
      other.m_current = nullptr;
    }
    return *this;
  }

  /**
   * @brief Set the value to trace, then set the changed flag to true if the value has changed
   * @param value The value to trace
   */
  void set(const T& value)
  {
    if (!m_current)
    {
      m_current = new T{value};
      m_changed = true;
    }
    else if (*m_current != value)
    {
      *m_current = value;
      m_changed  = true;
    }
  }

  /**
   * @brief Get the value of the variable
   * @return const T& The value of the variable
   */
  const T& get() const
  {
    return *m_current;
  }

  /**
   * @brief Check if the value of the variable has changed then reset the changed flag
   * @return true If the value of the variable has changed
   * @return false If the value of the variable has not changed
   */
  bool has_changed()
  {
    bool changed = m_changed;
    m_changed    = false;
    return m_changed;
  }

private:
  SmartPointerType m_current;
  TracerType       m_changed;
};

} // namespace setsugen
