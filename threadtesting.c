#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

_threadLock *lk;

void f1(void *arg1, void *arg2)
{
  int num = *(int *)arg1;
  if (num)
    lock_acquire(lk);
  printf(1, "1.%s\n", num ? "first" : "whenever");
  printf(1, "-- sleeping in 1\n");
  sleep(100);
  if (num)
    lock_release(lk);
  exit();
}

void f2(void *arg1, void *arg2)
{
  int num = *(int *)arg1;
  if (num)
    lock_acquire(lk);
  printf(1, "2.%s\n", num ? "second" : "whenever");
  printf(1, "-- sleeping in 2\n");
  sleep(100);
  if (num)
    lock_release(lk);
  exit();
}

void f3(void *arg1, void *arg2)
{
  int num = *(int *)arg1;
  if (num)
    lock_acquire(lk);
  printf(1, "3.%s\n", num ? "third" : "whenever");
  printf(1, "-- sleeping in 3\n");
  sleep(100);
  if (num)
    lock_release(lk);
  exit();
}

int main(int argc, char *argv[])
{
  lock_initial(lk);
  int a = 1, b = 1;

  printf(1, "** Sequential print: **\n");
  thread_create(&f1, (void *)&a, (void *)&b);
  thread_create(&f2, (void *)&a, (void *)&b);
  thread_create(&f3, (void *)&a, (void *)&b);
  thread_join();
  thread_join();
  thread_join();

  int c = 0;
  printf(1, "===============================\n");
  printf(1, "** Shuffle print: **\n");
  thread_create(&f1, (void *)&c, (void *)&b);
  thread_create(&f2, (void *)&c, (void *)&b);
  thread_create(&f3, (void *)&c, (void *)&b);
  thread_join();
  thread_join();
  thread_join();

  exit();
}