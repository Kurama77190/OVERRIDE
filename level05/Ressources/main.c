#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char input[100];
	unsigned int i = 0;

	// Lecture utilisateur (maximum 99 caractères + '\0')
	fgets(input, sizeof(input), stdin);

	while (1) {
		// Calcul de la longueur de la chaîne (simule la boucle avec uVar2)
		size_t len = strnlen(input, 100);

		if (i >= len) {
			// Print vulnérable (format string)
			printf(input);
			exit(0);
		}

		// Si le caractère est une lettre majuscule A-Z (ASCII @ < c < [)
		if (input[i] && input[i] >= 'A' && input[i] <= 'Z') {
			input[i] += 32;  // Convertit en minuscule (ex: A → a)
		}
		i++;
	}

	return (0);
}