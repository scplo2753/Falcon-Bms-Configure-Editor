cmake_minimum_required(VERSION 3.16)

project(BMSConfigure VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES BMSConfigure_zh_CN.ts)

set(LOCALIZATION_DIR "${CMAKE_SOURCE_DIR}/Localization")
set(BUILD_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

add_custom_target(copy_json_files
    COMMAND ${CMAKE_COMMAND} -E copy
         "${LOCALIZATION_DIR}/MP.cfg.json"
         "${LOCALIZATION_DIR}/Comm.cfg.json"
         "${LOCALIZATION_DIR}/Graphic.cfg.json"
         "${LOCALIZATION_DIR}/HotasAndKey.cfg.json"
         "${LOCALIZATION_DIR}/Other.cfg.json"
         "${LOCALIZATION_DIR}/VR.cfg.json"
         "${BUILD_OUTPUT_DIR}/"
    COMMENT "Copying JSON configuration files..."
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BMSConfigure
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/mpitemmodel.h src/mpitemmodel.cpp
        src/cfgreader.h src/cfgreader.cpp
        src/usercfgreader.h src/usercfgreader.cpp
        src/userdefinejsonmanager.h src/userdefinejsonmanager.cpp
        resources.qrc

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BMSConfigure APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(BMSConfigure SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BMSConfigure
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

add_dependencies(BMSConfigure copy_json_files)

target_link_libraries(BMSConfigure PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BMSConfigure)
endif()
set_target_properties(BMSConfigure PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS BMSConfigure
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BMSConfigure)
endif()
