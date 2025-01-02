#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Book Ŭ����: �� å�� ���� ����
class Book {
public:
    string title;   // å ����
    string author;  // å ����

    // ������: å ����� ���ڸ� �޾Ƽ� �ʱ�ȭ
    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

// BorrowManager Ŭ����: å �뿩 �� �ݳ� ����
class BorrowManager {
private:
    unordered_map<string, int> stock;  // å �������� ��� ����

public:
    // å�� ��� �ʱ�ȭ
    void initializeStock(Book& book, int quantity = 3) {
        stock[book.title] = quantity;
        cout << book.title << "�� �ʱ� ��� " << quantity << "������ �����Ǿ����ϴ�." << endl;
    }

    // å �뿩 ó��
    void borrowBook(const string& title) {
        if (stock.find(title) != stock.end() && stock[title] > 0) {
            stock[title]--;
            cout << title << "��(��) �뿩�Ǿ����ϴ�." << endl;
        }
        else {
            cout << title << "��(��) �뿩�� �� �����ϴ�. ��� �����ϴ�." << endl;
        }
    }

    // �۰��� å �뿩 ó��
    void borrowBookByAuthor(const string& author, const vector<Book*>& booksByAuthor) {
        bool bookFound = false;
        for (auto& book : booksByAuthor) {
            if (stock.find(book->title) != stock.end() && stock[book->title] > 0) {
                stock[book->title]--;
                cout << book->title << "��(��) �뿩�Ǿ����ϴ�." << endl;
                bookFound = true;
                break;
            }
        }
        if (!bookFound) {
            cout << author << "�� å�� �뿩�� �� �����ϴ�. ��� �����ϴ�." << endl;
        }
    }

    // å �ݳ� ó��
    void returnBook(const string& title) {
        if (stock.find(title) != stock.end()) {
            stock[title]++;
            cout << title << "��(��) �ݳ��Ǿ����ϴ�." << endl;
        }
        else {
            cout << title << "��(��) �뿩 ����� �����ϴ�." << endl;
        }
    }

    // �۰��� å �ݳ� ó��
    void returnBookByAuthor(const string& author, const vector<Book*>& booksByAuthor) {
        bool bookFound = false;
        for (auto& book : booksByAuthor) {
            if (stock.find(book->title) != stock.end()) {
                stock[book->title]++;
                cout << book->title << "��(��) �ݳ��Ǿ����ϴ�." << endl;
                bookFound = true;
                break;
            }
        }
        if (!bookFound) {
            cout << author << "�� å�� �ݳ��� �� �����ϴ�. �뿩 ����� �����ϴ�." << endl;
        }
    }

    // ���� ��� ���� ���
    void displayStock() {
        if (stock.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }
        cout << "���� å ��� ���:" << endl;
        for (const auto& entry : stock) {
            cout << entry.first << ": " << entry.second << "��" << endl;
        }
    }
};

// BookManager Ŭ����: å ����
class BookManager {
private:
    vector<Book> books;  // å ��� ����

public:
    // å �������� å�� ã�� �Լ�
    Book* findBookByTitle(const string& title) {
        for (auto& book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr;  // å�� ã�� ���� ���
    }

    // å �۰��� å�� ã�� �Լ� (���� å�� ��ȯ)
    vector<Book*> findBooksByAuthor(const string& author) {
        vector<Book*> booksByAuthor;
        for (auto& book : books) {
            if (book.author == author) {
                booksByAuthor.push_back(&book);
            }
        }
        return booksByAuthor;
    }

    // å �߰� �޼���
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    }

    // ��� å ��� �޼���
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (const auto& book : books) {
            cout << "- " << book.title << " by " << book.author << endl;
        }
    }

    // �������� å ��ȯ �޼���
    Book* getBookByTitle(const string& title) {
        return findBookByTitle(title);  // �������� ã��
    }

    // �۰��� å ��ȯ �޼���
    vector<Book*> getBooksByAuthor(const string& author) {
        return findBooksByAuthor(author);  // �۰��� ã��
    }
};

int main() {
    BookManager bookManager;
    BorrowManager borrowManager;

    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl;
        cout << "2. ��� å ���" << endl;
        cout << "3. å �뿩" << endl;
        cout << "4. å �ݳ�" << endl;
        cout << "5. ��� ����" << endl;
        cout << "6. ����" << endl;
        cout << "����: ";

        int choice;
        cin >> choice;


        if (choice == 1) {
            string title, author;
            cout << "å ����: ";
            cin.ignore();  // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title);
            cout << "å ����: ";
            getline(cin, author);
            bookManager.addBook(title, author); // å �߰�
            borrowManager.initializeStock(*bookManager.getBookByTitle(title)); // ��� �ʱ�ȭ
        }
        else if (choice == 2) {
            bookManager.displayAllBooks();  // ��� å ���
        }
        else if (choice == 3) {
            string titleOrAuthor;
            cout << "�뿩�� å ���� �Ǵ� �۰�: ";
            cin.ignore();  // �Է� ���� ����
            getline(cin, titleOrAuthor);

            // å �������� �뿩
            Book* book = bookManager.getBookByTitle(titleOrAuthor);
            if (book != nullptr) {
                borrowManager.borrowBook(book->title);
            }
            else {
                // �۰� �̸����� �뿩
                vector<Book*> booksByAuthor = bookManager.getBooksByAuthor(titleOrAuthor);
                if (!booksByAuthor.empty()) {
                    borrowManager.borrowBookByAuthor(titleOrAuthor, booksByAuthor);
                }
                else {
                    cout << "���� �Ǵ� �۰��� ã�� �� �����ϴ�." << endl;
                }
            }
        }
        else if (choice == 4) {
            string titleOrAuthor;
            cout << "�ݳ��� å ���� �Ǵ� �۰�: ";
            cin.ignore();  // �Է� ���� ����
            getline(cin, titleOrAuthor);

            // å �������� �ݳ�
            Book* book = bookManager.getBookByTitle(titleOrAuthor);
            if (book != nullptr) {
                borrowManager.returnBook(book->title);
            }
            else {
                // �۰� �̸����� �ݳ�
                vector<Book*> booksByAuthor = bookManager.getBooksByAuthor(titleOrAuthor);
                if (!booksByAuthor.empty()) {
                    borrowManager.returnBookByAuthor(titleOrAuthor, booksByAuthor);
                }
                else {
                    cout << "���� �Ǵ� �۰��� ã�� �� �����ϴ�." << endl;
                }
            }
        }
        else if (choice == 5) {
            borrowManager.displayStock();  // ��� ���� ���
        }
        else if (choice == 6) {
            cout << "���α׷��� �����մϴ�." << endl;
            break;  // ���α׷� ����
        }
        else {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }
    return 0;
}