# Deploy libtorch model with gRPC (Ubuntu 18.04)

this project shows how to deploy a resnet libtorch model using gRPC.

## 1. serving with docker

The easiest and most reliable way to deploy the resnet libtorch model is to use docker, make sure you have already install docker and run the following command.

```sh
# in project root dir
cd docker
# build the image from Dockerfile
[sudo] docker build --pull -t resnet-libtorch-serving -f libtorch_cpu_Dockerfile .
# create docker container and provide service
[sudo] sudo docker run -p 50051:50051 --name=resnet_service -d -it resnet-libtorch-serving /bin/bash -c './resnet_server'
```

Now you can create a client and send a request to the resnet service, here I use python client to do the demonstration.

```sh
# in project root dir
cd python
# make sure your python environment has installed grpcio-tools
python -m grpc_tools.protoc -I../protos --python_out=. --grpc_python_out=. ../protos/example.proto
python resnet_client.py  # image category: image_category_num
```

## 2. serving without docker

If you want to get all things without docker, You need to follow the instructions below. Since there is no prebuilt gRPC package in C++, it must be compiled and installed from source.

### install prerequisites

- necessary package
```sh
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install build-essential autoconf libtool pkg-config libgflags-dev libgtest-dev clang libc++-dev libssl-dev cmake python3-distutils vim tree git curl

```

- go language

```sh
wget https://storage.googleapis.com/golang/go1.12.9.linux-amd64.tar.gz
sudo tar -C /usr/local -xzf go*linux-amd64.tar.gz
echo 'export PATH=$PATH:/usr/local/go/bin' >> $HOME/.bashrc
echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib' >> $HOME/.bashrc
source $HOME/.bashrc
```

- download gRPC project

```sh
# in $HOME folder
git clone -b v1.23.0 https://github.com/grpc/grpc.git
cd grpc
git submodule update --init
```

The build process is a bit tricky, If you follow the build instructions given by the grpc's readme, it won't automatically generate *targets.cmake files which is useful when you use cmake to link grpc into your project and you will receive the error:

```
include could not find load file:

  /usr/local/lib/cmake/grpc/gRPCTargets.cmake
```

The current workaround is to build zlib, cares, protobuf at first, then tell cmake to use these installed packages when build grpc, and grpc will generate all the files as expected.

### install zlib

```sh
GPRC_COMPILE_ROOT_PATH=$(pwd)
cd $GPRC_COMPILE_ROOT_PATH/third_party/zlib
mkdir build && cd build
cmake ..
make -j $(nproc)
sudo make install
```

### install cares
```sh
cd $GPRC_COMPILE_ROOT_PATH/third_party/cares/cares
mkdir build && cd build
cmake ..
make -j $(nproc)
sudo make install
```

### install protobuf
```sh
cd $GPRC_COMPILE_ROOT_PATH/third_party/protobuf/cmake
mkdir build && cd build
cmake -Dprotobuf_BUILD_TESTS=OFF ..
make -j $(nproc)
sudo make install
```

## install gRPC
```sh
cd $GPRC_COMPILE_ROOT_PATH
mkdir build && cd build
cmake -DgRPC_INSTALL=ON -DgRPC_ZLIB_PROVIDER=package -DgRPC_CARES_PROVIDER=package -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_SSL_PROVIDER=package ..
make -j $(nproc)
sudo make install
sudo ldconfig
```

## Install libtorch library

```sh
cd $HOME
wget https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.2.0.zip
unzip libtorch*.zip
```

## build resnet model service

### generate resnet libtorch checkpoint from pytorch

```sh
curl -O https://bootstrap.pypa.io/get-pip.py
# ubuntu 18.04 python3.6.8
sudo python3 get-pip.py
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
# sudo apt-get install python3-pip
sudo pip install torch==1.2.0+cpu torchvision==0.4.0+cpu -f https://download.pytorch.org/whl/torch_stable.html
```



```sh
cd libtorch_grpc_demo
python3 get_resnet_libtorch_save.py
```

### generate protoc side code

- generate C++ server side code

```sh
# in libtorch_grpc_demo root dir
PROTO_SRC_DIR=./protos
## generate C++ server side code
protoc -I $PROTO_SRC_DIR --grpc_out=./protos --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $PROTO_SRC_DIR/example.proto
## generate C++ message classes needed by server
protoc -I $PROTO_SRC_DIR --cpp_out=./protos $PROTO_SRC_DIR/example.proto  

```

- generate python client side code

```sh
# in libtorch_grpc_demo root dir
sudo pip install grpcio-tools
python3 -m grpc_tools.protoc -I$PROTO_SRC_DIR --python_out=./python --grpc_python_out=./python $PROTO_SRC_DIR/example.proto
```

### build the project

```sh
# in libtorch_grpc_demo root dir
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=$HOME/libtorch ..
make -j $(nproc)
```

### start resnet server

```sh
# in libtorch_grpc_demo root dir
./build/bin/resnet_server &  # Server listening on 0.0.0.0:50051
```

### Client request from server

```sh
# in libtorch_grpc_demo root dir
python3 python/resnet_client.py  # image category: image_category_num
```

















