# ofxDuckDuckGo

An openFrameworks addon for searching using the DuckDuckGo Instant Answer API.

## Features

- Simple and easy-to-use API for searching with DuckDuckGo
- Handles various error codes and provides user-friendly error messages
- Uses openFrameworks built-in functions for HTTP requests and JSON parsing

## Dependencies

- openFrameworks 0.11.0 or later

## Installation

1. Clone or download this repository into your `openFrameworks/addons` directory.
2. Add the `ofxDuckDuckGo` addon to your openFrameworks project.

## Usage

1. Include the addon header in your ofApp.h file:


```cpp
#include "ofxDuckDuckGo.h"
```

2. Create an instance of the `ofxDuckDuckGo` class in your ofApp.h file:


```cpp
ofxDuckDuckGo duckDuckGo;
```

3. Call the `search` method with your search query and a callback function:


```
duckDuckGo.search("search query", [&](const ofJson& result, ofxDuckDuckGo::ErrorCode errorCode) {
// Handle the search result and error code here
});
```

4. In the callback function, check the error code and handle the search results:


```
void ofApp::onSearchResult(const ofJson& result, ofxDuckDuckGo::ErrorCode errorCode) {
if (errorCode == ofxDuckDuckGo::Success) {
// Process the search results
} else {
ofLogError() << "Error: " << duckDuckGo.getErrorMessage(errorCode);
}
}
```

## License

This project is released under the MIT License. See the included LICENSE file for more information.

## Authors

This addon was primarily developed by the OpenAI Assistant with the help and guidance of tettou771.

