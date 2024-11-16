cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME main)
set(CMAKE_CXX_STANDARD 17)


set(workspaceFolder $(WORKING_DIRECTORY))
project(${PROJECT_NAME} VERSION 1.0.0)

set(Sources
    src/main.cpp
    src/TCPSockInet.cpp
)

add_executable(${PROJECT_NAME} ${Sources})


include(FetchContent)
set(FETCHCONTENT_QUIET ON)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG 68fd0277eea5412aff9b91c0b70efc698359dae0
)
FetchContent_Declare(
    sockpp
    GIT_REPOSITORY https://github.com/fpagliughi/sockpp
    GIT_TAG e6c4688a576d95f42dd7628cefe68092f6c5cd0f
)
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml
    GIT_TAG db78afc2b7d8f043b4bc6b185635d949ea2ed2a8
)
FetchContent_MakeAvailable(argparse sockpp pugixml)
FetchContent_GetProperties(argparse
    POPULATED argparse_POPULATED
    SOURCE_DIR argparse_SOURCE_DIR
    BINARY_DIR argparse_BINARY_DIR
)
FetchContent_GetProperties(sockpp
    POPULATED sockpp_POPULATED
    SOURCE_DIR sockpp_SOURCE_DIR
    BINARY_DIR sockpp_BINARY_DIR
)
FetchContent_GetProperties(pugixml
    POPULATED pugixml_POPULATED
    SOURCE_DIR pugixml_SOURCE_DIR
    BINARY_DIR pugixml_BINARY_DIR
)
target_link_libraries(${PROJECT_NAME} PUBLIC argparse sockpp pugixml)



include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME})
