#include <setsugen/application.h>

// Setsugen headers
#include <setsugen/exception.h>

#include "application_basic-app.h"

// C++ standard libraries
#include <memory>

namespace setsugen
{
ApplicationBuilder::ApplicationBuilder() : m_description{}
{
  m_description.name                       = "Setsugen Application";
  m_description.version                    = {0, 1, 0};
  m_description.author                     = "Unknown";
  m_description.description                = "Setsugen Application";
  m_description.logger_config.log_template = "{time} [{level}] {tag}: {message}";
  m_description.window_config.width        = 800;
  m_description.window_config.height       = 600;
  m_description.window_config.title        = "Setsugen Application";
}

ApplicationBuilder*
ApplicationBuilder::set_name(const std::string& name)
{
  m_description.name = name;
  return this;
}

ApplicationBuilder*
ApplicationBuilder::set_version(const Version& version)
{
  m_description.version = version;
  return this;
}

ApplicationBuilder*
ApplicationBuilder::set_author(const std::string& author)
{
  m_description.author = author;
  return this;
}

ApplicationBuilder*
ApplicationBuilder::set_description(const std::string& desc)
{
  m_description.description = desc;
  return this;
}

ApplicationBuilder*
ApplicationBuilder::set_logger_format(const std::string& format)
{
  m_description.logger_config = {format};
  return this;
}

std::unique_ptr<ApplicationBuilder>
ApplicationBuilder::create()
{
  return std::make_unique<ApplicationBuilder>();
}

ApplicationBuilder*
ApplicationBuilder::set_window_config(const std::string& title, int width, int height)
{
  m_description.window_config = {title, width, height};
  return this;
}

std::unique_ptr<Application>
ApplicationBuilder::build()
{
  return std::make_unique<BasicApplication>(std::move(this->m_description));
}
} // namespace setsugen
