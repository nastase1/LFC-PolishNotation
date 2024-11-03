#include<iostream>
#include<string>
#include<fstream>
#include<stack>

int prioritate(char op) {
	if (op == '(')
		return 0;
	if (op == '|')
		return 1;
	if (op == '.')
		return 2;
	if (op == '*')
		return 3;
	return -1;
}

std::string FormaPoloneza(std::string& expresie) {
	std::string fp;
	std::stack<char> operatori;
	for (auto& curent : expresie) {
		if (isalnum(curent))
			fp.push_back(curent);
		else
			if (curent == ')') {
				while (!operatori.empty() && operatori.top() != '(') {
					fp.push_back(operatori.top());
					operatori.pop();
				}
				if (!operatori.empty())
					operatori.pop();
			}
			else {
				while (!operatori.empty() && prioritate(operatori.top()) >= prioritate(curent)) {
					fp.push_back(operatori.top());
					operatori.pop();
				}
				operatori.push(curent);
			}
	}
	while (!operatori.empty()) {
		fp.push_back(operatori.top());
		operatori.pop();
	}
	return fp;
}

int main() {
	std::string expresie;
	std::ifstream f("fisier.in");
	f >> expresie;
	std::cout << "Expresia este:" << expresie << "\n";
	std::cout << "Expresia dupa forma normala poloneza:" << FormaPoloneza(expresie) << "\n";
	return 0;
}