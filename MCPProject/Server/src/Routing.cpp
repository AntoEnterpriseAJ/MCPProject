#include "Routing.h"

void Routing::run()
{
    CROW_ROUTE(m_server, "/greet").methods(crow::HTTPMethod::Get)
    ([](){
        return crow::response("hello");
    });

    m_server.port(kPort).multithreaded().run();
}
