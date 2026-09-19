# Drone Web Dashboard

This Angular app provides a flight dashboard with command buttons for every movement action and telemetry indicators.

## Features

- command buttons for all supported drone movements
- emergency stop button
- live status and telemetry indicators
- command log/history panel
- API integration through Angular services and DTOs

## Run locally

```bash
npm install
npm start
```

## API base URL

The default service target is:

```text
http://localhost:5158/api/drone
```

Update it in `src/app/drone-api.service.ts` if the backend port changes.
