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

#include <assert.h>
#include <stdbool.h>

/* The glibc/gnulib implementation of getopt supports setting optind =
   0, but not all other implementations do.  This matters for getopt.
   But for getopt_long, we require GNU compatibility.  */
#if defined __GETOPT_PREFIX || (__GLIBC__ >= 2 && !defined __UCLIBC__)
# define OPTIND_MIN 0
#elif HAVE_DECL_OPTRESET
# define OPTIND_MIN (optreset = 1)
#else
# define OPTIND_MIN 1
#endif

static void
getopt_loop (int argc, const char **argv,
             const char *options,
             int *a_seen, int *b_seen,
             const char **p_value, const char **q_value,
             int *non_options_count, const char **non_options,
             int *unrecognized, bool *message_issued)
{
  int c;
  int pos = ftell (stderr);

  while ((c = getopt (argc, (char **) argv, options)) != -1)
    {
      switch (c)
        {
        case 'a':
          (*a_seen)++;
          break;
        case 'b':
          (*b_seen)++;
          break;
        case 'p':
          *p_value = optarg;
          break;
        case 'q':
          *q_value = optarg;
          break;
        case '\1':
          /* Must only happen with option '-' at the beginning.  */
          assert(options[0] == '-');
          non_options[(*non_options_count)++] = optarg;
          break;
        case ':':
          /* Must only happen with option ':' at the beginning.  */
          assert(options[0] == ':'
                  || ((options[0] == '-' || options[0] == '+')
                      && options[1] == ':'));
          FALLTHROUGH;
        case '?':
          *unrecognized = optopt;
          break;
        default:
          *unrecognized = c;
          break;
        }
    }

  *message_issued = pos < ftell (stderr);
}

