cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

add_executable (iirdemo iirdemo.cpp)
target_link_libraries(iirdemo iir)

add_executable (ecg50hzfilt ecg50hzfilt.cpp)
target_link_libraries(ecg50hzfilt iir)
