using Accw;
using Microsoft.Extensions.Configuration;
using Owin;
using Serilog;
using SimpleInjector.Integration.WebApi;
using SimpleInjector.Lifestyles;
using SimpleInjector;
using System.Web.Http;
using System;
using WPCommSharpClient;

public class Startup
{
    private MTSCBServerClass _server;
    private WPCallbackClient _client;

    public void Configuration(IAppBuilder appBuilder)
    {
        // Tạo và cấu hình container DI
        var container = ConfigureDependencyInjection();

        // Đăng ký Web API với OWIN
        HttpConfiguration config = ConfigureWebApi(container);
        appBuilder.UseWebApi(config);
    }

    private Container ConfigureDependencyInjection()
    {
        var container = new Container();
        container.Options.DefaultScopedLifestyle = new AsyncScopedLifestyle();

        // Tạo instance của _server và login
        _server = new MTSCBServerClass();
        _client = new WPCallbackClient();

        // Lấy thông tin từ appsettings.json
        IConfiguration configuration = new ConfigurationBuilder()
            .SetBasePath(AppDomain.CurrentDomain.BaseDirectory)
            .AddJsonFile("appsettings.json", optional: false, reloadOnChange: true)
            .Build();

        string username = configuration.GetSection("login")["username"];
        string password = configuration.GetSection("login")["password"];
        Log.Debug("Username: " + username);
        if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
        {
            Log.Error("Username or password not found in configuration (file appsetting.json).");
            throw new Exception("Username or password not found in configuration (file appsetting.json).");
        }

        // goị tới login của server
        // _client: mặc định với _client là đối tượng có sẵn
        // 3 : tức nhận cả Alarm và Event( 1: Alarm, 2: Event )
        // username
        // password
        // 1: id của user đăng nhâp(ở đây đăng nhập với user mặc định ban đầu của winPak là 1)
        bool isConnected = _server.InitServer(_client, 3, username, password, 1);
        if (!isConnected)
        {
            Log.Error("Failed to initialize and login to the server.");
            throw new Exception("Failed to initialize and login to the server.");
        }

        Log.Information("Server initialized and logged in successfully.");

        // Đăng ký _server vào container làm singleton
        container.RegisterInstance(_server);

        // Đăng ký WinPakApiController
        container.Register<WinPakApiController>(Lifestyle.Scoped);

        return container;
    }

    private HttpConfiguration ConfigureWebApi(Container container)
    {
        var config = new HttpConfiguration
        {
            DependencyResolver = new SimpleInjectorWebApiDependencyResolver(container)
        };

        config.MapHttpAttributeRoutes();
        config.Routes.MapHttpRoute(
            name: "DefaultApi",
            routeTemplate: "api/{controller}/{id}",
            defaults: new { id = RouteParameter.Optional }
        );

        return config;
    }
}
