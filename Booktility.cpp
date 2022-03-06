#include <iostream>
#include <cstring>

using namespace std;

class carte {
    char *denumire, *autorPrincipal, *autorSecundar;
    int pagini;
    float pret, rating;
public:
    carte();

    carte(char *denumire, char *autorPrincipal, char *autorSecundar, int pagini, float pret, float rating);

    carte(const carte &c);

    ~carte();

    friend ostream &operator<<(ostream &out, carte &c);

    friend istream &operator>>(istream &in, carte &c);

    carte &operator=(carte &c);

    bool operator>(carte &c);

    bool operator>=(carte &c);

    bool operator<(carte &c);

    bool operator<=(carte &c);

    void setDenumire(char *denumire);

    char *getDenumire();

    void setAutorPrincipal(char *autorPrincipal);

    char *getAutorPrincipal();

    void setAutorSecundar(char *autorSecundar);

    char *getAutorSecundar();

    void setPagini(int pagini);

    int getPagini();

    void setPret(float pret);

    float getPret();

    void setRating(float rating);

    float getRating();
};


carte::carte() {
    denumire = new char[100];
    autorPrincipal = new char[50];
    autorSecundar = new char[50];
    pret = 0;
    pagini = 0;
    rating = 0;
}

carte::carte(char *denumire, char *autorPrincipal, char *autorSecundar, int pagini, float pret, float rating) {
    if (pagini < 0) cout << "Error: Number of pages must be a positive number";
    else if (pret < 0) cout << "Error: Price must be a positive number";
    else if (rating < 0 or rating > 0) cout << "Error: Rating must be between 0 and 5";
    else {
        strcpy(this->denumire, denumire);
        strcpy(this->autorPrincipal, autorPrincipal);
        strcpy(this->autorSecundar, autorSecundar);
        this->pagini = pagini;
        this->pret = pret;
        this->rating = rating;
    }
}

carte::carte(const carte &c) {
    strcpy(denumire, c.denumire);
    strcpy(autorPrincipal, c.autorPrincipal);
    strcpy(autorSecundar, c.autorSecundar);
    pagini = c.pagini;
    pret = c.pret;
    rating = c.rating;
}

carte::~carte() {
    delete[]denumire;
    delete[]autorPrincipal;
    delete[]autorSecundar;
}

void carte::setDenumire(char *denumire) {
    strcpy(this->denumire, denumire);
}

char *carte::getDenumire() { return denumire; }

void carte::setAutorPrincipal(char *autorPrincipal) {
    strcpy(this->autorPrincipal, autorPrincipal);
}

char *carte::getAutorPrincipal() { return autorPrincipal; }

void carte::setAutorSecundar(char *autorSecundar) {
    strcpy(this->autorSecundar, autorSecundar);
}

char *carte::getAutorSecundar() { return autorSecundar; }

void carte::setPagini(int pagini) { this->pagini = pagini; }

int carte::getPagini() { return pagini; }

void carte::setPret(float pret) {
    if (pret < 0) {
        cout << "Value error: Price cannot be a negative number.";
        return;
    }
    this->pret = pret;
}

float carte::getPret() { return pret; }

void carte::setRating(float rating) {
    if (rating > 10 or rating < 0) {
        cout << "Value error: Rating must be between 0.00 and 10.00";
        return;
    }

    this->rating = rating;
}

float carte::getRating() { return rating; }

istream &operator>>(istream &in, carte &c) {
    in.get();
    in.getline(c.denumire, 100, '\t');
    in.getline(c.autorPrincipal, 50, '\t');
    in.getline(c.autorSecundar, 50, '\t');
    in >> c.pagini;
    while (c.pagini < 0) {
        cout << "Error: Number of pages must be a positive integer";
    }

    in >> c.pret;
    while (c.pret < 0) {
        cout << "Error: Price must be a positive number ";
        in >> c.pret;
    }

    in >> c.rating;
    while (c.rating > 5 or c.rating < 0) {
        cout << "Error: Rating must be between 0 and 5 ";
        in >> c.rating;
    }
    return in;
}

ostream &operator<<(ostream &out, carte &c) {
    out << "\"" << c.denumire << "\" - " << c.autorPrincipal << ", " << c.autorSecundar << " - "
        << c.pagini << " pages - " << c.pret << "€ - " << c.rating << "/5.0 stars";

    return out;
}

