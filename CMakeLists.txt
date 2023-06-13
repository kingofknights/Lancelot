cmake_minimum_required(VERSION 3.14)
project(Lancelot)

find_package(SQLiteCpp REQUIRED)
find_package(fmt REQUIRED)

add_library(${PROJECT_NAME}
	    include/Logger.hpp
		include/StoreProcedures.hpp
		include/Contract.hpp
		src/Contract.cpp
	    )
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt SQLiteCpp)
