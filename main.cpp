#include <iostream> //input/output stream --> allow take input from console screen and print output to screen
#include <string> //provide support for strings and its functions
#include <iomanip> //define type of data for input and output (manipulate i guess)
#include <fstream> // file stream - file handling - r, w, a
#include <stdlib.h> //to clear screen
using namespace std;

#define LIBRARY_SIZE 26 
int total = 0;

struct Book {
    string name;
    string author;
    string type;
    int id, quantity;
    struct Book *prev;
    struct Book *next;
public: //???
    Book(string new_name, string new_author, string new_type,int new_id, int new_quantity) {
        name = new_name;
        author = new_author;
        type = new_type;
        id = new_id;
        next = NULL;
        prev = NULL;
        quantity = new_quantity;
    }
};

struct Book *library[LIBRARY_SIZE]; //hash table

int hashing(char ch);
Book *getBook(string str);
int checkId(int id);
void add(int id, string name, string author, string type, int quantity);
int update(Book* bk, string author, string type, int quantity);
int borrow(Book* bk, int quantity);
int returnBook(Book* bk, int quantity);
void delete_book(Book* bk);
Book* searchByName(string name);
void load_data(string filename);
int display_alphabetical(char ch);
void show_columns();
void show_book_info(Book *bk);
void save_data(string filename);

//string filename = "C:/Users/HUONG GIANG/Desktop/UNI/Data Structures and Algorithm/Final/final.csv";
string filename = "final.csv";

