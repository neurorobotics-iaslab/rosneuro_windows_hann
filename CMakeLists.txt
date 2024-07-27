cmake_minimum_required(VERSION 2.8.3)
project(rosneuro_windows_hann)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(ROSNEURO_DATA_MIN_VERSION "1.0.0")

##############################################################################
# Find dependencies
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
			 roscpp 
			 roslib
			 std_msgs
			 pluginlib
			 rosneuro_windows)

find_package(Eigen3 REQUIRED)

find_package(PkgConfig)

SET(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(${catkin_INCLUDE_DIRS} 
                    ${EIGEN3_INCLUDE_DIRS}
					include)

##############################################################################
# Define package
##############################################################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES 
  ${PROJECT_NAME}
	
  CATKIN_DEPENDS
  	roscpp
	roslib
	std_msgs
	pluginlib
	rosneuro_windows
  DEPENDS
)

#################
##	Test	   ##
#################

catkin_add_gtest(TestHann test/TestHann.cpp)
target_link_libraries(TestHann ${GTEST_BOTH_LIBRARIES} pthread gmock ${Eigen3_LIBRARIES})
target_link_libraries(TestHann ${PROJECT_NAME} ${catkin_LIBRARIES})
include_directories(${GTEST_INCLUDE_DIRS} gmock pthread include include/${PROJECT_NAME}/)

##############################################################################
# Build
##############################################################################

add_definitions(${EIGEN3_DEFINITIONS})

## Plugin

# DC Spatial filter
add_library(${PROJECT_NAME} src/Hann.cpp)
target_link_libraries(${PROJECT_NAME} ${Eigen3_LIBRARIES} 
									  ${catkin_LIBRARIES}
)

#################
## Executables ##
#################

add_executable(hann_window example/run.cpp)
target_link_libraries(hann_window ${PROJECT_NAME} ${catkin_LIBRARIES}) 


#################
##   Install   ##
#################
install(TARGETS ${PROJECT_NAME}

	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(FILES plugins_rosneuro_windows_hann.xml
	DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
