export type DroneCommandName =
  | 'moveUp'
  | 'moveDown'
  | 'moveForward'
  | 'moveBackward'
  | 'moveSidewardLeft'
  | 'moveSidewardRight'
  | 'rotateHorizontal'
  | 'emergencyStop';

export interface DroneCommandRequest {
  command: DroneCommandName;
  strength: number;
  durationMs: number;
  timestampUtc: string;
}

export interface DroneCommandResponse {
  accepted: boolean;
  command: string;
  status: string;
  message: string;
  durationMs: number;
  timestampUtc: string;
}

export interface DroneStatusResponse {
  state: string;
  armed: boolean;
  connected: boolean;
  emergencyStopActive: boolean;
  batteryPercent: number;
  lastCommand: string;
  lastUpdatedUtc: string;
}

export interface DroneTelemetryResponse {
  batteryPercent: number;
  connected: boolean;
  state: string;
  lastCommand: string;
  timestampUtc: string;
}

export interface DroneApiEnvelope<T> {
  success: boolean;
  message: string;
  errorCode?: string;
  data?: T;
}
