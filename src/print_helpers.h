#ifndef PRINT_HELPERS_H
#define PRINT_HELPERS_H

#include <iostream>
using namespace std;

// ANSI escape codes
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"

inline void printTitulo(const string &titulo) {
  cout << CYAN << BOLD << "\n===== " << titulo << " =====" << RESET << endl;
}

inline void printError(const string &mensaje) {
  cout << RED << BOLD << mensaje << RESET << endl;
}

inline void printOK(const string &mensaje) {
  cout << GREEN << BOLD << mensaje << RESET << endl;
}

#endif
