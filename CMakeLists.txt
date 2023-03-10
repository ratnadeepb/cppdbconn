cmake_minimum_required(VERSION 3.3)
project(dbconn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
# file(GLOB_RECURSE sources      src/*.cc include/*.hpp)
file(GLOB_RECURSE sources *.cc)
# file(GLOB_RECURSE sources_test src/test/*.cc)
# file(GLOB_RECURSE data resources/*)
# you can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically
# set(HDR_FILES includes/dbconn.hpp)
# set(SRC_FILES src/dbconn.cc)
include_directories(/usr/include/mysql)

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
# add_executable(dbconn ${sources} ${data})
add_executable(dbconn ${sources})

# just for example add some compiler flags
target_compile_options(dbconn PUBLIC -std=c++20 -Wall -Wfloat-conversion -lsoci_core -lsoci_mysql -ldl -lmysqlclient)

# include_directories(/mydata/cpp/soci-4.0.3/include)
# this lets me include files relative to the root source directory with a <> pair
# target_include_directories(dbconn PUBLIC src/main)

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executable
# file(COPY ${data} DESTINATION resources)

###############################################################################
## dependencies ###############################################################
###############################################################################

# this defines the variables Boost_LIBRARIES that contain all library names
# that we need to link to
# find_package(Boost 1.36.0 COMPONENTS filesystem system REQUIRED)

# target_link_libraries(dbconn PUBLIC
#   ${Boost_LIBRARIES}
#   # here you can add any library dependencies
# )

# link_directories(/usr/lib/mysql)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(mysql)
target_link_libraries(dbconn ${MYSQL_LIBRARY})

link_directories("/mydata/cpp/soci-4.0.3/build/lib/")
target_link_libraries(dbconn soci_mysql)
target_link_libraries(dbconn soci_core)

###############################################################################
## testing ####################################################################
###############################################################################

# this is for our testing framework
# we don't add REQUIRED because it's just for testing
find_package(GTest)

if(GTEST_FOUND)
  add_executable(unit_tests ${sources_test} ${sources})

  # we add this define to prevent collision with the main
  # this might be better solved by not adding the source with the main to the
  # testing target
  target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

  # this allows us to use our executable as a link library
  # therefore we can inherit all compiler options and library dependencies
  set_target_properties(dbconn PROPERTIES ENABLE_EXPORTS on)

  target_link_libraries(unit_tests PUBLIC
    ${GTEST_BOTH_LIBRARIES}
    dbconn
  )

  target_include_directories(unit_tests PUBLIC
    ${GTEST_INCLUDE_DIRS} # doesn't do anything on Linux
  )
endif()

###############################################################################
## packaging ##################################################################
###############################################################################

# all install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS dbconn DESTINATION dbconn_destination)
# this is basically a repeat of the file copy instruction that copies the
# resources in the build directory, but here we tell CMake that we want it
# in the package
install(DIRECTORY resources DESTINATION dbconn_destination)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "DBconn")
set(CPACK_PACKAGE_VERSION "1.0.0")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)
