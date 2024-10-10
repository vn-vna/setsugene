#pragma once

#include <setsugen/pch.h>

namespace setsugen
{

class Renderer;
class RenderTarget;
class PresentTarget;

enum class RendererType
{
  Vulkan,
};

enum class RenderTargetType
{
  Scene,
};

enum class PresentTargetType
{
  Window,
  Texture,
};

} // namespace setsugen
