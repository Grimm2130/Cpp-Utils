add_library(${LIB_MUTEX} STATIC Mutex.cpp)

add_library(${LIB_SEMAPHORE} STATIC Semaphore.cpp )

add_library(${LIB_CONDITIONAL_VARIABLE} STATIC ConditionalVariable.cpp)
target_link_libraries(${LIB_CONDITIONAL_VARIABLE} PUBLIC ${LIB_MUTEX})

add_library(${LIB_THREAD} STATIC Thread.cpp)