import { CommonModule } from '@angular/common';
import { HttpClientModule } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { finalize } from 'rxjs';

import { DroneApiService } from './drone-api.service';
import { DroneCommandRequest, DroneCommandResponse, DroneStatusResponse, DroneTelemetryResponse } from './drone.models';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [CommonModule, HttpClientModule],
  templateUrl: './app.html',
  styleUrl: './app.scss'
})
export class App implements OnInit {
  readonly commandDefinitions = [
    { key: 'moveUp', label: 'Move Up', description: 'Ascend' },
    { key: 'moveDown', label: 'Move Down', description: 'Descend' },
    { key: 'moveForward', label: 'Forward', description: 'Advance' },
    { key: 'moveBackward', label: 'Backward', description: 'Retreat' },
    { key: 'moveSidewardLeft', label: 'Left', description: 'Strafe left' },
    { key: 'moveSidewardRight', label: 'Right', description: 'Strafe right' },
    { key: 'rotateHorizontal', label: 'Rotate', description: 'Turn body' }
  ] as const;

  status: DroneStatusResponse | null = null;
  telemetry: DroneTelemetryResponse | null = null;
  commandHistory: DroneCommandResponse[] = [];
  isBusy = false;
  lastMessage = 'Drone system ready.';
  lastError = '';

  constructor(private readonly droneApi: DroneApiService) {}

  ngOnInit(): void {
    this.refreshStatus();
    this.refreshTelemetry();
  }

  executeCommand(command: string): void {
    const payload: DroneCommandRequest = {
      command: command as DroneCommandRequest['command'],
      strength: 1,
      durationMs: 250,
      timestampUtc: new Date().toISOString()
    };

    this.isBusy = true;
    this.lastError = '';

    this.droneApi.sendCommand(payload)
      .pipe(finalize(() => (this.isBusy = false)))
      .subscribe({
        next: (response) => {
          const result = response.data ?? {
            accepted: false,
            command: payload.command,
            status: 'Unknown',
            message: response.message,
            durationMs: payload.durationMs,
            timestampUtc: payload.timestampUtc
          };

          this.commandHistory.unshift(result);
          this.lastMessage = response.message || result.message;
          this.refreshStatus();
          this.refreshTelemetry();
        },
        error: (err) => {
          this.lastError = err?.error?.message ?? 'Command rejected by the drone API.';
          this.lastMessage = 'Command failed.';
        }
      });
  }

  triggerEmergencyStop(): void {
    this.isBusy = true;
    this.lastError = '';

    this.droneApi.emergencyStop()
      .pipe(finalize(() => (this.isBusy = false)))
      .subscribe({
        next: (response) => {
          const result = response.data ?? {
            accepted: true,
            command: 'emergencyStop',
            status: 'EmergencyStop',
            message: response.message,
            durationMs: 0,
            timestampUtc: new Date().toISOString()
          };

          this.commandHistory.unshift(result);
          this.lastMessage = response.message || result.message;
          this.refreshStatus();
          this.refreshTelemetry();
        },
        error: (err) => {
          this.lastError = err?.error?.message ?? 'Emergency stop could not be processed.';
          this.lastMessage = 'Emergency stop failed.';
        }
      });
  }

  private refreshStatus(): void {
    this.droneApi.getStatus().subscribe({
      next: (response) => {
        this.status = response.data ?? null;
      },
      error: () => {
        this.status = { state: 'Offline', armed: false, connected: false, emergencyStopActive: false, batteryPercent: 0, lastCommand: 'none', lastUpdatedUtc: new Date().toISOString() };
      }
    });
  }

  private refreshTelemetry(): void {
    this.droneApi.getTelemetry().subscribe({
      next: (response) => {
        this.telemetry = response.data ?? null;
      },
      error: () => {
        this.telemetry = { batteryPercent: 0, connected: false, state: 'Offline', lastCommand: 'none', timestampUtc: new Date().toISOString() };
      }
    });
  }
}
