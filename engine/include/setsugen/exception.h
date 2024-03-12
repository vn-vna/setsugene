#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/format.h>

// C++ standard library
#include <stdexcept>

namespace setsugen
{

class SetsugenException : public std::exception,
                          public Formattable
{
public:
  explicit SetsugenException(const String& message);
  ~SetsugenException() override = default;

public:
  String to_string() const override;
};

class NotImplementedException : public SetsugenException
{
public:
  explicit NotImplementedException();
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

}  // namespace setsugen