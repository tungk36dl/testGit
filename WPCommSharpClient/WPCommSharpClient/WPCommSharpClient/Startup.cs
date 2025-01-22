using System.Web.Http;
using Accw;
using Owin;
using SimpleInjector;
using SimpleInjector.Integration.WebApi;
using SimpleInjector.Lifestyles;

namespace WPCommSharpClient
{
    public class Startup
    {
        public void Configuration(IAppBuilder appBuilder)
        {
            var container = ConfigureDependencyInjection();
            HttpConfiguration config = ConfigureWebApi(container);

            appBuilder.UseWebApi(config);
        }

        private Container ConfigureDependencyInjection()
        {
            var container = new Container();
            container.Options.DefaultScopedLifestyle = new AsyncScopedLifestyle();

            // Suwr dungj singleton xuyen suot vong doi ung dung
            container.Register<MTSCBServerClass>(Lifestyle.Singleton);

            container.Register<ApiController>(Lifestyle.Scoped);

            container.Verify();
            return container;
        }

        private HttpConfiguration ConfigureWebApi(Container container)
        {
            var config = new HttpConfiguration
            {
                DependencyResolver = new SimpleInjectorWebApiDependencyResolver(container)
            };

            // Thiết lập DependencyResolver để sử dụng Simple Injector
            config.DependencyResolver = new SimpleInjectorWebApiDependencyResolver(container);


            config.MapHttpAttributeRoutes();
            config.Routes.MapHttpRoute(
                name: "DefaultApi",
                routeTemplate: "api/{controller}/{id}",
                defaults: new { id = RouteParameter.Optional }
            );

            // config.Filters.Add(new AuthorizeAttribute()); // Thêm kiểm tra xác thực
            return config;
        }
    }
}
