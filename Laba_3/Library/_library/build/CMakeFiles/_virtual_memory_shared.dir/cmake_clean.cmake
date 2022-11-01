file(REMOVE_RECURSE
  "lib_virtual_memory_shared.pdb"
  "lib_virtual_memory_shared.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/_virtual_memory_shared.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
