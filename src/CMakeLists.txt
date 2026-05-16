include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(iterator STATIC 
    iterator/iterator.hpp
    iterator/iterator.cpp
)

add_library(json_reporter STATIC
    json_reporter/json_reporter.hpp
    json_reporter/json_reporter.cpp
)
target_link_libraries(json_reporter PUBLIC
    nlohmann_json_lib
)


add_executable(scanner 
    scanner/scanner.hpp
    scanner/scanner.cpp
    main.cpp
)
target_link_libraries(scanner PRIVATE
    iterator
)