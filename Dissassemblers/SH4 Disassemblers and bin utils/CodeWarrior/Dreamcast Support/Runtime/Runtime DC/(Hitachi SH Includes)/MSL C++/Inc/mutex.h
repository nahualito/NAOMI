/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/18/98 12:27 PM                                 $ 
 *  $Revision:: 12                                           $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  mutex.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_MUTEX_H
#define MSIPL_MUTEX_H

#include <mcompile.h>

#ifdef MSIPL_MULTITHREAD

// LINUX threads
#ifdef MSIPL_LINUX

#  define _P(x) x
#  define __p(x) x
#  define __attribute__(x)
#  include <pthread.h>
#  define rw_mutex mutex
#  ifdef AIXV3
#    ifndef _AIX32_THREADS
#      define POSIX_DRAFT7_THREADS
#    endif
#  endif

   static const   pthread_mutexattr_t msipl_rec_mutex = {PTHREAD_MUTEX_RECURSIVE_NP};

   typedef pthread_t msipl_thread_t;
   typedef pthread_mutex_t msipl_mutex_t;

   typedef pthread_t thread_t;
   typedef pthread_mutex_t mutex_t;

#  define msipl_thread_self pthread_self

#  define msipl_mutex_trylock(m) pthread_mutex_trylock(m)
#  define msipl_mutex_lock(m) pthread_mutex_lock(m)
#  define msipl_mutex_unlock(m) pthread_mutex_unlock(m)
#  define msipl_mutex_destroy(m) pthread_mutex_destroy(m)
#  define msipl_mutex_init(m) pthread_mutex_init(m, &msipl_rec_mutex)
#  define thr_create(a, b, c, d, e, f) pthread_create(f, b, c, d)
#  define thr_exit(a) pthread_exit(a)
#  define thr_join(a, b, c) pthread_join(a, c)

#else

// SUN OS, UNIX SVR ...
#ifdef MSIPL_SUN_OS

#  include <synch.h>        // hh 971220 fixed MOD_INCLUDE
#  include <thread.h>       // hh 971220 fixed MOD_INCLUDE
#  include <sys/errno.h>    // hh 971220 fixed MOD_INCLUDE

   typedef thread_t msipl_thread_t;
   typedef mutex_t msipl_mutex_t;

#  define msipl_thread_self thr_self

#  define msipl_mutex_init(m) mutex_init(m,USYNC_THREAD,0)
#  define msipl_mutex_trylock(m) mutex_trylock(m)
#  define msipl_mutex_lock(m) mutex_lock(m)
#  define msipl_mutex_unlock(m) mutex_unlock(m)
#  define msipl_mutex_destroy(m) mutex_destroy(m)

#else

// WINDOWS 95/NT
#ifdef MSIPL_WIN32

#  define BOOL wBOOL

#  ifdef Status
#    undef Status
#    define Status wStatus
#  endif

//#  include <windows.h>
	#include <x86_prefix.h>
	#include <wtypes.h>
	#include <WINBASE.h>

#  ifdef Status
#    undef Status
#  define Status int
#  endif

#  undef BOOL

   typedef DWORD msipl_thread_t;
   typedef CRITICAL_SECTION msipl_mutex_t;

#  define msipl_thread_self GetCurrentThreadId

#  define _XMUTEX_NESTS
#  define msipl_mutex_init(m) InitializeCriticalSection(m)
#  define msipl_mutex_trylock(m) EnterCriticalSection(m)
#  define msipl_mutex_lock(m) EnterCriticalSection(m)
#  define msipl_mutex_unlock(m) LeaveCriticalSection(m)
#  define msipl_mutex_destroy(m) DestroyCriticalSection(m)

#endif /* MSIPL_WIN32 */ 

#endif /* MSIPL_SUN_OS */

#endif /* MSIPL_LINUX */

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

MSIPL_STD_BEGIN

#if defined(MSIPL_LINUX)
class mutex {
    typedef msipl_mutex_t mutex_type;
protected:
    mutex_type _lock;
public:
    mutex(){ ::msipl_mutex_init(&_lock); }
    ~mutex(){}
    int try_lock(){ return ::msipl_mutex_trylock(&_lock); } 
    int remove(){ return ::msipl_mutex_destroy(&_lock); }
    int acquire(int i = 0){ return ::msipl_mutex_lock(&_lock); }
    int release(){ return ::msipl_mutex_unlock(&_lock); }
};
#endif

#if defined(MSIPL_SUN_OS) || defined(MSIPL_WIN32)
class mutex {
    typedef msipl_mutex_t mutex_type;
    mutex_type _lock;
    msipl_thread_t tid;
    unsigned int count;
public:
    mutex (): count(0), tid(0) { ::msipl_mutex_init(&_lock); }
    ~mutex (){}
    int try_lock (){ return ::msipl_mutex_trylock(&_lock); }
    int remove (){ return ::msipl_mutex_destroy(&_lock); }
    int acquire (int i = 0);
    int release ();
    void settid(thread_t ptid) { tid = ptid; count=1; }
};

