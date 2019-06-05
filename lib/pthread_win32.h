#ifndef _PTHREAD_
#define _PTHREAD_

#ifdef __cplusplus
extern "C" {
#endif

int NotImplemented( const char* file, int line );

#define pthread_create(A, B, C, D) (NotImplemented(__FILE__, __LINE__))
#define pthread_join(A, B) (NotImplemented(__FILE__, __LINE__))
#define pthread_cancel(A) (NotImplemented(__FILE__, __LINE__))
#define pthread_self() (1)
#define pthread_equal(A,B) (A==B)

typedef void* pthread_mutex_t;
typedef void* pthread_mutexattr_t;
typedef int pthread_t;

int pthread_mutex_init ( pthread_mutex_t* mutex, const pthread_mutexattr_t* attr );
int pthread_mutex_destroy ( pthread_mutex_t* mutex );
int pthread_mutex_lock ( pthread_mutex_t* mutex );
int pthread_mutex_unlock ( pthread_mutex_t* mutex );

#ifdef __cplusplus
}
#endif

#endif //_PTHREAD_