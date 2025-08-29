#pragma once
#include <string>
#include <iostream>

class Member {
private:
	int id;
	std::string name;
	int borrowedBooksCount;

public:
	Member(int id = 0, const std::string& name = "");

	int getId() const;
	std::string getName() const;
	int getBorrowedBooksCount() const;

	void borrowBook();
	void returnBook();
	void display() const;

	std::string serialize() const;
	static Member deserialize(const std::string& data);
};
