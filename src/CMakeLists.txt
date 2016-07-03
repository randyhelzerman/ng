CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

ADD_EXECUTABLE(ngx
               ng_main.c)

TARGET_LINK_LIBRARIES(ngx
                      ng )
