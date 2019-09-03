#ifndef RESNET_H_
#define RESNET_H_

#include <torch/script.h> // One-stop header.
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class ResNetModule : public torch::jit::script::Module {
 public:
  ResNetModule(const std::string& model_path) {
    _module = torch::jit::load(model_path);
  }
  void classify(std::vector<int>& vec);
 private:
  torch::jit::script::Module _module;
};

#endif // RESNET_H_
