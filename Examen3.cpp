#include <iostream>
#include <map>
#include <variant>
#include <stdexcept>


class Environment {
private:
    std::map<std::string, std::variant<int, double, std::string>> symbolTable;

public:

    void insert(const std::string& symbol, const std::variant<int, double, std::string>& value) {
        auto it = symbolTable.find(symbol);
        if (it != symbolTable.end()) {
            throw std::invalid_argument("El símbolo ya existe en el entorno.");
        } else {
            symbolTable.insert({symbol, value});
        }
    }


    std::variant<int, double, std::string> lookup(const std::string& symbol) {
        auto it = symbolTable.find(symbol);
        if (it != symbolTable.end()) {
            return it->second;
        } else {
            throw std::out_of_range("El simbolo no existe en el entorno.");
        }
    }


    void remove(const std::string& symbol) {
        auto it = symbolTable.find(symbol);
        if (it != symbolTable.end()) {
            symbolTable.erase(it);
        } else {
            throw std::invalid_argument("El simbolo no existe en el entorno para eliminar.");
        }
    }


    bool exists(const std::string& symbol) {
        return symbolTable.find(symbol) != symbolTable.end();
    }
};

int main() {
    Environment env;


    try {
        env.insert("x", 10);
        env.insert("pi", 3.14159);
        env.insert("message", std::string("Hello"));
    } catch (const std::exception& e) {
        std::cout << "Error al insertar simbolo: " << e.what() << std::endl;
    }


    try {
        std::cout << "x: " << std::get<int>(env.lookup("x")) << std::endl;
        std::cout << "pi: " << std::get<double>(env.lookup("pi")) << std::endl;
        std::cout << "message: " << std::get<std::string>(env.lookup("message")) << std::endl;


        std::cout << "y: " << std::get<int>(env.lookup("y")) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error al buscar simbolo: " << e.what() << std::endl;
    }


    try {
        env.remove("pi");
        std::cout << "pi eliminado." << std::endl;

        std::cout << "Existe 'pi'?: " << (env.exists("pi") ? "Sí" : "No") << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error al eliminar simbolo: " << e.what() << std::endl;
    }

    return 0;
}


