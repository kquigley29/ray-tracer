project(raytracer)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Release)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Eigen3_INCLUDE_DIRS})
MESSAGE("Eigen3 include:    ${EIGEN3_INCLUDE_DIRS}")
MESSAGE("OpenCV include:    ${OpenCV_INCLUDE_DIRS}")

add_library(objects
        src/objects/Object.cpp
        src/objects/Sphere.cpp
        src/objects/Plane.cpp
        src/objects/Disc.cpp
        )

add_library(lights
        src/lights/Light.cpp
        src/lights/PointLight.cpp
        )

add_library(${PROJECT_NAME}
        src/Camera.cpp
        src/Scene.cpp
        src/utils.cpp
        src/parser.cpp
        )

target_link_libraries(${PROJECT_NAME}
        objects
        lights
        pthread
        Eigen3::Eigen
        ${OpenCV_LIBS}
        )

add_executable(trace
        src/main.cpp
        )

target_link_libraries(trace
        ${PROJECT_NAME}
        )

set_target_properties(trace ${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
