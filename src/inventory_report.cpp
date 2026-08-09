#include "inventory_report.hpp"
#include <fstream>

using namespace std;

bool isValidQuantity(int quantity) {
    return quantity >= 0;
}

bool isValidPrice(double price) {
    return price >= 0.0;
}

bool isValidMenuChoice(int choice) {
    return choice >= 0 && choice <= 4;
}

double calculateCardValue(const PokemonCard& card) {
    if (!isValidQuantity(card.quantity) ||
        !isValidPrice(card.price)) {
        return 0.0;
    }

    return card.quantity * card.price;
}

double calculateTotalCollectionValue(
    const PokemonCard cards[],
    int count) {

    if (cards == nullptr || count <= 0) {
        return 0.0;
    }

    double total = 0.0;

    for (int i = 0; i < count; i++) {
        total += calculateCardValue(cards[i]);
    }

    return total;
}

int readCardFile(
    string filename,
    PokemonCard cards[],
    int maxCards) {

    if (cards == nullptr || maxCards <= 0) {
        return 0;
    }

    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        return 0;
    }

    int count = 0;

    while (count < maxCards &&
           inputFile >> cards[count].cardNumber
                     >> cards[count].name
                     >> cards[count].setName
                     >> cards[count].quantity
                     >> cards[count].price) {

        if (isValidQuantity(cards[count].quantity) &&
            isValidPrice(cards[count].price)) {

            count++;
        }
    }

    inputFile.close();

    return count;
}

int findCardByName(
    const PokemonCard cards[],
    int count,
    string name) {

    if (cards == nullptr || count <= 0) {
        return -1;
    }

    for (int i = 0; i < count; i++) {

        if (cards[i].name == name) {
            return i;
        }
    }

    return -1;
}

void sortCardsByPrice(
    PokemonCard cards[],
    int count) {

    if (cards == nullptr || count <= 1) {
        return;
    }

    for (int i = 0; i < count - 1; i++) {

        for (int j = 0; j < count - i - 1; j++) {

            if (cards[j].price < cards[j + 1].price) {

                PokemonCard temp = cards[j];

                cards[j] = cards[j + 1];

                cards[j + 1] = temp;
            }
        }
    }
}

void addSearchHistory(
    SearchNode*& head,
    string cardName) {

    SearchNode* newNode = new SearchNode;

    newNode->cardName = cardName;

    newNode->next = head;

    head = newNode;
}

int countSearchHistory(SearchNode* head) {
    int count = 0;

    SearchNode* current = head;

    while (current != nullptr) {

        count++;

        current = current->next;
    }

    return count;
}

void clearSearchHistory(SearchNode*& head) {
    SearchNode* current = head;

    while (current != nullptr) {

        SearchNode* nextNode = current->next;

        delete current;

        current = nextNode;
    }

    head = nullptr;
}
