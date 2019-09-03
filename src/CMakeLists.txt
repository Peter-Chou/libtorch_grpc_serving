add_library(resnet resnet.h resnet.cc)
target_link_libraries(resnet
    ${TORCH_LIBRARIES})

#link_libraries("/usr/local/lib/libgrpc++.a")

add_executable(resnet_server resnet_server.cc ${PROTO_GENERATED_FILES_DIR}/example.pb.cc ${PROTO_GENERATED_FILES_DIR}/example.grpc.pb.cc)
target_link_libraries(resnet_server
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF}
    resnet)
