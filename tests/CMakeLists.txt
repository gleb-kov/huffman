add_executable(tests
        main.cpp
        ${GTEST_SRC})

if (UNIX AND NOT APPLE)
    target_link_libraries(tests pthread)
endif (UNIX AND NOT APPLE)