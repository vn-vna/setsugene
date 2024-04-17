#version 450

struct CameraUniformData
{
    mat4 view;
    mat4 projection;
};

struct TransformUniformData
{
    mat4 transform;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

layout (binding = 0) uniform CameraBuffer {
  CameraUniformData main_camera;
} scene_ubo;

layout (binding = 1) uniform ModelBuffer {
  TransformUniformData model_transform;
} model_ubo;

layout (location = 0) out vec3 fragPos;
layout (location = 1) out vec3 fragNormal;

void main() {
    gl_Position = scene_ubo.main_camera.projection * scene_ubo.main_camera.view * model_ubo.model_transform.transform * vec4(position, 1.0);
    fragPos = position;
    fragNormal = normal;
}