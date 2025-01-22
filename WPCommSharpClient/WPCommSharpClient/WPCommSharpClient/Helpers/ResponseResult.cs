namespace WPCommSharpClient
{
    public class ResponseResult<T>
    {
        public bool Success { get; set; } // Trạng thái thành công hoặc thất bại
        public string Message { get; set; } // Thông điệp kèm theo
        public T Data { get; set; } // Dữ liệu trả về (nếu có)

        public ResponseResult() { }

        public ResponseResult(bool success, string message, T data)
        {
            Success = success;
            Message = message;
            Data = data;
        }

        public static ResponseResult<T> SuccessResult(T data, string message = "Success")
        {
            return new ResponseResult<T>(true, message, data);
        }

        public static ResponseResult<T> ErrorResult(string message, T data = default)
        {
            return new ResponseResult<T>(false, message, data);
        }
    }
}
