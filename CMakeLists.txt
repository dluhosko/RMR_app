cmake_minimum_required(VERSION 3.6)
project(robot_demo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    definitions.h
    dijkstra.cpp
    dijkstra.h
    global_planner.cpp
    global_planner.h
    grid_map.h
    irobotcreate.cpp
    irobotcreate.h
    lidar.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mapping.h
    moc_mainwindow.cpp
    navigation.h
    rplidar.cpp
    rplidar.h
    ui_mainwindow.h)

add_executable(robot_demo ${SOURCE_FILES})