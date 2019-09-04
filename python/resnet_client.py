# -*- coding: utf-8 -*-

import grpc
import example_pb2
import example_pb2_grpc 

def run():
  with grpc.insecure_channel('localhost:50051') as channel:
    stub = example_pb2_grpc.ResNetStub(channel)
    request = example_pb2.ImageMatrix()
    request.image_matrix.extend([100]*1*3*224*224)
    response = stub.ClassifyImage(request)
  print("image category: " + str(int(response.category)))

if __name__ == '__main__':
  run()
      
