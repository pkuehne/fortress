FROM ubuntu:xenial

# Refresh repo information
RUN apt -qq update

# Install build and test libs and tools
RUN apt install -qq -y \
    cmake \
    cppcheck \
    google-mock \
    libboost-all-dev \
    libglfw3-dev \
    libgoogle-glog-dev \
    liblua5.3-dev \
    libsoil-dev \
    libyaml-cpp-dev \
    software-properties-common \
    > /dev/null

# Build gmock and install
WORKDIR /usr/src/gmock
RUN cmake .
RUN make gmock
RUN cp libgmock.a /usr/local/lib

# Set up source files
COPY . /fortress
WORKDIR /fortress
RUN make clean