add_executable(${EXE_UTILS_TESTS} TestRunner.cpp)
target_link_libraries(${EXE_UTILS_TESTS} PRIVATE 
    ${LIB_MUTEX}
    ${LIB_SEMAPHORE}
    ${LIB_CONDITIONAL_VARIABLE}
    ${LIB_THREAD}
)