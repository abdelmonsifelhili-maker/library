#include "Library.h"
#include "ConsoleColors.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <iomanip>

// ------------------ إدارة الكتب والأعضاء ------------------

void Library::addBook(const Book& book) {
	for (const auto& b : books)
		if (b.getId() == book.getId()) {
			std::cout << RED << "Error: Book ID already exists.\n" << RESET;
			return;
		}
	books.push_back(book);
}

void Library::addMember(const Member& member) {
	for (const auto& m : members)
		if (m.getId() == member.getId()) {
			std::cout << RED << "Error: Member ID already exists.\n" << RESET;
			return;
		}
	members.push_back(member);
}

void Library::addNewBook() {
	int id;
	std::string title, author;

	while (true) {
		std::cout << "Enter Book ID (positive number): ";
		std::cin >> id;
		if (std::cin.fail() || id <= 0) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << RED << "Invalid ID. Please enter a positive number.\n" << RESET;
		}
		else { std::cin.ignore(10000, '\n'); break; }
	}

	while (true) {
		std::cout << "Enter Book Title: ";
		std::getline(std::cin, title);
		if (title.empty()) std::cout << RED << "Title cannot be empty.\n" << RESET;
		else break;
	}

	while (true) {
		std::cout << "Enter Author Name: ";
		std::getline(std::cin, author);
		if (author.empty()) std::cout << RED << "Author cannot be empty.\n" << RESET;
		else break;
	}

	addBook(Book(id, title, author));
	std::cout << GREEN << "Book added successfully.\n" << RESET;
}

void Library::addNewMember() {
	int id;
	std::string name;

	while (true) {
		std::cout << "Enter Member ID (positive number): ";
		std::cin >> id;
		if (std::cin.fail() || id <= 0) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << RED << "Invalid ID. Please enter a positive number.\n" << RESET;
		}
		else { std::cin.ignore(10000, '\n'); break; }
	}

	while (true) {
		std::cout << "Enter Member Name: ";
		std::getline(std::cin, name);
		if (name.empty()) std::cout << RED << "Name cannot be empty.\n" << RESET;
		else break;
	}

	addMember(Member(id, name));
	std::cout << GREEN << "Member added successfully.\n" << RESET;
}

// ------------------ استعارة وإرجاع الكتب ------------------

void Library::borrowBook(int bookId, int memberId) {
	Book* foundBook = nullptr;
	Member* foundMember = nullptr;

	for (auto& book : books)
		if (book.getId() == bookId) { foundBook = &book; break; }

	for (auto& member : members)
		if (member.getId() == memberId) { foundMember = &member; break; }

	if (!foundBook) { std::cout << RED << "Book not found.\n" << RESET; return; }
	if (!foundMember) { std::cout << RED << "Member not found.\n" << RESET; return; }
	if (foundBook->getIsBorrowed()) { std::cout << RED << "Book already borrowed.\n" << RESET; return; }

	foundBook->borrowBook();
	foundMember->borrowBook();
	std::cout << GREEN << "Book borrowed successfully.\n" << RESET;
}

void Library::borrowBookByUser() {
	int bookId, memberId;
	std::cout << "Enter Book ID to borrow: ";
	std::cin >> bookId;
	std::cout << "Enter Member ID: ";
	std::cin >> memberId;
	borrowBook(bookId, memberId);
}

void Library::returnBook(int bookId, int memberId) {
	Book* foundBook = nullptr;
	Member* foundMember = nullptr;

	for (auto& book : books)
		if (book.getId() == bookId) { foundBook = &book; break; }

	for (auto& member : members)
		if (member.getId() == memberId) { foundMember = &member; break; }

	if (!foundBook) { std::cout << RED << "Book not found.\n" << RESET; return; }
	if (!foundMember) { std::cout << RED << "Member not found.\n" << RESET; return; }
	if (!foundBook->getIsBorrowed()) { std::cout << RED << "Book is not borrowed.\n" << RESET; return; }

	foundBook->returnBook();
	foundMember->returnBook();
	std::cout << GREEN << "Book returned successfully.\n" << RESET;
}

