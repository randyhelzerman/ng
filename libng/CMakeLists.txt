CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET(LIBNG_SRCS
    ng_color.h         ng_color.c
    ng_interval.h      ng_interval.c 
    ng_rb_tree_node.h  ng_rb_tree_node.c
    ng_rb_tree.h       ng_rb_tree.c
    ng_vector.h        ng_vector.c
)

ADD_LIBRARY(ng STATIC
            ${LIBNG_SRCS} )




