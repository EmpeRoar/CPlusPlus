using DroneApi.Models;

namespace DroneApi.Services;

public sealed class DroneCommandValidator
{
    private static readonly HashSet<string> AllowedCommands =
    [
        "moveUp",
        "moveDown",
        "moveForward",
        "moveBackward",
        "moveSidewardLeft",
        "moveSidewardRight",
        "rotateHorizontal",
        "emergencyStop"
    ];

    public bool IsValid(DroneCommandRequest request, out string error)
    {
        if (string.IsNullOrWhiteSpace(request.Command))
        {
            error = "Command is required.";
            return false;
        }

        if (!AllowedCommands.Contains(request.Command.Trim()))
        {
            error = $"Unsupported command '{request.Command}'.";
            return false;
        }

        if (request.Strength is < 0 or > 2)
        {
            error = "Strength must be between 0 and 2.";
            return false;
        }

        if (request.DurationMs is <= 0 or > 5000)
        {
            error = "DurationMs must be between 1 and 5000.";
            return false;
        }

        error = string.Empty;
        return true;
    }
}
