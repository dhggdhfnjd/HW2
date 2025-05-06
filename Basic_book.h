#include<iostream>
#include<string>
#include<vector> 
#include<unordered_set>
using namespace std;
class Book
{
    public:
    string title;
    string author;
    string genre;
    string ISBN;
    int findingcount;
    double rating;
    int borrowcount;
    int year;
    int copies;
    unordered_set<string> tag;
    string publisher;
   
     Book(string title,string publisher,int copies,int year,string author,string genre,unordered_set<string> tag,string ISBN)
        : title(title), author(author), year(year), copies(copies),
          genre(genre), ISBN(ISBN),publisher(publisher),tag(tag) 
          {
            findingcount=0;
            rating=0;
            borrowcount=0;
          }
};