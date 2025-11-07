#include <stdio.h>
#include <string.h>

/*  Dans le code assemble on on peut voir que la clé varie de 1 a 21.
    On peut donc essayer toutes les clés possibles pour déchiffrer le message.
    Le message chiffré est "Q}|u`sfg~sf{}|a3" et on sait que le message déchiffré doit être "Congratulation!".
*/

int main(void)
{
    char encrypted[] = "Q}|u`sfg~sf{}|a3";
    int key;
    char result[100];

    for (key = 1; key <= 21; key++)
    {
        // On copie pour chaque clé
        for (int i = 0; i < strlen(encrypted); i++)
        {
            result[i] = encrypted[i] ^ key; // Déchiffrement par XOR avec la clé
        }
        result[strlen(encrypted)] = '\0'; // fin de chaîne

        printf("Key %2d: %s\n", key, result);
    }

    return 0;
}
