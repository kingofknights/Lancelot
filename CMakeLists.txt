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
	    include/Lancelot/Logger.hpp
		include/Lancelot/StoreProcedures.hpp
		include/Lancelot/ContractFetcher.hpp
		include/Lancelot/Structure.hpp
		include/Lancelot/ContractInfo.hpp
		src/ContractFetcher.cpp
		src/ContractInfo.cpp
	    )
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt SQLiteCpp)
