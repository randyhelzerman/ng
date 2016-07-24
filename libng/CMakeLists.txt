CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET(LIBNG_SRCS
    ng_color.h                 ng_color.c
    ng_interval.h              ng_interval.c 
    ng_rb_tree_node.h          ng_rb_tree_node.c
    ng_rb_tree.h               ng_rb_tree.c
    ng_vector.h                ng_vector.c
    ng_nfa_state.h             ng_nfa_state.c
    ng_nfa.h                   ng_nfa.c
    ng_nfa_factory.h           ng_nfa_factory.c
    ng_parser.h                ng_parser.c
    ng_symbol_table_entry.h    ng_symbol_table_entry.c
    ng_symbol_table.h          ng_symbol_table.c
    ng_token.h                 ng_token.c
    ng_token_array.h           ng_token_array.c
    ng_ascii_util.h            ng_ascii_util.c
)

ADD_LIBRARY(ng STATIC
            ${LIBNG_SRCS} )




