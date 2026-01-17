execute_process(
    COMMAND ${TEST_PROG}
    OUTPUT_VARIABLE TEST_OUTPUT
    ERROR_VARIABLE TEST_OUTPUT
    RESULT_VARIABLE TEST_RESULT
)

message("${TEST_OUTPUT}")

# Determine Success
if(TEST_RESULT EQUAL 0)
    message(STATUS "Test Passed.")
else()
    message(FATAL_ERROR "Test Failed: Process exited with code ${TEST_RESULT}")
endif()
