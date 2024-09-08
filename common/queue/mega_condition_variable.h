// <condition_variable> -*- C++ -*-

// Copyright (C) 2008-2019 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file include/condition_variable
 *  This is a Standard C++ Library header.
 */

#pragma once

#if __cplusplus < 201103L
#include <bits/c++0x_warning.h>
#else

#include "gthr-default.h"
#include <chrono>
// #include <bits/std_mutex.h>
// #include <bits/unique_lock.h>
#include <mutex>
// #include <ext/concurrence.h>
// #include <bits/alloc_traits.h>
// #include <bits/allocator.h>
// #include <bits/unique_ptr.h>
// #include <bits/shared_ptr.h>
// #include <bits/cxxabi_forced.h>

using namespace std;

#define _GLIBCXX_HAS_GTHREADS 1

#define __PRINT_MACRO(x) #x
#define PRINT_MARCO(x) #x "=" __PRINT_MACRO(x)

// #pragma message(PRINT_MARCO(_GLIBCXX_HAS_GTHREADS))
// #pragma message(PRINT_MARCO(_GLIBCXX_BEGIN_NAMESPACE_VERSION))
// #pragma message(PRINT_MARCO(_GLIBCXX_USE_PTHREAD_COND_CLOCKWAIT))

#if defined(_GLIBCXX_HAS_GTHREADS)

namespace megatronix
{
    /**
   * @defgroup condition_variables Condition Variables
   * @ingroup concurrency
   *
   * Classes for condition_variable support.
   * @{
   */

    /// cv_status
    enum class cv_status
    {
        no_timeout,
        timeout
    };

    /// condition_variable
    class condition_variable
    {
        using steady_clock = chrono::steady_clock;
        using system_clock = chrono::system_clock;
#ifdef _GLIBCXX_USE_PTHREAD_COND_CLOCKWAIT
        using __clock_t = steady_clock;
#else
        using __clock_t = system_clock;
#endif
        typedef __gthread_cond_t __native_type;

#ifdef __GTHREAD_COND_INIT
        __native_type _M_cond = __GTHREAD_COND_INIT;
#else
        __native_type _M_cond;
#endif

    public:
        typedef __native_type *native_handle_type;

        condition_variable() noexcept;
        ~condition_variable() noexcept;

        condition_variable(const condition_variable &) = delete;
        condition_variable &operator=(const condition_variable &) = delete;

        void
        notify_one();

        void
        notify_all();

        void
        wait(unique_lock<mutex> &__lock) noexcept;

        template <typename _Predicate>
        void
        wait(unique_lock<mutex> &__lock, _Predicate __p)
        {
            while (!__p())
                wait(__lock);
        }

        template <typename _Duration>
        cv_status
        wait_until(unique_lock<mutex> &__lock,
                   const chrono::time_point<system_clock, _Duration> &__atime)
        {
            return __wait_until_impl(__lock, __atime);
        }

        template <typename _Clock, typename _Duration>
        cv_status
        wait_until(unique_lock<mutex> &__lock,
                   const chrono::time_point<_Clock, _Duration> &__atime)
        {
            const typename _Clock::time_point __c_entry = _Clock::now();
            const __clock_t::time_point __s_entry = __clock_t::now();
            const auto __delta = __atime - __c_entry;
            const auto __s_atime = __s_entry + __delta;

            if (__wait_until_impl(__lock, __s_atime) == cv_status::no_timeout)
                return cv_status::no_timeout;
            // We got a timeout when measured against __clock_t but
            // we need to check against the caller-supplied clock
            // to tell whether we should return a timeout.
            if (_Clock::now() < __atime)
                return cv_status::no_timeout;
            return cv_status::timeout;
        }

        template <typename _Clock, typename _Duration, typename _Predicate>
        bool
        wait_until(unique_lock<mutex> &__lock,
                   const chrono::time_point<_Clock, _Duration> &__atime,
                   _Predicate __p)
        {
            while (!__p())
                if (wait_until(__lock, __atime) == cv_status::timeout)
                    return __p();
            return true;
        }

        template <typename _Rep, typename _Period>
        cv_status
        wait_for(unique_lock<mutex> &__lock,
                 const chrono::duration<_Rep, _Period> &__rtime)
        {
            using __dur = typename steady_clock::duration;
            auto __reltime = chrono::duration_cast<__dur>(__rtime);
            if (__reltime < __rtime)
                ++__reltime;
            return wait_until(__lock, steady_clock::now() + __reltime);
        }

        template <typename _Rep, typename _Period, typename _Predicate>
        bool
        wait_for(unique_lock<mutex> &__lock,
                 const chrono::duration<_Rep, _Period> &__rtime,
                 _Predicate __p)
        {
            using __dur = typename steady_clock::duration;
            auto __reltime = chrono::duration_cast<__dur>(__rtime);
            if (__reltime < __rtime)
                ++__reltime;
            return wait_until(__lock, steady_clock::now() + __reltime,
                              std::move(__p));
        }

        native_handle_type
        native_handle()
        {
            return &_M_cond;
        }

    private:
        template <typename _Dur>
        cv_status
        __wait_until_impl(unique_lock<mutex> &__lock,
                          const chrono::time_point<__clock_t, _Dur> &__atime)
        {
            auto __s = chrono::time_point_cast<chrono::seconds>(__atime);
            auto __ns = chrono::duration_cast<chrono::nanoseconds>(__atime - __s);

            __gthread_time_t __ts =
                {
                    static_cast<std::time_t>(__s.time_since_epoch().count()),
                    static_cast<long>(__ns.count())};

            __gthread_cond_timedwait(&_M_cond, __lock.mutex()->native_handle(),
                                     &__ts);

            return (__clock_t::now() < __atime
                        ? cv_status::no_timeout
                        : cv_status::timeout);
        }
    };

    void
    notify_all_at_thread_exit(condition_variable &, unique_lock<mutex>);

    struct __at_thread_exit_elt
    {
        __at_thread_exit_elt *_M_next;
        void (*_M_cb)(void *);
    };

    // @} group condition_variables
} // namespace megatronix

#endif // _GLIBCXX_HAS_GTHREADS
#endif // C++11