int main(){

    load_data(filename);
    int choice;

    menu: while (true) {
        system("CLS");
        cout << "\n\n\n\t\t\t    L I B R A R Y  M A N A G E M E N T  S Y S T E M";
        cout << "\n\n\t\t\t\t\t\tM E N U\n\n\n";
        cout << "\t\t\t\t0. Exit\n";
        cout << "\t\t\t\t1. Display all books in alphabetical order\n";
        cout << "\t\t\t\t2. Search book with first letter of name\n";
        cout << "\t\t\t\t3. Add a book\n";
        cout << "\t\t\t\t4. Search book by full name\n";
        cout << "\n\t\t\t\tSelect an option : ";

        cin >> choice;
        switch (choice){
            exitn:case 0: {
                system("CLS");
                cout << "\t\t\t\t\tThank you for using the system.";
                exit(0);
            }
            case 1: {
                system("CLS");
                cout << "\n\t\t\t\t\tD I S P L A Y  A L L  B O O K S\n\n";
                int count=0;
                show_columns();
                for (int i='a'; i<'z';i++)
                    count += display_alphabetical(i);
                cout <<"\n\nCount: "<<count<<"\\"<<total;
                string opt;
                cout <<"\n\n\t\t\t\tChoose another action option?\n\t\t\t\tPress 1 to go back to menu page: ";
                cin >> opt;
                if (opt == "1") goto menu;
                else goto exitn;
            }  
            case 2: {
                system("CLS");
                cout << "\n\t\t\t\t\tS E A R C H  B Y  F I R S T  L E T T E R\n\n";
                char rep;
                cout << "\n\t\t\t\tInsert a character from a-z to search for books: ";
                cin >> rep;

                show_columns();
                int count = display_alphabetical(rep);
                if (count == 0) cout << "\n\n\t\t\tThere's no book start with "<<rep;
                else {
                    cout <<"\n\n\t\t\tCount: "<<count<<"\\"<<total;
                }
    
                string opt;
                cout <<"\n\n\t\t\t\tChoose another action option?\n\t\t\t\tPress 1 to go back to menu page: ";
                cin >> opt;
                if (opt == "1") goto menu;
                else goto exitn;
            }     
            case 3: {
                system("CLS");
                cout << "\n\t\t\t\t\t\tA D D\n";
                int id, quantity;
                string name, author, type;
                cout << "\n\t\t\t\tBook ID: "; cin >> id;
                cin.ignore();
                while (checkId(id)){
                    cout << "\n\t\t\t\tID already exist. Enter ID again.\n";
                    cout << "\n\t\t\t\tBook ID: "; cin >> id;
                    cin.ignore();
                }
                
                cout << "\n\t\t\t\tBook's name: "; getline(cin, name);
                cout << "\n\t\t\t\tAuthor's name: "; getline(cin, author);
                int choice1;
                cout << "\n\t\t\t\tCategory list"; 
                cout << "\n\t\t\t\t1. Novel";
                cout << "\n\t\t\t\t2. Romance";
                cout << "\n\t\t\t\t3. Literature";
                cout << "\n\t\t\t\t4. Horror";
                cout << "\n\t\t\t\t5. Lifestyle";
                cout << "\n\t\t\t\t6. Other\n";
    
                chooseCategory:
                    cout << "\n\t\t\t\tSelect a category: ";
                    cin >> choice1;
                    switch(choice1){
                        case 1: {
                            type = "Novel";
                            break;
                        }
                        case 2: {
                            type = "Romance";
                            break;
                        }
                        case 3: {
                            type = "Literature";
                            break;
                        }
                        case 4: {
                            type = "Horror";
                            break;
                        }
                        case 5: {
                            type = "Lifestyle";
                            break;
                        }
                        case 6: {
                            type = "Other";
                            break;
                        }
                        default: {
                            cout << "\n\t\t\tThere aren't any category corresponding to this number.\n\t\t\tPlease select again.\n";
                            goto chooseCategory;
                        }
                    }
                cout << "\n\t\t\t\tQuantity: "; 
                cin >> quantity;
                add(id, name, author, type, quantity);

                string opt;
                cout <<"\n\n\t\t\t\tChoose another action option?\n\t\t\t\tPress 1 to go back to menu page: ";
                cin >> opt;
                if (opt == "1") goto menu;
                else goto exitn;
            }
            case 4: {
                system("CLS");
                cout << "\n\t\t\t\t\t\tS E A R C H\n";
                string name;
                cout << "\n\t\t\t\tInsert name of the book you want to search: "; 
                cin.ignore();
                getline(cin, name);
                Book* bk = searchByName(name);
                if (bk != NULL){
                    show_columns();
                    show_book_info(bk);

                    cout << "\n\n\t\t\t\t1. Back\n";
                    cout << "\t\t\t\t2. Delete this book\n";
                    cout << "\t\t\t\t3. Update this book\n";
                    cout << "\t\t\t\t4. Lend this book\n";
                    cout << "\t\t\t\t5. Receive back this book\n";
                    int choice2;
                    cout << "\n\t\t\t\tSelect an option: "; cin >> choice2;
                    switch(choice2){
                        case 1: break;
                        case 2: {
                            system("CLS");
                            delete_book(bk);
                            string opt;
                            cout <<"\n\n\t\t\t\tChoose another action option?\n\t\t\t\tPress 1 to go back to menu page: ";
                            cin >> opt;
                            if (opt == "1") goto menu;
                            else goto exitn;
                        }
                        case 3: {
                            system("CLS");
                            int new_quantity;
                            string new_author, new_type;
                            cout << "\n\t\t\t\tInsert new information:\n";
                            cin.ignore();
                            cout << "\n\t\t\t\tNew author's name: "; getline(cin, new_author);
                            int choice1;
                            cout << "\n\t\t\t\tCategory list"; 
                            cout << "\n\t\t\t\t1. Novel";
                            cout << "\n\t\t\t\t2. Romance";
                            cout << "\n\t\t\t\t3. Literature";
                            cout << "\n\t\t\t\t4. Horror";
                            cout << "\n\t\t\t\t5. Lifestyle";
                            cout << "\n\t\t\t\t6. Other\n";
        
                            choosenewCategory:
                                int choice3;
                                cout << "\n\t\t\t\tSelect new category: ";
                                cin >> choice3;
                                switch(choice3){
                                    case 1: {
                                        new_type = "Novel";
                                        break;
                                    }
                                    case 2: {
                                        new_type = "Romance";
                                        break;
                                    }
                                    case 3: {
                                        new_type = "Literature";
                                        break;
                                    }
                                    case 4: {
                                        new_type = "Horror";
                                        break;
                                    }
                                    case 5: {
                                        new_type = "Lifestyle";
                                        break;
                                    }
                                    case 6: {
                                        new_type = "Other";
                                        break;
                                    }
                                    default: {
                                        cout << "\n\t\t\tThere aren't any category corresponding to this number.\n\t\t\tPlease select again.\n";
                                        goto choosenewCategory;
                                    }
                            }
                            cout << "\n\t\t\t\tNew quantity: "; cin >> new_quantity;
                            update(bk, new_author, new_type, new_quantity);
                            string opt;
                            cout <<"\n\n\t\t\t\tChoose another action option?\n\t\t\t\tPress 1 to go back to menu page: ";
                            cin >> opt;
                            if (opt == "1") goto menu;
                            else goto exitn;
                        }
                        case 4: {
                            system("CLS");
                            int quantityBorrow;
                            cout << "\n\t\t\t\tNumber of books lend: "; cin >> quantityBorrow;
                            borrow(bk, quantityBorrow);
                            string opt;
                            cout <<"\n\n\t\t\t\tChoose another action option?\n\t\t\t\tPress 1 to go back to menu page: ";
                            cin >> opt;
                            if (opt == "1") goto menu;
                            else goto exitn;
                        }
                        case 5: {
                            system("CLS");
                            int quantityReceive;
                            cout << "\n\t\t\t\tNumber of books receive back: "; cin >> quantityReceive;
                            returnBook(bk, quantityReceive);
                            string opt;
                            cout <<"\n\n\t\t\t\tChoose another action option?\n\t\t\t\tPress 1 to go back to menu page: ";
                            cin >> opt;
                            if (opt == "1") goto menu;
                            else goto exitn;
                        }
                    }
                }
                string opt;
                cout <<"\n\n\t\t\t\tChoose another action option?\n\t\t\t\tPress 1 to go back to menu page: ";
                cin >> opt;
                if (opt == "1") goto menu;
                else goto exitn;
            }

            default:
            {
                cout << "\nOption doesn't exist.";
                string opt;
                cout <<"\n\n\t\t\t\tChoose another action option?\n\t\t\t\tPress 1 to go back to menu page: ";
                cin >> opt;
                if (opt == "1") goto menu;
                else goto exitn;
            }
        }
    }
    return 0;
}

