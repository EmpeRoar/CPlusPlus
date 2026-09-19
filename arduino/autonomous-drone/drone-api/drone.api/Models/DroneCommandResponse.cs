namespace DroneApi.Models;

public sealed class DroneCommandResponse
{
    public bool Accepted { get; set; }
    public string Command { get; set; } = string.Empty;
    public string Status { get; set; } = string.Empty;
    public string Message { get; set; } = string.Empty;
    public int DurationMs { get; set; }
    public DateTimeOffset TimestampUtc { get; set; } = DateTimeOffset.UtcNow;
}
