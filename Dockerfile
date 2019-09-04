FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
	build-essential \
	cmake \
	git \
	curl \
    wget \
    zip \
    unzip \
	vim \
	tree \
	autoconf \
	libtool \
	pkg-config \
	libgflags-dev \
	libgtest-dev \
	clang \
	libc++-dev \
	libssl-dev \
	python3-distutils

RUN ln -s /usr/bin/python3.6 /usr/bin/python

RUN curl -O https://bootstrap.pypa.io/get-pip.py && \
    python get-pip.py && \
    rm get-pip.py

# use tsing hua mirror
RUN pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/

RUN pip install grpcio-tools==1.23.0 torch==1.2.0+cpu torchvision==0.4.0+cpu -f https://download.pytorch.org/whl/torch_stable.html

# Install golang
RUN cd /tmp && \
    wget https://storage.googleapis.com/golang/go1.12.9.linux-amd64.tar.gz && \
    tar -C /usr/local -xzf go*linux-amd64.tar.gz && \
    rm -rf go1.12.9.linux-amd64.tar.gz

ENV PATH="/usr/local/go/bin:${PATH}"
ENV LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:/usr/local/lib"

# Install gRPC
RUN cd /tmp && \
    git clone -b v1.23.0 https://github.com/grpc/grpc.git && \
    cd /tmp/grpc && \
    git submodule update --init && \
    cd /tmp/grpc/third_party/zlib && \
    mkdir build && cd build && cmake .. && make -j $(nproc) && make install && \
    cd /tmp/grpc/third_party/cares/cares && \
    mkdir build && cd build && cmake .. && make -j $(nproc) && make install && \
    cd /tmp/grpc/third_party/protobuf/cmake && \
    mkdir build && cd build && cmake -Dprotobuf_BUILD_TESTS=OFF .. && make -j $(nproc) && make install && \
    cd /tmp/grpc && mkdir build && cd build && \
    cmake -DgRPC_INSTALL=ON -DgRPC_ZLIB_PROVIDER=package -DgRPC_CARES_PROVIDER=package -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_SSL_PROVIDER=package .. && \
    make -j $(nproc) && make install && ldconfig && \
    rm -rf /tmp/grpc

RUN cd /opt && \
    wget https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.2.0.zip && \
    unzip libtorch*.zip && \
    rm -rf libtorch-cxx11-abi-shared-with-deps-1.2.0.zip

RUN mkdir /models && \
    cd /models && \
    git clone https://github.com/Peter-Chou/libtorch_grpc_serving.git && \
    cd /models/libtorch_grpc_serving && \
    python get_resnet_libtorch_save.py && \
    protoc -I ./protos --grpc_out=./protos --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./protos/example.proto && \
    protoc -I ./protos --cpp_out=./protos ./protos/example.proto && \
    python -m grpc_tools.protoc -I./protos --python_out=./python --grpc_python_out=./python ./protos/example.proto && \
    mkdir build && cd build && cmake -DCMAKE_PREFIX_PATH=/opt/libtorch .. && make -j $(nproc) && \
    chmod +x /models/libtorch_grpc_serving/build/bin/resnet_server && \
    ./models/libtorch_grpc_serving/build/bin/resnet_server &
