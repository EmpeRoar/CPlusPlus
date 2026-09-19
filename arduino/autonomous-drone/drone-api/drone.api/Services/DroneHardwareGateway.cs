using DroneApi.Models;

namespace DroneApi.Services;

public sealed class DroneHardwareGateway
{
    private readonly ILogger<DroneHardwareGateway> _logger;

    public DroneHardwareGateway(ILogger<DroneHardwareGateway> logger)
    {
        _logger = logger;
    }

    public Task<bool> SendCommandAsync(DroneCommandRequest request, CancellationToken cancellationToken = default)
    {
        _logger.LogInformation(
            "Simulating device command: {Command}, strength {Strength}, duration {DurationMs}ms",
            request.Command,
            request.Strength,
            request.DurationMs);

        return Task.FromResult(true);
    }

    public DroneTelemetryResponse GetTelemetry()
    {
        return new DroneTelemetryResponse
        {
            BatteryPercent = 88.4,
            Connected = true,
            State = "Idle",
            LastCommand = "none",
            TimestampUtc = DateTimeOffset.UtcNow
        };
    }
}
