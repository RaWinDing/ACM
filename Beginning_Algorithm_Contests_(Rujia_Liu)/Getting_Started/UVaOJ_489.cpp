// UVaOJ 489
// Hangman Judge
// by A Code Rabbit

#include <cstdio>
#include <cstring>

int num_round;
char solution[10000];
char guess[10000];
bool letter[26];

int main() {
    while (scanf("%d", &num_round) && num_round != -1) {
        getchar();
        gets(solution);
        gets(guess);
        memset(letter, false, sizeof(letter));
        int cnt_letter = 0;
        for (int i = 0; i < strlen(solution); i++)
            if (!letter[solution[i] - 'a']) {
                letter[solution[i] - 'a'] =  true;
                cnt_letter++;
            }
        int cnt_wrong = 0;
        bool end = false;
        for (int i = 0; i < strlen(guess); i++) {
            if (letter[guess[i] - 'a']) {
                cnt_letter--;
                letter[guess[i] - 'a'] = false;
            } else {
                cnt_wrong++;
            }
            if (!cnt_letter || cnt_wrong >= 7) {
                printf("Round %d\n", num_round);
                printf("%s\n", cnt_letter ? "You lose." : "You win.");
                end = true;
                break;
            }
        }
        if (!end)
            printf("Round %d\nYou chickened out.\n", num_round);
    }

    return 0;
}
