# Drone API

The backend is an ASP.NET Core Web API that acts as the BFF between the Angular dashboard and the robot controller hardware.

## Endpoints

- `POST /api/drone/command`
- `POST /api/drone/emergency-stop`
- `GET /api/drone/status`
- `GET /api/drone/telemetry`

## Supported commands

- `moveUp`
- `moveDown`
- `moveForward`
- `moveBackward`
- `moveSidewardLeft`
- `moveSidewardRight`
- `rotateHorizontal`
- `emergencyStop`

## Validation rules

- A command name must be one of the supported values.
- `strength` must be within the range `0` to `2`.
- `durationMs` must be between `1` and `5000`.

## Run locally

```bash
dotnet restore
dotnet build
dotnet run --project drone.api/drone.api.csproj
```
