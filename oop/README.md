# Raspberry Pi Robot C++ Project

This project is a Raspberry Pi-style C++ starter for a robot that can communicate with the internet.

## Project goal

- build C++ robot logic
- talk to an API over HTTP
- prepare the project for Raspberry Pi or embedded Linux development
- simulate a Pi-like environment in Docker

## Folder structure

- `main.cpp` - app entry point
- `include/` - header files
- `src/` - implementation files
- `docs/` - documentation
- `Dockerfile` - Raspberry Pi-like container setup

## Requirements

- Docker installed
- a terminal or PowerShell

## Build Docker image

From the project root:

```bash
docker build -t raspberrypi-cpp .
```

## Run the container

If you hit a permission issue while compiling inside the container, use the root user version:

```bash
docker run -it --rm -u root raspberrypi-cpp bash
```

This starts a Debian-based Raspberry Pi-like environment inside the container.

## Compile the project inside the container

Once inside the container:

```bash
g++ -std=c++17 -Iinclude main.cpp src/ApiClient.cpp src/RobotController.cpp -o robot_app
```

Then run:

```bash
./robot_app
```

## Notes

- This Docker environment is meant to emulate a Raspberry Pi-like Linux environment.
- It is useful for testing cross-platform C++ code and robot logic.
- Real GPIO hardware access still requires a physical Raspberry Pi or device mapping in Docker.

## Example workflow

```bash
docker build -t raspberrypi-cpp .
docker run -it --rm raspberrypi-cpp
```

Inside the container:

```bash
g++ -std=c++17 -Iinclude main.cpp src/ApiClient.cpp src/RobotController.cpp -o robot_app
./robot_app
```
