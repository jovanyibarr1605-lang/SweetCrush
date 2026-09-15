cmake_minimum_required(VERSION 3.19)
project(SweetCrush LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(SweetCrush
    main.cpp
    tablero.h
    tablero.cpp
    combinaciones.h
    combinaciones.cpp
    visualizacion.h
    visualizacion.cpp
)

target_link_libraries(SweetCrush
    PRIVATE
        Qt::Core
)

install(TARGETS SweetCrush
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
