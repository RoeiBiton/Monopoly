# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Monopoly_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Monopoly_autogen.dir/ParseCache.txt"
  "Monopoly_autogen"
  )
endif()
