cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME XmlEditor)
set(TEST_NAME test_${PROJECT_NAME})

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(${PROJECT_NAME} VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(${PROJECT_NAME})
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PATHS
    Widgets/
    Tools/
    Serialization/
    Serialization/pugi/
)

file(GLOB HRDS
    *.h
    Tools/*.h
    Widgets/*.h
    Serialization/*.h
    Serialization/pugi/*.hpp
)
file(GLOB SRCS
    FilterDataModel.cpp
    TableModel.cpp
    SettingsModel.cpp
    ListItemDelegate.cpp
    MathFunc.cpp
    Tools/*.cpp
    Widgets/*.cpp
    Serialization/*.cpp
    Serialization/pugi/*.cpp
)

add_executable( ${PROJECT_NAME} ${SRCS} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_LIST_DIR}
)
target_include_directories(${PROJECT_NAME} PRIVATE ${PATHS})

target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

file(GLOB TEST_SRCS
    Tests/*.cpp
)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(${TEST_NAME}
    ${SRCS}
    ${TEST_SRCS}
)

target_include_directories(${TEST_NAME} PUBLIC
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_include_directories(${TEST_NAME} PRIVATE
    ${PATHS}
    ${CMAKE_BINARY_DIR}
    )
target_link_libraries(${TEST_NAME} PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${TEST_NAME} PRIVATE ${LIBRARY_NAME})
target_link_libraries(${TEST_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TEST_NAME} PRIVATE pthread)
target_link_libraries(${TEST_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(${TEST_NAME} PRIVATE
        /W4
    )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${TEST_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
enable_testing()

add_test(${TEST_NAME} ${TEST_NAME})
