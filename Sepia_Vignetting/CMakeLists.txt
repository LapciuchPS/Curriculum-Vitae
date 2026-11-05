cmake_minimum_required(VERSION 3.19)
project(Sepia_Vignetting LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Sepia_Vignetting
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    popupwindow.h popupwindow.cpp popupwindow.ui
    effects.h effects.cpp
)

target_link_libraries(Sepia_Vignetting
    PRIVATE
        Qt::Core
        Qt::Widgets
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/ImageEffectsCPP.lib
)

target_include_directories(Sepia_Vignetting
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

install(TARGETS Sepia_Vignetting
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Sepia_Vignetting
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
