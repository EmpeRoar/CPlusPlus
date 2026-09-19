namespace DroneApi.Models;

public sealed class DroneTelemetryResponse
{
    public double BatteryPercent { get; set; } = 100.0;
    public bool Connected { get; set; } = true;
    public string State { get; set; } = "Idle";
    public string LastCommand { get; set; } = "none";
    public DateTimeOffset TimestampUtc { get; set; } = DateTimeOffset.UtcNow;
}
