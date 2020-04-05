project(run)

add_executable(ums main.c)

target_link_libraries(ums umscore)
