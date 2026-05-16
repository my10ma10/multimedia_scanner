include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(socket_lib STATIC 
    socket/socket.hpp
    socket/socket.cpp
)

add_library(http_server_lib STATIC 
    http_server/http_server.hpp
    http_server/http_server.cpp
)
target_link_libraries(http_server_lib PUBLIC
    socket_lib
    nlohmann_json::nlohmann_json
)

add_library(json_reporter_lib STATIC
    json_reporter/json_reporter.hpp
    json_reporter/json_reporter.cpp
)
target_link_libraries(json_reporter_lib PUBLIC
    http_server_lib
)

add_library(iterator_lib STATIC 
    iterator/iterator.hpp
    iterator/iterator.cpp
)
target_link_libraries(iterator_lib PUBLIC
    json_reporter_lib
)



add_executable(scanner 
    scanner/scanner.hpp
    scanner/scanner.cpp
    main.cpp
)
target_link_libraries(scanner PRIVATE
    iterator_lib
)