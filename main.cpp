//
//  Project 1 Starter Code - Recommendations
// 
// Author: Nikita Mashchenko, U. of Illinois Chicago, Spring 2021
//  
// Creative component : advice function
// to call just type "advice"
//if user watched all of the movies from advanced and Basic
//and wants to comeback and re-watch something he can use advice

#include "ourvector.h"
#include <fstream>
#include <string>


using namespace std;


        // struct to keep usernames and their ratings
struct netflix 
{
    string user = "";
    ourvector<int> rating;
};

        // struct to keep filmnames, their indexes and averages
struct films
{
    string filmname;
    int index;
    double average;
};

        //ourvector function that finds digits in line rating user 
        //and push them back inside the ratings ourvector.
        //after that operations the function returns ourvector ratings

ourvector<int> getRating(string &ratinguser, ourvector<netflix> &data)
{
    ourvector<int> ratings;
    
     while(!ratinguser.empty())
     {
    size_t pos = ratinguser.find(" ");
    string rtngTemp = ratinguser.substr(0,pos);
    
    int rtngStr = stoi(rtngTemp);
    
    ratings.push_back(rtngStr);
    
    
    ratinguser = ratinguser.substr(pos + 1, ratinguser.size() - rtngTemp.size() - 1);
    }
 
    return ratings;
}

        //readfile function that take 2 files itemsFile and ratingsFile and take data from them
        //then after recieving data it push_back it inside the ourvector of structs that is called data

void readFile(string filename1, string filename2, ourvector<netflix> &data, ourvector<string> &podcasts, int &countpodcasts)
{
    
    countpodcasts = 0;
    ourvector<int> rating;

    cin >> filename1;  // input filename:
    cin >> filename2;


    cout << endl;

    ifstream infile(filename1);
    ifstream infile1(filename2);

    string podcast;
    string username;
    string ratinguser;
    
    
    if (!infile.good())
    {
        cout << "**file not found" << endl;
        exit(0);
    }

    while (!infile.eof())  // while not end-of-file
    {
        getline(infile, podcast, '\n');
        if (!infile.fail())
        {
            podcasts.push_back(podcast);
            countpodcasts++;
        }
    }
    
    cout << "Reading items file..." << endl;
    for(int i = 0; i < podcasts.size(); i++)
    {
        cout << podcasts[i] << endl;
    }
    
    cout << endl;
    
    
    
    if (!infile1.good())
    {
        cout << "**file not found" << endl;
        exit(0);
    }

   
    while (!infile1.eof())  // while not end-of-file
    {
         getline(infile1, username, '\n');
         getline(infile1, ratinguser, '\n');
         
        if (!infile1.fail())
        
        {
            netflix name;
            name.user = username;
            name.rating = getRating(ratinguser, data); 
            data.push_back(name);
        }
    }
    
   
   cout << "Reading ratings file..." << endl;
    for (auto st: data)
    {
        cout << st.user << endl;
        for(auto e: st.rating)
        {
        cout << e << " ";
        }
        
        cout << endl;
    }
    cout << endl;
    cout << "Welcome to the Recommendations App!" << endl;
    
}


            // simple function that lets user login
            // check is used to verify that user is logged in.

void loginUser(string &user_login, ourvector<netflix> &data)
{
    
    int check = 0;
    
     for (auto n: data)
    {
        if(user_login == n.user)
        {
            cout << "Success." << endl;
            cout << "Logged in as: " << user_login << endl;
            check = 1;
            break;
        }
    }
        if(check != 1)
        {
            user_login = "N/A";
            cout << "User not found, please try again." << endl;
            cout << "Logged in as: " << user_login << endl;
        }
    
}

            //this function adds new users and fill
            //their ratings with zeroes

void addUser(ourvector<netflix> &data,string &user_login, int &countpodcasts)
{
    netflix newuser;
   
    ourvector<int> ratings;
   
    for(int i = 0; i < countpodcasts; i++)
    {
         ratings.push_back(0);
    }
    
    newuser.user = user_login;
    newuser.rating = ratings;
    
    data.push_back(newuser);
    cout << "Logged in as: " << user_login << endl;
}

            //this function adds rating to users by accessing indexes of ratings
            //insert rating number at a specific index
            //same check if user is logged or not using check
            
