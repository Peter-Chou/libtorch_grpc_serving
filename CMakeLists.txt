cmake_minimum_required(VERSION 3.10)

project(custom_ops
    VERSION 1.0
    LANGUAGES C CXX)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)
set(PROTO_GENERATED_FILES_DIR "${PROJECT_SOURCE_DIR}/protos")

#set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

find_package(Torch REQUIRED)
message(STATUS "Torch libraries: ${TORCH_LIBRARIES}")

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

include_directories("${PROTO_GENERATED_FILES_DIR}")

add_subdirectory(src)
