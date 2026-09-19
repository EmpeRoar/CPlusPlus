using DroneApi.Services;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllers();
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddOpenApi();
builder.Services.AddSingleton<DroneCommandValidator>();
builder.Services.AddSingleton<DroneHardwareGateway>();
builder.Services.AddSingleton<DroneCommandService>();

var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.MapOpenApi();
}

app.UseHttpsRedirection();
app.MapControllers();
app.MapGet("/", () => new { name = "drone-api", status = "ok" });

app.Run();
