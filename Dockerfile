# Use an official GCC image
FROM gcc:12.3.0

# Set working directory
WORKDIR /app

# Install required dependencies
RUN apt-get update && apt-get install -y \
    cmake ninja-build git curl zip unzip tar \
    autoconf automake autoconf-archive libtool pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Clone vcpkg and bootstrap it
RUN mkdir -p /app/vcpkg-downloads && \
    git clone https://github.com/microsoft/vcpkg.git /app/vcpkg && \
    /app/vcpkg/bootstrap-vcpkg.sh

# Install Boost libraries via vcpkg
RUN /app/vcpkg/vcpkg install boost:x64-linux

# Copy project files
COPY . /app

# Configure and build the project
RUN cmake -Bbuild -DCMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug -S. \
    && cmake --build build --config Debug

# Specify the command to run the server
CMD ["./build/boost_asio_server"]
