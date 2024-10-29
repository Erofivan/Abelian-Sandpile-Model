add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}   convertors 
                                        dynamic_structures 
                                        parser 
                                        helper 
                                        readfile
                                        sandpile)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})