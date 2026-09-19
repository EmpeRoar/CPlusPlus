# Drone Device Control

This firmware simulates the embedded controller layer for the drone system. It accepts command strings from a serial port and interprets them into motor patterns with timeout and emergency-stop safety logic.

## Supported command format

```text
CMD:moveForward,1.0,250
CMD:moveSidewardLeft,0.6,400
CMD:rotateHorizontal,0.8,300
CMD:emergencyStop
```

## State model

- Idle
- Armed
- Active
- Stopped

## Safety rules

- Any command expires after its `durationMs` value.
- `emergencyStop` cancels active motion immediately.
- Invalid instructions are rejected.

## Programming notes

This code is intentionally lightweight so it can be ported to a real drone controller with motor drivers and UART communication.
