


using Accw;
using Microsoft.Extensions.Configuration;
using Serilog;
using System;
using System.Reflection;
using System.Threading.Tasks;
using System.Web.Http;
using WPCommSharpClient.FormRequests;

namespace WPCommSharpClient
{
    public class ApiController : System.Web.Http.ApiController
    {
        private readonly MTSCBServerClass _server;
        private readonly WPCallbackClient _client;

        public ApiController(MTSCBServerClass server)
        {
            _server = server ?? throw new ArgumentNullException(nameof(server));
            _client = new WPCallbackClient();
        }

        [HttpPost]
        [Route("api/login")]
        public async Task<IHttpActionResult> Login([FromBody] FormLoginRequest loginRequest)
        {
            Log.Debug("Calling login....");
            if (loginRequest == null)
            {
                return Json(ResponseResult<object>.ErrorResult("Invalid login request."));
            }

            try
            {
                bool isConnected = string.IsNullOrWhiteSpace(loginRequest.Domain)
                    ? _server.InitServer(_client, 3, loginRequest.UserName, loginRequest.Password, 1)
                    : _server.InitServer2(_client, 3, loginRequest.UserName, loginRequest.Password, loginRequest.Domain, 1);

                Log.Information("Login {Status}", isConnected ? "successful" : "failed");

                //var listDevice = _server.ListConnectedDevices();
                //Log.Debug(listDevice.ToString());

                if (isConnected)
                {
                    return Json(ResponseResult<object>.SuccessResult(null, "Login successful."));
                }
                else
                {
                    return Json(ResponseResult<object>.ErrorResult("Login failed."));
                }
            }
            catch (Exception ex)
            {
                Log.Error(ex, "Login failed.");
                return Json(ResponseResult<object>.ErrorResult("An error occurred during login."));
            }
        }

        [HttpGet]
        [Route("api/logout")]
        public async Task<IHttpActionResult> logout()
        {
            Log.Debug("Calling logout....");

            int isConnected = 0;
            _server.IsConnected(out isConnected);
            if(isConnected > 0)
            {
                bool isLogout = _server.DoneServer(_client);
                if( isLogout)
                {
                    Log.Debug("Logout successfully.");
                    return Json(ResponseResult<object>.SuccessResult(null, "Logout successfully"));
                }
                else
                {
                    return Json(ResponseResult<object>.ErrorResult("Logout fail"));
                }
            }
            return Json(ResponseResult<object>.ErrorResult("Server not login!!!"));
        }

        [HttpPost]
        [Route("api/unLock")]
        public async Task<IHttpActionResult> EntryUnLockById([FromBody] FormLockRequest formLockRequest)
        {
            DateTime startCallAPI = DateTime.Now;
            Log.Debug("Calling unlock ....");

            // Đọc cấu hình từ appsettings.json // 1 thu vien doc file json
            IConfiguration configuration = new ConfigurationBuilder()
                .SetBasePath(AppDomain.CurrentDomain.BaseDirectory)
                .AddJsonFile("appsettings.json", optional: false, reloadOnChange: true)
                .Build();

            var login = configuration.GetSection("login");
            string username = login["username"];
            string password = login["password"];
            Log.Debug("Username: " + username);
            Log.Debug("Password: " + password);
            if(string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
            {
                Log.Error("Not found username or password!");
                return Json(ResponseResult<Object>.ErrorResult("Not found username or password!"));
            }
        // goị tới login của server
        // _client: mặc định với _client là đối tượng có sẵn
        // 3 : tức nhận cả Alarm và Event( 1: Alarm, 2: Event )
        // username
        // password
        // 1: id của user đăng nhâp(ở đây đăng nhập với user mặc định ban đầu của winPak là 1)
            bool isConnected = _server.InitServer(_client, 3, username, password, 1);
            if(isConnected)
            {
                if (formLockRequest?.HID == null)
                {
                    Log.Error("Not found HID!!!");
                    return Json(ResponseResult<String>.ErrorResult("HID is required."));
                }

                try
                {
                    int hID = (int) formLockRequest.HID.Value;

                    // Hàm nhận vào 1 giá trị là Hardware ID cua output
                    Log.Debug("Call Pulse.....");
                    _server.PulseByHID(hID);
                    TimeSpan totalTime = (DateTime.Now - startCallAPI);
                    Log.Debug($"Total time: {totalTime.TotalMilliseconds} ms");
                    return Json(ResponseResult<String>.SuccessResult(null, "UnLock successful."));
                }
                catch (Exception ex)
                {
                    Log.Error(ex, "Failed to unlock entry.");
                    return Json(ResponseResult<String>.ErrorResult("An error occurred during unlocking."));
                }
            }else
            {
                Log.Error("Error Login with initServer");
                return Json(ResponseResult<object>.ErrorResult("An error occurred during login."));
            }
            
        }


    
    }
}
