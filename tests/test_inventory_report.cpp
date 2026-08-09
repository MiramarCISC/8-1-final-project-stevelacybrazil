#include "inventory_report.hpp"
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

bool nearlyEqual(
    double actual,
    double expected,
    double tolerance = 0.0001) {

    return fabs(actual - expected)
           <= tolerance;
}

void createTestCardFile(string filename) {
    ofstream out(filename);

    out << "025/102 Pikachu BaseSet 2 15.50"
        << endl;

    out << "004/102 Charizard BaseSet 1 120.00"
        << endl;

    out << "044/102 Bulbasaur BaseSet 3 8.25"
        << endl;

    out.close();
}

void testWeek1ProgramBasics() {
    PokemonCard card = {
        "025/102",
        "Pikachu",
        "BaseSet",
        2,
        15.50
    };

    assert(
        nearlyEqual(
            calculateCardValue(card),
            31.00
        )
    );
}

void testWeek2DecisionsAndValidation() {
    assert(isValidQuantity(0));

    assert(!isValidQuantity(-1));

    assert(isValidPrice(15.50));

    assert(!isValidPrice(-1.00));

    assert(isValidMenuChoice(0));

    assert(isValidMenuChoice(4));

    assert(!isValidMenuChoice(5));
}

void testWeek3Functions() {
    PokemonCard cards[] = {

        {
            "025/102",
            "Pikachu",
            "BaseSet",
            2,
            15.50
        },

        {
            "004/102",
            "Charizard",
            "BaseSet",
            1,
            120.00
        }
    };

    assert(
        nearlyEqual(
            calculateTotalCollectionValue(
                cards,
                2
            ),
            151.00
        )
    );
}

void testWeek4ArraysSearchAndSort() {
    PokemonCard cards[] = {

        {
            "025/102",
            "Pikachu",
            "BaseSet",
            2,
            15.50
        },

        {
            "004/102",
            "Charizard",
            "BaseSet",
            1,
            120.00
        },

        {
            "044/102",
            "Bulbasaur",
            "BaseSet",
            3,
            8.25
        }
    };

    assert(
        findCardByName(
            cards,
            3,
            "Charizard"
        ) == 1
    );

    assert(
        findCardByName(
            cards,
            3,
            "Mewtwo"
        ) == -1
    );

    sortCardsByPrice(cards, 3);

    assert(
        cards[0].name == "Charizard"
    );

    assert(
        cards[1].name == "Pikachu"
    );

    assert(
        cards[2].name == "Bulbasaur"
    );
}

void testWeek5StringsAndStructures() {
    PokemonCard card = {

        "025/102",
        "Pikachu",
        "BaseSet",
        2,
        15.50
    };

    assert(
        card.cardNumber == "025/102"
    );

    assert(
        card.name == "Pikachu"
    );

    assert(
        card.setName == "BaseSet"
    );
}

void testWeek6PointersAndLinkedList() {
    SearchNode* head = nullptr;

    addSearchHistory(
        head,
        "Pikachu"
    );

    addSearchHistory(
        head,
        "Charizard"
    );

    assert(head != nullptr);

    assert(
        head->cardName == "Charizard"
    );

    assert(
        countSearchHistory(head) == 2
    );

    clearSearchHistory(head);

    assert(head == nullptr);
}

void testWeek7FileInput() {
    string filename =
        "tests/resources/test_cards.txt";

    createTestCardFile(filename);

    PokemonCard cards[10];

    int count = readCardFile(
        filename,
        cards,
        10
    );

    assert(count == 3);

    assert(
        cards[0].name == "Pikachu"
    );

    assert(
        cards[1].name == "Charizard"
    );

    assert(
        cards[2].name == "Bulbasaur"
    );
}

int main() {
    testWeek1ProgramBasics();

    testWeek2DecisionsAndValidation();

    testWeek3Functions();

    testWeek4ArraysSearchAndSort();

    testWeek5StringsAndStructures();

    testWeek6PointersAndLinkedList();

    testWeek7FileInput();

    cout << "All Pokemon Card Collection "
         << "Tracker tests passed!"
         << endl;

    return 0;
}
