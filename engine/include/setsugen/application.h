#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/logger.h>
#include <setsugen/version.h>

#include "scene.h"

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
    String title;
    Int32  width;
    Int32  height;
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

  ApplicationBuilder();
  ~ApplicationBuilder() = default;

  Observer<ApplicationBuilder> set_name(const String& name);
  Observer<ApplicationBuilder> set_version(const Version& version);
  Observer<ApplicationBuilder> set_author(const String& author);
  Observer<ApplicationBuilder> set_description(const String& desc);
  Observer<ApplicationBuilder> set_window_config(const String& title, Int32 width, Int32 height);
  Observer<ApplicationBuilder> set_logger_format(const String& format);

  SharedPtr<Application> build();

  static UniquePtr<ApplicationBuilder> create();

private:
  ApplicationDescription m_description;
  LoggerFactory          m_logger_factory;
};

class Application
{
public:
  Application();
  virtual ~Application();

  virtual Void              run() = 0;
  virtual SharedPtr<Logger> create_logger(const String& name) const = 0;
  virtual Observer<Window>  get_window() = 0;
  virtual Observer<Scene>   get_current_scene() = 0;

  static Observer<Application> current_app();

protected:
  static Atomic<Observer<Application>> s_current_app;

private:
  friend class ApplicationBuilder;
};
} // namespace setsugen
