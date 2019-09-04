# Deploy libtorch model with gRPC (Ubuntu 18.04)

this project shows how to deploy a resnet libtorch model using gRPC.

## Build gRPC

Since there is no prebuilt gRPC package in C++, it must be compiled and installed from source.

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

```
# in libtorch_grpc_demo root dir
python3 python/resnet_client.py  # image category: 15
```

