void addRating(ourvector<netflix> &data, int &item_num, ourvector<string> podcasts, string &user_login,int &rating_num)
{
    int check = 0;
    
   
  for(auto &st: data)
  {
      if(st.user == user_login)
      {
        
        cout << "Item number to add/change rating: ";
        cin >> item_num;
        
        cout << "Add the rating for " << podcasts.at(item_num) << ": ";
        cin >> rating_num;
          st.rating[item_num] = rating_num;
          
          cout << endl;
          cout << "Logged in as: " << user_login << endl;
          check = 1;
      }
  }
        if(check != 1)
        {
          cout << "To complete the operation, you must first login." << endl;
          cout << "Type \"login username\"." << endl;
          cout << endl;
          cout << "Logged in as: N/A" << endl;
        }
}

            //show rating of a specific user ignoring all zeroes 
            //which means that user hasn't watched the movie.
            //same check if user is logged or not using check
            
void showRating(string &user_login, ourvector<netflix> &data, ourvector<string> &podcasts, int& countpodcasts)
{
    int check = 0;
    for(auto n: data)
    {
      if(user_login == n.user)
      {
          cout << user_login << "'s Ratings:" << endl;
          for(int i = 0; i < n.rating.size(); i++)
          {
              if(n.rating[i] != 0)
              {
                  cout << podcasts[i] << ", " << n.rating[i] << "/5" << endl;
              }
          }
          check = 1;
          cout << endl;
          cout << "Logged in as: " << user_login << endl;
          break;
      }
    }
        if(check != 1)
        {
                
          cout << "To complete the operation, you must first login." << endl;
          cout << "Type \"login username\"." << endl;
          cout << endl;
          cout << "Logged in as: N/A" << endl;
           
        }
    
}

            //swap function that works with doubles and used
            //in the bubble sort function 

void swap(double *xp, double *yp)  
{  
    double temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  


            //swap function that works with strings and used
            //in the buuble sort
            
void swap_string(string *first, string *second)  
{  
    string temp1 = *first;  
    *first = *second;  
    *second = temp1;  
}  

  
            // A bubbleSort function that is used to detect top 
            // five movies that we have to recommend 
            
void bubbleSort(ourvector<films> &temp, int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)      
      
    for (j = 0; j < n-i-1; j++)  
        if (temp[j].average < temp[j+1].average)
        { 
            swap(&temp[j].average, &temp[j+1].average); 
            swap_string(&temp[j].filmname, &temp[j+1].filmname);
        }
}  


            //Basic function that is used to calculate the average rating for all the podcasts
            //in the database and then suggest the top 5 podcasts that user hasn't already rated.
            
void showBasic(int& countpodcasts,ourvector<netflix> &data, string &user_login, ourvector<string> &podcasts)
{
    double ratingTotal = 0.0;
    double ratingAvg = 0.0;
    int n;
    int check = 0;
    
    //ourvector of struct films that is used to keep track 
    //of movies that user hasn't watched
    
    ourvector<films> temp;
    
    //for loop that is used to find movies that
    //are rated by 0 and push_back them to temp
    
    for(int i = 0; i < countpodcasts; i++)
    {
        for(int j = 0; j < data.size(); j++)
        {
            if(data[j].user == user_login && data[j].rating[i] == 0)
            {
                temp.push_back({podcasts[i],i,0});
            }
        }
    }
    
    //for loop to calculate total rating
    
    for(int k = 0; k < temp.size(); k++)
    {
        for(auto &d: data)
        {
            if(d.user != user_login)
            {
                ratingTotal += d.rating[temp[k].index];
            }
        }
        ratingAvg = ratingTotal / (data.size() - 1);
        temp[k].average = ratingAvg;
        ratingTotal = 0.0;
    }
    
    n = temp.size();
    
    //we use bubble sort to find top 5 movies
    
    bubbleSort(temp, n);
    int z = 0;
    
    for(auto ch: data)
    {
         if(user_login == ch.user)
              {
                     cout << "Basic recommendations: " << endl;
    
                        while(z < 5 && z < temp.size())
                    {
                         cout << temp[z].filmname << endl; 
                         z++;
                    }
                     
                     check = 1;
                     cout << endl;
                     cout << "Logged in as: " << user_login << endl;
                     break;
              }
    }

            if(check != 1)
        {
                
          cout << "To complete the operation, you must first login." << endl;
          cout << "Type \"login username\"." << endl;
          cout << endl;
          cout << "Logged in as: " << user_login << endl;
           
        }

}

            //Advanced function that is used to calculate the pair-wise similarity between one specific user and every other user,
            //then identify whose ratings are most similar to specific user’s.  
            
