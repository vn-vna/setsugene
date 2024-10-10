#include <setsugen/format.h>

int
main()
{
  std::cout << setsugen::Formatter::format("Hello {} {}! My name is {vna}", {"World", "Yay!!!", {"vna", "Anh Vu"}});
}
