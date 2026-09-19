import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import {
  DroneApiEnvelope,
  DroneCommandRequest,
  DroneCommandResponse,
  DroneStatusResponse,
  DroneTelemetryResponse,
} from './drone.models';

@Injectable({ providedIn: 'root' })
export class DroneApiService {
  private readonly baseUrl = 'http://localhost:5158/api/drone';

  constructor(private http: HttpClient) {}

  sendCommand(request: DroneCommandRequest): Observable<DroneApiEnvelope<DroneCommandResponse>> {
    return this.http.post<DroneApiEnvelope<DroneCommandResponse>>(`${this.baseUrl}/command`, request);
  }

  emergencyStop(): Observable<DroneApiEnvelope<DroneCommandResponse>> {
    return this.http.post<DroneApiEnvelope<DroneCommandResponse>>(`${this.baseUrl}/emergency-stop`, {});
  }

  getStatus(): Observable<DroneApiEnvelope<DroneStatusResponse>> {
    return this.http.get<DroneApiEnvelope<DroneStatusResponse>>(`${this.baseUrl}/status`);
  }

  getTelemetry(): Observable<DroneApiEnvelope<DroneTelemetryResponse>> {
    return this.http.get<DroneApiEnvelope<DroneTelemetryResponse>>(`${this.baseUrl}/telemetry`);
  }
}
