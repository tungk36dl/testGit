


using Accw;
using Serilog;
using System;
using System.Reflection;
using System.Threading.Tasks;
using System.Web.Http;

namespace WPCommSharpClient
{
    public class WinPakController : ApiController
    {
        private readonly MTSCBServerClass _server;
        private readonly WPCallbackClient _client;

        public WinPakController(MTSCBServerClass server)
        {
            _server = server ?? throw new ArgumentNullException(nameof(server));
            _client = new WPCallbackClient();
        }

        [HttpPost]
        [Route("api/login")]
        public async Task<IHttpActionResult> Login([FromBody] LoginRequest loginRequest)
        {
            //this._server = new MTSCBServerClass();
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


        //public async Task<IHttpActionResult> LoginAuto()
        //{
        //    //this._server = new MTSCBServerClass();

        //    try
        //    {
        //        bool isConnected = string.IsNullOrWhiteSpace(loginRequest.Domain)
        //            ? _server.InitServer(_client, 3, loginRequest.UserName, loginRequest.Password, 1)
        //            : _server.InitServer2(_client, 3, loginRequest.UserName, loginRequest.Password, loginRequest.Domain, 1);

        //        Log.Information("Login {Status}", isConnected ? "successful" : "failed");

        //        //var listDevice = _server.ListConnectedDevices();
        //        //Log.Debug(listDevice.ToString());

        //        if (isConnected)
        //        {
        //            return Json(ResponseResult<object>.SuccessResult(null, "Login successful."));
        //        }
        //        else
        //        {
        //            return Json(ResponseResult<object>.ErrorResult("Login failed."));
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        Log.Error(ex, "Login failed.");
        //        return Json(ResponseResult<object>.ErrorResult("An error occurred during login."));
        //    }
        //}

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
        [Route("api/lock")]
        public async Task<IHttpActionResult> EntryLockById([FromBody] FormLockRequest formLockRequest)
        {
            if (formLockRequest?.HID == null)
            {
                return Json(ResponseResult<object>.ErrorResult("HID is required."));
            }

            try
            {
                if (formLockRequest.Point != 0)
                {
                    _server.EntryPointLock(formLockRequest.HID.Value, formLockRequest.Point.Value);
                }
                else
                {
                    _server.EntryPointLockByHID(formLockRequest.HID.Value);
                }

                Log.Debug("Lock successful for HID={HID}", formLockRequest.HID);
                return Json(ResponseResult<object>.SuccessResult(null, "Lock successful."));
            }
            catch (Exception ex)
            {
                Log.Error(ex, "Failed to lock entry.");
                return Json(ResponseResult<object>.ErrorResult("An error occurred during locking."));
            }
        }


        [HttpPost]
        [Route("api/unLock")]
        public async Task<IHttpActionResult> EntryUnLockById([FromBody] FormLockRequest formLockRequest)
        {
            if (formLockRequest?.HID == null)
            {
                return Json(ResponseResult<String>.ErrorResult("HID is required."));
            }

            try
            {
                if (formLockRequest.Point != 0)
                {
                    _server.EntryPointUnLock(formLockRequest.HID.Value, formLockRequest.Point.Value);
                }
                else
                {
                    _server.EntryPointUnLockByHID(formLockRequest.HID.Value);
                }

                Log.Debug("Lock successful for HID={HID}", formLockRequest.HID);
                return Json(ResponseResult<String>.SuccessResult(null, "Lock successful."));
            }
            catch (Exception ex)
            {
                Log.Error(ex, "Failed to lock entry.");
                return Json(ResponseResult<String>.ErrorResult("An error occurred during locking."));
            }
        }


        [HttpGet]
        [Route("api/getStatus")]
        public async Task<IHttpActionResult> GetConnectToServer()
        {
            if (_server == null)
            {
                Log.Error("Server instance is null");
                return Json(ResponseResult<object>.ErrorResult("Server instance is null."));
            }

            try
            {
                _server.IsConnected(out int isConnected);
                Log.Information("Connection status: {Status}", isConnected == 1 ? "Connected" : "Disconnected");

                return isConnected == 1
                    ? Json(ResponseResult<object>.SuccessResult(null, "Server is connected."))
                    : Json(ResponseResult<object>.ErrorResult("Server is not connected."));
            }
            catch (Exception ex)
            {
                Log.Error(ex, "Failed to check connection status.");
                return Json(ResponseResult<object>.ErrorResult("An error occurred while checking the server status."));
            }
        }

        [HttpGet]
        [Route("api/getListDevice")]
        public async Task<IHttpActionResult> getListDevice()
        {
            try
            {
                Log.Debug("Getting list device.....");
                _server.IsConnected(out int isConnected);
                if (isConnected == 0)
                {
                    Log.Error("Server is not connected.");
                    return Json(ResponseResult<object>.ErrorResult("Server is not connected."));
                }
                Log.Debug("Get list Device.");
                object myObject = _server.ListConnectedDevices(); // Đối tượng của bạn
                Log.Debug("Get list device success");
                Type type = myObject.GetType();
                PropertyInfo[] properties = type.GetProperties();

                foreach (PropertyInfo property in properties)
                {
                    Console.WriteLine($"{property.Name}: {property.GetValue(myObject)}");
                }
                return Json(ResponseResult<object>.SuccessResult("Get list device successfull"));
            }
            catch(Exception ex)
            {
                return Json(ResponseResult<object>.ErrorResult("Error get list device!!!"));
            }
        }



    }

    public class InfoDeviceView
    {

    }

    public class LoginRequest
    {
        public string UserName { get; set; }
        public string Password { get; set; }
        public string Domain { get; set; }
    }

    public class FormLockRequest
    {
        public int? HID { get; set; }
        public int? Point { get; set; }
    }
}
