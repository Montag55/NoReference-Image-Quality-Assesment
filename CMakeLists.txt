cmake_minimum_required(VERSION 3.5.1)
PROJECT (Quality)

#set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/opencv-4.1.0)
find_package(OpenCV REQUIRED)

set(SRC
    src/main.cpp
    src/spatialdomain.cpp
)

set(HEADERS       
    include/spatialdomain.hpp
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable( Quality ${SRC} ${HEADERS})

target_link_libraries( Quality ${OpenCV_LIBS})