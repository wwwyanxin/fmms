#include "../include/Handler.h"

#include <glog/logging.h>

using namespace std;

unordered_map<string,unordered_map<string,function<void ()>>>* wyx::Handler::webResource = new unordered_map<string,unordered_map<string,function<void ()>>>();

