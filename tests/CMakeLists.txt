add_executable(tests
        main.cpp
        ${GTEST_SRC})

target_link_libraries(tests huflib)

if (UNIX AND NOT APPLE)
    target_link_libraries(tests pthread)
endif (UNIX AND NOT APPLE)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2 -flto")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -ggdb -fsanitize=address,undefined,leak")
endif()
