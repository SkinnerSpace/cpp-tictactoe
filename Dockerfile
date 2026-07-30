FROM ubuntu:24.04

# Install the C++ compiler, CMake, and Boost.
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

# This becomes the working directory inside the container.
WORKDIR /app

# Copy the entire project into /app.
COPY . .

# Generate Linux build files.
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Compile only the server.
RUN cmake --build build --target TcpServer --parallel

# Start the server when the container starts.
CMD ["./build/TcpServer"]
