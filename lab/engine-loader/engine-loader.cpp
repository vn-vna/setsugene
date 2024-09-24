#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

#include <setsugen/chrono.h>
#include <setsugen/conf.h>
#include <setsugen/format.h>
#include <setsugen/serde.h>

using setsugen::ConfigurationLoader;
using setsugen::Date;
using setsugen::FileConfigurationSource;
using setsugen::Formatter;
using setsugen::TimeZoneOffset;

int
main()
{
  try
  {
    std::string str = "w=10,f=sdkfjklsdfg,h=20";

    auto begin_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10'000'000; ++i)
    {
      auto spec_view =
          std::views::all(str) | std::views::split(',') |
          std::views::transform(
              [](auto&& rng)
              {
                return rng | std::views::split('=') |
                       std::views::transform(
                           [](auto&& view) {
                             return std::string_view(view.begin(), view.end());
                           });
              }) |
          std::views::transform(
              [](auto&& kv)
              {
                auto p = kv.begin();
                auto k = std::string_view((*p).begin(), (*p).end());
                ++p;
                auto v = std::string_view((*p).begin(), (*p).end());
                return std::make_tuple(k, v);
              });
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << "Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - begin_time)
                     .count()
              << "ms" << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
