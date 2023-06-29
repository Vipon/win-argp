/***
 * MIT License
 *
 * Copyright (c) 2023 Konychev Valera
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef _WIN32
# include <io.h>
# include <stdio.h>
# include <stdlib.h>
# include <Windows.h>

static inline
int setenv(const char *name, const char *value, int overwrite)
{
    if (name == NULL)
        return EINVAL;

    if (overwrite) {
        return _putenv_s(name, value);
    } else
        if (getenv(name))
            return 0;
        else
            return -1;
}

static inline
int unsetenv(const char *name)
{
    return _putenv_s(name, "");
}

# ifndef STDERR_FILENO
#  define STDERR_FILENO _fileno(stderr)
# endif /* STDERR_FILENO */

# define DLLEXPORT __declspec(dllexport)
# define DLLIMPORT __declspec(dllimport)
#else /* _WIN32 */
# include <unistd.h>

# define DLLEXPORT
# define DLLIMPORT
#endif /* _WIN32 */

#if __GNUC__ >= 3 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
# define _GL_UNUSED __attribute__ ((__unused__))
#else
# define _GL_UNUSED
#endif

/* The name _UNUSED_PARAMETER_ is an earlier spelling, although the name
   is a misnomer outside of parameter lists.  */
#define _UNUSED_PARAMETER_ _GL_UNUSED

#ifndef FALLTHROUGH
# if (__GNUC__ >= 7) || (__clang_major__ >= 10)
#  define FALLTHROUGH __attribute__ ((__fallthrough__))
# else
#  define FALLTHROUGH ((void) 0)
# endif
#endif

#endif /* __CONFIG_H */

