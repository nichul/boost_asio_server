cmake_minimum_required(VERSION 3.15)
project(boost_asio_server)

set(CMAKE_CXX_STANDARD 17)

# Boost 라이브러리 설정
find_package(Boost REQUIRED COMPONENTS system)

# 실행 파일 추가
add_executable(boost_asio_server src/main.cpp)

# Boost 라이브러리 링크
target_link_libraries(boost_asio_server PRIVATE Boost::system)

# Boost 헤더 경로 포함
target_include_directories(boost_asio_server PRIVATE ${Boost_INCLUDE_DIRS})
