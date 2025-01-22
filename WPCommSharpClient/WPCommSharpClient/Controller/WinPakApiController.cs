


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
    public class WinPakApiController : ApiController
    {
        private readonly MTSCBServerClass _server;
        private readonly WPCallbackClient _client;

        public WinPakApiController(MTSCBServerClass server)
        {
            _server = server ?? throw new ArgumentNullException(nameof(server));
            _client = new WPCallbackClient();
        }

        [HttpPost]
        [Route("api/unLock")]
        public async Task<IHttpActionResult> EntryUnLockById([FromBody] FormLockRequest formLockRequest)
        {
            DateTime startCallAPI = DateTime.Now;
            Log.Debug("Calling unlock ....");

            if (formLockRequest?.HID == null)
            {
                Log.Error("Not found HID!!!");
                return Json(ResponseResult<String>.ErrorResult("HID is required."));
            }

            try
            {
                int hID = (int) formLockRequest.HID.Value;

                // Hàm nhận vào 1 giá trị là Hardware ID cua output
                Log.Debug("---Unlock with HID: " + hID);
                _server.PulseByHID(hID);
                   
                TimeSpan totalTime = (DateTime.Now - startCallAPI);
                Log.Debug($"Total time: {totalTime.TotalMilliseconds} ms");
                Log.Debug("UnLock successful.");
                return Json(ResponseResult<String>.SuccessResult(null, "UnLock successful."));
            }
            catch (Exception ex)
            {
                Log.Error(ex, "Failed to unlock entry.");
                return Json(ResponseResult<String>.ErrorResult("An error occurred during unlocking."));
            } 
            
        }

    }
}
