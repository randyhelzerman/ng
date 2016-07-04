CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET(LIBNG_SRCS
    ng_color.h      ng_color.c
    ng_interval.h   ng_interval.c 
)

ADD_LIBRARY(ng STATIC
            ${LIBNG_SRCS} )




