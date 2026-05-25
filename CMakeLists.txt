cmake_minimum_required(VERSION 3.19)
project(ABChat LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Widgets
    Network
)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    logindialog.h logindialog.cpp logindialog.ui
    rc.qrc
    registerdialog.h registerdialog.cpp registerdialog.ui
    global.h global.cpp
)

if(WIN32)
    list(APPEND SOURCES app.rc)
endif()

qt_add_executable(ABChat
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
    singleton.h
    httpmgr.h httpmgr.cpp
)

target_link_libraries(ABChat
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

include(GNUInstallDirs)

install(TARGETS ABChat
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ABChat
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
