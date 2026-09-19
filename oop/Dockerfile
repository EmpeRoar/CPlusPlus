# Raspberry Pi-style Linux container for C++ development.
# This uses a Debian base to keep the image buildable and stable.
# Real Raspberry Pi GPIO access still requires a physical Pi or mapped device access.

FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive
WORKDIR /app

# Install a reliable toolchain and common networking libraries for C++ robot projects.
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    g++ \
    make \
    cmake \
    git \
    pkg-config \
    curl \
    libcurl4-openssl-dev \
    libssl-dev \
    python3 \
    python3-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Create a normal development user.
RUN useradd -m -s /bin/bash appuser
USER appuser

# Copy project files into the container.
COPY . /app

# Default shell for development inside the container.
CMD ["bash"]
