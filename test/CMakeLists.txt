add_executable(Test "")

target_sources(Test PRIVATE test.cc)

target_link_libraries(Test PRIVATE ${PROJECT_NAME})

add_test(NAME UnitTest COMMAND Test)
