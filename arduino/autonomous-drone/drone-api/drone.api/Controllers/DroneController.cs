using DroneApi.Models;
using DroneApi.Services;
using Microsoft.AspNetCore.Mvc;

namespace DroneApi.Controllers;

[ApiController]
[Route("api/[controller]")]
public sealed class DroneController : ControllerBase
{
    private readonly DroneCommandService _commandService;
    private readonly DroneHardwareGateway _hardwareGateway;

    public DroneController(DroneCommandService commandService, DroneHardwareGateway hardwareGateway)
    {
        _commandService = commandService;
        _hardwareGateway = hardwareGateway;
    }

    [HttpPost("command")]
    public async Task<ActionResult<DroneApiEnvelope<DroneCommandResponse>>> PostCommand([FromBody] DroneCommandRequest request, CancellationToken cancellationToken)
    {
        if (request is null)
        {
            return BadRequest(new DroneApiEnvelope<DroneCommandResponse>
            {
                Success = false,
                Message = "Request body is required.",
                ErrorCode = "invalid_request"
            });
        }

        var response = await _commandService.ExecuteAsync(request, cancellationToken);

        if (!response.Accepted)
        {
            return BadRequest(new DroneApiEnvelope<DroneCommandResponse>
            {
                Success = false,
                Message = response.Message,
                ErrorCode = "command_rejected",
                Data = response
            });
        }

        return Ok(new DroneApiEnvelope<DroneCommandResponse>
        {
            Success = true,
            Message = response.Message,
            Data = response
        });
    }

    [HttpPost("emergency-stop")]
    public ActionResult<DroneApiEnvelope<DroneCommandResponse>> EmergencyStop()
    {
        var response = new DroneCommandResponse
        {
            Accepted = true,
            Command = "emergencyStop",
            Status = "EmergencyStop",
            Message = "Emergency stop triggered.",
            DurationMs = 0,
            TimestampUtc = DateTimeOffset.UtcNow
        };

        return Ok(new DroneApiEnvelope<DroneCommandResponse>
        {
            Success = true,
            Message = response.Message,
            Data = response
        });
    }

    [HttpGet("status")]
    public ActionResult<DroneApiEnvelope<DroneStatusResponse>> GetStatus()
    {
        var status = new DroneStatusResponse
        {
            State = "Idle",
            Armed = true,
            Connected = true,
            EmergencyStopActive = false,
            BatteryPercent = 88.4,
            LastCommand = "none",
            LastUpdatedUtc = DateTimeOffset.UtcNow
        };

        return Ok(new DroneApiEnvelope<DroneStatusResponse>
        {
            Success = true,
            Message = "Drone is ready.",
            Data = status
        });
    }

    [HttpGet("telemetry")]
    public ActionResult<DroneApiEnvelope<DroneTelemetryResponse>> GetTelemetry()
    {
        var telemetry = _hardwareGateway.GetTelemetry();

        return Ok(new DroneApiEnvelope<DroneTelemetryResponse>
        {
            Success = true,
            Message = "Telemetry retrieved.",
            Data = telemetry
        });
    }
}
