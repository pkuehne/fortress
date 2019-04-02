FROM ubuntu:xenial

# Refresh repo information
RUN apt -qq update

# Install build and test libs and tools
RUN apt install -qq -y \
    cppcheck \
    git \
    wget \
    libboost-all-dev \
    liblua5.3-dev \
    xorg-dev \
    libgl1-mesa-dev \
    software-properties-common \
    python-pip \
    > /dev/null

RUN pip install cpplint

RUN apt purge --auto-remove cmake
RUN wget https://cmake.org/files/v3.14/cmake-3.14.1.tar.gz
RUN tar -xzvf cmake-3.14.1.tar.gz
WORKDIR ./cmake-3.14.1/
RUN ./bootstrap
RUN make -j4
RUN make install

# Set up source files
COPY . /fortress
RUN rm -fr /fortress/build
RUN mkdir /fortress/build
WORKDIR /fortress/build
RUN cmake ..