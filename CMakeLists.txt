cmake_minimum_required(VERSION 3.14)

project(Lancelot
        VERSION 1.0
        LANGUAGES C CXX
        )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SQLiteCpp REQUIRED)
find_package(fmt REQUIRED)

add_library(${PROJECT_NAME}
        include/Logger.hpp
        include/StoreProcedures.hpp
        include/ContractFetcher.hpp
        include/Structure.hpp
        src/ContractFetcher.cpp
        src/ContractInfo.cpp
		include/ContractInfo.hpp)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt SQLiteCpp)
