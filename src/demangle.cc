// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <cxxabi.h>

#if defined(__clang__)
static const char personality[] = "Clang/LLVM";
#elif defined(__ICC) || defined(__INTEL_COMPILER)
static const char personality[] = "Intel ICC/ICPC";
#elif defined(__GNUC__) || defined(__GNUG__)
static const char personality[] = "GNU GCC/G++";
#elif defined(_MSC_VER)
static const char personality[] = "Microsoft Visual Studio";
#else
static const char personality[] = "Unknown";
#endif

static void demangle(const char *mangled_name, bool quiet) {
  int status = 0;
  const char *realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
  switch (status) {
  case 0:
    if (quiet) {
      puts(realname);
    } else {
      printf("%s  %s\n", realname, mangled_name);
    }
    break;
  case -1:
    printf("FAIL: failed to allocate memory while demangling %s\n",
           mangled_name);
    break;
  case -2:
    printf("FAIL: %s is not a valid name under the C++ ABI mangling rules\n",
           mangled_name);
    break;
  default:
    printf("FAIL: some other unexpected error: %d\n", status);
    break;
  }
  free((void *)realname);
}

int main(int argc, char **argv) {
  int c;
  bool quiet = false;
  for (;;) {
    static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                           {"personality", no_argument, 0, 'p'},
                                           {"quiet", no_argument, 0, 'q'},
                                           {0, 0, 0, 0}};
    int option_index = 0;
    c = getopt_long(argc, argv, "hpq", long_options, &option_index);
    if (c == -1) {
      break;
    }
    switch (c) {
    case 'h':
      printf("Usage: %s [-h|--help] [-p|--personality] [-q|--quiet] "
             "[MANGLED]...\n", argv[0]);
      return 0;
    case 'p':
      printf("Personality: %s\n", personality);
      break;
    case 'q':
      quiet = true;
      break;
    case '?':
    default:
      printf("Option '-%c' is invalid: ignored\n", optopt);
      break;
    }
  }
  
  // demangle args else stdin
  if (argc > optind) {
    for (int i = optind; i < argc; i++) {
      demangle(argv[i], quiet);
    }
  } else {
    char buf[100];
    while (fgets (buf, sizeof(buf), stdin)) {
      char *newline = strchr (buf, '\n');
      if (newline) {
        *newline = '\0';
      }
      demangle(buf, quiet);
    }
  }
}
