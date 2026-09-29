#include "db.h"
#include "lexer.h"
#include "parser.h"

// Temp hack for testing
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " input.csv" << std::endl;
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);
    Table tb{};
    tb.addFromCSV(input);

    std::string line = "";
    while (1) {
        // Print table
        tb.print();

        // Get the next command
        line = "";
        while (line == "") {
            std::cout << "> ";
            if (!getline(std::cin, line)) {
                // Ctrl-D / EOL
                std::cout << std::endl;
                line = "exit";
                break;
            }
        }
        // Exit command
        if (line == "exit") break;

        std::cout << "Running: '" << line << "'" << std::endl << std::endl;

        // Lex
        std::vector<Token> tokens = lex(line);
        if (tokens.size() == 0) {
            std::cout << "Failed to lex!" << std::endl;
            continue;
        }
        for (const auto &t : tokens) {
            t.print();
            std::cout << ", ";
        }
        std::cout << std::endl;

        // Parse
        Parser parser;
        Node ast = parser.parse(tokens);
        if (ast == nullptr) {
            std::cout << "Failed to parse!" << std::endl;
            continue;
        }
        ast->print();
        std::cout << std::endl;

        // Run
        //run(ast);
    }
}
