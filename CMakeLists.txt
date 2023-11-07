cmake_minimum_required(VERSION 3.14)

project(Lancelot VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_ENABLE_EXPORTS ON)

find_package(SQLiteCpp CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
add_subdirectory(repo/xcd)

add_library(${PROJECT_NAME}
        include/Lancelot/Logger/Logger.hpp
        include/Lancelot/ContractInfo/StoreProcedures.hpp
        include/Lancelot/ContractInfo/ContractFetcher.hpp
        include/Lancelot/ContractInfo/ContractInfo.hpp
        include/Lancelot/Security/Security.hpp
        include/Lancelot/Structure.hpp
        include/Lancelot/Enums.hpp
        include/Lancelot.hpp

        src/ContractFetcher.cpp
        src/ContractInfo.cpp
        src/Enums.cpp
        src/Security.cpp
        )

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE repo/xcd)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt SQLiteCpp xcd)
