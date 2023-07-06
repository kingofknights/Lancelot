cmake_minimum_required(VERSION 3.14)

project(Lancelot
	    VERSION 1.0
		LANGUAGES C CXX
	    )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS "Download MySqlCppConn from https://dev.mysql.com/downloads/connector/cpp/")
find_package(SQLiteCpp REQUIRED)
find_package(fmt REQUIRED)

set(MYSQL_ROOT "C:/Program Files/MySQL/Connector C++ 8.0")
set(MYSQL_INCLUDE_DIR ${MYSQL_ROOT}/include)
set(MYSQL_LIBS_DIR ${MYSQL_ROOT}/lib64/vs14)

message(STATUS ${MYSQL_INCLUDE_DIR})
message(STATUS ${MYSQL_LIBS_DIR})

include_directories(${MYSQL_INCLUDE_DIR})
link_directories(${MYSQL_LIBS_DIR})

add_library(${PROJECT_NAME}
	    include/Lancelot/Logger/Logger.hpp
		include/Lancelot/ContractInfo/StoreProcedures.hpp
		include/Lancelot/ContractInfo/ContractFetcher.hpp
		include/Lancelot/ContractInfo/ContractInfo.hpp
		include/Lancelot/Structure.hpp
		include/Lancelot/Database/DatabaseHandler.hpp
		include/Lancelot.hpp
		src/ContractFetcher.cpp
		src/ContractInfo.cpp
		src/DatabaseHandler.cpp
	    )
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt SQLiteCpp )
