add_executable(resnet_server resnet_server.cc ${PROTO_GENERATED_FILES_DIR}/example.pb.cc ${PROTO_GENERATED_FILES_DIR}/example.grpc.pb.cc)
target_link_libraries(resnet_server
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF}
    ${TORCH_LIBRARIES})
set_property(TARGET resnet_server PROPERTY CXX_STANDARD 11)
