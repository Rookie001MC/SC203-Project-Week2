cmake_minimum_required(VERSION 3.15)

project(benchmark_sorting_algos)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME}
        main.cpp
        sort_algos/enhanced.cpp
        sort_algos/counting_cocktail.cpp
        sort_algos/traditionals.cpp
        sort_algos/sorting_algo.hpp
        sort_algos/quicksort.cpp
 )
