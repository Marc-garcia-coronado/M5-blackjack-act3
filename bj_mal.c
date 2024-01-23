#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Constant definition
#define TOTAL_CARDS 52
#define CARD_VALUES 13
#define MAX_HAND 10

// Card representation
char *values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *suits[] = {"Hearts", "Diamonds", "Spades", "Clovers"};

// Card structure
struct card {
    char *value;
    char *suit;
    int numericValue;
};

// Variables declaration
struct card deck[TOTAL_CARDS];
struct card playerHand[MAX_HAND];
int numPlayerCards = 0;
int playerSum = 0;
char choice;

// Prints the card value and the suit 
void showCard(struct card c) {
    printf("-> %s de %s\n", c.value, c.suit);
}

// Does the sum of the cards in your hand
int sumHand(struct card hand[], int numCards) {
    int sum = 0;
    int numAces = 0;
    for (int i = 0; i < numCards; i++) {
        // If the next card its an Ace, this means that the value of the card is 11 so we check if numeric value of the Ace plus the actual sum exceed 21 then we modify the numeric value of the Ace to 1
        if (hand[i].numericValue == 11 && hand[i].numericValue + sum > 21 ){
            sum += 1;
        } else {
            sum += hand[i].numericValue;
        }
    }
    return sum;
}

int main() {

    // Initialize deck
    for (int i = 0; i < TOTAL_CARDS; i++) {
        deck[i].value = values[i % CARD_VALUES];
        deck[i].suit = suits[i / CARD_VALUES];
        deck[i].numericValue = (i % CARD_VALUES) + 2; // Instead of adding 1, add 2 cause values array starts with 2, not with 1
        if (deck[i].numericValue > 10) deck[i].numericValue = 10; // If the numeric value is greater than 10 this means is a figure (J, Q, K, A)
        if (i % CARD_VALUES == CARD_VALUES - 1) deck[i].numericValue = 11; // If its the last card which is the A this counts as 11
    }

    // Shuffle deck
    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARDS; i++) {
        int j = rand() % TOTAL_CARDS;
        struct card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    printf("Welcome to Blackjack!\n");

    playerHand[numPlayerCards++] = deck[0];
    playerHand[numPlayerCards++] = deck[1];
    playerSum = sumHand(playerHand, numPlayerCards);

    printf("Your cards:\n");
    showCard(playerHand[0]);
    showCard(playerHand[1]);
    printf("Total sum: %d\n", playerSum);

    // Game loop
    while (playerSum < 21) {
        printf("Do you want another cards? (s/n): ");
        scanf(" %c", &choice);

        if (choice == 's' || choice == 'S') {
            playerHand[numPlayerCards] = deck[numPlayerCards + 1];
            playerSum = sumHand(playerHand, ++numPlayerCards);

            printf("New cards:\n");
            showCard(playerHand[numPlayerCards - 1]);
            printf("Total sum: %d\n", playerSum);
        } else {
            break;
        }
    }

    if (playerSum == 21) {
        printf("BlackJack! You Win.\n");
    } else if (playerSum > 21) {
        printf("You have exceeded. Game over.\n");
    } else {
        printf("You have stood with. %d Game over.\n", playerSum);
    }

    return 0;
}
