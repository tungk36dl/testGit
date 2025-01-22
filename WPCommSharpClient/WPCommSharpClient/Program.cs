using System;
using System.Windows.Forms;
using Accw;
using Microsoft.Extensions.Configuration;
using Microsoft.Owin.Hosting;
using Serilog;
namespace WPCommSharpClient
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // Đọc cấu hình từ appsettings.json // 1 thu vien doc file json
            IConfiguration configuration = new ConfigurationBuilder()
                .SetBasePath(AppDomain.CurrentDomain.BaseDirectory)
                .AddJsonFile("appsettings.json", optional: false, reloadOnChange: true)
                .Build();


            // Cấu hình Serilog
            LoggingConfig.ConfigureLogger(configuration);

            string baseAddress = configuration["BaseAddress"];
            if (string.IsNullOrEmpty(baseAddress))
            {
                Log.Error("baseAddress not found in appsettings.json");
                return;
            }

            try
            {
                WebApp.Start<Startup>(url: baseAddress);

                Log.Information($"API server started successfully at {baseAddress}");

                // 
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new MessageLoopContext());
            } catch(Exception ex)
            {
                Log.Error($" Application failed to start!!! , {ex}");
            }
        }

        private class MessageLoopContext : ApplicationContext
        {
            public MessageLoopContext()
            { 

            }
        }
    }


}


