CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

ADD_EXECUTABLE(ng.t
               ng_c_tricks.t.cpp
               ng_vector.t.cpp
               ng_color.t.cpp
               ng_interval.t.cpp
               ng_rb_tree_node.t.cpp
               ng_rb_tree.t.c
               ng_rb_tree.t.cpp
               ng_rb_tree_node.t.c
	       ng_nfa.t.cpp
	       ng_nfa_state.t.cpp
	       ng_symbol_table_entry.t.cpp
	       ng_symbol_table.t.cpp
	       ng_token_array_entry.t.cpp
	       ng_token_array.t.cpp
	       ng_token_array.t.c
	       ng_nfa_factory.t.c
	       ng_nfa_factory.t.cpp
               test_fruit.c
               test_fruit_int.c
)

TARGET_LINK_LIBRARIES(ng.t
                      ng gtest gmock gtest_main)

TARGET_INCLUDE_DIRECTORIES(ng.t PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           "${CMAKE_CURRENT_SOURCE_DIR}/../libng")
