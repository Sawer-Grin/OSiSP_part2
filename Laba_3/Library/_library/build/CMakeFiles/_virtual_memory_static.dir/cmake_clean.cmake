file(REMOVE_RECURSE
  "lib_virtual_memory_static.a"
  "lib_virtual_memory_static.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/_virtual_memory_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
