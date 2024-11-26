#include "networking.hpp"

#include <fstream>
#include <iostream>

// Define the port for communication
constexpr int PORT = 12345;

// Function to read the JSON file and parse it into a Rectangle instance
Rectangle parseRectangleFromFile(const std::string& fileName) {
    std::ifstream file(fileName, std::ifstream::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file: " + fileName);
    }

    Json::Value root;
    Json::CharReaderBuilder readerBuilder;
    std::string errors;

    if (!Json::parseFromStream(readerBuilder, file, &root, &errors)) {
        throw std::runtime_error("Failed to parse JSON: " + errors);
    }

    if (!root.isMember("Rectangle") || !root["Rectangle"].isArray() || root["Rectangle"].size() != 4) {
        throw std::runtime_error("Invalid JSON format");
    }

    Rectangle rect;
    rect.x = root["Rectangle"][0].asFloat();
    rect.y = root["Rectangle"][1].asFloat();
    rect.width = root["Rectangle"][2].asFloat();
    rect.height = root["Rectangle"][3].asFloat();

    return rect;
}

// The server
void startServer() {
    try {
        asio::io_context ioContext;
        asio::ip::tcp::acceptor acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), PORT));

        std::cout << "Server is running on port " << PORT << "..." << std::endl;

        for (;;) {
            asio::ip::tcp::socket socket(ioContext);
            acceptor.accept(socket);

            std::vector<char> buffer(1024);
            asio::error_code error;

            size_t length = socket.read_some(asio::buffer(buffer), error);
            if (error == asio::error::eof) {
                break; // Connection closed cleanly by peer
            } else if (error) {
                throw asio::system_error(error);
            }

            std::string data(buffer.data(), length);
            std::cout << "Received data: " << data << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}

// The client
void startClient(const std::string& jsonFileName) {
    try {
        Rectangle rect = parseRectangleFromFile(jsonFileName);

        Json::Value root;
        root["Rectangle"][0] = rect.x;
        root["Rectangle"][1] = rect.y;
        root["Rectangle"][2] = rect.width;
        root["Rectangle"][3] = rect.height;

        Json::StreamWriterBuilder writerBuilder;
        std::string jsonData = Json::writeString(writerBuilder, root);

        asio::io_context ioContext;

        asio::ip::tcp::resolver resolver(ioContext);
        asio::ip::tcp::socket socket(ioContext);
        asio::connect(socket, resolver.resolve("127.0.0.1", std::to_string(PORT)));

		asio::error_code error;
        asio::write(socket, asio::buffer(jsonData), error);

        std::cout << "Sent data to server: " << jsonData << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }
}