int hashing(char ch){ //???
    int key = ch;
    if (ch >= 'A' && ch <= 'Z') key += 32;
    key %= LIBRARY_SIZE;
    return key;
}

// check if id number has existed in file already
int checkId(int id){
    for (int i = 0; i < LIBRARY_SIZE; i++){
        struct Book* temp = library[i];
        while(temp != NULL){
            if (temp->id == id) {
                return 1;
                break;
            }
            temp = temp->next;
        }  
    }
    return 0;
};

void add(int id, string name, string author, string type, int quantity) {
    // int id = create_id; create_id += 1;
    //cout << name[0];
    struct Book* bk = new Book(name, author, type, id, quantity); //new Book???
    int index = hashing(name[0]);//?
    //cout << index<<endl;
    if (library[index] ==  NULL){
        library[index] = bk;
    } else{
        struct Book* temp = library[index];
        while(temp != NULL){
            if (temp->next == NULL) {
                temp->next = bk;
                bk->prev = temp;
                break;
            }
            temp = temp->next;
        }  
    }
    total += 1;
    save_data(filename);
}

int update(Book* bk, string author, string type, int quantity){
    if( bk == NULL) cout << "\n\t\t\t\t Book does not existed.";
    else
        {
            bk->author = author;
            bk->type = type;
            bk->quantity = quantity;
            save_data(filename);
            cout << "\n\t\t\t\tUpdate successfull.\n";
        }
    return 0;
}

