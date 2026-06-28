all: vigenere autofill encryption

vigenere: vigenere.c
	gcc -Wall -std=c99 vigenere.c -o vigenere -lm

autofill: autofill.c
	gcc -Wall -std=c99 autofill.c -o autofill -lm

encryption: encryption.c
	gcc -Wall -std=c99 encryption.c -o encryption -lm

clean:
	rm vigenere
	rm autofill
	rm encryption
