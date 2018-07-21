# Copyright (c) 2017 The Lyokocoin developers

project(lyokocoin-seeder)

include_directories(.)

add_executable(lyokocoin-seeder
	lyokocoin.cpp
	db.cpp
	dns.cpp
	main.cpp
)

target_link_libraries(lyokocoin-seeder common)
