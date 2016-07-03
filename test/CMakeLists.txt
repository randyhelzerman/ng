CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

ADD_EXECUTABLE(ng.t
ng_interval.t.cpp
)

TARGET_LINK_LIBRARIES(ng.t
                      ng gtest gmock gtest_main)

TARGET_INCLUDE_DIRECTORIES(ng.t PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}/../libng")
