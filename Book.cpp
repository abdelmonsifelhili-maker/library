#include "Book.h"
#include <sstream>

Book::Book(int id, const std::string& title, const std::string& author)
	: id(id), title(title), author(author), isBorrowed(false), timesBorrowed(0) {}

int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
bool Book::getIsBorrowed() const { return isBorrowed; }
int Book::getTimesBorrowed() const { return timesBorrowed; }

void Book::borrowBook() {
	if (!isBorrowed) {
		isBorrowed = true;
		timesBorrowed++;
	}
}

void Book::returnBook() {
	if (isBorrowed) {
		isBorrowed = false;
	}
}

void Book::display() const {
	std::cout << id << " | " << title << " | " << author
		<< " | Borrowed: " << (isBorrowed ? "Yes" : "No")
		<< " | Times Borrowed: " << timesBorrowed << std::endl;
}

std::string Book::serialize() const {
	return std::to_string(id) + "|" + title + "|" + author + "|" +
		std::to_string(isBorrowed) + "|" + std::to_string(timesBorrowed);
}

Book Book::deserialize(const std::string& data) {
	std::stringstream ss(data);
	std::string token;
	int id, borrowed, times;
	std::string title, author;

	std::getline(ss, token, '|');
	id = std::stoi(token);
	std::getline(ss, title, '|');
	std::getline(ss, author, '|');
	std::getline(ss, token, '|');
	borrowed = std::stoi(token);
	std::getline(ss, token, '|');
	times = std::stoi(token);

	Book b(id, title, author);
	if (borrowed) b.borrowBook();
	b.timesBorrowed = times;
	return b;
}
