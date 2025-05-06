#include<iostream>
#include<string>
#include<vector> 
#include<unordered_set>
#include"User.h"
#include"Basic_book.h"
using namespace std;
class Library
{
    public:
    vector<Book> archive;
    vector<User> users;
    void add(string title,string publisher,int copies,int year,string author,string genre,unordered_set<string> tag,string ISBN)
    {
        if(check_ISBN_title(title,ISBN))
        {archive.push_back(Book(title,publisher,copies,year,author,genre,tag, ISBN));}
        else
        cout<<"The book is already exist."<<endl;
    }
    bool check_ISBN_title(string title,string ISBN)
    {
        for(auto &it:archive)
        {
            if(it.ISBN==ISBN || it.title==title)
            {
                return false;
            }
        }
        return true;
    }
    void adddays()
    {
        for(auto &it:users)
        it.adddays();
    }
    void show_user(string name)
    {
        bool flag=true;
        int count=0;
        vector<pair<string, int> > all;
        pair<string, int> input;
        unordered_multimap<string,pair<string, int> > match;
        for(auto &it:users)
        {
            input=it.unreturnedBook();
            if(name==it.name)
            {
                match.insert({name,input});
                count++;
            }
        }
        if(count<5)
        cout<<"User "<<name<<" have borrowed "<<count<<" books and he can still borrow "<<5-count<<" books."<<endl;
        else
        cout<<"User "<<name<<" have reached the borrowing limit"<<endl;
        for(auto [name,books]:match)
        {
            if(books.second/3-3+1>0)
            cout<<setw(20)<<books.first<<" already overdue for "<<books.second/3-3+1<<" days"<<endl;
            else
            cout<<setw(20)<<books.first<<" already borrow for "<<books.second/3-3+1<<" days"<<endl;
        }
        cout<<endl;
        flag=false;
        
        if(flag)
        cout<<"This user haven't borrow any book yet. "<<name<<" still have 5 books borrowing limit"<<endl;
    }
    
    void show_all_users()
    {
        int count=0;
        vector<pair<string, int>> all;
        unordered_set<string> allname;
        unordered_multimap<string,vector<pair<string, int>> > match;
        for(auto it:users)
        {
            all=it.unreturnedBooks();
            if(all.empty())
            continue;
            else
            {
                match.insert({it.name, all});
                allname.insert(it.name);
            }
        }
         for(auto name:allname)
        {
            for (auto& [user, allbooks] : match) 
            {
                if (user == name) 
                {
                    for (const auto& [title, days] : allbooks) 
                    {
                        count++;
                    }
                } 
            }
            if(all.size()<5)
                cout<<"User "<<name<<" have borrowed "<<count<<" books and he can still borrow "<<5-count<<" books."<<endl;
                else
                cout<<"User "<<name<<" have reached the borrowing limit"<<endl;
            for (auto& [user, overdue] : match) 
            {
                if (user == name) 
                {
                    for (const auto& [title, days] : overdue) 
                    {
                        if(days/3-2>0)
                        cout<<setw(20)<<title<<" already overdue for "<<days/3-2<<" days"<<endl;
                        else
                        cout<<setw(20)<<title<<" already borrow for "<<days/3-2<<" days"<<endl;
                    }
                } 
            }
            count=0;
        }
    }
    void show_overdue_users()
    {
        int count=0;
        vector<pair<string, int>> all;
        unordered_set<string> allname;
        unordered_multimap<string,vector<pair<string, int>> > match;
        for(auto it:users)
        {
            all=it.overdueBooks(it.name);
            if(all.empty())
            continue;
            else
            {
                match.insert({it.name, all});
                allname.insert(it.name);
            }
        }
         for(auto name:allname)
        {
            for (auto [user, overdue] : match) 
            {
                if (user == name) 
                {
                    for (auto [title, days] : overdue) 
                    {
                        count++;
                    }
                } 
            }
            cout<<name<<" have "<<count<<" books are overdued"<<endl;
            for (auto& [user, overdue] : match) 
            {
                if (user == name) 
                {
                    for (auto [title, days] : overdue) 
                    {
                        cout << title << " already overdue for " << days/3-2 << " days\n";
                    }
                } 
            }
            count=0;
            cout<<endl;
        }
    }
    void check_out_title(string title,string name)
    {
        int borrowcount=0;
        for(auto &it:archive)
        {
            for(auto &i:users)
            {
                if(i.name==name)
                {
                    borrowcount++;
                }
            }
            if(it.title==title)
            {
                if(it.copies>=1)
                {
                if(borrowcount>=5)
                cout<<"The book is available, but you already reach your borrowing limit. You need to return some books to borrow another"<<endl;
                else
                {
                cout<<"You can borrow this book, but remember to return it within three days."<<endl;
                users.push_back(User(name,0,title));
                it.copies--;
                it.borrowcount++;
                }
                }
                else
                {
                    cout<<"You can't borrow this book, because this book is currently out of stock."<<endl;
                }
            }
        }
    }
    void return_title(string title,string name)
    {
        for(auto &it:archive)
        {
            if(it.title==title)
            {
            it.copies++;
            for(auto it:users)
            {
                if(name==it.name)
                {
                    it.return_book(title);
                    return;
                }
            }
            }
        }
        //可以用ISBN或是title去做還書的操作
        for(auto &it:archive)
        {
            if(it.ISBN==title)
            {
            it.copies++;
            title=it.title;
            for(auto it:users)
            {
                if(name==it.name)
                {
                    it.return_book(title);
                    return;
                }
            }
            }
        }
        cout<<"The return book title is wrong"<<endl;
        return ;
    }

