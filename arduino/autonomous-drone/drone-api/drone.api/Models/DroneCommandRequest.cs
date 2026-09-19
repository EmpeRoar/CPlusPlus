namespace DroneApi.Models;

public sealed class DroneCommandRequest
{
    public string Command { get; set; } = string.Empty;
    public double Strength { get; set; } = 1.0;
    public int DurationMs { get; set; } = 250;
    public DateTimeOffset TimestampUtc { get; set; } = DateTimeOffset.UtcNow;
}
