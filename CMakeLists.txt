cmake_minimum_required(VERSION 2.8.3)
project(refill_checker)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  std_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES refill_checker
#  CATKIN_DEPENDS cv_bridge roscpp std_msgs
#  DEPENDS system_lib
)

include_directories( include
  ${catkin_INCLUDE_DIRS}
)


add_executable(check src/check.cpp)

target_link_libraries(check
  ${catkin_LIBRARIES}
)