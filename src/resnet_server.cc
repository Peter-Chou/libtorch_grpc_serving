#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include <grpcpp/grpcpp.h>
#include "example.grpc.pb.h"
#include "resnet.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using example::ImageMatrix;
using example::ClassifyResult;
using example::ResNet;

ResNetModule resnet(std::string("/home/peter/libtorch_grpc_demo/traced_resnet_model.pt"));

class ResNetServiceImpl : public ResNet::Service {
  Status ClassifyImage (ServerContext* context, const ImageMatrix* image,
                         ClassifyResult* res) override {
    std::vector<int> temp;
    for (int i = 0; i < image->image_matrix_size(); ++i) {
      temp.push_back(image->image_matrix(i)); 
    }
    auto classify_result = resnet.classify(temp);
    res->set_category(classify_result);
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  ResNetServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}


int main(int argc, const char* argv[]) {
  // Deserialize the ScriptModule from a file using torch::jit::load().
  // module = torch::jit::load("/home/peter/pytorch_libtorch/traced_resnet_model.pt");

  // assert(module != nullptr);
  // std::cout << "ok\n";

  RunServer();
  return 0;
}
