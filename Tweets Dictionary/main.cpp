/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/yyr8mdoh
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "hashTable.h"
#include "ioUtils.h"
#include "tweet.h"
#include "adts/stlList.h"
#include "adts/stlMaxPriorityQueue.h"

using namespace std;

void helper2(STLList<Tweet>* userList, string choice){
  vector<pair<int, Tweet>> vect1; 
  if(choice == "l"){
    for(int i = 0; i < userList->getSize(); i++) {
      Tweet tweet_i = userList->get(i); //maybe we have to change this to removeFirst at some point
      int like = tweet_i.likes; 
      pair<int, Tweet> p1(like, tweet_i);
      vect1.push_back(p1);
    }
  }
  else if(choice == "r") {
      for(int i = 0; i < userList->getSize(); i++) {
        Tweet tweet_i = userList->get(i); //maybe we have to change this to removeFirst at some point
        int retweet = tweet_i.retweets; 
        pair<int, Tweet> p1(retweet, tweet_i);
        vect1.push_back(p1);
      }
  }
  STLMaxPriorityQueue<int, Tweet> Q1(vect1); 
  
  for(int i = 0; i < 5; i++){
    if(!Q1.isEmpty()){
      Tweet tweet_i = Q1.remove(); 
      cout << tweet_i.username << "           " << tweet_i.date << endl; 
      cout << tweet_i.contents << endl; 
      cout << "Rpl: " << tweet_i.replies << "     Rtw: " << tweet_i.retweets << "       Lik: " << tweet_i.likes << "      URL: " << tweet_i.url << endl << endl; 
    }
  }

}

void helper1(HashTable<string, STLList<Tweet>*>* our_list, string input){
  if(our_list->contains(input) == false){
            cout << "Username not found!" << endl; 
  }

  else{
    STLList<Tweet>* userList = our_list->get(input);
    cout << "Search by (r)etweet count or (l)ike count? " << endl; 
    string input3;
    cin >> input3;

    if(input3 == "l"){
      helper2(userList, "l");
    }
    else if(input3 == "r") {
      helper2(userList, "r");
    }
    else{
      cout << "Invalid input! Try again." << endl;
    }
    
  }
}



int main(int argc, char** argv) {
    // TODO: implement the query tool
    
    if(argc == 2){

      cout << "Loading tweets..." << endl; 
      cout << "Processing tweets..." << endl; 
      cout << "File " << string(argv[1]) << " loaded." << endl;  
      cout << "Welcome to the tweet database query tool!" << endl; 
 
      try{
        List<Tweet>* Data = readTweetFile(argv[1]);
        if(Data->isEmpty()){
          throw runtime_error("Wrong.");
        }
        //have a try catch here 
        //dictionary will have keys equal to username and values equal to list of tweets by that user
        //next ditionary will have keys = dates and values = lists of tweet from that date
        
        
        HashTable<string, STLList<Tweet>*>* by_username  = new HashTable<string, STLList<Tweet>*>();
        HashTable<string, STLList<Tweet>*>* by_date = new HashTable<string, STLList<Tweet>*>();
        
        //creating dictionaries
        for(int i = 0; i < Data->getSize(); i++) {
          Tweet tweet_i = Data->removeFirst(); 
          string username = tweet_i.username;
          string date = tweet_i.date;

          if(by_username->contains(username) == false) {
            STLList<Tweet>* new_list = new STLList<Tweet>(); 
            by_username->insert(username, new_list);
          }
          
          STLList<Tweet>* list2 = by_username->get(username);  
          list2->insertFirst(tweet_i);  
          
          if(by_date->contains(date) == false) {
            STLList<Tweet>* new_list = new STLList<Tweet>(); 
            by_date->insert(date, new_list);
          }

          STLList<Tweet>* list3 = by_date->get(date);  
          list3->insertFirst(tweet_i);  
      
        }
        
        bool cond = true;
        string input1; 
        string input2; 

        while(cond){
          cout << "Please choose from the following options: " << endl; 
          cout << "A) Search by username " << endl;
          cout << "B) Search by date " << endl; 
          cout << "C) Quit " << endl; 
          cout << "? "; 
          cin >> input1; 

          if(input1 == "A"){//have a helper function for A case and handle B separately
            cout << "Please enter your search username: " << endl; 
            cin >> input2; 
            helper1(by_username, input2);
          }

          else if(input1 == "B"){//have a helper function for A case and handle B separately
            cout << "Please enter your search date: " << endl; 
            cin >> input2; 
            helper1(by_date, input2);
          }

          else if(input1 == "C"){
            cond = false; 
          }
          else{
            cout<<"Invalid input! Try again." <<endl;
          }
        }

      }
      catch(runtime_error e){
        cout<<"Problem with file!"<<endl;
      }
      
    }

    else{
      cout<<"Incorrrect number of arguments!";
    }
    
    return 0;
}
