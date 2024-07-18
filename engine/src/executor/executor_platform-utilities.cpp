#include "executor_platform-utilities.h"

namespace setsugen
{

void
terminate_thread(std::thread& thread)
{
  auto handle = thread.native_handle();
#if defined(__GNUC__)
  pthread_kill(handle, SIGINT);
#elif defined(_WIN32)
  TerminateThread(handle, 0);
#elif
  pthread_cancel(handle);
#endif
}

} // namespace setsugen
