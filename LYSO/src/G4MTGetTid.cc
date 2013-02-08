#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#ifdef __cplusplus
extern "C" {
#endif

pid_t gettid()
{
  pid_t mytid = syscall(SYS_gettid);
  return mytid;
}

#ifdef __cplusplus
}
#endif
