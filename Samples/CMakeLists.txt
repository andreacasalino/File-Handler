option(BUILD_01 "Build Sample 1" ON)
if(BUILD_01)
add_subdirectory(./Sample_01) 
endif()

option(BUILD_02 "Build Sample 2" ON)
if(BUILD_02)
add_subdirectory(./Sample_02) 
endif()

option(BUILD_03 "Build Sample 3" ON)
if(BUILD_03)
add_subdirectory(./Sample_03) 
endif()

