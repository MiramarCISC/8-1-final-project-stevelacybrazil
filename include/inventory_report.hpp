#ifndef INVENTORY_REPORT_HPP
#define INVENTORY_REPORT_HPP

#include <string>

const int MAX_CARDS = 100;

struct PokemonCard {
    std::string cardNumber;
    std::string name;
    std::string setName;
    int quantity;
    double price;
};

struct SearchNode {
    std::string cardName;
    SearchNode* next;
};

bool isValidQuantity(int quantity);

bool isValidPrice(double price);

bool isValidMenuChoice(int choice);

double calculateCardValue(const PokemonCard& card);

double calculateTotalCollectionValue(const PokemonCard cards[], int count);

int readCardFile(std::string filename, PokemonCard cards[], int maxCards);

int findCardByName(const PokemonCard cards[], int count, std::string name);

void sortCardsByPrice(PokemonCard cards[], int count);

void addSearchHistory(SearchNode*& head, std::string cardName);

int countSearchHistory(SearchNode* head);

void clearSearchHistory(SearchNode*& head);

#endif
