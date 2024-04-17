#pragma once

#include <memory>
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
  std::string name;
  Version     version;
  std::string author;
  std::string description;

  struct
  {
    std::string title;
    int         width;
    int         height;
  } window_config;

  struct
  {
    std::string log_template;
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
  using LoggerConfigCallback = std::function<void(ApplicationBuilder&, LoggerFactory&)>;

  ApplicationBuilder();
  ~ApplicationBuilder() = default;

  ApplicationBuilder* set_name(const std::string& name);
  ApplicationBuilder* set_version(const Version& version);
  ApplicationBuilder* set_author(const std::string& author);
  ApplicationBuilder* set_description(const std::string& desc);
  ApplicationBuilder* set_window_config(const std::string& title, int width, int height);
  ApplicationBuilder* set_logger_format(const std::string& format);

  std::unique_ptr<Application> build();

  static std::unique_ptr<ApplicationBuilder> create();

private:
  ApplicationDescription m_description;
  LoggerFactory          m_logger_factory;
};

class Application
{
public:
  Application();
  virtual ~Application();

  virtual Application* run() = 0;
  virtual Application* join() = 0;

  virtual std::shared_ptr<Logger> create_logger(const std::string& name) const = 0;
  virtual Window*                 get_window()                                 = 0;
  virtual SceneManager*           get_scene_manager()                          = 0;

  static Application* current_app();
  static std::string  get_assets_path();
  static std::string  get_root_path();

protected:
  static std::atomic<Application*> s_current_app;

private:
  friend class ApplicationBuilder;
};
} // namespace setsugen
