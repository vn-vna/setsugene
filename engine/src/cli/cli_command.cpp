#include <setsugen/cli.h>

namespace setsugen
{

CliCommand::CliCommand(const std::string& name, const std::string& description, CommandCallback callback)
    : m_name(name), m_description(description), m_callback(std::move(callback))
{}

CliCommand::~CliCommand() = default;

void
CliCommand::add_argument(const std::string& name, const std::string& description, SerializedType type,
                         const SerializedData& default_value)
{
  m_arguments.emplace_back(name, description, type, default_value);
}

void
CliCommand::parse(int argc, char** argv)
{

  if (argc < 1)
  {
    return;
  }

  if (std::string_view(argv[0]) != m_name)
  {
    return;
  }

  ExecutionData execution_data;
  int           i = 1;
  for (; i < argc; ++i)
  {
    auto sv = std::string_view(argv[i]);

    if (sv.starts_with("--"))
    {
      sv.remove_prefix(2);

      m_arguments | std::views::filter([&sv](const auto& arg) { return arg.m_name == sv; }) |
          std::views::transform([&execution_data](const auto& arg)
                                { return &execution_data.get_argument(arg.m_name); });
    }
    else
    {
      break;
    }
  }

  m_callback(execution_data);
}

} // namespace setsugen
