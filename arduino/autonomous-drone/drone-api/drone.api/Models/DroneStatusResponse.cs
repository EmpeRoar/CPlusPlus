namespace DroneApi.Models;

public sealed class DroneStatusResponse
{
    public string State { get; set; } = "Idle";
    public bool Armed { get; set; }
    public bool Connected { get; set; } = true;
    public bool EmergencyStopActive { get; set; }
    public double BatteryPercent { get; set; } = 100.0;
    public string LastCommand { get; set; } = "none";
    public DateTimeOffset LastUpdatedUtc { get; set; } = DateTimeOffset.UtcNow;
}
