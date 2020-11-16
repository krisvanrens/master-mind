add_library(
  helpers
  STATIC helpers.cpp)
target_link_libraries(
  helpers
  PRIVATE project_options
          project_warnings)

add_library(
  solvers
  STATIC solvers/naive.cpp
         solvers/brute-force.cpp
         solvers/knuth.cpp
         solvers/optimal.cpp
         solvers/solver.cpp)
target_link_libraries(
  solvers
  PRIVATE project_options
          project_warnings
          helpers
          CONAN_PKG::fmt)

add_executable(master-mind-cli master-mind-cli.cpp)
target_link_libraries(
  master-mind-cli
  PRIVATE project_options
          project_warnings
          helpers
          CONAN_PKG::docopt.cpp)

add_executable(master-mind-solver master-mind-solver.cpp)
target_link_libraries(
  master-mind-solver
  PRIVATE project_options
          project_warnings
          helpers
          solvers
          CONAN_PKG::docopt.cpp
          CONAN_PKG::fmt)
