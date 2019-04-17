CMAKE_MINIMUM_REQUIRED(VERSION 3.5)


ADD_EXECUTABLE(ng.t
               ng_c_tricks.t.cpp
               ng_vector.t.c                 ng_vector.t.cpp
               ng_color.t.c                  ng_color.t.cpp
               ng_interval.t.c               ng_interval.t.cpp
               ng_rb_tree_node.t.c           ng_rb_tree_node.t.cpp
               ng_rb_tree.t.c                ng_rb_tree.t.cpp
	       ng_nfa.t.c                    ng_nfa.t.cpp
	       ng_nfa_state.t.c              ng_nfa_state.t.cpp
	       ng_symbol_table_entry.t.c     ng_symbol_table_entry.t.cpp
	       ng_symbol_table.t.c	     ng_symbol_table.t.cpp
	       ng_token.t.c                  ng_token.t.cpp
	       ng_token_array.t.c            ng_token_array.t.cpp
	       ng_nfa_factory.t.c            ng_nfa_factory.t.cpp
	       ng_parser.t.c                 ng_parser.t.cpp
	                                     ng_ascii_util.t.cpp
					     ng_util_io.t.cpp
               test_fruit.c
               test_fruit_int.c

               Parser.d.cpp
	       Parser.t.cpp
	       Nfa.t.cpp
	       Nfa.d.cpp
)

TARGET_LINK_LIBRARIES(ng.t
                      ng ngpp ng_util gtest gmock gtest_main)

TARGET_INCLUDE_DIRECTORIES(ng.t PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           "${CMAKE_CURRENT_SOURCE_DIR}/../libng"
                           "${CMAKE_CURRENT_SOURCE_DIR}/../ngpp"
                           "${CMAKE_CURRENT_SOURCE_DIR}/../ng_util")


set_property(TARGET ng.t PROPERTY CXX_STANDARD 11)
set_property(TARGET ng.t PROPERTY CXX_STANDARD_REQUIRED ON)
