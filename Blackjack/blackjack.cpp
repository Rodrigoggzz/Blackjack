#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <limits>

using namespace std;


struct Card {
    string rank;
    string suit;
    int value;
};


vector<Card> createShuffledDeck() {
    vector<Card> deck;
    vector<string> suits = { "Hearts", "Diamonds", "Clubs", "Spades" };
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
    vector<int> values = { 2,3,4,5,6,7,8,9,10,10,10,10,11 };

    for (const auto& suit : suits) {
        for (size_t i = 0; i < ranks.size(); ++i) {
            deck.push_back({ ranks[i], suit, values[i] });
        }
    }

    
    static random_device rd;
    static mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
    return deck;
}


int calculateHandValue(vector<Card>& hand) {
    int total = 0;
    int aceCount = 0;

    for (const auto& card : hand) {
        total += card.value;
        if (card.rank == "Ace") {
            ++aceCount;
        }
    }

  
    while (total > 21 && aceCount > 0) {
        total -= 10;
        --aceCount;
    }

    return total;
}


void displayHand(const vector<Card>& hand, const string& who) {
    cout << who << "'s hand:\n";
    for (const auto& card : hand) {
        cout << " - " << card.rank << " of " << card.suit << "\n";
    }
    cout << "Total: " << calculateHandValue(const_cast<vector<Card>&>(hand)) << "\n\n";
}

int main() {
    char playAgain;
    do {
        vector<Card> deck = createShuffledDeck();
        vector<Card> playerHand, dealerHand;

        
        playerHand.push_back(deck.back()); deck.pop_back();
        dealerHand.push_back(deck.back()); deck.pop_back();
        playerHand.push_back(deck.back()); deck.pop_back();
        dealerHand.push_back(deck.back()); deck.pop_back();

        cout << "\n=== Blackjack ===\n";
        displayHand(playerHand, "Player");

        
        string choice;
        while (true) {
            int playerTotal = calculateHandValue(playerHand);
            if (playerTotal > 21) {
                cout << "You bust! Dealer wins.\n";
                break;
            }

            cout << "Do you want another card? (H for hit / S for stand): ";
            cin >> choice;

            if (choice == "H" || choice == "h") {
                playerHand.push_back(deck.back());
                deck.pop_back();
                displayHand(playerHand, "Player");
            }
            else if (choice == "S" || choice == "s") {
                break;
            }
            else {
                cout << "Invalid input. Please enter H or S.\n";
            }
        }

        
        if (calculateHandValue(playerHand) <= 21) {
            
            cout << "\nDealer's turn...\n";
            displayHand(dealerHand, "Dealer");
            while (calculateHandValue(dealerHand) <= 17) {
                cout << "Dealer hits...\n";
                dealerHand.push_back(deck.back());
                deck.pop_back();
                displayHand(dealerHand, "Dealer");
            }

            int dealerTotal = calculateHandValue(dealerHand);
            int playerTotal = calculateHandValue(playerHand);

            if (dealerTotal > 21) {
                cout << "Dealer busts! You win.\n";
            }
            else if (dealerTotal > playerTotal) {
                cout << "Dealer wins with " << dealerTotal << ".\n";
            }
            else if (dealerTotal < playerTotal) {
                cout << "You win with " << playerTotal << "!\n";
            }
            else {
                cout << "Push! It's a tie.\n";
            }
        }

       
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "Thanks for playing Blackjack!\n";
    return 0;
}
