# Generic test that uses conan libs
add_executable(master-mind master-mind.cpp)
target_link_libraries(
  master-mind
  PRIVATE project_options
          project_warnings
          CONAN_PKG::docopt.cpp
          CONAN_PKG::fmt
          CONAN_PKG::spdlog)
