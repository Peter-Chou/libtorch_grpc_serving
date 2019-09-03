#include "resnet.h"

void ResNetModule::classify(std::vector<int>& vec) {
  torch::Tensor tensor_image = torch::from_blob(vec.data(), {1, 3, 224, 224}, torch::kInt32);
  // Create a vector of inputs.
  std::vector<torch::jit::IValue> inputs;
  inputs.push_back(tensor_image);

  auto output = _module.forward(inputs).toTensor();
  std::cout << output.slice(/*dim=*/1, /*start=*/0, /*end=*/5) << '\n';
}


