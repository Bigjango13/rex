#include "db.h"
#include "lexer.h"

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
    tb.print();
}
