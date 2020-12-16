add_executable(Test test.cc)

target_link_libraries(Test ${PROJECT_NAME})

add_test(NAME UnitTest COMMAND Test)
