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

  void set_position(const Vec3F& position);
  void set_center(const Vec3F& center);

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
                     const Vec3F& up = Vec3F{0.0f, 1.0f, 0.0f}, float near_plane = 0.5f, float far_plane = 1000.0f,
                     float fov = 75.0f, float aspect = 16.0f / 9.0f);
  ~PerspectiveCamera() override = default;

  float   get_near_plane() const;
  float   get_far_plane() const;
  float   get_fov() const;
  Mat4x4F get_projection_matrix() const override;

  void set_near_plane(float near_plane);
  void set_far_plane(float far_plane);
  void set_fov(float fov);
  void set_aspect_ratio(float aspect);

private:
  float m_near;
  float m_far;
  float m_fov;
  float m_aspect;
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