carte &carte::operator=(carte &c) {
    strcpy(denumire, c.denumire);
    strcpy(autorPrincipal, c.autorPrincipal);
    strcpy(autorSecundar, c.autorSecundar);
    pagini = c.pagini;
    pret = c.pret;
    rating = c.rating;
    return *this;
}

bool carte::operator>(carte &c) {
    return rating > c.rating;
}

bool carte::operator>=(carte &c) {
    return rating >= c.rating;
}

bool carte::operator<(carte &c) {
    return rating < c.rating;
}

bool carte::operator<=(carte &c) {
    return rating <= c.rating;
}


int main() {
    carte *books = new carte[100];
    int n, command = -3, option1 = -3, option2 = -3, option3;
    float option4;
    char auxiliary[100];

//    array reading and welcome message
    cout << "Welcome to Booktility v1.0 !\n..........LOADING...........\n\n";
    cout << ">>> Enter the number of books you wish to input: ";
    cin >> n;
    while(n<=0){
        if (n==-2) return 0;    // quit
        cout<<"Error: The number of books must be a positive non-null integer\n";
        cout << ">>> Enter the number of books you wish to input: ";
        cin>>n;
    }
    cout << ">>> Enter a list of books in the following format, using TAB as a field delimiter: \n";
    cout << "BookName       MainAuthor      SecondAuthor      NumberOfPages       Price       GoodReadsRating\n\n";

    for (int i = 0; i < n; i++) {           // reading and storing of books
        cout << ">>> Enter book number " << i + 1 << ":\n";
        cin >> books[i];
    }

    // program functions and instructions listing
    cout << "\nBooktility employs the following functions:\n";
    cout << "1) modify book\n";
    cout << "2) compare two books by their rating\n";
    cout << "3) print all stored books\n\n";
    cout << "Instruction manual:\n";
    cout << "- function-menus can only be accessed by giving their ID number as input\n";
    cout << "- to abort current function-menu, type \"-1\"\n";
    cout << "- to quit the program, type \"-2\"\n";
    cout << "- books can only be identified by their order number in the list\n";

    while (command != -2) {
        cout<< "\n>>> Enter a valid function-menu or command ID: ";           // request and verify input is valid (1-3 for menu options, -1 to abort, -2 to quit
        cin>>command;
        switch (command) {
            case 1:         // modify book menu
                cout << "Modify menu options:\n";
                cout << "1) Book title\n";
                cout << "2) Main author\n";
                cout << "3) Second author\n";
                cout << "4) Number of pages\n";
                cout << "5) Price\n";
                cout << "6) Goodreads rating\n";
                cout << ">>> Enter a valid function-menu option or command ID: ";
                cin >> option1;

                while (option1 < -2 or option1 > 6) {
                    cout << "Error: out of range modify-menu option (1-6) and command (-1,-2) IDs\n";
                    cout << ">>> Enter a valid function-menu option or command ID: ";
                    cin >> option1;
                }

                if (option1 == -1) {        // abort
                    cout<<"Aborting\n";
                    break;
                }
                else if (option1 == -2) {       // quit
                    command = -2;
                    break;
                } else {
                    cout << ">>> Enter the ID of the book to be modified: ";
                    cin >> option2;

                    while (option2 < -2 or option2 > n or option2==0) {
                        cout << "Error: book IDs must be positive, non-null and cannot exceed total book number\n";
                        cout << ">>> Enter the ID of the book to be modified: ";
                        cin >> option2;
                    }

                    if (option2 == -1) {       // abort
                        cout<<"Aborting\n";
                        break;
                    }
                    else if (option2 == -2) {       // quit
                        command = -2;
                        break;
                    } else {                    // both function-menu option and book ID have been received and verified
                        option2--;
                        switch (option1) {
                            case 1:         // modify book title
                                cout << ">>> Enter a new book title for \"" << books[option2].getDenumire() << "\": ";
                                cin.get(); cin.getline(auxiliary, 100);
                                books[option2].setDenumire(auxiliary);
                                cout << "Book title has been modified\n";
                                break;

                            case 2:         // modify main author
                                cout << ">>> Enter a new main book author for \"" << books[option2].getDenumire() << "\": ";
                                cin.get(); cin.getline(auxiliary, 50);
                                books[option2].setAutorPrincipal(auxiliary);
                                cout << "Main book author has been modified\n";
                                break;

                            case 3:         // modify second author
                                cout << ">>> Enter a new second book author for \"" << books[option2].getDenumire()
                                     << "\": ";
                                cin.get(); cin.getline(auxiliary, 50);
                                books[option2].setAutorSecundar(auxiliary);
                                cout << "Second book author has been modified\n";
                                break;

                            case 4:         //  modify number of pages
                                cout << ">>> Enter a new number of pages for \"" << books[option2].getDenumire() << "\": ";
                                cin >> option3;
                                while (option3<0) {
                                    cout<<"Error: Number of pages must be a positive number\n";
                                    cout << ">>> Enter a new number of pages for \"" << books[option2].getDenumire() << "\": ";
                                    cin>>option3;
                                }
                                books[option2].setPagini(option3);
                                cout << "Number of pages has been modified\n";
                                break;

                            case 5:         // modify price
                                cout << ">>> Enter a new price for \"" << books[option2].getDenumire() << "\": ";
                                cin >> option4;
                                while(option4<0.0) {
                                    cout<<"Error: Price must be a positive number\n";
                                    cout << ">>> Enter a new price for \"" << books[option2].getDenumire() << "\": ";
                                    cin>>option4;
                                }
                                books[option2].setPret(option4);
                                cout << "Price has been modified\n";
                                break;

                            case 6:         // modify rating
                                cout << ">>> Enter a new GoodReads rating for \"" << books[option2].getDenumire() << "\": ";
                                cin >> option4;
                                while(option4<0.0 or option4>5.0){
                                    cout<<"Error: Rating must be between 0 and 5\n";
                                    cout << ">>> Enter a new GoodReads rating for \"" << books[option2].getDenumire() << "\": ";
                                    cin>>option4;
                                }
                                books[option2].setRating(option4);
                                cout << "Rating has been modified\n";
                                break;
                        }
                    }
                }
                break;


            case 2:         // compare books menu
                cout << ">>> Enter book IDs or a valid command ID: ";
                cin >> option1;
                while (option1 < -2 or option1 > n) {        // verify option1 is a valid number
                    cout << "Error: book IDs must be positive and cannot exceed total book number\n";
                    cout << ">>> Enter book IDs or a valid command ID: ";
                    cin >> option1;
                }

                switch (option1) {
                    case -1: {       // abort
                        cout<<"Aborting\n";
                        break;
                    }
                    case -2:        // quit
                        command = -2;
                        break;

                    default:
                        option1--;
                        cin >> option2;
                        while (option2 < -2 or option2 > n) {       // verify option2 is a valid number
                            cout
                                    << "Error: book IDs must be positive and cannot exceed total book number\nType '-1' to abort or '-2' to quit ";
                            cout << ">>> Enter book ID or a valid command ID: ";
                            cin >> option2;
                        }

                        switch (option2) {
                            case -1: {        // abort
                                cout<<"Aborting\n";
                                break;
                            }
                            case -2:        // quit
                                command = -2;
                                break;

                            default:
                                option2--;
                                if (books[option1] > books[option2]) {
                                    cout << "\"" << books[option1].getDenumire() << "\" is better rated than \""
                                         << books[option2].getDenumire() << "\"\n";
                                    break;
                                } else if (books[option1] < books[option2]) {
                                    cout << "\"" << books[option2].getDenumire() << "\" is better rated than \""
                                         << books[option1].getDenumire() << "\"\n";
                                    break;
                                } else {
                                    cout << "\"" << books[option1].getDenumire() << "\" and \"" << books[option2].getDenumire()
                                         << "\" are equally rated\n";
                                    break;
                                }
                        }
                }
                break;


            case 3:         // print all stored books
                cout << "All stored books will be printed to the screen:\n";
                for (int i = 0; i < n; i++) cout << books[i] << '\n';  // printing to the screen
                break;


            case -1:         // abort
                cout << "Error: abort command can only be used inside function-menus\n";
                break;
            case -2:         // quit
                break;
            default:
                cout << "Error: out of range function-menu (1-3) and command (-1,-2) IDs\n";
                break;
        }
    }

    delete[]books;
    return 0;
}

//t1  a1  a12 10  10  1.5
//t2  a2  a22 20  20  2
//t3  a3  a32 30  30  2.5
//t4  a4  a42 35  35  3