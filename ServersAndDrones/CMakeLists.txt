#cmake_minimum_required(VERSION 3.15)
#project(ServersAndDrones)
#
#set(CMAKE_CXX_STANDARD 14)
#
#add_executable(ServersAndDrones main.cpp)

cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME ServersAndDrones)
set(PROJECT_FILES main.cpp Field.cpp Field.h Server.cpp Server.h Vector2D.cpp
        Vector2D.h FieldDraw.cpp FieldDraw.h Triangle.cpp Triangle.h determinant.cpp determinant.h Polygon.cpp Polygon.h Drone.cpp Drone.h)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

IF (WIN32)
    message(STATUS ">>> Win32")
    add_compile_definitions(USE_FREEGLUT)
    set(GLUT_DIR F:/freeglut-3.0.0)
    set(GLUT_INTERFACE_DIRS  ../glutInterface)
    set(GLUT_INTERFACE_LIB_DIRS  ../glutInterface/cmake-build-debug)
    set(CMAKE_PREFIX_PATH FREEGLUT)

    set(FREEGLUT_INCLUDE_DIRS F:/freeglut-3.0.0/include)
    set(FREEGLUT_LIBRARY_DIRS F:/freeglut-3.0.0/cmake-build-debug/lib)
    set(FREEGLUT_LIBRARIES freeglutd.lib)

    find_package(OPENGL REQUIRED)

    include_directories(${FREEGLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLUT_INTERFACE_DIRS})
    link_directories(${FREEGLUT_LIBRARY_DIRS} ${OPENGL_LIBRARY_DIRS} ${GLUT_INTERFACE_LIB_DIRS})
    add_definitions(${FREEGLUT_DEFINITIONS} ${OPENGL_DEFINITIONS})
    add_executable(${PROJECT_NAME} ${PROJECT_FILES})
    target_link_libraries(${PROJECT_NAME} ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} glutInterface.lib)
ENDIF (WIN32)

IF(LINUX)
    message(STATUS ">>> LINUX")
    add_compile_definitions(USE_FREEGLUT)

    SET(GLUT_INCLUDE_DIR /usr/include)
    SET(GLUT_glut_LIBRARY /usr/lib/x86_64-linux-gnu/libglut.so)
    set(GLUT_INTERFACE_DIRS  ../../glutInterface)
    set(GLUT_INTERFACE_LIB_DIRS  ../../glutInterface/cmake-build-debug)

    find_package(GLUT REQUIRED)
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    if(NOT GLUT_FOUND)
        message(ERROR " GLUT not found!")
    endif(NOT GLUT_FOUND)

    find_package(OpenGL REQUIRED)

    include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLUT_INTERFACE_DIRS} )
    link_directories(${FREEGLUT_LIBRARY_DIRS} ${OPENGL_LIBRARY_DIRS} ${GLUT_INTERFACE_LIB_DIRS})
    add_definitions(${FREEGLUT_DEFINITIONS} ${OPENGL_DEFINITIONS})
    add_executable(${PROJECT_NAME} ${PROJECT_FILES})
    target_link_libraries(${PROJECT_NAME} ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} libglutInterface.so)
ENDIF(LINUX)

IF (APPLE)
    message(STATUS ">>> APPLE")
    set(GLUT_INTERFACE_DIRS  ../glutInterface)
    set(GLUT_INTERFACE_LIB_DIRS  ../glutInterface/cmake-build-debug)

    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLUT_INTERFACE_DIRS})
    link_directories(${OPENGL_LIBRARY_DIRS} ${GLUT_INTERFACE_LIB_DIRS})
    add_executable(${PROJECT_NAME} ${PROJECT_FILES})
    target_link_libraries(${PROJECT_NAME} ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} libglutInterface.dylib)
ENDIF(APPLE)