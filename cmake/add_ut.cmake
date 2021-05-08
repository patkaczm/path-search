include(CMakeParseArguments)

function(add_ut)
set(options)
set(oneValueArgs NAME)
set(multiValueArgs SOURCES DEPENDS)
cmake_parse_arguments(ADD_UT "${options}" "${oneValueArgs}"
                             "${multiValueArgs}" ${ARGN} )

add_executable(${ADD_UT_NAME}Test ${TEST_MAIN} ${ADD_UT_SOURCES})
target_link_libraries(${ADD_UT_NAME}Test PRIVATE
    gtest
    gmock
    ${ADD_UT_NAME}Lib
    ${ADD_UT_DEPENDS})
target_include_directories(${ADD_UT_NAME}Test PRIVATE ${INCLUDE_DIR})
add_test(NAME ${ADD_UT_NAME}Test COMMAND ${ADD_UT_NAME}Test)

endfunction()
