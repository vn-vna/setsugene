#pragma once

#include <setsugen/component.h>
#include <setsugen/math.h>
#include <setsugen/pch.h>


namespace setsugen
{
class Transform : public Component
{
public:
  Transform(Entity* entity, const Vec3F& position = Vec3F{}, const Vec3F& rotation = Vec3F{},
            const Vec3F& scale = Vec3F{1.0f, 1.0f, 1.0f});

  ~Transform() override = default;

  const Vec3F& get_position() const;
  const Vec3F& get_rotation() const;
  const Vec3F& get_scale() const;

  void set_position(const Vec3F& position);
  void set_rotation(const Vec3F& rotation);
  void set_scale(const Vec3F& scale);

  Mat4x4F get_model_matrix() const;

  const char* get_type() override;

protected:
  Vec3F m_position;
  Vec3F m_rotation;
  Vec3F m_scale;
};
} // namespace setsugen
