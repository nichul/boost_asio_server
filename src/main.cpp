#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

const std::string response =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<html><body><h1>Welcome to Boost.Asio Web Server!</h1></body></html>";

void handle_connection(tcp::socket socket) {
    try {
        char buffer[1024] = {0};
        socket.read_some(boost::asio::buffer(buffer));
        boost::asio::write(socket, boost::asio::buffer(response));
    } catch (std::exception& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
        std::cout << "Server running on http://localhost:8080" << std::endl;

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            handle_connection(std::move(socket));
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}
