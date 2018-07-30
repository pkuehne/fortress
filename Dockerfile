FROM ubuntu:xenial

# Refresh repo information
RUN apt -qq update

# Install build and test libs and tools
RUN apt install -qq -y \
    cmake \
    cppcheck \
    git \
    libboost-all-dev \
    libglfw3-dev \
    libgoogle-glog-dev \
    liblua5.3-dev \
    libsoil-dev \
    libyaml-cpp-dev \
    software-properties-common \
    python-pip \
    > /dev/null

RUN pip install cpplint

# Build gmock and install
RUN git clone https://github.com/google/googletest.git usr/src/googletest
WORKDIR /usr/src/googletest
RUN cmake .
RUN make gmock
RUN make install

# Set up source files
COPY . /fortress
WORKDIR /fortress
RUN make clean