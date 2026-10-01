cmake_minimum_required(VERSION 3.16)
project(etiquette_demos LANGUAGES CXX)

# Standard settings applied to every target below.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /EHsc)
else()
    add_compile_options(-Wall -Wextra)
endif()

find_package(Threads REQUIRED)
find_package(OpenMP)   # optional: the OpenMP demos still build serially without it

add_executable(01_containers           01_containers.cpp)
add_executable(02_algorithms_lambdas   02_algorithms_lambdas.cpp)
add_executable(03_class                03_class/main.cpp 03_class/Vector2D.cpp)   # 2 translation units
add_executable(04_raii_smart_pointers  04_raii_smart_pointers.cpp)
add_executable(05_polymorphism         05_polymorphism_range_for.cpp)
add_executable(06_dynamic_programming  06_dynamic_programming.cpp)

foreach(t 07_threads_mutex_atomic 08_async_future 09_condition_variable_scoped_lock)
    add_executable(${t} ${t}.cpp)
    target_link_libraries(${t} PRIVATE Threads::Threads)
endforeach()

foreach(t 10_openmp_loops 11_openmp_tasks)
    add_executable(${t} ${t}.cpp)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${t} PRIVATE OpenMP::OpenMP_CXX)
    endif()
endforeach()
