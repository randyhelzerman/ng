CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

ADD_EXECUTABLE(ng.t
               ng_c_tricks.t.cpp
               ng_vector.t.cpp
               ng_color.t.cpp
               ng_interval.t.cpp
               ng_rb_tree_node.t.cpp
               ng_rb_tree.t.cpp
	       ng_nfa.t.cpp
	       ng_nfa_state.t.cpp
               test_fruit.c
               test_fruit_int.c
)

TARGET_LINK_LIBRARIES(ng.t
                      ng gtest gmock gtest_main)

TARGET_INCLUDE_DIRECTORIES(ng.t PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}/../libng")
