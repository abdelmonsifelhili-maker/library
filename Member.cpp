#include "Member.h"
#include <sstream>

Member::Member(int id, const std::string& name)
	: id(id), name(name), borrowedBooksCount(0) {}

int Member::getId() const { return id; }
std::string Member::getName() const { return name; }
int Member::getBorrowedBooksCount() const { return borrowedBooksCount; }

void Member::borrowBook() {
	borrowedBooksCount++;
}

void Member::returnBook() {
	if (borrowedBooksCount > 0) borrowedBooksCount--;
}

void Member::display() const {
	std::cout << id << " | " << name
		<< " | Borrowed Books: " << borrowedBooksCount << std::endl;
}

std::string Member::serialize() const {
	return std::to_string(id) + "|" + name + "|" + std::to_string(borrowedBooksCount);
}

Member Member::deserialize(const std::string& data) {
	std::stringstream ss(data);
	std::string token;
	int id, count;
	std::string name;

	std::getline(ss, token, '|');
	id = std::stoi(token);
	std::getline(ss, name, '|');
	std::getline(ss, token, '|');
	count = std::stoi(token);

	Member m(id, name);
	m.borrowedBooksCount = count;
	return m;
}
