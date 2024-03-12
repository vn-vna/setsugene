#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/logger.h>
#include <setsugen/version.h>

namespace setsugen
{

struct ApplicationDescription;
class ApplicationBuilder;
class Application;
class Window;

/**
 * Represents the description of an application.
 * An application description contains the name, version, author, and description of an application.
 */
struct ApplicationDescription
{
  String  name;
  Version version;
  String  author;
  String  description;

  struct
  {
    Int32  width;
    Int32  height;
    String title;
  } window_config;

  struct
  {
    String log_template;
  } logger_config;
};

/**
 * Builder class for creating an application.
 * This class is used to create an application by setting the application's name, version, author,
 * and description. Once all of these fields have been set, the application can be built by calling
 * the build() method.
 */
class ApplicationBuilder
{
public:
  using LoggerConfigCallback = Fn<Void(ApplicationBuilder&, LoggerFactory&)>;

public:
  ApplicationBuilder& set_name(const String& name);
  ApplicationBuilder& set_version(const Version& version);
  ApplicationBuilder& set_author(const String& author);
  ApplicationBuilder& set_description(const String& desc);
  ApplicationBuilder& set_window_config(Int32 width, Int32 height, const String& title);
  ApplicationBuilder& set_logger_format(const String& format);

  SharedPtr<Application> build();

public:
  ApplicationBuilder();
  ~ApplicationBuilder() = default;

private:
  ApplicationDescription m_description;
  LoggerFactory          m_logger_factory;
};

class Application
{
public:
  virtual Void              run()                                   = 0;
  virtual SharedPtr<Logger> create_logger(const String& name) const = 0;
  virtual WeakPtr<Window>   get_window() const                      = 0;

public:
  static SharedPtr<Application> current_app();

private:
  static Optional<WeakPtr<Application>> s_current_app;

  friend class ApplicationBuilder;
};

}  // namespace setsugen