include(CMakeParseArguments)

function(bin2c) 
	cmake_parse_arguments(bin2c "" "LENGTH;OUTPUT;HEADER" "ARRAYS" ${ARGN})

	foreach(array_file_pair ${bin2c_ARRAYS})
		string(REPLACE " " ";" array_file_list ${array_file_pair})
		list(GET array_file_list 0 array_name)
		list(GET array_file_list 1 file_name)
		set(bin2c_names ${bin2c_names} ${file_name})
		set(bin2c_args ${bin2c_args} -a ${array_name} ${CMAKE_CURRENT_SOURCE_DIR}/${file_name})
	endforeach()
	set(bin2c_output_file bin2coutput.c)
	if(bin2c_OUTPUT)
		set(bin2c_args ${bin2c_args} -o ${bin2c_OUTPUT})
		set(bin2c_output_file ${bin2c_OUTPUT})
	endif()
	if(bin2c_HEADER)
		set(bin2c_args ${bin2c_args} -h ${bin2c_HEADER})
	endif()
	if(bin2c_LENGTH)
		set(bin2c_args ${bin2c_args} -l ${bin2c_LENGTH})
	endif()

	add_custom_command(OUTPUT ${bin2c_output_file} ${bin2c_HEADER}
		               COMMAND $<TARGET_FILE:bin2c> ${bin2c_args}
		               DEPENDS bin2c ${bin2c_names}
		               VERBATIM)
endfunction(bin2c)