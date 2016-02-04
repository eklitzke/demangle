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

#include <iostream>
#include <getopt.h>
#include <stdlib.h>
#include <cxxabi.h>

static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                       {0, 0, 0, 0}};

static void demangle(const char *mangled_name) {
  int status = 0;
  const char *realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
  switch (status) {
  case 0:
    std::cout << realname << "  " << mangled_name << "\n";
    break;
  case -1:
    std::cout << "FAIL: failed to allocate memory while demangling "
              << mangled_name << "\n";
    break;
  case -2:
    std::cout << "FAIL: " << mangled_name << " is not a valid name under "
              << "the C++ ABI mangling runles\n";
    break;
  default:
    std::cout << "FAIL: some other unexpected error\n";
    break;
  }
  if (realname != NULL) {
    free((void *)realname);
  }
}

int main(int argc, char **argv) {
  int c;
  for (;;) {
    int option_index = 0;
    c = getopt_long(argc, argv, "h", long_options, &option_index);
    if (c == -1) {
      break;
    }
    switch (c) {
    case 'h':
      std::cout << "usage: " << argv[1] << " [-h|--help] [MANGLED]...\n";
      return 0;
    case '?':
      break;
    default:
      abort();
    }
  }

  for (int i = optind; i < argc; i++) {
    demangle(argv[i]);
  }
}
