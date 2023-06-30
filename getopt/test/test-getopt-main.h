/* Test of command line argument processing.
   Copyright (C) 2009-2023 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Bruno Haible <bruno@clisp.org>, 2009.  */

#include "win-argp-config.h"
#include "getopt.h"

#include "signature.h"
SIGNATURE_CHECK(getopt, int, (int, char * const[], char const *));

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This test intentionally remaps stderr.  So, we arrange to have fd 10
   (outside the range of interesting fd's during the test) set up to
   duplicate the original stderr.  */

#define BACKUP_STDERR_FILENO 10
#define ASSERT_STREAM myerr

static FILE *myerr;

#include "test-getopt.h"
#if TEST_GETOPT_GNU
# include "test-getopt_long.h"
#endif

int main(void)
{
    /* This test validates that stderr is used correctly, so move the
        original into fd 10.  */
#ifdef _WIN32
    if (_dup2(STDERR_FILENO, BACKUP_STDERR_FILENO) != 0
        || (myerr = fdopen(BACKUP_STDERR_FILENO, "w")) == NULL)
        return 2;
#else /* _WIN32 */
    if (dup2(STDERR_FILENO, BACKUP_STDERR_FILENO) != BACKUP_STDERR_FILENO
        || (myerr = fdopen(BACKUP_STDERR_FILENO, "w")) == NULL)
        return 2;
#endif /* _WIN32 */

    assert(freopen(TEST_GETOPT_TMP_NAME, "w", stderr) == stderr);

    /* These default values are required by POSIX.  */
    assert(optind == 1);
    assert(opterr != 0);

    setenv("POSIXLY_CORRECT", "1", 1);
    test_getopt();

#if TEST_GETOPT_GNU
    test_getopt_long_posix();
#endif

    unsetenv("POSIXLY_CORRECT");
    test_getopt();

#if TEST_GETOPT_GNU
    test_getopt_long();
    test_getopt_long_only();
#endif

    assert(fclose(stderr) == 0);
    assert(remove(TEST_GETOPT_TMP_NAME) == 0);

  return 0;
}

