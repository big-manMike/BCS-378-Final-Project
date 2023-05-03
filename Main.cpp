#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int rotor_size = 26;
string rotor1;
string rotor2;
string rotor3;
// The rotor class represents a single rotor in the Enigma machine
class Rotor {
private:
	char mapping[rotor_size];
	int offset;

public:
	Rotor(string mapping_str) {
		offset = 0;
		for (int i = 0; i < rotor_size; i++) {
			mapping[i] = mapping_str[i];
		}
	}

	char encrypt(char c) {
		int index = (c - 'A' + offset) % rotor_size;
		char result = mapping[index];
		index = (index - offset + rotor_size) % rotor_size;
		offset = (offset + 1) % rotor_size;
		return result;
	}

	void reset() {
		offset = 0;
	}
};

// The enigma class represents the entire Enigma machine, which is composed of several rotors
class Enigma {
private:
	Rotor rotor1, rotor2, rotor3;

public:
	Enigma(string mapping1, string mapping2, string mapping3)
		: rotor1(mapping1), rotor2(mapping2), rotor3(mapping3)
	{
		srand(time(0));
		int offset1 = rand() % rotor_size;
		int offset2 = rand() % rotor_size;
		int offset3 = rand() % rotor_size;
		for (int i = 0; i < offset1; i++) rotor1.encrypt('A');
		for (int i = 0; i < offset2; i++) rotor2.encrypt('A');
		for (int i = 0; i < offset3; i++) rotor3.encrypt('A');
	}

	char encrypt(char c) {
		char result = rotor1.encrypt(c);
		result = rotor2.encrypt(result);
		result = rotor3.encrypt(result);
		result = 'A' + (result - 'A' + 13) % rotor_size; // reflector
		result = rotor3.encrypt(result);
		result = rotor2.encrypt(result);
		result = rotor1.encrypt(result);
		return result;
	}

	void reset() {
		rotor1.reset();
		rotor2.reset();
		rotor3.reset();
	}
};

int main() {
	cout << "Enter rotor mappings with 26 letters and non repeating letters" << endl;
	getline(cin, rotor1);
	getline(cin, rotor2);
	getline(cin, rotor3);
	Enigma enigma(rotor1, rotor2, rotor3);
	string plaintext, ciphertext;
	cout << "Enter plaintext: " << endl;
	getline(cin, plaintext);
	for (char c : plaintext) {
		if (c >= 'A' && c <= 'Z') {
			ciphertext += enigma.encrypt(c);
		}
	}
	
	cout << "Ciphertext: " << ciphertext << endl;
	return 0;
}
