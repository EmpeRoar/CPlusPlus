
# Build Drone System

Build the complete drone control system for this repository using the following architecture:

- `drone-api` is the backend BFF for the Angular web app.
- `drone-web` is the Angular front-end used to send movement commands.
- `drone-device-control` is the Arduino firmware that drives the drone hardware.

## Goal

Create a working drone controller system where the Angular app sends movement commands to the backend API, and the backend forwards those commands to the Arduino controller firmware for execution.

## Required movement commands

Implement support for the following drone actions:

- move up
- move down
- move forward
- move backward
- move sideward left
- move sideward right
- horizontal rotate

## Architecture requirements

- The API should act as a BFF and orchestration layer.
- The Angular app should expose a dashboard with buttons or joystick controls for all commands.
- The Arduino firmware should interpret commands and drive the drone motors safely.
- Communication between the frontend and API should be via HTTP endpoints.
- Communication between the API and hardware should be via serial/UART or another hardware-friendly protocol.
- Include safety logic for emergency stop, command timeout, and invalid command rejection.

## Backend (`drone-api`)

Create or extend a clean ASP.NET Core Web API with:

- controllers or minimal API endpoints for drone commands
- DTOs for command payloads and telemetry
- service layer for validation and execution
- response models for success and error states
- environment configuration and dependency setup
- endpoints such as:
  - `POST /api/drone/command`
  - `POST /api/drone/emergency-stop`
  - `GET /api/drone/status`
  - `GET /api/drone/telemetry`
- command handling for:
  - `moveUp`
  - `moveDown`
  - `moveForward`
  - `moveBackward`
  - `moveSidewardLeft`
  - `moveSidewardRight`
  - `rotateHorizontal`
- validation of command payloads and command names
- command queueing or throttle handling if needed
- telemetry models for battery, connection state, and drone status

## Frontend (`drone-web`)

Create or extend the Angular application with:

- a control dashboard UI
- command buttons for all movement commands
- emergency stop button
- status indicators for command state and connectivity
- battery and telemetry widgets
- command log/history panel
- Angular service layer for API calls
- models for requests and responses
- loading, error, and success states

## Firmware (`drone-device-control`)

Implement Arduino-based control logic with:

- a command parser for incoming instructions from the backend
- motor or actuator mapping for each movement type
- safe motor stop behavior
- emergency stop logic
- command timeout behavior
- telemetry reporting back to the API
- a state model for idle, armed, active, and stopped states

## Suggested payload format

Use a structured request payload like this:

```json
{
  "command": "moveForward",
  "strength": 1.0,
  "durationMs": 250,
  "timestampUtc": "2026-09-19T00:00:00Z"
}
```

Other commands should follow the same structure with appropriate values.

## Safety expectations

- Never allow uncontrolled continuous movement without a stop condition.
- Treat emergency stop as the highest priority command.
- Add reasonable command validation and timeout behavior.
- Ensure the frontend and backend clearly communicate command success or failure.

## Deliverables

Generate the following:

1. backend API with endpoints and models
2. Angular UI with actions and status display
3. Arduino firmware logic for device control
4. README files with setup and usage instructions
5. sample payloads and API usage examples

## Implementation guidance

- Keep the code maintainable and modular.
- Separate responsibilities by layer: UI, API, service, device control.
- Use clear naming and explicit models rather than ambiguous strings.
- Add comments only where the control flow is important.
- Favor a basic but working system before advanced optimization.
- Keep the implementation aligned with the current repository structure.

## Output

Provide a practical, readable implementation that works end-to-end from the Angular web app to the backend API and to the Arduino firmware.
