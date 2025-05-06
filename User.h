#include<iostream>
#include<string>
#include<vector> 
#include<unordered_map>
using namespace std;
class User
{
    public:
    string name;
    unordered_map<string,int> borrowinfo;
    User(string name,int days,string title):name(name)
    {
        borrowinfo.insert({title,days});
    }
    void adddays()
    {
    for (auto& i : borrowinfo)
    {
        i.second++;
    }
    }
    void return_book(string title)
    {
        borrowinfo.erase(title);
    }
    vector<pair<string, int> > unreturnedBooks() {
        vector<pair<string, int> > allbooks;
        for (auto& i : borrowinfo) {
            allbooks.push_back({i.first,i.second});
        }
        return allbooks;
    }
   pair<string, int> unreturnedBook() {
        pair<string, int>allbooks;
        for (auto& i : borrowinfo) {
            allbooks={i.first,i.second};
        }
        return allbooks;
    }
    vector<pair<string, int>> overdueBooks(string name) {
        vector<pair<string, int>> overdue;
        for (auto& i : borrowinfo) {
            if (i.second > 3*3) {
                overdue.push_back({i.first,i.second});
            }
        }
        return overdue;
    }
};
   