#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Book 클래스: 각 책의 정보 저장
class Book {
public:
    string title;   // 책 제목
    string author;  // 책 저자

    // 생성자: 책 제목과 저자만 받아서 초기화
    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

// BorrowManager 클래스: 책 대여 및 반납 관리
class BorrowManager {
private:
    unordered_map<string, int> stock;  // 책 제목으로 재고 관리

public:
    // 책의 재고 초기화
    void initializeStock(Book& book, int quantity = 3) {
        stock[book.title] = quantity;
        cout << book.title << "의 초기 재고가 " << quantity << "권으로 설정되었습니다." << endl;
    }

    // 책 대여 처리
    void borrowBook(const string& title) {
        if (stock.find(title) != stock.end() && stock[title] > 0) {
            stock[title]--;
            cout << title << "이(가) 대여되었습니다." << endl;
        }
        else {
            cout << title << "은(는) 대여할 수 없습니다. 재고가 없습니다." << endl;
        }
    }

    // 작가로 책 대여 처리
    void borrowBookByAuthor(const string& author, const vector<Book*>& booksByAuthor) {
        bool bookFound = false;
        for (auto& book : booksByAuthor) {
            if (stock.find(book->title) != stock.end() && stock[book->title] > 0) {
                stock[book->title]--;
                cout << book->title << "이(가) 대여되었습니다." << endl;
                bookFound = true;
                break;
            }
        }
        if (!bookFound) {
            cout << author << "의 책은 대여할 수 없습니다. 재고가 없습니다." << endl;
        }
    }

    // 책 반납 처리
    void returnBook(const string& title) {
        if (stock.find(title) != stock.end()) {
            stock[title]++;
            cout << title << "이(가) 반납되었습니다." << endl;
        }
        else {
            cout << title << "은(는) 대여 기록이 없습니다." << endl;
        }
    }

    // 작가로 책 반납 처리
    void returnBookByAuthor(const string& author, const vector<Book*>& booksByAuthor) {
        bool bookFound = false;
        for (auto& book : booksByAuthor) {
            if (stock.find(book->title) != stock.end()) {
                stock[book->title]++;
                cout << book->title << "이(가) 반납되었습니다." << endl;
                bookFound = true;
                break;
            }
        }
        if (!bookFound) {
            cout << author << "의 책은 반납할 수 없습니다. 대여 기록이 없습니다." << endl;
        }
    }

    // 현재 재고 상태 출력
    void displayStock() {
        if (stock.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }
        cout << "현재 책 재고 목록:" << endl;
        for (const auto& entry : stock) {
            cout << entry.first << ": " << entry.second << "권" << endl;
        }
    }
};

// BookManager 클래스: 책 관리
class BookManager {
private:
    vector<Book> books;  // 책 목록 관리

public:
    // 책 제목으로 책을 찾는 함수
    Book* findBookByTitle(const string& title) {
        for (auto& book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr;  // 책을 찾지 못한 경우
    }

    // 책 작가로 책을 찾는 함수 (여러 책을 반환)
    vector<Book*> findBooksByAuthor(const string& author) {
        vector<Book*> booksByAuthor;
        for (auto& book : books) {
            if (book.author == author) {
                booksByAuthor.push_back(&book);
            }
        }
        return booksByAuthor;
    }

    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (const auto& book : books) {
            cout << "- " << book.title << " by " << book.author << endl;
        }
    }

    // 제목으로 책 반환 메서드
    Book* getBookByTitle(const string& title) {
        return findBookByTitle(title);  // 제목으로 찾기
    }

    // 작가로 책 반환 메서드
    vector<Book*> getBooksByAuthor(const string& author) {
        return findBooksByAuthor(author);  // 작가로 찾기
    }
};

int main() {
    BookManager bookManager;
    BorrowManager borrowManager;

    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl;
        cout << "2. 모든 책 출력" << endl;
        cout << "3. 책 대여" << endl;
        cout << "4. 책 반납" << endl;
        cout << "5. 재고 보기" << endl;
        cout << "6. 종료" << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;


        if (choice == 1) {
            string title, author;
            cout << "책 제목: ";
            cin.ignore();  // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title);
            cout << "책 저자: ";
            getline(cin, author);
            bookManager.addBook(title, author); // 책 추가
            borrowManager.initializeStock(*bookManager.getBookByTitle(title)); // 재고 초기화
        }
        else if (choice == 2) {
            bookManager.displayAllBooks();  // 모든 책 출력
        }
        else if (choice == 3) {
            string titleOrAuthor;
            cout << "대여할 책 제목 또는 작가: ";
            cin.ignore();  // 입력 버퍼 비우기
            getline(cin, titleOrAuthor);

            // 책 제목으로 대여
            Book* book = bookManager.getBookByTitle(titleOrAuthor);
            if (book != nullptr) {
                borrowManager.borrowBook(book->title);
            }
            else {
                // 작가 이름으로 대여
                vector<Book*> booksByAuthor = bookManager.getBooksByAuthor(titleOrAuthor);
                if (!booksByAuthor.empty()) {
                    borrowManager.borrowBookByAuthor(titleOrAuthor, booksByAuthor);
                }
                else {
                    cout << "제목 또는 작가를 찾을 수 없습니다." << endl;
                }
            }
        }
        else if (choice == 4) {
            string titleOrAuthor;
            cout << "반납할 책 제목 또는 작가: ";
            cin.ignore();  // 입력 버퍼 비우기
            getline(cin, titleOrAuthor);

            // 책 제목으로 반납
            Book* book = bookManager.getBookByTitle(titleOrAuthor);
            if (book != nullptr) {
                borrowManager.returnBook(book->title);
            }
            else {
                // 작가 이름으로 반납
                vector<Book*> booksByAuthor = bookManager.getBooksByAuthor(titleOrAuthor);
                if (!booksByAuthor.empty()) {
                    borrowManager.returnBookByAuthor(titleOrAuthor, booksByAuthor);
                }
                else {
                    cout << "제목 또는 작가를 찾을 수 없습니다." << endl;
                }
            }
        }
        else if (choice == 5) {
            borrowManager.displayStock();  // 재고 상태 출력
        }
        else if (choice == 6) {
            cout << "프로그램을 종료합니다." << endl;
            break;  // 프로그램 종료
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }
    return 0;
}