int borrow(Book* bk, int quantity){
    if( bk == NULL) cout << "\n\t\t\t\t Book does not existed.";
    else
        {
            bk->quantity = bk->quantity - quantity;
            save_data(filename);
            cout << "\n\t\t\t\tLend successfull.\n";
            cout <<"\t\t\t\tCurrent quantity of "<<bk->name<<":"<<bk->quantity;
        }
    return 0;
}

int returnBook(Book* bk, int quantity){
    if( bk == NULL) cout << "\n\t\t\t\t Book does not existed.";
    else
        {
            bk->quantity = bk->quantity + quantity;
            save_data(filename);
            cout << "\n\t\t\t\tReceive back successfull.\n";
            cout <<"\t\t\t\tCurrent quantity of "<<bk->name<<":"<<bk->quantity;
        }
    return 0;
}

void delete_book(Book* bk){//???
    if (bk->prev == NULL){ //head?
        int index = hashing(bk->name[0]);//?
        library[index] = bk->next;
        if (bk->next != NULL){
            bk->next->prev = NULL;
        }
    } else if (bk->next == NULL){
        bk->prev->next = NULL;
    } else {
        bk->prev->next = bk->next->prev;
        bk->next->prev = bk->prev->next;
    }
    free(bk);
    total -= 1;
    cout << "\n\t\t\t\tDelete successfull.\n";
    save_data(filename);
}

Book* searchByName(string name){
    int index = hashing(name[0]);
    if(library[index] == NULL) 
    {
        cout << "\n\t\t\t\tBook does not existed.";
        return NULL;
    }
    struct Book* temp = library[index];
    while(temp != NULL){
        if (temp->name == name) break;
        temp = temp->next;
    }  
    if (temp == NULL) {
        cout << "\n\t\t\t\tBook does not existed.\n";
        return NULL;
    }
    return temp; 
}

void load_data(string filename){
    ifstream file;
    file.open(filename);
    if (!file) {
        cerr << "Unable to open data file";
        exit(1);   // call system to stop
    }

    int mark, start, id, quantity;
    mark = 1;
    string line, name, author, type;

    while (getline(file, line)) {

        for(int i=0; i<line.length(); i++)
            if (line[i] == ',')
                if (mark == 1){
                    id = stoi(line.substr(0,i)); 
                    start = i+1; 
                    mark += 1;                
                } else if (mark == 2){
                    name = line.substr(start,i-start);
                    start = i+1;
                    mark += 1;
                } else if (mark == 3){
                    author = line.substr(start,i-start);
                    start = i+1;
                    mark += 1;
                } else if (mark == 4){
                    type = line.substr(start,i-start);
                    start = i+1;
                    quantity = stoi(line.substr(start, line.length()-start));
                    mark = 1;
                }

        add(id, name, author, type, quantity);
    }
    
    file.close();
}

int display_alphabetical(char ch){
    int count = 0;
    int index = hashing(ch);
    if (library[index] == NULL) {
        return count;
    } else{
        struct Book* temp = library[index];
        while(temp != NULL){
            show_book_info(temp);
            temp = temp->next;
            count += 1;
        }  
    }
    return count;
}

void show_columns(){
    cout<< "\n\tID\tNAME\t\t\t          AUTHOR\t\t   CATEGORY\t       QUANTITY\n";
}

void show_book_info(Book *bk){
    int id = bk->id;
    string name = bk->name;
    string author = bk->author;
    string type = bk->type;
    int quantity = bk->quantity;
    cout<<"\t---------------------------------------------------------------------------------------------------\n";
    cout<<"\t"<<setw(5)<<left<<id<<"\t"<<setw(34)<<left<<name<<setw(25)<<left<<author<<setw(20)<<left<<type<<quantity<<endl;
}

void save_data(string filename){
    ofstream file(filename);
    
    for(int i=0; i<LIBRARY_SIZE; i++){
        struct Book* temp = library[i];
        if (temp != NULL){
            struct Book* temp2 = temp;
            while(temp2 != NULL){
                file <<temp2->id<<","<<temp2->name<<","<<temp2->author<<","<<temp2->type<<","<<temp2->quantity<<"\n";
                temp2 = temp2->next;
        }  
        }
    }
}