void Library::returnBookByUser() {
	int bookId, memberId;
	std::cout << "Enter Book ID to return: ";
	std::cin >> bookId;
	std::cout << "Enter Member ID: ";
	std::cin >> memberId;
	returnBook(bookId, memberId);
}

// ------------------ عرض البيانات ------------------

void Library::displayBooks() const {
	if (books.empty()) { std::cout << RED << "No books in library.\n" << RESET; return; }

	std::cout << CYAN << std::left << std::setw(5) << "ID"
		<< std::setw(30) << "Title"
		<< std::setw(20) << "Author"
		<< std::setw(10) << "Status" << RESET << std::endl;

	for (const auto& book : books) {
		std::string status = book.getIsBorrowed() ? RED "Borrowed" RESET : GREEN "Available" RESET;
		std::cout << std::left << std::setw(5) << book.getId()
			<< std::setw(30) << book.getTitle()
			<< std::setw(20) << book.getAuthor()
			<< std::setw(10) << status
			<< std::endl;
	}
}

void Library::displayMembers() const {
	if (members.empty()) { std::cout << RED << "No members in library.\n" << RESET; return; }

	std::cout << CYAN << std::left << std::setw(5) << "ID"
		<< std::setw(25) << "Name"
		<< std::setw(15) << "Borrowed Books" << RESET << std::endl;

	for (const auto& member : members) {
		std::cout << std::left << std::setw(5) << member.getId()
			<< std::setw(25) << member.getName()
			<< std::setw(15) << member.getBorrowedBooksCount()
			<< std::endl;
	}
}

void Library::displayAvailableBooks() const {
	bool found = false;
	std::cout << CYAN << "\n=== Available Books ===\n" << RESET;
	for (const auto& book : books) {
		if (!book.getIsBorrowed()) {
			found = true;
			std::string status = GREEN "Available" RESET;
			std::cout << std::left << std::setw(5) << book.getId()
				<< std::setw(30) << book.getTitle()
				<< std::setw(20) << book.getAuthor()
				<< std::setw(10) << status << std::endl;
		}
	}
	if (!found) std::cout << RED << "No available books.\n" << RESET;
}

void Library::displayBorrowedBooks() const {
	bool found = false;
	std::cout << CYAN << "\n=== Borrowed Books ===\n" << RESET;
	for (const auto& book : books) {
		if (book.getIsBorrowed()) {
			found = true;
			std::string status = RED "Borrowed" RESET;
			std::cout << std::left << std::setw(5) << book.getId()
				<< std::setw(30) << book.getTitle()
				<< std::setw(20) << book.getAuthor()
				<< std::setw(10) << status << std::endl;
		}
	}
	if (!found) std::cout << RED << "No borrowed books.\n" << RESET;
}

void Library::displayActiveMembers() const {
	bool found = false;
	std::cout << CYAN << "\n=== Active Members ===\n" << RESET;
	for (const auto& member : members) {
		if (member.getBorrowedBooksCount() > 0) {
			found = true;
			std::cout << std::left << std::setw(5) << member.getId()
				<< std::setw(25) << member.getName()
				<< std::setw(15) << member.getBorrowedBooksCount()
				<< std::endl;
		}
	}
	if (!found) std::cout << RED << "No active members.\n" << RESET;
}

// ------------------ البحث ------------------

void Library::searchBookByTitle(const std::string& title) const {
	bool found = false;
	for (const auto& book : books) {
		if (book.getTitle().find(title) != std::string::npos) {
			book.display();
			found = true;
		}
	}
	if (!found) std::cout << RED << "No books found with this title.\n" << RESET;
}

void Library::searchBookByAuthor(const std::string& author) const {
	bool found = false;
	for (const auto& book : books) {
		if (book.getAuthor().find(author) != std::string::npos) {
			book.display();
			found = true;
		}
	}
	if (!found) std::cout << RED << "No books found for this author.\n" << RESET;
}

void Library::searchMemberByName(const std::string& name) const {
	bool found = false;
	for (const auto& member : members) {
		if (member.getName().find(name) != std::string::npos) {
			member.display();
			found = true;
		}
	}
	if (!found) std::cout << RED << "No members found with this name.\n" << RESET;
}

