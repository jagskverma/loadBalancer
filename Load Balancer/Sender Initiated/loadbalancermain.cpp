//Program entry point

#include "request.cpp"
#include "webserver.h"
#include "loadbalancer.h"


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

#define NUMBEROFSERVERS 5

 
//Creates a random request with random ips. 
request createRandomRequest(){
    stringstream ip_source,ip_destination;
    request r;
    ip_source << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ip_destination << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    r.source = ip_source.str();
    r.destination = ip_destination.str();
    return r;
}



//Display adapter for menu driven program
void displayMenu(){
    cout<<endl<<"1.See Server List with load"<<endl;
    cout<<"2.Add task to server i"<<endl;
    cout<<"3.Remove task from server i"<<endl;
    cout<<"4.Display Menu"<<endl;
    cout<<"5.Exit"<<endl;
}



int main(){
    //seed for random numbers
    srand(time(0));

    //create a loadbalancer object
    loadBalancer lb;

    //populate loadbalancer buffer
    for(int i=0;i<NUMBEROFSERVERS*20;i++){
        request r = createRandomRequest();
        lb.addRequestToBuffer(r);
    }


    //create server array
    webserver serverArray[NUMBEROFSERVERS]; 
    //cout<<endl<<"*2*"<<endl;

    //initialize servers with one task each
    for(int i=0;i<NUMBEROFSERVERS;i++){
        webserver w((char)(i+65));
        serverArray[i]=w;
        request r=lb.getRequestFromBuffer();
        serverArray[i].addRequest(r);
    }

    //populate each server with other server's address
    //Workaround for message passing between objects
    for (int i = 0; i < NUMBEROFSERVERS;i++){
        for (int j = 0; j < NUMBEROFSERVERS;j++){
            if(i!=j){
                serverArray[i].addWebserverAddress(&serverArray[j]);
            }
        }
    }

    
    int flag=1,i;
    //displayMenu();
    while(flag){
        displayMenu();
        int ch;cin>>ch;
        switch(ch){
            case 1: //1. See Server List with load
                for(int i=0;i<NUMBEROFSERVERS;i++){
                    serverArray[i].displayData();
                    cout<<endl;
                }
                break;
            case 2: //2.Add task to server i
                cout<<"Enter server number to add task: (0-"<<NUMBEROFSERVERS-1<<")"<<endl;
                cin>>i;
                if(i>=NUMBEROFSERVERS || i<0)
                    cout<<"Enter a valid choice between 0-"<<NUMBEROFSERVERS-1<<endl;
                else{
                    if(!lb.isRequestBufferEmpty())
                        serverArray[i].addRequest(lb.getRequestFromBuffer());
                }
                break;
            case 3: //3.Remove task from server i
                cout << "Enter server number to remove task from: (0-" << NUMBEROFSERVERS - 1 << ")";
                cin>>i;
                if(i>=NUMBEROFSERVERS || i<0)
                    cout<<"Enter a valid choice between 0-"<<NUMBEROFSERVERS-1;
                else{
                    serverArray[i].removeRequest();
                }
                break;
            case 4 :
                displayMenu();
                break;
            case 5: //5.Exit
                flag=0;
                break;
            default:
                cout<<"Please Enter a valid choice"<<endl;
                break;
        }

    }

return 0;
}


