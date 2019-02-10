FROM ubuntu:xenial

# Refresh repo information
RUN apt -qq update

# Install build and test libs and tools
RUN apt install -qq -y \
    cmake \
    cppcheck \
    git \
    libboost-all-dev \
    liblua5.3-dev \
    xorg-dev \
    libgl1-mesa-dev \
    software-properties-common \
    python-pip \
    > /dev/null

RUN pip install cpplint

# Set up source files
COPY . /fortress
RUN mkdir /fortress/build
WORKDIR /fortress/build
RUN cmake ..