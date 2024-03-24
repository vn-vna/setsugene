#include <setsugen/exception.h>

// Setsugen headers
#include <setsugen/format.h>

namespace setsugen
{
SetsugenException::SetsugenException(const String& message)
    : std::exception(message.c_str())
{}

Void

SetsugenException::stringify(const FormatContext& context) const
{}

NotImplementedException::NotImplementedException(const String& message)
    : SetsugenException(Formatter::format("Not implemented: {0}", message))
{}

InvalidStateException::InvalidStateException(const String& message)
    : SetsugenException(Formatter::format("Invalid state: {0}", message))
{}

InvalidFormatException::InvalidFormatException(const String& message)
    : SetsugenException(Formatter::format("Invalid format: {0}", message))
{}

InvalidArgumentException::InvalidArgumentException(const String& message)
    : SetsugenException(Formatter::format("Invalid argument: {0}", message))
{}

InvalidOperationException::InvalidOperationException(const String& message)
    : SetsugenException(Formatter::format("Invalid operation: {0}", message))
{}

EngineException::EngineException(const String& message)
    : SetsugenException(Formatter::format("Engine error: {0}", message))
{}
} // namespace setsugen
