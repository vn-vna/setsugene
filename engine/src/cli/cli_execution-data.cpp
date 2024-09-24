#include <setsugen/cli.h>

namespace setsugen
{

ExecutionData::ExecutionData() = default;

SerializedData& ExecutionData::get_argument(const std::string& name)
{
  return m_arguments.at(name);
}

}
