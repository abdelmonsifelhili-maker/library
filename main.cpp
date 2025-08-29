#include "Library.h"
#include <iostream>
#include "ConsoleColors.h"

int main() {
	Library library;
	library.loadData();  // Load existing data from files

	int choice;

	do {
		std::cout << CYAN << "\n=== Library Management System ===\n" << RESET;
		std::cout << "1. Add New Book\n";
		std::cout << "2. Add New Member\n";
		std::cout << "3. Display All Books\n";
		std::cout << "4. Display All Members\n";
		std::cout << "5. Borrow Book\n";
		std::cout << "6. Return Book\n";
		std::cout << "7. Save Data\n";
		std::cout << "8. Search Book by Title\n";
		std::cout << "9. Search Book by Author\n";
		std::cout << "10. Search Member by Name\n";
		std::cout << "11. Sort Books by Title\n";
		std::cout << "12. Sort Books by ID\n";
		std::cout << "13. Sort Members by Name\n";
		std::cout << "14. Sort Members by ID\n";
		std::cout << "15. Display Available Books\n";
		std::cout << "16. Display Borrowed Books\n";
		std::cout << "17. Display Active Members\n";
		std::cout << "18. Top Borrowed Books\n";
		std::cout << "19. Top Active Members\n";
		std::cout << "20. Top Authors\n";
		std::cout << "0. Exit\n";
		std::cout << YELLOW << "Enter your choice: " << RESET;
		std::cin >> choice;

		switch (choice) {
		case 1:
			library.addNewBook();
			break;
		case 2:
			library.addNewMember();
			break;
		case 3:
			library.displayBooks();
			break;
		case 4:
			library.displayMembers();
			break;
		case 5:
			library.borrowBookByUser(); // استخدام الدالة الصحيحة
			break;
		case 6:
			library.returnBookByUser(); // استخدام الدالة الصحيحة
			break;
		case 7:
			library.saveData();
			std::cout << GREEN << "Data saved successfully.\n" << RESET;
			break;
		case 8: {
			std::cin.ignore();
			std::string title;
			std::cout << "Enter title to search: ";
			std::getline(std::cin, title);
			library.searchBookByTitle(title);
			break;
		}
		case 9: {
			std::cin.ignore();
			std::string author;
			std::cout << "Enter author to search: ";
			std::getline(std::cin, author);
			library.searchBookByAuthor(author);
			break;
		}
		case 10: {
			std::cin.ignore();
			std::string name;
			std::cout << "Enter member name to search: ";
			std::getline(std::cin, name);
			library.searchMemberByName(name);
			break;
		}
		case 11:
			library.sortBooksByTitle();
			break;
		case 12:
			library.sortBooksById();
			break;
		case 13:
			library.sortMembersByName();
			break;
		case 14:
			library.sortMembersById();
			break;
		case 15:
			library.displayAvailableBooks();
			break;
		case 16:
			library.displayBorrowedBooks();
			break;
		case 17:
			library.displayActiveMembers();
			break;
		case 18:
			library.reportTopBorrowedBooks(5); // يمكن تغيير الرقم لعرض أكثر أو أقل
			break;
		case 19:
			library.reportTopActiveMembers(5); // يجب أن تضيف دالة في Library إذا لم تكن موجودة
			break;
		case 20:
			library.reportTopAuthors(5);
			break;
		case 0:
			library.saveData();
			std::cout << GREEN << "Exiting program. Goodbye!\n" << RESET;
			break;
		default:
			std::cout << RED << "Invalid choice. Please try again.\n" << RESET;
		}

	} while (choice != 0);

	return 0;
}
