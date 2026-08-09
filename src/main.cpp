#include "inventory_report.hpp"
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

void displayCards(
    const PokemonCard cards[],
    int count) {

    if (count <= 0) {
        cout << "No cards are loaded." << endl;
        return;
    }

    cout << fixed << setprecision(2);

    for (int i = 0; i < count; i++) {

        cout << i + 1 << ". "
             << cards[i].name
             << " | Card: "
             << cards[i].cardNumber
             << " | Set: "
             << cards[i].setName
             << " | Quantity: "
             << cards[i].quantity
             << " | Price: $"
             << cards[i].price
             << endl;
    }
}

int main() {
    PokemonCard cards[MAX_CARDS];

    SearchNode* searchHistory = nullptr;

    int count = readCardFile(
        "data/cards.txt",
        cards,
        MAX_CARDS
    );

    int choice = -1;

    cout << "Pokemon Card Collection Tracker"
         << endl;

    cout << "Loaded "
         << count
         << " card(s)."
         << endl;

    do {
        cout << endl;

        cout << "1. View collection" << endl;
        cout << "2. Search for a card" << endl;
        cout << "3. Sort cards by price" << endl;
        cout << "4. Show collection value" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter choice: ";

        if (!(cin >> choice)) {

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Invalid input." << endl;

            choice = -1;

            continue;
        }

        if (!isValidMenuChoice(choice)) {

            cout << "Invalid choice." << endl;

            continue;
        }

        if (choice == 1) {

            displayCards(cards, count);
        }

        else if (choice == 2) {

            string name;

            cout << "Enter Pokemon name: ";

            cin >> name;

            addSearchHistory(
                searchHistory,
                name
            );

            int index = findCardByName(
                cards,
                count,
                name
            );

            if (index == -1) {

                cout << "Card not found."
                     << endl;
            }

            else {

                cout << fixed
                     << setprecision(2);

                cout << "Found: "
                     << cards[index].name
                     << " | Set: "
                     << cards[index].setName
                     << " | Price: $"
                     << cards[index].price
                     << endl;
            }
        }

        else if (choice == 3) {

            sortCardsByPrice(
                cards,
                count
            );

            cout << "Cards sorted from highest "
                 << "price to lowest price."
                 << endl;

            displayCards(
                cards,
                count
            );
        }

        else if (choice == 4) {

            cout << fixed
                 << setprecision(2);

            cout << "Total collection value: $"
                 << calculateTotalCollectionValue(
                        cards,
                        count
                    )
                 << endl;
        }

    } while (choice != 0);

    clearSearchHistory(searchHistory);

    cout << "Goodbye!" << endl;

    return 0;
}
