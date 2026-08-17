#include "crow.h"
#include "crow/middlewares/cors.h"
#include "DBConfig/DBConfig.h"
#include "Repositories/RegistroRepository.h"
#include "Services/RegistroService.h"
#include "Controllers/RegistroController.h"

using namespace std;
using App = crow::App<crow::CORSHandler>;

int main() {
    App app;

    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("Content-Type", "Authorization")
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method)
        .origin("*");

    DBConfig config;
    string databaseUrl = config.obtenerDatabaseUrl();

    RegistroRepository registroRepo(config);
    RegistroService registroService(registroRepo);
    RegistroController registroController(registroService);

    registroController.registrarRutas(app, "/api/registros");
    registroController.contadorDeRegistros(app, registroService);

    app.port(8083).multithreaded().run();
}