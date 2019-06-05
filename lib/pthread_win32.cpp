#include "pthread_win32.h"

#include <mutex>
#include <iostream>
#include <cassert>

int pthread_mutex_init ( pthread_mutex_t* mutex, const pthread_mutexattr_t* attr )
{
  *mutex = new std::mutex;
  return 0;
}

int pthread_mutex_destroy ( pthread_mutex_t* mutex )
{
  delete static_cast<std::mutex*>( *mutex );
  *mutex = nullptr;
  return 0;
}

int pthread_mutex_lock ( pthread_mutex_t* mutex )
{
  assert( mutex && *mutex );
  static_cast<std::mutex*>( *mutex )->lock();
  return 0;
}

int pthread_mutex_unlock ( pthread_mutex_t* mutex )
{
  assert( mutex && *mutex );
  static_cast<std::mutex*>( *mutex )->unlock();
  return 0;
}

int NotImplemented( const char* file, int line )
{
  std::cout << file << ":" << line << " Not implemented !!! " << std::endl;
  std::abort();
  return -1;
}