#include "ofxDuckDuckGo.h"

void ofxDuckDuckGo::search(const std::string& query, std::function<void(const ofJson&, ErrorCode)> callback) {
    searchCallback = callback;

    std::string url = "https://api.duckduckgo.com/?q=" + uriEncode(query) + "&format=json";

    ofAddListener(ofURLResponseEvent(), this, &ofxDuckDuckGo::onResponse);
    ofLoadURLAsync(url, "search_request");
}

void ofxDuckDuckGo::onResponse(ofHttpResponse& response) {
    if (response.request.name != "search_request") return;
    ofRemoveListener(ofURLResponseEvent(), this, &ofxDuckDuckGo::onResponse);

    ErrorCode errorCode = parseErrorResponse(response);
    if (errorCode == Success) {
        ofJson jsonData = ofJson::parse(response.data.getText());
        ofLogVerbose("ofxDuckDuckGo") << "Response JSON: " << jsonData;
        if (searchCallback) {
            searchCallback(jsonData, errorCode);
        }
    } else {
        ofLogError("ofxDuckDuckGo") << getErrorMessage(errorCode);
    }
}

string ofxDuckDuckGo::uriEncode(const string& str) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (auto c : str) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << std::setw(2) << int((unsigned char) c);
        }
    }

    return escaped.str();
}

ofxDuckDuckGo::ErrorCode ofxDuckDuckGo::parseErrorResponse(const ofHttpResponse &response) {
    switch (response.status) {
        case 200:
            return Success;
        case 400:
            return BadRequest;
        case 401:
            return Unauthorized;
        case 403:
            return Forbidden;
        case 404:
            return NotFound;
        case 408:
            return RequestTimeout;
        case 500:
            return InternalServerError;
        case 503:
            return ServiceUnavailable;
        default:
            return UnknownError;
    }
}

string ofxDuckDuckGo::getErrorMessage(ErrorCode errorCode) {
    switch (errorCode) {
        case Success:
            return "Success";
        case BadRequest:
            return "Bad Request";
        case Unauthorized:
            return "Unauthorized";
        case Forbidden:
            return "Forbidden";
        case NotFound:
            return "Not Found";
        case RequestTimeout:
            return "Request Timeout";
        case InternalServerError:
            return "Internal Server Error";
        case ServiceUnavailable:
            return "Service Unavailable";
        case UnknownError:
            return "Unknown error";
    }
    return "";
}