static void
test_getopt (void)
{
  int start;
  bool posixly = !!getenv ("POSIXLY_CORRECT");
  /* See comment in getopt.c:
     glibc gets a LSB-compliant getopt.
     Standalone applications get a POSIX-compliant getopt.  */
#if defined __GETOPT_PREFIX || !(__GLIBC__ >= 2 || defined __MINGW32__)
  /* Using getopt from gnulib or from a non-glibc system.  */
  posixly = true;
#endif

  /* Test processing of boolean options.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-a";
      argv[argc++] = "foo";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "ab",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 2);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-b";
      argv[argc++] = "-a";
      argv[argc++] = "foo";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "ab",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 1);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 3);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-ba";
      argv[argc++] = "foo";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "ab",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 1);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 2);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-ab";
      argv[argc++] = "-a";
      argv[argc++] = "foo";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "ab",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 2);
      assert(b_seen == 1);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 3);
      assert(!output);
    }

  /* Test processing of options with arguments.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-pfoo";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "p:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 0);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 2);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc++] = "foo";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "p:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 0);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 3);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-ab";
      argv[argc++] = "-q";
      argv[argc++] = "baz";
      argv[argc++] = "-pfoo";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 1);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value != NULL && strcmp (q_value, "baz") == 0);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 5);
      assert(!output);
    }

#if GNULIB_TEST_GETOPT_GNU
  /* Test processing of options with optional arguments.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-pfoo";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "p::q::",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 0);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 2);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc++] = "foo";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "p::q::",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 0);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 2);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "abp::q::",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 3);
      assert(!output);
    }
#endif /* GNULIB_TEST_GETOPT_GNU */

  /* Check that invalid options are recognized; and that both opterr
     and leading ':' can silence output.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc++] = "foo";
      argv[argc++] = "-x";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 42;
      getopt_loop (argc, argv, "abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 'x');
      assert(optind == 5);
      assert(output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc++] = "foo";
      argv[argc++] = "-x";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 0;
      getopt_loop (argc, argv, "abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 'x');
      assert(optind == 5);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc++] = "foo";
      argv[argc++] = "-x";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, ":abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 'x');
      assert(optind == 5);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc++] = "foo";
      argv[argc++] = "-:";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 42;
      getopt_loop (argc, argv, "abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == ':');
      assert(optind == 5);
      assert(output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc++] = "foo";
      argv[argc++] = "-:";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 0;
      getopt_loop (argc, argv, "abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == ':');
      assert(optind == 5);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc++] = "foo";
      argv[argc++] = "-:";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, ":abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "foo") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == ':');
      assert(optind == 5);
      assert(!output);
    }

  /* Check for missing argument behavior.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-ap";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 'p');
      assert(optind == 2);
      assert(output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-ap";
      argv[argc] = NULL;
      optind = start;
      opterr = 0;
      getopt_loop (argc, argv, "abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 'p');
      assert(optind == 2);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-ap";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, ":abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 'p');
      assert(optind == 2);
      assert(!output);
    }

  /* Check that by default, non-options arguments are moved to the end.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "donald";
      argv[argc++] = "-p";
      argv[argc++] = "billy";
      argv[argc++] = "duck";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      if (posixly)
        {
          assert(strcmp (argv[0], "program") == 0);
          assert(strcmp (argv[1], "donald") == 0);
          assert(strcmp (argv[2], "-p") == 0);
          assert(strcmp (argv[3], "billy") == 0);
          assert(strcmp (argv[4], "duck") == 0);
          assert(strcmp (argv[5], "-a") == 0);
          assert(strcmp (argv[6], "bar") == 0);
          assert(argv[7] == NULL);
          assert(a_seen == 0);
          assert(b_seen == 0);
          assert(p_value == NULL);
          assert(q_value == NULL);
          assert(non_options_count == 0);
          assert(unrecognized == 0);
          assert(optind == 1);
          assert(!output);
        }
      else
        {
          assert(strcmp (argv[0], "program") == 0);
          assert(strcmp (argv[1], "-p") == 0);
          assert(strcmp (argv[2], "billy") == 0);
          assert(strcmp (argv[3], "-a") == 0);
          assert(strcmp (argv[4], "donald") == 0);
          assert(strcmp (argv[5], "duck") == 0);
          assert(strcmp (argv[6], "bar") == 0);
          assert(argv[7] == NULL);
          assert(a_seen == 1);
          assert(b_seen == 0);
          assert(p_value != NULL && strcmp (p_value, "billy") == 0);
          assert(q_value == NULL);
          assert(non_options_count == 0);
          assert(unrecognized == 0);
          assert(optind == 4);
          assert(!output);
        }
    }

  /* Check that '--' ends the argument processing.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[20];

      argv[argc++] = "program";
      argv[argc++] = "donald";
      argv[argc++] = "-p";
      argv[argc++] = "billy";
      argv[argc++] = "duck";
      argv[argc++] = "-a";
      argv[argc++] = "--";
      argv[argc++] = "-b";
      argv[argc++] = "foo";
      argv[argc++] = "-q";
      argv[argc++] = "johnny";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      if (posixly)
        {
          assert(strcmp (argv[0], "program") == 0);
          assert(strcmp (argv[1], "donald") == 0);
          assert(strcmp (argv[2], "-p") == 0);
          assert(strcmp (argv[3], "billy") == 0);
          assert(strcmp (argv[4], "duck") == 0);
          assert(strcmp (argv[5], "-a") == 0);
          assert(strcmp (argv[6], "--") == 0);
          assert(strcmp (argv[7], "-b") == 0);
          assert(strcmp (argv[8], "foo") == 0);
          assert(strcmp (argv[9], "-q") == 0);
          assert(strcmp (argv[10], "johnny") == 0);
          assert(strcmp (argv[11], "bar") == 0);
          assert(argv[12] == NULL);
          assert(a_seen == 0);
          assert(b_seen == 0);
          assert(p_value == NULL);
          assert(q_value == NULL);
          assert(non_options_count == 0);
          assert(unrecognized == 0);
          assert(optind == 1);
          assert(!output);
        }
      else
        {
          assert(strcmp (argv[0], "program") == 0);
          assert(strcmp (argv[1], "-p") == 0);
          assert(strcmp (argv[2], "billy") == 0);
          assert(strcmp (argv[3], "-a") == 0);
          assert(strcmp (argv[4], "--") == 0);
          assert(strcmp (argv[5], "donald") == 0);
          assert(strcmp (argv[6], "duck") == 0);
          assert(strcmp (argv[7], "-b") == 0);
          assert(strcmp (argv[8], "foo") == 0);
          assert(strcmp (argv[9], "-q") == 0);
          assert(strcmp (argv[10], "johnny") == 0);
          assert(strcmp (argv[11], "bar") == 0);
          assert(argv[12] == NULL);
          assert(a_seen == 1);
          assert(b_seen == 0);
          assert(p_value != NULL && strcmp (p_value, "billy") == 0);
          assert(q_value == NULL);
          assert(non_options_count == 0);
          assert(unrecognized == 0);
          assert(optind == 5);
          assert(!output);
        }
    }

#if GNULIB_TEST_GETOPT_GNU
  /* Check that the '-' flag causes non-options to be returned in order.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "donald";
      argv[argc++] = "-p";
      argv[argc++] = "billy";
      argv[argc++] = "duck";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "-abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(strcmp (argv[0], "program") == 0);
      assert(strcmp (argv[1], "donald") == 0);
      assert(strcmp (argv[2], "-p") == 0);
      assert(strcmp (argv[3], "billy") == 0);
      assert(strcmp (argv[4], "duck") == 0);
      assert(strcmp (argv[5], "-a") == 0);
      assert(strcmp (argv[6], "bar") == 0);
      assert(argv[7] == NULL);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "billy") == 0);
      assert(q_value == NULL);
      assert(non_options_count == 3);
      assert(strcmp (non_options[0], "donald") == 0);
      assert(strcmp (non_options[1], "duck") == 0);
      assert(strcmp (non_options[2], "bar") == 0);
      assert(unrecognized == 0);
      assert(optind == 7);
      assert(!output);
    }

  /* Check that '--' ends the argument processing.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[20];

      argv[argc++] = "program";
      argv[argc++] = "donald";
      argv[argc++] = "-p";
      argv[argc++] = "billy";
      argv[argc++] = "duck";
      argv[argc++] = "-a";
      argv[argc++] = "--";
      argv[argc++] = "-b";
      argv[argc++] = "foo";
      argv[argc++] = "-q";
      argv[argc++] = "johnny";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "-abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(strcmp (argv[0], "program") == 0);
      assert(strcmp (argv[1], "donald") == 0);
      assert(strcmp (argv[2], "-p") == 0);
      assert(strcmp (argv[3], "billy") == 0);
      assert(strcmp (argv[4], "duck") == 0);
      assert(strcmp (argv[5], "-a") == 0);
      assert(strcmp (argv[6], "--") == 0);
      assert(strcmp (argv[7], "-b") == 0);
      assert(strcmp (argv[8], "foo") == 0);
      assert(strcmp (argv[9], "-q") == 0);
      assert(strcmp (argv[10], "johnny") == 0);
      assert(strcmp (argv[11], "bar") == 0);
      assert(argv[12] == NULL);
      assert(a_seen == 1);
      assert(b_seen == 0);
      assert(p_value != NULL && strcmp (p_value, "billy") == 0);
      assert(q_value == NULL);
      assert(!output);
      if (non_options_count == 2)
        {
          /* glibc behaviour.  */
          assert(non_options_count == 2);
          assert(strcmp (non_options[0], "donald") == 0);
          assert(strcmp (non_options[1], "duck") == 0);
          assert(unrecognized == 0);
          assert(optind == 7);
        }
      else
        {
          /* Another valid behaviour.  */
          assert(non_options_count == 7);
          assert(strcmp (non_options[0], "donald") == 0);
          assert(strcmp (non_options[1], "duck") == 0);
          assert(strcmp (non_options[2], "-b") == 0);
          assert(strcmp (non_options[3], "foo") == 0);
          assert(strcmp (non_options[4], "-q") == 0);
          assert(strcmp (non_options[5], "johnny") == 0);
          assert(strcmp (non_options[6], "bar") == 0);
          assert(unrecognized == 0);
          assert(optind == 12);
        }
    }

  /* Check that the '-' flag has to come first.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "donald";
      argv[argc++] = "-p";
      argv[argc++] = "billy";
      argv[argc++] = "duck";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "abp:q:-",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      if (posixly)
        {
          assert(strcmp (argv[0], "program") == 0);
          assert(strcmp (argv[1], "donald") == 0);
          assert(strcmp (argv[2], "-p") == 0);
          assert(strcmp (argv[3], "billy") == 0);
          assert(strcmp (argv[4], "duck") == 0);
          assert(strcmp (argv[5], "-a") == 0);
          assert(strcmp (argv[6], "bar") == 0);
          assert(argv[7] == NULL);
          assert(a_seen == 0);
          assert(b_seen == 0);
          assert(p_value == NULL);
          assert(q_value == NULL);
          assert(non_options_count == 0);
          assert(unrecognized == 0);
          assert(optind == 1);
          assert(!output);
        }
      else
        {
          assert(strcmp (argv[0], "program") == 0);
          assert(strcmp (argv[1], "-p") == 0);
          assert(strcmp (argv[2], "billy") == 0);
          assert(strcmp (argv[3], "-a") == 0);
          assert(strcmp (argv[4], "donald") == 0);
          assert(strcmp (argv[5], "duck") == 0);
          assert(strcmp (argv[6], "bar") == 0);
          assert(argv[7] == NULL);
          assert(a_seen == 1);
          assert(b_seen == 0);
          assert(p_value != NULL && strcmp (p_value, "billy") == 0);
          assert(q_value == NULL);
          assert(non_options_count == 0);
          assert(unrecognized == 0);
          assert(optind == 4);
          assert(!output);
        }
    }

  /* Check that the '+' flag causes the first non-option to terminate the
     loop.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "donald";
      argv[argc++] = "-p";
      argv[argc++] = "billy";
      argv[argc++] = "duck";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "+abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(strcmp (argv[0], "program") == 0);
      assert(strcmp (argv[1], "donald") == 0);
      assert(strcmp (argv[2], "-p") == 0);
      assert(strcmp (argv[3], "billy") == 0);
      assert(strcmp (argv[4], "duck") == 0);
      assert(strcmp (argv[5], "-a") == 0);
      assert(strcmp (argv[6], "bar") == 0);
      assert(argv[7] == NULL);
      assert(a_seen == 0);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 1);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-+";
      argv[argc] = NULL;
      optind = start;
      getopt_loop (argc, argv, "+abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 0);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == '+');
      assert(optind == 2);
      assert(output);
    }

  /* Check that '--' ends the argument processing.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[20];

      argv[argc++] = "program";
      argv[argc++] = "donald";
      argv[argc++] = "-p";
      argv[argc++] = "billy";
      argv[argc++] = "duck";
      argv[argc++] = "-a";
      argv[argc++] = "--";
      argv[argc++] = "-b";
      argv[argc++] = "foo";
      argv[argc++] = "-q";
      argv[argc++] = "johnny";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "+abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(strcmp (argv[0], "program") == 0);
      assert(strcmp (argv[1], "donald") == 0);
      assert(strcmp (argv[2], "-p") == 0);
      assert(strcmp (argv[3], "billy") == 0);
      assert(strcmp (argv[4], "duck") == 0);
      assert(strcmp (argv[5], "-a") == 0);
      assert(strcmp (argv[6], "--") == 0);
      assert(strcmp (argv[7], "-b") == 0);
      assert(strcmp (argv[8], "foo") == 0);
      assert(strcmp (argv[9], "-q") == 0);
      assert(strcmp (argv[10], "johnny") == 0);
      assert(strcmp (argv[11], "bar") == 0);
      assert(argv[12] == NULL);
      assert(a_seen == 0);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 1);
      assert(!output);
    }
#endif /* GNULIB_TEST_GETOPT_GNU */

  /* Check that the '+' flag has to come first.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "donald";
      argv[argc++] = "-p";
      argv[argc++] = "billy";
      argv[argc++] = "duck";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "abp:q:+",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      if (posixly)
        {
          assert(strcmp (argv[0], "program") == 0);
          assert(strcmp (argv[1], "donald") == 0);
          assert(strcmp (argv[2], "-p") == 0);
          assert(strcmp (argv[3], "billy") == 0);
          assert(strcmp (argv[4], "duck") == 0);
          assert(strcmp (argv[5], "-a") == 0);
          assert(strcmp (argv[6], "bar") == 0);
          assert(argv[7] == NULL);
          assert(a_seen == 0);
          assert(b_seen == 0);
          assert(p_value == NULL);
          assert(q_value == NULL);
          assert(non_options_count == 0);
          assert(unrecognized == 0);
          assert(optind == 1);
          assert(!output);
        }
      else
        {
          assert(strcmp (argv[0], "program") == 0);
          assert(strcmp (argv[1], "-p") == 0);
          assert(strcmp (argv[2], "billy") == 0);
          assert(strcmp (argv[3], "-a") == 0);
          assert(strcmp (argv[4], "donald") == 0);
          assert(strcmp (argv[5], "duck") == 0);
          assert(strcmp (argv[6], "bar") == 0);
          assert(argv[7] == NULL);
          assert(a_seen == 1);
          assert(b_seen == 0);
          assert(p_value != NULL && strcmp (p_value, "billy") == 0);
          assert(q_value == NULL);
          assert(non_options_count == 0);
          assert(unrecognized == 0);
          assert(optind == 4);
          assert(!output);
        }
    }

#if GNULIB_TEST_GETOPT_GNU
  /* If GNU extensions are supported, require compliance with POSIX
     interpretation on leading '+' behavior.
     http://austingroupbugs.net/view.php?id=191  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "donald";
      argv[argc++] = "-p";
      argv[argc++] = "billy";
      argv[argc++] = "duck";
      argv[argc++] = "-a";
      argv[argc++] = "bar";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      getopt_loop (argc, argv, "+:abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(strcmp (argv[0], "program") == 0);
      assert(strcmp (argv[1], "donald") == 0);
      assert(strcmp (argv[2], "-p") == 0);
      assert(strcmp (argv[3], "billy") == 0);
      assert(strcmp (argv[4], "duck") == 0);
      assert(strcmp (argv[5], "-a") == 0);
      assert(strcmp (argv[6], "bar") == 0);
      assert(argv[7] == NULL);
      assert(a_seen == 0);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 0);
      assert(optind == 1);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-p";
      argv[argc] = NULL;
      optind = start;
      getopt_loop (argc, argv, "+:abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 0);
      assert(b_seen == 0);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 'p');
      assert(optind == 2);
      assert(!output);
    }
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int a_seen = 0;
      int b_seen = 0;
      const char *p_value = NULL;
      const char *q_value = NULL;
      int non_options_count = 0;
      const char *non_options[10];
      int unrecognized = 0;
      bool output;
      int argc = 0;
      const char *argv[10];

      argv[argc++] = "program";
      argv[argc++] = "-b";
      argv[argc++] = "-p";
      argv[argc] = NULL;
      optind = start;
      getopt_loop (argc, argv, "+:abp:q:",
                   &a_seen, &b_seen, &p_value, &q_value,
                   &non_options_count, non_options, &unrecognized, &output);
      assert(a_seen == 0);
      assert(b_seen == 1);
      assert(p_value == NULL);
      assert(q_value == NULL);
      assert(non_options_count == 0);
      assert(unrecognized == 'p');
      assert(optind == 3);
      assert(!output);
    }

  /* Check that 'W' does not dump core:
     https://sourceware.org/bugzilla/show_bug.cgi?id=12922
     Technically, POSIX says the presence of ';' in the opt-string
     gives unspecified behavior, so we only test this when GNU compliance
     is desired.  */
  for (start = OPTIND_MIN; start <= 1; start++)
    {
      int argc = 0;
      const char *argv[10];
      int pos = ftell (stderr);

      argv[argc++] = "program";
      argv[argc++] = "-W";
      argv[argc++] = "dummy";
      argv[argc] = NULL;
      optind = start;
      opterr = 1;
      assert(getopt (argc, (char **) argv, "W;") == 'W');
      assert(ftell (stderr) == pos);
      assert(optind == 2);
    }
#endif /* GNULIB_TEST_GETOPT_GNU */
}
