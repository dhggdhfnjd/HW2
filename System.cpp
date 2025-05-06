#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector> 
#include<unordered_set>
#include<iomanip>
#include<sstream>
#include"Librart.h"
using namespace std;
int main()
{
    cout << left;
    int choice;
    int countdays=0;
    string name;
    string tagline;
    string title;
    string author;
    string genre;
    string ISBN;
    string tags;
    double rating;
    int borrowCount;
    int year;
    int copies;
    
    string publisher;

    Library System;
    
    while(1)
    {
    System.adddays();
    cout<<"Library Management System"<<endl;
    
    cout<<"1.  Add a new book"<<endl;
    cout<<"2.  Search for a book by published year"<<endl;
    cout<<"3.  Search for a book by ISBN or title"<<endl;
    cout<<"4.  Search for a book by genre"<<endl;
    cout<<"5.  Display leaderboard by finding count"<<endl;
    cout<<"6.  Display leaderboard by rating"<<endl;
    cout<<"7.  Display the book which have highest borrow count"<<endl;
    cout<<"8.  Display the book which have highest overall rating"<<endl;
    cout<<"9.  Check out a book"<<endl;
    cout<<"10. Return books"<<endl;
    cout<<"11. List all books"<<endl;
    cout<<"12. Display users with overdue unreturned books"<<endl;
    cout<<"13. Display user you want to find"<<endl;
    cout<<"14. Display all users"<<endl;
    cout<<"15. Find the book by tag"<<endl;
    cout<<"16. Exit"<<endl;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice)
    {
    case 1:
    {
    unordered_set<string> tag;
    cout<<"Enter book title:";
    cin>>title;
    getchar();
    cout<<"Enter author:";
    getline(cin,author);
    cout<<"Enter published year:";
    cin>>year;
    getchar();
    cout<<"Enter Book's ISBN:";
    cin>>ISBN;
    getchar();
    cout<<"Enter Book's tag:";
    getline(cin,tagline);
    istringstream iss(tagline);  
    while (iss >> tags) {
        tag.insert(tags);  
    }
    cout<<"F for Fiction;"<<endl;
    cout<<"M for Math;"<<endl;
    cout<<"CS for Computer Science;"<<endl;
    cout<<"P for Philosophy;"<<endl;
    cout<<"Enter Book's genre:";
    cin>>genre;
    if(genre=="F")
    genre="Fiction";
    if(genre=="M")
    genre="Math";
    if(genre=="CS")
    genre="Computer Science";
    if(genre=="P")
    genre="Philosophy";
    getchar();
    
    cout<<"Enter the numbers of availiable copies:";
    cin>>copies;
    getchar();
    System.add(title,publisher,copies,year,author,genre,tag,ISBN);
    }
    break;
    case 2:
    {
        cout<<"Enter published year:";
        cin>>year;
        cin.ignore(); 
        System.search_year(year);
    }
    break;
    case 3:
    {
        cout<<"Enter the book's title or ISBN:";
        cin>>title;
        cin.ignore(); 
        System.search_name(title);
    }
    break;
    case 4:
    {
        cout<<"Enter the book's genre:";
        cin>>genre;
        cin.ignore(); 
        System.search_genre(genre);
    }
    break;
    case 5:
    {
        System.print_findingcount();
    }
    break;
    case 6:
    {
        System.print_rating();
    }
    break;
    case 7:
    {
        System.print_higgest_borrowcount();
    }
    break;
    case 8:
    {
        System.print_higgest_overall_rating();
    }
    break;
    case 9:
    {
        cout<<"Enter your name:";
        cin>>name;
        cin.ignore(); 
        cout<<"Enter book title:";
        cin>>title;
        cin.ignore(); 
        System.check_out_title(title,name);
    }
    break;
    case 10:
    {
        cout<<"Enter your name:";
        cin>>name;
        cin.ignore(); 
        cout<<"Enter the book title you want to return:";
        cin>>title;
        cin.ignore(); 
        cout<<"Please rate this book on a scale of 1 to 10.: ";
        cin>>rating;
        cin.ignore();
        System.ratecount(rating,title);
        System.return_title(title,name);
    }
    break;
    case 11:
    {
        System.printall();
    }
    break;
    case 12:
    {
        System.show_overdue_users();
    }
    break;
    case 13:
    {
        cout<<"Enter the name you want to find:";
        cin>>name;
        System.show_user(name);
    }
    break;
    case 14:
    {
        System.show_all_users();
    }
    break;
    case 15:
    {
        vector<Book> tagging=System.archive;
        cout<<"Enter the tag you want to find:";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');//可以把緩衝區清空直到'\n'
        getline(cin,tagline);
        cout<<"The "<<tagline<<"is inlcuded in those books' tag."<<endl;
        vector<string> alltags;
        istringstream iss(tagline);  
        while (iss >> tags) {
            tagging=System.find_tag(tags,tagging);
        }
        System.print(tagging);
    }
    break;
    case 16:
    {
        cout<<"Exit library management system. Thank you!!!";
        return 0;
    }
    break;
    
    }
    }
}   