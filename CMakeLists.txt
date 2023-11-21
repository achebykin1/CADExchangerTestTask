cmake_minimum_required(VERSION 3.5.0)
project(GeometricShapes VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(GeometricShapes 
        main.cpp 
        geometricShape.hpp 
        geometricShape.cpp 
        circle.hpp 
        ellipse.hpp 
        helix.hpp 
        circle.cpp 
        ellipse.cpp 
        helix.cpp 
        Geometry.hpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
