#cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(MakingCorrelations)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS}")
  set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
set(CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net EG)
include(${ROOT_USE_FILE})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${binFolder}/MakingCorrelations)
include_directories(${CMAKE_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_CXX_FLAGS})

# SET(KITTY_PATH "${CMAKE_SOURCE_DIR}/GentleKitty")#where are all CATS related .h files
# SET(FORGIVEN_PATH "${CMAKE_SOURCE_DIR}/ForgivingQA")#where are all CATS related .h files
# SET(GAMI_PATH "${CMAKE_SOURCE_DIR}/FemtoGami")#where are all CATS related .h files
# SET(SYSTEMATIC_PATH "${CMAKE_SOURCE_DIR}/Systematics")#where are all CATS related .h files

# include_directories(${KITTY_PATH})
# include_directories(${FORGIVEN_PATH})
# include_directories(${GAMI_PATH})
# include_directories(${SYSTEMATIC_PATH})
# include_directories(${CATS_INCLUDE})
# include_directories("${ROOFOLD}")
include_directories(${PROJECT_SOURCE_DIR})

set(SRCS
  ${PROJECT_SOURCE_DIR}/DreamCF.cxx
  ${PROJECT_SOURCE_DIR}/DreamData.cxx
  ${PROJECT_SOURCE_DIR}/DreamDist.cxx
  #${PROJECT_SOURCE_DIR}/DreamKayTee.cxx
  # ${PROJECT_SOURCE_DIR}/DreamdEtadPhi.cxx
  ${PROJECT_SOURCE_DIR}/DreamPair.cxx
  # ${PROJECT_SOURCE_DIR}/DreamPlot.cxx
  # ${PROJECT_SOURCE_DIR}/DreamHEP.cxx
  # ${PROJECT_SOURCE_DIR}/DreamSystematics.cxx
  ${PROJECT_SOURCE_DIR}/ReadDreamFile.cxx
  )

set(HEADERS
  ${PROJECT_SOURCE_DIR}/DreamCF.h
  ${PROJECT_SOURCE_DIR}/DreamData.h
  ${PROJECT_SOURCE_DIR}/DreamDist.h
  #${PROJECT_SOURCE_DIR}/DreamKayTee.h
  # ${PROJECT_SOURCE_DIR}/DreamdEtadPhi.h
  ${PROJECT_SOURCE_DIR}/DreamPair.h
  # ${PROJECT_SOURCE_DIR}/DreamPlot.h
  # ${PROJECT_SOURCE_DIR}/DreamHEP.h
  # ${PROJECT_SOURCE_DIR}/DreamSystematics.h
  ${PROJECT_SOURCE_DIR}/ReadDreamFile.h
  )
add_library(MakingCorrelations STATIC ${SRCS})
set_target_properties(MakingCorrelations PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
target_link_libraries(MakingCorrelations ${ROOT_LIBRARIES})

add_executable(executeCorrelations_pp ${PROJECT_SOURCE_DIR}/Scripts/ExecuteCorrelations_pp.C)
target_link_libraries(executeCorrelations_pp MakingCorrelations)

