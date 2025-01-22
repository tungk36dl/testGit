using Serilog;
using Microsoft.Extensions.Configuration;
using System;

namespace WPCommSharpClient
{
    public static class LoggingConfig
    {
        public static void ConfigureLogger(IConfiguration configuration)
        {
            var loggingConfig = configuration.GetSection("Logging");

            string logFilePath = loggingConfig["LogFilePath"] ?? "Logs/log-.txt";
            string rollingInterval = loggingConfig["RollingInterval"] ?? "Day";
            int retainedFileCountLimit = int.TryParse(loggingConfig["RetainedFileCountLimit"], out var limit) ? limit : 7;

            // Cấu hình Serilog để lưu tất cả log
            Log.Logger = new LoggerConfiguration()
                .MinimumLevel.Verbose() // Ghi mọi log từ Verbose trở lên
                .WriteTo.Console() // Ghi log ra console
                .WriteTo.File(
                    path: logFilePath,
                    rollingInterval: Enum.TryParse<RollingInterval>(rollingInterval, true, out var interval) ? interval : RollingInterval.Day,
                    retainedFileCountLimit: retainedFileCountLimit,
                    outputTemplate: "{Timestamp:yyyy-MM-dd HH:mm:ss.fff zzz} [{Level:u3}] {Message:lj}{NewLine}{Exception}"
                ) // Ghi log vào file
                .CreateLogger();

        }
    }
}
