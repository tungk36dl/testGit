using System;
using System.Windows.Forms;
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
                Log.Debug("baseAddress not found in appsettings.json");
                return;
            }


            WebApp.Start<Startup>(url: baseAddress);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainView());
        }
    }


}
