#include<iostream>
#include<string>
#include<fstream>
#include<limits>

using namespace std;

class Book{
private:
    string title;
    string author;
    int year;
    int id;

public:
    Book():title(""),author(""),year(0),id(0){}
    Book(string t,string a,int y,int i)
    :title(t),author(a),year(y),id(i){}

    void setTitle(const string& t){
    title=t;}
    void setAuthor(const string& a){
    author=a;}
    void setYear(int y){
    year=y;}
    void setID(int i){
    id=i;}

    string getTitle()const{
    return title;}
    string getAuthor()const{
    return author;}
    int getYear()const{
    return year;}
    int getID()const{
    return id;}

    void print()const{
    cout<<"ID: "<<id;
    cout<<" | Title: "<<title;
    cout<<" | Author: "<<author;
    cout<<" | Year: "<<year<<endl;
    }
};

class Library{
private:
    Book* books;
    int size;
    int capacity;

void resize(){
if(size < capacity) return;

int newCapacity;
if (capacity == 0){
    newCapacity=2;
}else{
newCapacity=capacity*2;
}
Book* newArr=new Book[newCapacity];
for(int i=0;i<size;i++){
    newArr[i]=books[i];
    }

delete[] books;
books=newArr;
capacity=newCapacity;
}
public:
    Library():books(nullptr),size(0),capacity(0){}

    ~Library(){
    delete [] books;
    }

    int getSize()const{
        return size;}

        int findById(int searchID)const{
        for(int i=0;i<size;i++){
            if(books[i].getID()==searchID){
                return i;
            }
        }
            return -1;
        }
        void addBook(const Book& b){
        resize();
        books[size]=b;
        size++;
        cout<<"Book added successfully "<<endl;
        }
        void printAll()const{
        if(size==0){
            cout<<"Library is empty. "<<endl;
            return;
        }
            for(int i=0;i<size;i++){
                books[i].print();
            }
        }
        void deleteByID(int delID){
        int idx=findById(delID);
        if(idx==-1){
            cout<<"Book not found. "<<endl;
        return;}
        for(int i=idx;i<size-1;i++){
            books[i]=books[i+1];
        }
        size--;
        cout<<"Book deleted successfully "<<endl;
        }

     void searchAndPrintByID(int searchID)const{
     int idx=findById(searchID);
     if(idx==-1){
        cout<<"Book not found. "<<endl;
        return;
     }
     books[idx].print();
     }
     void editById(int editId){
     int idx=findById(editId);
     if(idx==-1){
        cout<<"Book not found "<<endl;
     return;}
     cout<<"Editing book: ";
     books[idx].print();
     cout<<endl;

     cout<<"What do you want to edit?"<<endl;
     cout<<"1)Title\n2)Author\n3)Year\nChoice: ";
     int choice;
     cin>>choice;
     cin.ignore(numeric_limits<streamsize>::max(),'\n');
     if(choice==1){
        string newTitle;
        cout<<"new title: ";
        getline(cin,newTitle);
        books[idx].setTitle(newTitle);
     }else if(choice==2){
     string newAuthor;
     cout<<"New author: ";
     getline(cin,newAuthor);
     books[idx].setAuthor(newAuthor);
     }else if(choice==3){
     int newYear;
     cout<<"New year: ";
     cin>>newYear;
     books[idx].setYear(newYear);
     }else{
     cout<<"Invalid choice.";
     return;
     }
     cout<<"\nBook updated\n";
     }
     void sortByTitle(){
     for(int i=0;i<size-1;i++){
        for(int j=0;j<size-i-1;j++){
            if(books[j].getTitle()>books[j+1].getTitle()){
                Book temp=books[j];
                books[j]=books[j+1];
                books[j+1]=temp;
            }
        }
     }
     cout<<"Sorted by tittle.\n";
     }
     void sortByYear(){
     for(int i=0;i<size-1;i++){
        for(int j=0;j<size-i-1;j++){
            if(books[j].getYear()>books[j+1].getYear()){
        Book temp=books[j];
        books[j]=books[j+1];
        books[j+1]=temp;
            }
        }
     }
     cout<<"Sorted by year."<<endl;
     }
     void saveToFile(const string& filename)const{
     ofstream out(filename);
     if(!out){
        cout<<"Error cannot open file. "<<endl;
     return;}
     for(int i=0;i<size;i++){
        out<<books[i].getID()<<"| "
        <<books[i].getTitle()<<"| "
        <<books[i].getAuthor()<<"| "
        <<books[i].getYear()<<endl;
     }
     out.close();
     cout<<"Saved to file: "<<filename<<endl;
     }

};

int main(){
Library lib;
int choice;
while(true){
    cout<<"\n==== Library Menu ====\n";
    cout<<"1) Add book\n";
    cout<<"2) Search book by ID\n";
    cout<<"3) Display all books\n";
    cout<<"4) Delete book by ID\n";
    cout<<"5) Edit book by ID\n";
    cout<<"6) Sort books by title\n";
    cout<<"7) Sort books by year\n";
    cout<<"8) Save to file\n";
    cout<<"9) Exit\n";
    cout<<"Choice: ";

    cin>>choice;
    if(choice==9){
        cout<<"Good Bye!\n";
        break;
    }
    if(choice==1){
        int id,year;
        string title,author;
        cout<<"Enter ID: ";
        cin>>id;
        cout<<"Enter year: ";
        cin>>year;

        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Enter Title: ";
        getline(cin,title);
        cout<<"Enter author: ";
        getline(cin,author);

        lib.addBook(Book(title,author,year,id));
    }else if(choice==2){
        int id;
        cout<<"Enter ID: ";
        cin>>id;
    lib.searchAndPrintByID(id);
    }else if(choice==3){
    lib.printAll();
    }else if(choice==4){
    int id;
    cout<<"Enter ID: ";
    cin>>id;
    lib.deleteByID(id);
    }else if(choice==5){
    int id;
    cout<<"Enter ID: ";
    cin>>id;
    lib.editById(id);
    }else if(choice==6){
    lib.sortByTitle();
    }else if(choice==7){
    lib.sortByYear();
    }else if(choice==8){
    string filename;
    cout<<"File name: ";
    cin>>filename;
    lib.saveToFile(filename);
    }else{
    cout<<"Invalid Choice.\n";
        }

    }

}
