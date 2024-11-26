#pragma once

#include <asio.hpp>
#include <json/json.h>
#include <raylib.h>
#include <string>

Rectangle parseRectangleFromFile(const std::string& fileName);
void startServer();
void startClient(const std::string& jsonFileName);
