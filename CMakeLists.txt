﻿cmake_minimum_required(VERSION 3.5)

project(AllStudy_project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES AllStudy_project_zh_CN.ts)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(PROJECT_SOURCES
        src/main.cpp

        src/mainwindow.cpp
        src/DesignModel/observer.cpp
        src/DesignModel/subject.cpp
        src/Game_2048/core/board.cpp
        src/Game_2048/core/tile.cpp
        src/Game_2048/core/game.cpp
        src/Game_2048/gui/qgameboard.cpp
        src/Game_2048/gui/qgameoverwindow.cpp
        src/Game_2048/gui/qtile.cpp
        src/Game_2048/gui/qresetbutton.cpp


        include/mainwindow.h
        include/DesignModel/observer.h
        include/DesignModel/subject.h
        include/Game_2048/core/board.h
        include/Game_2048/core/tile.h
        include/Game_2048/core/game.h
        include/Game_2048/gui/qgameboard.h
        include/Game_2048/gui/qgameoverwindow.h
        include/Game_2048/gui/qtile.h
        include/Game_2048/gui/qresetbutton.h

        ui/mainwindow.ui


        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AllStudy_project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AllStudy_project APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(AllStudy_project SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AllStudy_project
            ${PROJECT_SOURCES}


            # src/Design_model/observer.h src/Design_model/observer.cpp
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(AllStudy_project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AllStudy_project)
endif()
set_target_properties(AllStudy_project PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
include_directories(include)
include(GNUInstallDirs)
install(TARGETS AllStudy_project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
# 获得qmake所在路径(Qt5.15.2/5.15.2/msvc2019_64/bin/qmake.exe)
# get_target_property(qmake_exec_filepath Qt5::qmake IMPORTED_LOCATION)
# qt bin所在目录 (Qt5.15.2/5.15.2/msvc2019_64/bin)
# get_filename_component(qt_exec_bin_dir "${qmake_exec_filepath}" DIRECTORY)
# windeployqt所在路径(Qt5.15.2/5.15.2/msvc2019_64/bin/windeployqt.exe)
# find_program(windeployqt_exec_filepath windeployqt HINTS "${qt_exec_bin_dir}")
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND "${CMAKE_COMMAND}" -E
#         COMMENT "Running windeployqt..."
#         )



if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AllStudy_project)
endif()
