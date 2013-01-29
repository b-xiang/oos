/*
 * This file is part of OpenObjectStore OOS.
 *
 * OpenObjectStore OOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenObjectStore OOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenObjectStore OOS. If not, see <http://www.gnu.org/licenses/>.
 */

#include "tools/library.hpp"

#include <unistd.h>

namespace oos {

library::library()
  : handle_(0)
{}

library::library(const std::string &lib)
  : lib_(lib)
  , handle_(0)
{}

library::~library()
{
  unload();
}

bool library::load()
{
#ifdef WIN32
  handle_ = LoadLibrary((lib_ + ".dll").c_str());
#else
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL)
    fprintf(stdout, "Current working dir: %s\n", cwd);
  else
    perror("getcwd() error");
  fprintf(stdout, "try to open [%s]\n", std::string("lib" + lib_ + ".so").c_str());
  handle_ = dlopen(std::string("lib" + lib_ + ".so").c_str(), RTLD_LAZY);
#endif
  if (!handle_) {
    fprintf(stdout, "dlopen error: %s", dlerror());
    return false;
  }
  return true;
}

bool library::load(const std::string &lib)
{
  if (handle_) {
    return false;
  }
  lib_ = lib;
  return load();
}

bool library::unload()
{
  bool ret(true);
  if (handle_) {
#ifdef WIN32
    ret = FreeLibrary(handle_) == TRUE;
#else
    ret = dlclose(handle_) == 0;
#endif
    if (!ret) {
    } else {
      handle_ = 0;
    }
  }
  return ret;
}

func_ptr library::function(const std::string &f) const
{
#ifdef WIN32
  return GetProcAddress(handle_, f.c_str());
#else
  return dlsym(handle_, f.c_str());
#endif
}

}
