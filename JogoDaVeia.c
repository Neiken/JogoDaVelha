#include <stdio.h>
#include <stdlib.h>

char pixels[] = "\n 1 | 2 | 3 \n-----------\n 4 | 5 | 6 \n-----------\n 7 | 8 | 9 \n\n";

char *X, *O;

unsigned emptyNodes = 9;

void replace(char c, char v)
{
	for(unsigned x = 0; x < sizeof(pixels); x++) { if(pixels[x] == c) { pixels[x] = v; break; } }
}

int has(char *a, unsigned len, char b)
{
	for(unsigned x = 0; x < len; x++) { if(a[x] == b) { return 1; } }

	return 0;
}

int win(char *sc, unsigned len)
{
	unsigned n[9];

	for(unsigned x = 0; x < 9; x++) { n[x] = has(sc, len, (x + 1) + '0'); }

	return
		(n[0] && n[1] && n[2]) ||
		(n[3] && n[4] && n[5]) ||
		(n[6] && n[7] && n[8]) ||

		(n[0] && n[3] && n[6]) ||
		(n[1] && n[4] && n[7]) ||
		(n[2] && n[5] && n[8]) ||

		(n[0] && n[4] && n[8]) ||
		(n[2] && n[4] && n[6]);
}

int main()
{
	system("clear");

	printf("%s", pixels);

	unsigned player = 1;
	char symbol[] = {'X', 'O'};

	while(emptyNodes > 0)
	{
		printf("Jogador %u (%c): ", player, symbol[player-1]);

		int node = 0;
		scanf("%d", &node);

		if(node < 1 || node > 9) { system("clear"); printf("Selecione uma das casas disponiveis!\n"); printf("%s", pixels); continue; }
		else if(has((player == 1 ? O : X), 9 - (emptyNodes + emptyNodes % (player == 1 ? 3 : 2)), node + '0')) 
		{ 
			system("clear"); 

			printf("Esta casa ja esta em uso! Selecione uma das casas disponiveis!\n"); 

			printf("%s", pixels);

			continue; 
	  }

		emptyNodes--;

		replace(node + '0', symbol[player-1]);

		system("clear");

		printf("%s", pixels);

		if(player == 1)
		{
			unsigned len = 9 - (emptyNodes + emptyNodes % 2);

			char *antX = X;
			X = (char *) malloc(len * sizeof(char));

	    for(unsigned x = 0; x < len-1; x++) { X[x] = antX[x]; }

			X[len-1] = node + '0';

			free(antX);

			if(win(X, len)) { printf("Jogador 1 (X) venceu!\n"); return 0; }
		}
		else
		{
			unsigned len = 9 - (emptyNodes + emptyNodes % 3);

			char *antO = O;
			O = (char *) malloc(len * sizeof(char));

			for(unsigned x = 0; x < len-1; x++) { O[x] = antO[x]; }

			O[len-1] = node + '0';

			free(antO);

			if(win(O, len)) { printf("Jogador 2 (O) venceu!\n"); return 0; }
		}

		player = (player == 1 ? 2 : 1);
	}

	printf("\nEmpate!");

	return 0;
}
