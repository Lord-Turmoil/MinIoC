set(LIBRARIES mioc)
set(MIOC_TESTS SingletonTest TransientTest AssignmentTest)

foreach(test ${MIOC_TESTS})
    add_executable(${test} doctest.cpp ${test}.cpp)
    target_include_directories(${test} PRIVATE .)
    target_link_libraries(${test} ${LIBRARIES})
    add_test(NAME ${test} COMMAND ${test})
endforeach(test ${MIOC_TESTS})
