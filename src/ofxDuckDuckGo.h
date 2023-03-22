#pragma once
#include "ofMain.h"

class ofxDuckDuckGo {
public:
    enum ErrorCode {
        Success,
        BadRequest,
        Unauthorized,
        Forbidden,
        NotFound,
        RequestTimeout,
        InternalServerError,
        ServiceUnavailable,
        UnknownError
    };

    void search(const string& query, function<void(const ofJson&, ErrorCode)> callback);
private:
    void onResponse(ofHttpResponse& response);
    function<void(const ofJson&, ErrorCode)> searchCallback;
    string uriEncode(const string& str);
    ErrorCode parseErrorResponse(const ofHttpResponse &response);
    
public:
    static string getErrorMessage(ErrorCode errorCode);
};
