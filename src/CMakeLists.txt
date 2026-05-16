include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(iterator STATIC 
    iterator/iterator.hpp
    iterator/iterator.cpp
)

add_executable(scanner 
    scanner/scanner.hpp
    scanner/scanner.cpp
    main.cpp
)
target_link_libraries(scanner PRIVATE
    iterator
)