void showAdvanced(int& countpodcasts,ourvector<netflix> &data, string &user_login, ourvector<string> podcasts)
{
   double temporary = 0.0;
   int check = 0;
   
   //ourvector for storing top movies
   
   ourvector<films> advtop;
   
   int index = 0;
   
   int index1 = 0;
   
   int maxVal = 0;
   
   //ourvector to calculate highest similarity
   
   ourvector<int> calculations;
   
   //we need to find index of a specific user
   //to use it further
   
   for(int i = 0; i < data.size(); i++)
   {
       if(user_login == data[i].user)
       {
           index = i;
       }
   }
   
   
    //for loop to calculate dot product between two users and then
    //push_back it to calculation vector
   
      for(int j = 0; j < data.size(); j++)
    {
        for(int i = 0; i < countpodcasts; i++)
        {
            if(data[j].user != user_login)
            {
                temporary += data[index].rating[i] * data[j].rating[i];
            }
        }
         calculations.push_back(temporary);

         temporary = 0;
    }
    
    //sort values in vector
    //by finding maxValue
    
    for(int k = 0; k < calculations.size(); k++)
    {
        if(maxVal < calculations[k])
        {
            maxVal = calculations[k];
            index1 = k;
        }
    }
    
    //forloop to find movies that user rated as zeroes
    //and then push them back to advtop 
    //we also push_back podcasts
    
    for(int i = 0; i < countpodcasts; i++)
    {
        if(data[index].rating[i] == 0)
        {
        advtop.push_back({podcasts[i],0, double(data[index1].rating[i])});
        }
    }
    
    int n = advtop.size();
   
    
    cout << endl;
    
    //same bubbleSort as in basic 
    
    bubbleSort(advtop,n);
    int z = 0;
    
           for(auto che: data)
    {
         if(user_login == che.user)
              {
                        cout << "Advanced recommendations: " << endl;
    
                        while(z < 5 && z < advtop.size())
                        {
                             cout << advtop[z].filmname << endl; 
                             z++;
                        }
                     
                     check = 1;
                     cout << endl;
                     cout << "Logged in as: " << user_login << endl;
                     break;
              }
    }

            if(check != 1)
        {
                
          cout << "To complete the operation, you must first login." << endl;
          cout << "Type \"login username\"." << endl;
          cout << endl;
          cout << "Logged in as: " << user_login << endl;
           
        }
   
}

            //this function simply print users

void printUsers(ourvector<netflix> &data, string &user_login)
{
    for(auto n:data)
    {
        cout << n.user << endl;
    }
    
    cout << endl;
    cout << "Logged in as: " << user_login << endl;
}

            //this function simply print items(e.g books,films)
            
void printItems(ourvector<netflix> &data, string &user_login, ourvector<string> &podcasts)
{
    int counter = 0;
    
    for(int i = 0; i < podcasts.size(); i++)
    {
        cout << counter << ". " << podcasts.at(i) << endl;
        counter++;
    }
    
    cout << endl;
    cout << "Logged in as: " << user_login << endl;
}
 
 //function is used to recomend users to re-watch movies
 //that he rated for 5 stars(only if he watched basic and advanced movies)
 
void showAdvice(int& countpodcasts,ourvector<netflix> &data, string &user_login, ourvector<string> podcasts)
{
    int index = 0;
    int z = 0;
    int check = 0;

       for(int i = 0; i < data.size(); i++)
   {
       if(user_login == data[i].user)
       {
           index = i;
       }
   }
        ourvector<films> random;
    
    
    for(int t = 0; t < countpodcasts; t++)
    {
            if(data[index].user == user_login && data[index].rating[t] == 5)
            {
                random.push_back({podcasts[t],t,0});
            }
    }
    
              for(auto che: data)
                {
         if(user_login == che.user)
              {
                        cout << "You should probably re-watch: " << endl;
    
                        while(z < 5 && z < random.size())
                        {
                            cout << random[z].filmname <<endl;
                            z++;
                        }
                     
                     check = 1;
                     cout << endl;
                     cout << "Logged in as: " << user_login << endl;
                     break;
              }
                }
    

            if(check != 1)
        {
                
          cout << "To complete the operation, you must first login." << endl;
          cout << "Type \"login username\"." << endl;
          cout << endl;
          cout << "Logged in as: " << user_login << endl;
           
        }
                
}
            //main function to design and keep track of commands that user enters 
            //all of the other functions are used here

