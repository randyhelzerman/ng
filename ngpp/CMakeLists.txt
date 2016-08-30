CMAKE_MINIMUM_REQUIRED(VERSION 3.5)


SET(NGPP_SRCS
    Parser.cpp                 Parser.h
    Nfa.cpp		       Nfa.h
)

ADD_LIBRARY(ngpp STATIC
            ${NGPP_SRCS} )


TARGET_INCLUDE_DIRECTORIES(ng.t PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}/../ng_util_hpp")

TARGET_LINK_LIBRARIES(ngpp gtest_main)

set_property(TARGET ngpp PROPERTY CXX_STANDARD 11)
set_property(TARGET ngpp PROPERTY CXX_STANDARD_REQUIRED ON)






