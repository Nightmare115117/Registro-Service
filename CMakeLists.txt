cmake_minimum_required(VERSION 3.14)
project(Registro-Service)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(JWT_BUILD_WITH_PICOJSON OFF CACHE BOOL "" FORCE)
set(JWT_BUILD_WITH_NLOHMANN_JSON ON CACHE BOOL "" FORCE)

set(JWT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(JWT_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.3.3
)

FetchContent_MakeAvailable(Crow)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(registro-service ${SOURCES})

target_include_directories(registro-service PRIVATE 
src 
${PQXX_INCLUDE_DIRS})
target_link_libraries(registro-service PRIVATE 
Crow::Crow 
Threads::Threads 
${PQXX_LIBRARIES} pq)