void enterCommand(ourvector<netflix> &data,ourvector<string> &podcasts, int& countpodcasts)
{
    string input1;
    string input2;
    string filename1;
    string filename2;
    string user_login;
    int item_num;
    int rating_num;
    string temp;
    user_login = "N/A";


    cout << "Enter command or # to quit: ";

    cin >> input1;

    while (input1 != "#")
    {
        if (input1 == "load")
        {
            readFile(filename1, filename2,data,podcasts,countpodcasts);
            cout << "Enter command or # to quit: ";
            
            cin >> input1;
        }
        else if(input1 == "login")
        {
           //cout << "chmo";
            getline(cin,user_login);
            user_login.erase(0,1);
            
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << endl;
            
            loginUser(user_login,data);
            
            
            cout << "Enter command or # to quit: ";
            
            cin >> input1;
        }
        else if(input1 == "show")
        {
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << endl;
            showRating(user_login,data,podcasts,countpodcasts);
        
            cout << "Enter command or # to quit: ";
            
            cin >> input1;
        }
        else if(input1 == "basic")
        {
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << endl;
           
            showBasic(countpodcasts,data,user_login,podcasts);
            
            cout << "Enter command or # to quit: ";
            
            cin >> input1;
        }
        else if(input1 == "advanced")
        {
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << endl;

            showAdvanced(countpodcasts,data,user_login,podcasts);
            
            cout << "Enter command or # to quit: ";
            
            cin >> input1;
        }
        else if(input1 == "print")
        {
            cin >> input2;
            {
                if(input2 == "users")
                {
                    cout << endl;
                    cout << "-----------------------------" << endl;
                    cout << endl;
                    printUsers(data,user_login);
                    cout << "Enter command or # to quit: ";
            
                    cin >> input1;
                }
                else if(input2 == "items")
                {
                    cout << endl;
                    cout << "-----------------------------" << endl;
                    cout << endl;
                    printItems(data,user_login,podcasts);
                    
                    cout << "Enter command or # to quit: ";
            
                    cin >> input1;
                }
            }
            
        }
        else if(input1 == "add")
        {
            cin >> input2;
            {
                if(input2 == "user")
                {
                    cout << endl;
                    cout << "-----------------------------" << endl;
                    cout << endl;
                    
                    cout << "Please enter the username: ";
                    getline(cin,temp,'\n');
                    getline(cin,user_login);
                    
                    addUser(data,user_login, countpodcasts);
                    
                    cout << "Enter command or # to quit: ";
            
                    cin >> input1;
                }
                else if(input2 == "rating")
                {
                    cout << endl;
                    cout << "-----------------------------" << endl;
                    cout << endl;
                    
                    addRating( data, item_num, podcasts, user_login, rating_num);
                    
                    cout << "Enter command or # to quit: ";
            
                    cin >> input1;
                }
            }
        }
        else if(input1 == "advice")
                {
                    cout << endl;
                    cout << "-----------------------------" << endl;
                    cout << endl;
                    
                    showAdvice(countpodcasts,data,user_login,podcasts);
                    
                    cout << "Enter command or # to quit: ";
            
                    cin >> input1;
                }
        if(input1 == "#")
        {
                    cout << endl;
                    cout << "-----------------------------" << endl;
                    cout << endl;
                    cout << endl;
                    cout << "Thank you for using the Recommendations app!" << endl;
                    break;
        }
        
    }

}


int main() {
    //TODO:  Write your code here.  You should have LOTS of function decomposition.
    cout << "To start the app, load the data." << endl;
    cout <<"Type \"load itemsFile ratingsFile\" and press enter." << endl;
    cout << endl;
    
    // count items
    
   int countpodcasts;
   
   //ourvector for items 
   
    ourvector<string> podcasts;
    
    //ourvector for struct
    //netflix
    
    ourvector<netflix> data;
    
    enterCommand(data,podcasts,countpodcasts);


    return 0;
}

