//
//  NetworkRequest.h
//
//  Created by duzixi.com on 15/8/25.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
//#include "json.h"
#include "boost/asio.hpp"

using namespace std;

/// GET请求
string GetRequest(char* host, char* path);
string GetRequest(string url);

/// POST请求
string PostRequest(const char* host, const char* path, string form);


