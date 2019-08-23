cmake_minimum_required(VERSION 3.14)
project(serenity-fh C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++ -lc++abi")

add_compile_options("-stdlib=libc++")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include(conan.cmake)

conan_cmake_run(REQUIRES boost/1.70.0@conan/stable
                         cppzmq/4.4.1@bincrafters/stable
                         fmt/5.3.0@bincrafters/stable
                         rapidjson/1.1.0@bincrafters/stable
                         rxcpp/4.1.0@bincrafters/stable
                         spdlog/1.3.1@bincrafters/stable
                         uvw/1.15.0@skypjack/stable
                         gtest/1.8.1@bincrafters/stable
        BASIC_SETUP BUILD missing)

find_package(LibCryptoMktData REQUIRED)
find_package(IXWebSocket REQUIRED)
find_package(CapnProto REQUIRED)

include_directories(include ${LIBCRYPTOMKTDATA_INCLUDE_DIR} ${LIBIXWEBSOCKET_INCLUDE_DIR} ${CAPNP_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CONAN_LIBS} ${LIBCRYPTOMKTDATA_LIBRARIES} ${LIBIXWEBSOCKET_LIBRARIES} ${CAPNP_LIBRARIES})

list(REMOVE_ITEM LIBS boost_unit_test_framework)

add_executable(serenity-fh-coinbase capnp/serenity-fh.capnp.c++ src/coinbase_main.cpp)
target_link_libraries(serenity-fh-coinbase ${LIBS})
if (APPLE)
    target_link_libraries(serenity-fh-coinbase "-framework foundation" "-framework security")
endif()
