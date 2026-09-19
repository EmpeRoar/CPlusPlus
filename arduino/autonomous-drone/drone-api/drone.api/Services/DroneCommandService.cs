using DroneApi.Models;

namespace DroneApi.Services;

public sealed class DroneCommandService
{
    private readonly DroneCommandValidator _validator;
    private readonly DroneHardwareGateway _hardwareGateway;
    private readonly ILogger<DroneCommandService> _logger;

    public DroneCommandService(
        DroneCommandValidator validator,
        DroneHardwareGateway hardwareGateway,
        ILogger<DroneCommandService> logger)
    {
        _validator = validator;
        _hardwareGateway = hardwareGateway;
        _logger = logger;
    }

    public async Task<DroneCommandResponse> ExecuteAsync(DroneCommandRequest request, CancellationToken cancellationToken = default)
    {
        if (!_validator.IsValid(request, out var error))
        {
            return new DroneCommandResponse
            {
                Accepted = false,
                Command = request.Command,
                Status = "Rejected",
                Message = error,
                DurationMs = request.DurationMs,
                TimestampUtc = DateTimeOffset.UtcNow
            };
        }

        if (request.Command.Equals("emergencyStop", StringComparison.OrdinalIgnoreCase))
        {
            _logger.LogWarning("Emergency stop command received.");
            return new DroneCommandResponse
            {
                Accepted = true,
                Command = request.Command,
                Status = "EmergencyStop",
                Message = "Drone motion halted immediately.",
                DurationMs = request.DurationMs,
                TimestampUtc = DateTimeOffset.UtcNow
            };
        }

        var sent = await _hardwareGateway.SendCommandAsync(request, cancellationToken);

        if (!sent)
        {
            return new DroneCommandResponse
            {
                Accepted = false,
                Command = request.Command,
                Status = "Failed",
                Message = "Device rejected the command.",
                DurationMs = request.DurationMs,
                TimestampUtc = DateTimeOffset.UtcNow
            };
        }

        return new DroneCommandResponse
        {
            Accepted = true,
            Command = request.Command,
            Status = "Queued",
            Message = "Command accepted for execution.",
            DurationMs = request.DurationMs,
            TimestampUtc = DateTimeOffset.UtcNow
        };
    }
}
