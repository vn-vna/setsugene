#pragma once

#include <setsugen/pch.h>

namespace setsugen
{
struct FormatContext;

class SetsugenException : public std::exception
{
public:
  explicit SetsugenException(const String& message);
  ~SetsugenException() override = default;

  virtual Void stringify(const FormatContext& context) const;
};

class NotImplementedException : public SetsugenException
{
public:
  explicit NotImplementedException(const String& message);
  ~NotImplementedException() override = default;
};

class InvalidStateException : public SetsugenException
{
public:
  explicit InvalidStateException(const String& message);
  ~InvalidStateException() override = default;
};

class InvalidFormatException : public SetsugenException
{
public:
  explicit InvalidFormatException(const String& message);
  ~InvalidFormatException() override = default;
};

class InvalidArgumentException : public SetsugenException
{
public:
  explicit InvalidArgumentException(const String& message);
  ~InvalidArgumentException() override = default;
};

class InvalidOperationException : public SetsugenException
{
public:
  explicit InvalidOperationException(const String& message);
  ~InvalidOperationException() override = default;
};

class EngineException : public SetsugenException
{
public:
  explicit EngineException(const String& message);
  ~EngineException() override = default;
};
} // namespace setsugen
