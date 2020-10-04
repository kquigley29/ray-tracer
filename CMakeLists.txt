project(raytracer)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Release)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(include
        ${OpenCV_INCLUDE_DIRS})

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

add_library(${PROJECT_NAME}lib
        src/Camera.cpp
        src/Scene.cpp
        src/utils.cpp
        )

target_link_libraries(${PROJECT_NAME}lib
        objects
        lights
        pthread
        Eigen3::Eigen
        ${OpenCV_LIBS}
        )

add_executable(${PROJECT_NAME}
        src/raytracer.cpp
        )

target_link_libraries(${PROJECT_NAME}
        ${PROJECT_NAME}lib
        )