    void search_year(int year)
    {
        bool flag;
        vector<Book> find;
        for(auto &it:archive)
        {
            if(it.year==year)
            {
                it.findingcount++;
                find.push_back(it);
                flag=true;
            }
        }
        if(flag)
        {
        sort_title(find);
        print(find);
        }
        else
        cout << "\033[31mNo books were published in this year.\033[0m" << endl;
    }
    void search_name(string title)
    {
        bool flag=false;
        vector<Book> find;
        for(auto &it:archive)
        {
            
            if(it.title==title || it.ISBN==title)
            {
                it.findingcount++;
                find.push_back(it);
                flag=true;
            }
        }
        if(flag)
        {
        sort_title(find);
        print(find);
        }
        else
        cout<<"There are no books that match your criteria."<<endl;
    }

    void search_genre(string genre)
    {
        bool flag=false;
        vector<Book> find;
        for(auto &it:archive)
        {
            
            if(it.genre==genre)
            {
                it.findingcount++;
                find.push_back(it);
                flag=true;
            }
        }
        if(flag)
        {
        sort_title(find);
        print(find);
        }
        else
        cout<<"There are no books that match your criteria."<<endl;
    }
    void print(vector<Book> &print)
    {
        if(print.empty())
        cout<<"There are no books that match your criteria."<<endl;
        else
        for(auto &it:print)
        {
            cout<<"Title: "<<it.title<<endl;
            cout<<"Author: "<<it.author<<endl;
            //cout<<it.publisher<<endl;
            cout<<"Available Copies: "<<it.copies<<endl;
            cout<<"Findingcount: "<<it.findingcount<<endl<<endl;
        }
    }
    void printall()
    {
        for(auto &it:archive)
        {
            cout<<"Title: "<<it.title<<endl;
            cout<<"Author: "<<it.author<<endl;
            //cout<<it.publisher<<endl;
            cout<<"Available Copies: "<<it.copies<<endl;
            cout<<"Findingcount: "<<it.findingcount<<endl<<endl;
        }
    }
    void print_findingcount()
    {
        sort_findingcount(archive);
        for(auto &it:archive)
        {
            cout<<"Title: "<<it.title<<endl;
            cout<<"Findingcount: "<<it.findingcount<<endl<<endl;
        }
        sort_title(archive);
    }
    void print_higgest_borrowcount()
    {
        int max=0;
        for(auto it:archive)
        {
            if(max<it.borrowcount)
            max=it.borrowcount;
        }
        for(auto it:archive)
        {
            if(max==0)
            {
                cout<<"No books have been checked out yet."<<endl;
            }
            else if(max==it.borrowcount)
            {
                cout<<it.title<<" has been borrowed "<<max<<" times"<<endl;
            }
        }
    }
    void print_higgest_overall_rating()
    {
        double overallmax=0;
        vector<Book>::iterator reserve;
        for(auto it:archive)
        {
            if(it.borrowcount==0)
            continue;
            if(overallmax<(it.rating/it.borrowcount)+it.findingcount)
            overallmax=(it.rating/it.borrowcount)+it.findingcount;
        }
        for(auto it:archive)
        {
            if(overallmax==0)
            {
                cout<<"No books have been rated yet."<<endl;
                return;
            }
            else if(overallmax==(it.rating/it.borrowcount)+it.findingcount)
            {
                cout<<it.title<<" has the highest overall rating."<<endl;
            }
        }

    }
    void print_rating()
    {
        sort_rating_count(archive);
        for(auto &it:archive)
        {
            if(it.borrowcount!=0)
            {
            cout<<"Title: "<<it.title<<endl;
            cout<<"Rating: "<<(double)it.rating/it.borrowcount<<endl<<endl;
            }
            else
            cout<<"This book hasn't been rated yet."<<endl;
        }
        sort_title(archive);
    }
    bool cmp_title(string first,string second)
    {
        int count=0;
        while(count<first.length() && count<second.length())
        {
    
            if(first[count]<second[count])
            return 0;
            if(first[count]>second[count])
            return 1;
            count++;
        }
        return second.length() < first.length();
    }
    void ratecount(double rate,string title)
    {
        for(auto &it:archive)
        {
            if(it.title==title || it.ISBN==title)
            {
                it.rating+=rate;
            }
        }
    }
   