inline int mutex::acquire(int i){ 
   int ret = -1;
   msipl_thread_t tmpid = msipl_thread_self();
   if( tid == tmpid ) { ++count; ret = 0; }
   else { 
       ret = ::msipl_mutex_lock(&_lock);
       if(!ret) { count = 1; tid = tmpid; }
   }
   return ret; 
}

inline int mutex::release() {
   return (--count) ? 0 : (tid=0, ::msipl_mutex_unlock (&_lock));
}
#endif

#ifdef MSIPL_SUN_OS
class rw_mutex {
    typedef rwlock_t mutex_type;
    mutex_type _lock;
    char dummy[24];    // due to bug in sol 2.4 thread lib
    unsigned int count;
    msipl_thread_t tid;
public:
    rw_mutex () : tid(0), count(0)
    { ::rwlock_init(&_lock, USYNC_THREAD,0); }
    ~rw_mutex (){}
    int try_rdlock () { return ::rw_tryrdlock(&_lock); }
    int try_wrlock () { return ::rw_trywrlock(&_lock); }
    int remove () { return ::rwlock_destroy(&_lock); }
    int acquire (int);
    int release ();
    void settid(thread_t ptid) { tid=ptid; count=1; }
};

inline int rw_mutex::acquire(int type){
    int retval = -1;
    msipl_thread_t tmpid = msipl_thread_self();
    if(tid == tmpid){ ++count; retval=0; }
    else {
        retval=(type==WR_LOCK) ? (::rw_wrlock(&_lock)) : (::rw_rdlock(&_lock));
        if(!retval){ tid = tmpid; count=1; }
    }
    return retval;
}

inline int rw_mutex::release(){
    return (--count) ? 0 : (tid=0, ::rw_unlock(&_lock));
}
#endif

template <class MUTEX> class mutex_block {
    MUTEX& _lock;
public:
    // Implicit lock acquisition
    mutex_block(MUTEX& m, int type=0) : _lock(m) {
#ifdef MSIPL_SUN_OS
         if(type>=SRD_LOCK) _lock.settid(msipl_thread_self());
         else
#endif
         _lock.acquire(type);
    }
    mutex_block (const MUTEX& m, int type=0) : _lock((MUTEX&)m) {
#ifdef MSIPL_SUN_OS
         if(type>=SRD_LOCK) _lock.settid(msipl_thread_self());
         else
#endif
         _lock.acquire(type);
    }
    // Implicit lock release
    ~mutex_block() { _lock.release(); }

    // Explicit lock release
    int remove(){ return _lock.remove(); }

    // Explicit lock release
    int release() { return _lock.release(); }

    // Explicit lock acquisition
    int acquire(int type=0) { return _lock.acquire(type); }
};


template <class TYPE,class MUTEX>
class mutex_arith {
    TYPE  _count;
    MUTEX _lock;
public:
    // Initialize _count to 0.
    mutex_arith(){ _count=0; }

    // Initialize _count to i.
    mutex_arith(TYPE i){ _count = i; }

    // Increment _count by unit.
    TYPE operator++(){
        mutex_block<MUTEX> _mutex(_lock);
        return ++_count; }

    TYPE operator++(int){
        mutex_block<MUTEX> _mutex(_lock);
        return  _count++; }

    // Increment _count by i.
    TYPE operator+= (const TYPE i){
        mutex_block<MUTEX> _mutex(_lock);
        return  _count += i; }

    // Decrement _count by unit.
    TYPE operator--(){
        mutex_block<MUTEX> _mutex(_lock);
        return  --_count; }

    TYPE operator--(int){
        mutex_block<MUTEX> _mutex(_lock);
        return _count--; }

    // Decrement _count by i.
    TYPE operator- (const TYPE i){
        mutex_block<MUTEX> _mutex (_lock);
        return  _count -= i; }

    // Compare _count with i.
    bool operator== (const TYPE i){
        mutex_block<MUTEX> _mutex(_lock);
        return  _count == i; }

    bool operator!= (const TYPE i){
        mutex_block<MUTEX> _mutex (_lock);
        return _count!=i; }

    // Check if _count >= i.
    bool operator>=(const TYPE i){
        mutex_block<MUTEX> _mutex(_lock);
        return  _count >= i; }

    // Check if _count > i.
    bool operator>(const TYPE i){
        mutex_block<MUTEX> _mutex(_lock);
        return  _count>i; }

    // Check if _count <= i.
    bool operator<= (const TYPE i){
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count <= i; }

    // Check if _count < i.
    bool operator< (const TYPE i){
        mutex_block<MUTEX> _mutex(_lock);
        return  _count < i; }

    // Assign i to count_.
    void operator= (const TYPE i){
        mutex_block<MUTEX> _mutex(_lock);
        _count = i; }

    // Return count_.
    operator TYPE(){
        mutex_block<MUTEX> _mutex(_lock);
        return  _count; }
};

MSIPL_STD_END

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_MULTITHREAD */

#endif /* MSIPL_MUTEX_H */

// hh 971220 fixed MOD_INCLUDE
// hh 971222 added alignment wrapper
