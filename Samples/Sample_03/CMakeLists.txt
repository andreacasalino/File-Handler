add_executable( Sample03 ./Main.cpp )

target_link_libraries( Sample03
	PUBLIC
		FH::File-Handler
)	

add_custom_command(TARGET Sample03 PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Salutations ${CMAKE_CURRENT_BINARY_DIR}/Salutations
)

