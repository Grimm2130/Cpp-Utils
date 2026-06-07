cmake_minimum_required(VERSION 3.20.0)

set(LIB_MUTEX "Mutex")
set(LIB_SEMAPHORE "Semaphore")
set(LIB_CONDITIONAL_VARIABLE "ConditionalVariable")
set(LIB_THREAD "Thread")

set(EXE_UTILS_TESTS "UtilsTests")

project(Utils
    VERSION 1.0.0
    LANGUAGES CXX
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/ExternalModules/Templates
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Tests)

