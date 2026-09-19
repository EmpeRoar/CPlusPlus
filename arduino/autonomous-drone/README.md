# Autonomous Drone System

This repository contains a minimal end-to-end drone control prototype composed of:

- `drone-api` - ASP.NET Core BFF orchestrating commands.
- `drone-web` - Angular dashboard that sends control requests.
- `drone-device-control` - Arduino firmware that simulates motor control and command handling.

## Architecture

1. The Angular web app sends HTTP requests to the API.
2. The API validates the command, applies safety checks, and passes the request onward.
3. The Arduino firmware interprets command strings and drives motors inside a safe timeout model.

## Starting the backend

```bash
cd drone-api
cd drone.api
dotnet run
```

The API will start on a local HTTPS endpoint; the web app is configured to call `http://localhost:5158/api/drone`.

## Starting the frontend

```bash
cd drone-web
npm install
npm start
```

Then open the Angular local development server in a browser.

## Example API payload

```json
{
  "command": "moveForward",
  "strength": 1.0,
  "durationMs": 250,
  "timestampUtc": "2026-09-19T00:00:00Z"
}
```

## Example commands

```bash
curl -X POST http://localhost:5158/api/drone/command \
  -H "Content-Type: application/json" \
  -d '{"command":"moveForward","strength":1.0,"durationMs":250,"timestampUtc":"2026-09-19T00:00:00Z"}'

curl http://localhost:5158/api/drone/status
curl http://localhost:5158/api/drone/telemetry
```

## Safety notes

- Every command has a maximum duration and is automatically stopped.
- `emergencyStop` is treated as the highest-priority action.
- Invalid commands are rejected with a structured error response.