    void sort_rating_count(vector<Book> &sort)
    {
        int check=1;
        while(check)
        {
            check=0;
            for(auto i=sort.begin();i!=sort.end()-1;i++)
            {
                if(i->rating/i->borrowcount<(i+1)->rating/(i+1)->borrowcount)
                {
                    Book temp = *i;
                    *i = *(i + 1);
                    *(i + 1) = temp;
                    check=1;
                }
                else if(i->rating/i->borrowcount==i->rating/i->borrowcount && (i+1)->borrowcount>i->borrowcount)
                {
                    Book temp = *i;
                    *i = *(i + 1);
                    *(i + 1) = temp;
                    check=1;
                }
            }
        }
    }
    void sort_title(vector<Book> &sort)
    {
        int check=1;
        while(check)
        {
            check=0;
            for(auto i=sort.begin();i!=sort.end()-1;i++)
            {
                if(cmp_title(i->title,(i+1)->title))
                {
                    Book temp = *i;
                    *i = *(i + 1);
                    *(i + 1) = temp;
                    check=1;
                }
            }
        }
    }
    void sort_findingcount(vector<Book> &sort)
   {
        int check=1;
        while(check)
        {
            check=0;
            for(auto i=sort.begin();i!=sort.end()-1;i++)
            {
                if(i->findingcount<(i+1)->findingcount)
                {
                    Book temp = *i;
                    *i = *(i + 1);
                    *(i + 1) = temp;
                    check=1;
                }
            }
        }
    }
    bool cmp_ISBN(string first,string second)
    {
        int count=0;
        while(count<first.length() && count<second.length())
        {
            if(first[count]<second[count])
            return 0;
            if(first[count]>second[count])
            return 1;
            count++;
        }
        return 0;
    }
   void sort_ISBN(vector<Book> &sort)
    {
        int check=1;
        while(check)
        {
            check=0;
            for(auto i=sort.begin();i!=sort.end()-1;i++)
            {
                if(cmp_ISBN(i->ISBN,(i+1)->ISBN))
                {
                    auto tmp=i;
                    i=(i+1);
                    (i+1)=tmp;
                    check=1;
                }
            }
        }
    }
    vector<Book> find_tag(string tag,vector<Book> after)
    {
        bool flag;
        vector<Book> find;
        
        for(auto &it:after)
        {
            flag=false;
            for(auto i=it.tag.begin();i!=it.tag.end();i++)
            {
                if(*i==tag)
                {
                    flag=true;
                    break;
                }
            }
            if(flag)
            find.push_back(it);
        }
        if(flag)
        {
        sort_title(find);
        return find;
        }
        else
        return find;
    }
};