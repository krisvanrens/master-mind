add_executable(master-mind-cli master-mind-cli.cpp)
target_link_libraries(
  master-mind-cli
  PRIVATE project_options
          project_warnings)
