#pragma once

#include "./vector_decl.inl"

namespace setsugen
{

using Vec2B  = Vec<Bool, 2>;
using Vec3B  = Vec<Bool, 3>;
using Vec4B  = Vec<Bool, 4>;
using Vec2C  = Vec<Int8, 2>;
using Vec3C  = Vec<Int8, 3>;
using Vec4C  = Vec<Int8, 4>;
using Vec2S  = Vec<Int16, 2>;
using Vec3S  = Vec<Int16, 3>;
using Vec4S  = Vec<Int16, 4>;
using Vec2I  = Vec<Int32, 2>;
using Vec3I  = Vec<Int32, 3>;
using Vec4I  = Vec<Int32, 4>;
using Vec2U  = Vec<UInt32, 2>;
using Vec3U  = Vec<UInt32, 3>;
using Vec4U  = Vec<UInt32, 4>;
using Vec2L  = Vec<Int64, 2>;
using Vec3L  = Vec<Int64, 3>;
using Vec4L  = Vec<Int64, 4>;
using Vec2UL = Vec<UInt64, 2>;
using Vec3UL = Vec<UInt64, 3>;
using Vec4UL = Vec<UInt64, 4>;
using Vec2F  = Vec<Float32, 2>;
using Vec3F  = Vec<Float32, 3>;
using Vec4F  = Vec<Float32, 4>;
using Vec2D  = Vec<Float64, 2>;
using Vec3D  = Vec<Float64, 3>;
using Vec4D  = Vec<Float64, 4>;

using Dim2I  = Vec<Int32, 2, VectorUsage::Size>;
using Dim3I  = Vec<Int32, 3, VectorUsage::Size>;
using Dim4I  = Vec<Int32, 4, VectorUsage::Size>;
using Dim2U  = Vec<UInt32, 2, VectorUsage::Size>;
using Dim3U  = Vec<UInt32, 3, VectorUsage::Size>;
using Dim4U  = Vec<UInt32, 4, VectorUsage::Size>;
using Dim2L  = Vec<Int64, 2, VectorUsage::Size>;
using Dim3L  = Vec<Int64, 3, VectorUsage::Size>;
using Dim4L  = Vec<Int64, 4, VectorUsage::Size>;
using Dim2UL = Vec<UInt64, 2, VectorUsage::Size>;
using Dim3UL = Vec<UInt64, 3, VectorUsage::Size>;
using Dim4UL = Vec<UInt64, 4, VectorUsage::Size>;
using Dim2F  = Vec<Float32, 2, VectorUsage::Size>;
using Dim3F  = Vec<Float32, 3, VectorUsage::Size>;
using Dim4F  = Vec<Float32, 4, VectorUsage::Size>;
using Dim2D  = Vec<Float64, 2, VectorUsage::Size>;
using Dim3D  = Vec<Float64, 3, VectorUsage::Size>;
using Dim4D  = Vec<Float64, 4, VectorUsage::Size>;

using Color3F = Vec<Float32, 3, VectorUsage::Color>;
using Color3D = Vec<Float64, 3, VectorUsage::Color>;
using Color4F = Vec<Float32, 4, VectorUsage::Color>;
using Color4D = Vec<Float64, 4, VectorUsage::Color>;

using Color     = Color4F;
using ColorFlag = Vec<Bool, 4, VectorUsage::Color>;
} // namespace setsugen