// ------------------ الفرز ------------------

void Library::sortBooksByTitle() {
	std::sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
		return a.getTitle() < b.getTitle();
		});
	std::cout << GREEN << "Books sorted by title.\n" << RESET;
}

void Library::sortBooksById() {
	std::sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
		return a.getId() < b.getId();
		});
	std::cout << GREEN << "Books sorted by ID.\n" << RESET;
}

void Library::sortMembersByName() {
	std::sort(members.begin(), members.end(), [](const Member& a, const Member& b) {
		return a.getName() < b.getName();
		});
	std::cout << GREEN << "Members sorted by name.\n" << RESET;
}

void Library::sortMembersById() {
	std::sort(members.begin(), members.end(), [](const Member& a, const Member& b) {
		return a.getId() < b.getId();
		});
	std::cout << GREEN << "Members sorted by ID.\n" << RESET;
}

// ------------------ التقارير ------------------

void Library::reportTopBorrowedBooks(int topN) const {
	std::vector<Book> borrowedBooks;
	for (const auto& book : books)
		if (book.getTimesBorrowed() > 0)
			borrowedBooks.push_back(book);

	std::sort(borrowedBooks.begin(), borrowedBooks.end(), [](const Book& a, const Book& b) {
		return a.getTimesBorrowed() > b.getTimesBorrowed();
		});

	std::cout << CYAN << "\n=== Top Borrowed Books ===\n" << RESET;
	int count = 0;
	for (const auto& book : borrowedBooks) {
		if (count >= topN) break;
		book.display();
		std::cout << "Times Borrowed: " << book.getTimesBorrowed() << "\n";
		count++;
	}
	if (borrowedBooks.empty()) std::cout << RED << "No borrowed books yet.\n" << RESET;
}

void Library::reportTopActiveMembers(int topN) const {
	std::vector<Member> activeMembers;
	for (const auto& member : members)
		if (member.getBorrowedBooksCount() > 0)
			activeMembers.push_back(member);

	std::sort(activeMembers.begin(), activeMembers.end(), [](const Member& a, const Member& b) {
		return a.getBorrowedBooksCount() > b.getBorrowedBooksCount();
		});

	std::cout << CYAN << "\n=== Top Active Members ===\n" << RESET;
	int count = 0;
	for (const auto& member : activeMembers) {
		if (count >= topN) break;
		member.display();
		count++;
	}
	if (activeMembers.empty()) std::cout << RED << "No active members yet.\n" << RESET;
}

void Library::reportTopAuthors(int topN) const {
	std::map<std::string, int> authorCount;
	for (const auto& book : books)
		authorCount[book.getAuthor()] += book.getTimesBorrowed();

	std::vector<std::pair<std::string, int>> authors(authorCount.begin(), authorCount.end());
	std::sort(authors.begin(), authors.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
		});

	std::cout << CYAN << "\n=== Top Authors ===\n" << RESET;
	int count = 0;
	for (const auto& author : authors) {
		if (count >= topN) break;
		std::cout << "Author: " << author.first
			<< ", Times Borrowed: " << author.second << "\n";
		count++;
	}
	if (authors.empty()) std::cout << RED << "No borrowed books yet.\n" << RESET;
}

// ------------------ حفظ وتحميل ------------------

void Library::saveData() const {
	std::ofstream booksFile("books.txt");
	for (const auto& book : books)
		booksFile << book.serialize() << "\n";
	booksFile.close();

	std::ofstream membersFile("members.txt");
	for (const auto& member : members)
		membersFile << member.serialize() << "\n";
	membersFile.close();
}

void Library::loadData() {
	books.clear();
	members.clear();

	std::ifstream booksFile("books.txt");
	std::string line;
	while (std::getline(booksFile, line))
		books.push_back(Book::deserialize(line));
	booksFile.close();

	std::ifstream membersFile("members.txt");
	while (std::getline(membersFile, line))
		members.push_back(Member::deserialize(line));
	membersFile.close();
}
