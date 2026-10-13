cmake_minimum_required(VERSION 3.19)
project(Nazwa_do_ustalenia_po_zatwierdzeniu LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Nazwa_do_ustalenia_po_zatwierdzeniu
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    popupwindow.h popupwindow.cpp popupwindow.ui
)

target_link_libraries(Nazwa_do_ustalenia_po_zatwierdzeniu
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Nazwa_do_ustalenia_po_zatwierdzeniu
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Nazwa_do_ustalenia_po_zatwierdzeniu
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
