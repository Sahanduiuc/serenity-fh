cmake_minimum_required(VERSION 3.14)
project(serenity-fh C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include(conan.cmake)

conan_cmake_run(REQUIRES boost/1.70.0@conan/stable
                         fmt/5.3.0@bincrafters/stable
                         rapidjson/1.1.0@bincrafters/stable
                         rxcpp/4.1.0@bincrafters/stable
                         spdlog/1.3.1@bincrafters/stable
                         uvw/1.15.0@skypjack/stable
                         gtest/1.8.1@bincrafters/stable
        BASIC_SETUP BUILD missing)

find_package(LibCryptoMktData REQUIRED)
find_package(IXWebSocket REQUIRED)

include_directories(include ${LIBCRYPTOMKTDATA_INCLUDE_DIR} ${LIBIXWEBSOCKET_INCLUDE_DIR})
set(LIBS ${LIBS} ${CONAN_LIBS} ${LIBCRYPTOMKTDATA_LIBRARIES} ${LIBIXWEBSOCKET_LIBRARIES})

list(REMOVE_ITEM LIBS boost_unit_test_framework)

add_executable(serenity-fh-coinbase src/coinbase_main.cpp)
target_link_libraries(serenity-fh-coinbase ${LIBS})
if (APPLE)
    target_link_libraries(serenity-fh-coinbase "-framework foundation" "-framework security")
endif()
