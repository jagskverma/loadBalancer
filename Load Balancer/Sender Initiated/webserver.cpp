//Webserver implemented per thread
//Sender-Initiated

#include <cstdlib>
#include<iostream>

#define numberOfPollingTrials 5
using namespace std;

int nAddresses;
float REQUEST_BUFFER_SIZE =10.0;
float loadThreshold=0.7;
//return servername
webserver::webserver(){
    serverName=' ';
}
webserver::webserver(char c){
    serverName=c;
}
char webserver:: getName()
{
    return serverName;
}
//simple method to push method on reciever end when server was overloaded
void webserver::migrateRequestOnLoad(request req){
    requestQueue.push(req);
}

//Server Initiated load Balancing Algorithm
void webserver :: ServerInitiatedLoadBalancing(request req){
    int p = numberOfPollingTrials;
    nAddresses = webserverPointers.size();

    while(p--){
        int i = rand() % (nAddresses);
        webserver *w = webserverPointers[i];

        if(w->calculateServerLoad()<loadThreshold){
            
            w->migrateRequestOnLoad(req);
            cout << "Server Overloaded : Migrated task to : "<<w->getName() << endl;
            break;
        }
    }
    if(p==0){
        cout<<"All Servers busy. Cannot Migrate Task"<<endl;
        requestQueue.push(req);
    }
    
}
//Method to add request
void webserver::addRequest(request req){
    float serverLoad = calculateServerLoad();
    if(serverLoad>=loadThreshold){
        
        ServerInitiatedLoadBalancing(req);
    }  
    else{
        requestQueue.push(req);
    }      
}

//return request from front of the queue;
request webserver:: getRequest(){
    request r;
    if (requestQueue.empty()){
        cout << "Cannot return task from SERVER : " << serverName << " - Request Buffer empty";
    }
    else{
        //cout task removed from server requestQueue.front()
        r = requestQueue.front();
        requestQueue.pop();
    }
    return r;
}

//remove requests
void webserver::removeRequest()
{
    if(requestQueue.empty()){
        cout<<"Cannot remove task from SERVER : "<<serverName<<" - Request Buffer empty";
    }else{
        //cout task removed from server requestQueue.front()
        requestQueue.pop();
    }
}

//return current server load
float webserver:: calculateServerLoad()
{
    float requestQueueSize = (float)getRequestQueueSize();
    //cout<<requestQueueSize<<endl;
    float serverLoad = requestQueueSize/REQUEST_BUFFER_SIZE;
    return serverLoad;
}
//Handler to populate server addresses
void webserver:: addWebserverAddress(webserver *webserverPointer){
    webserverPointers.push_back(webserverPointer);
    
}

//method to pring server data for debugging
void webserver::displayWebserverAddress(){
    for(int i=0;i<webserverPointers.size();i++){
        webserverPointers[i]->displayData();
        cout<<endl;
    }
}

//to display server name and load
void webserver::displayData(){
    cout<<"Server Name: " <<getName()<<" Load: "<<(float)calculateServerLoad()<<endl;
}

//helper to return buffer size
int webserver::getRequestQueueSize(){
    return requestQueue.size();
}


