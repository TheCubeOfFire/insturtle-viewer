cmake_minimum_required(VERSION 3.0)

project(InsturtleViewer
    VERSION 0.1.0
)

find_package(gf REQUIRED)

add_executable(insturtle-viewer
    main.cpp
)

target_link_libraries(insturtle-viewer
    gf::gf0
)
