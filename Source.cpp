#include <iostream>
#include <fstream>
#include "StackArray.h"

char* process(char* dest, const char* scr, const size_t stackSize);

int main() {
	try {
		std::string text, ans;
		int maxSize;
		std::string fileName;
		std::fstream in;
		std::cout << "Enter file name: ";
		std::cin >> fileName;
		in.open(fileName);
		if (!in.is_open()) {
			throw std::exception("failed to open fail.");
		}
		if (in.peek() == EOF) {
			throw std::exception("file is empty.");
		}

		while (!in.eof()) {
			in >> maxSize;
			if (in.peek() != '\n' || maxSize < 0) {
				throw std::exception("incorrect size.");
			}
			in.ignore();
			char* dest = new char[maxSize];
			char* src = new char[maxSize];
			in.getline(src, maxSize);
			std::cout << process(dest, src, maxSize) << "\n\n";
			delete[] src;
			delete[] dest;
		}
		in.close();
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}
	return 0;
}

char* process(char* dest, const char* scr, const size_t stackSize) {
	StackArray<char> stack(stackSize);
	if (!isalpha(*scr)) {
		throw std::exception("wrong first simbol.");
	}
	while (*scr) {
		if (isalpha(*scr) || *scr == ' ') {
			stack.push(*scr);
			++scr;
			continue;
		}
		switch (*scr) {
		case '$':
			if (stack.isEmpty()) {
				throw std::exception("wrong order of main simbol.");
			}
			while (stack.top() != ' ' && !stack.isEmpty()) {
				stack.pop();
			}
			if (stack.top() == ' ') {
				stack.pop();
			}
			break;
		case '*': 
			if (stack.isEmpty()) {
				throw std::exception("wrong order of main simbol.");
			}
			stack.pop(); 
			break;
		default: throw std::exception("wrong simbol in text."); break;
		}
		++scr;
	}
	int i = 0;
	while (!stack.isEmpty()) {
		*(dest + i) = stack.pop();
		++i;
	}
	for (int j = 0, l = i; j < l / 2; j++) {
		char c = dest[j];
		dest[j] = dest[l - j - 1];
		dest[l - j - 1] = c;
	}
	*(dest + i) = '\0';
	return dest;
}