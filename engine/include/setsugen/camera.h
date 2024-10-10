#pragma once

#include <setsugen/component.h>
#include <setsugen/math.h>
#include <setsugen/pch.h>

namespace setsugen
{
class Camera : public Component
{
public:
   Camera(Entity* entity, const Vec3F& position, const Vec3F& direction, const Vec3F& up);
  ~Camera() override = default;

  Vec3F get_position() const;
  Vec3F get_direction() const;

  Void set_position(const Vec3F& position);
  Void set_center(const Vec3F& center);

  Mat4x4F         get_view_matrix() const;
  virtual Mat4x4F get_projection_matrix() const = 0;

  const char* get_type() override;

private:
  Vec3F m_position;
  Vec3F m_center;
  Vec3F m_up;
};


class PerspectiveCamera : public Camera
{
public:
   PerspectiveCamera(Entity* entity, const Vec3F& position = Vec3F{}, const Vec3F& direction = Vec3F{0.0f, 1.0f, 0.0f},
                     const Vec3F& up = Vec3F{0.0f, 1.0f, 0.0f}, Float32 near_plane = 0.5f, Float32 far_plane = 1000.0f,
                     Float32 fov = 75.0f, Float32 aspect = 16.0f / 9.0f);
  ~PerspectiveCamera() override = default;

  Float32   get_near_plane() const;
  Float32   get_far_plane() const;
  Float32   get_fov() const;
  Mat4x4F get_projection_matrix() const override;

  Void set_near_plane(Float32 near_plane);
  Void set_far_plane(Float32 far_plane);
  Void set_fov(Float32 fov);
  Void set_aspect_ratio(Float32 aspect);

private:
  Float32 m_near;
  Float32 m_far;
  Float32 m_fov;
  Float32 m_aspect;
};


class OrthographicCamera : public Camera
{
public:
   OrthographicCamera(Entity* entity, const Vec3F& position = Vec3F{}, const Vec3F& direction = Vec3F{},
                      const Vec2F& horizontal = Vec2F{-10.0f, 10.0f}, const Vec2F& vertical = Vec2F{-10.0f, 10.0f},
                      const Vec2F& depth = Vec2F{1.0f, 1000.0f});
  ~OrthographicCamera() override = default;
};
} // namespace setsugen
