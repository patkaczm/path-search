cmake_minimum_required(VERSION 3.14)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

set(PROJECT_SOURCES
        main.cpp
        ${CMAKE_BASE_LIST_DIR}/qml.qrc
)

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    qt_add_executable(path-search
#        ${PROJECT_SOURCES}
#    )
#else()
#    if(ANDROID)
#        add_library(path-search SHARED
#            ${PROJECT_SOURCES}
#        )
#    else()
#        add_executable(path-search
#          ${PROJECT_SOURCES}
#        )
#    endif()
#endif()

add_subdirectory(Graph)
add_subdirectory(Grid)
add_subdirectory(Algorithm)
add_subdirectory(Backend)

add_executable(path-search ${PROJECT_SOURCES})

target_compile_definitions(path-search
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(path-search
  PRIVATE ${QtLib} BackendLib)
