CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET(NGPP_SRCS
    Parser.cpp                 Parser.h
)

ADD_LIBRARY(ngpp STATIC
            ${NGPP_SRCS} )




