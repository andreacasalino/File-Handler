add_executable( Sample01 ./Main.cpp )

target_link_libraries( Sample01
	PUBLIC
		FH::File-Handler
)	

add_custom_command(TARGET Sample01 PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/lorem_ipsum ${CMAKE_CURRENT_BINARY_DIR}/lorem_ipsum
)

