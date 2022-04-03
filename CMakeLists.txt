# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


cmake_minimum_required(VERSION 3.1...3.15)

project( AABB_Test )


find_package(CGAL REQUIRED)

set(EXECUTABLE_OUTPUT_PATH "bin")
# set(CMAKE_BUILD_TYPE "Release")

# include_directories(geometry)

# aux_source_directory(geometry SRC_LIST)

file(GLOB GEOMETRY_SRC_FILES geometry/*.cpp)
add_library(geometry STATIC ${GEOMETRY_SRC_FILES})
target_include_directories(geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/geometry)

add_executable(collision_detection collision_detection_kidney.cpp)
add_executable(boolean_operation boolean_operation.cpp)

target_link_libraries(collision_detection geometry)
target_link_libraries(boolean_operation geometry)

set(TINYGLTF_HEADER_ONLY ON CACHE INTERNAL "" FORCE)
set(TINYGLTF_INSTALL OFF CACHE INTERNAL "" FORCE)
add_subdirectory(tinygltf)

# if ( CGAL_FOUND )

#   # create a target per cppfile
#     # create_single_source_cgal_program( "collision_detection.cpp")

# else()
  
#     message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
# endif()

if ( CGAL_AUTO_LINK_ENABLED )
  target_link_libraries(collision_detection ${CGAL_3RD_PARTY_LIBRARIES})
  target_link_libraries(boolean_operation ${CGAL_3RD_PARTY_LIBRARIES})
else()
  target_link_libraries(collision_detection ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
  target_link_libraries(boolean_operation ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
endif()


find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(collision_detection OpenMP::OpenMP_CXX)
endif()


set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(boolean_operation ${Boost_LIBRARIES})
endif()


