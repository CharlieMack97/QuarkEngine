# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-src")
  file(MAKE_DIRECTORY "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-build"
  "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-subbuild/bgfx-populate-prefix"
  "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-subbuild/bgfx-populate-prefix/tmp"
  "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-subbuild/bgfx-populate-prefix/src/bgfx-populate-stamp"
  "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-subbuild/bgfx-populate-prefix/src"
  "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-subbuild/bgfx-populate-prefix/src/bgfx-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-subbuild/bgfx-populate-prefix/src/bgfx-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/new user/OneDrive/Documents/QuarkEngine/build/_deps/bgfx-subbuild/bgfx-populate-prefix/src/bgfx-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
