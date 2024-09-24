#pragma once

#include <setsugen/pch.h>

#include <setsugen/format.h>
#include <setsugen/serde.h>

namespace setsugen
{

class Configuration;
class ConfigurationSource;
class ConfigurationLoader;
class FileConfigurationSource;
class SerializedConfigurationSource;
class CliArgsConfigurationSource;
class EnvConfigurationSource;

SETSUGENE_DECLARE_EXCEPTION(ConfigurationException);
SETSUGENE_DECLARE_EXCEPTION(ConfigurationSourceException);

} // namespace setsugen
