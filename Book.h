#pragma once
#include <string>
#include <iostream>

class Book {
private:
	int id;
	std::string title;
	std::string author;
	bool isBorrowed;
	int timesBorrowed;

public:
	Book(int id = 0, const std::string& title = "", const std::string& author = "");

	int getId() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	bool getIsBorrowed() const;
	int getTimesBorrowed() const;

	void borrowBook();
	void returnBook();
	void display() const;

	std::string serialize() const;
	static Book deserialize(const std::string& data);
};
