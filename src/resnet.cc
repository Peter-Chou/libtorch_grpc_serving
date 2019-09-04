#include "resnet.h"

float ResNetModule::classify(std::vector<int>& vec) {
  torch::Tensor tensor_image = torch::from_blob(vec.data(), {1, 3, 224, 224}, torch::kInt32);
  tensor_image = tensor_image.toType(torch::kFloat);
  tensor_image = tensor_image.div(255);
  // Create a vector of inputs.
  std::vector<torch::jit::IValue> inputs;
  inputs.push_back(tensor_image);

  auto output = _module.forward(inputs).toTensor();

  auto max_result = output.max(1, true);
  auto max_index = std::get<1>(max_result).item<float>();
  return max_index;
}


