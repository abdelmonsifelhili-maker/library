#pragma once
#include <vector>
#include <string>
#include "Book.h"
#include "Member.h"

class Library {
private:
	std::vector<Book> books;
	std::vector<Member> members;

public:
	// إدارة الكتب والأعضاء
	void addBook(const Book& book);
	void addMember(const Member& member);
	void addNewBook();
	void addNewMember();

	void borrowBook(int bookId, int memberId);
	void borrowBookByUser();
	void returnBook(int bookId, int memberId);
	void returnBookByUser();

	void displayBooks() const;
	void displayMembers() const;
	void displayAvailableBooks() const;
	void displayBorrowedBooks() const;
	void displayActiveMembers() const;

	// البحث
	void searchBookByTitle(const std::string& title) const;
	void searchBookByAuthor(const std::string& author) const;
	void searchMemberByName(const std::string& name) const;

	// الفرز
	void sortBooksByTitle();
	void sortBooksById();
	void sortMembersByName();
	void sortMembersById();

	// التقارير
	void reportTopBorrowedBooks(int topN = 5) const;
	void reportTopActiveMembers(int topN = 5) const;
	void reportTopAuthors(int topN = 5) const;

	// حفظ و تحميل البيانات
	void saveData() const;
	void loadData();
};
