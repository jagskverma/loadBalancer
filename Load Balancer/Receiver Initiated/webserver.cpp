//Webserver implemented per thread
//Receiver-Initiated

#include <cstdlib>
#include<iostream>

#define numberOfPollingTrials 10.0
using namespace std;

int nAddresses;
float REQUEST_BUFFER_SIZE=10.0;
float loadThreshold=0.3;

//set servername constructors
webserver::webserver(){
    serverName=' ';
}
webserver::webserver(char c){
    serverName=c;
}

//return servername
char webserver:: getName()
{
    return serverName;
}

//return request if server was overloaded
request webserver::migrateRequestOnLoad(){
    request r=requestQueue.front();
    requestQueue.pop();
    return r;
}

//receiver load balancing
int webserver :: receiverInitiatedLoadBalancing(){
    int p = numberOfPollingTrials;
    nAddresses = webserverPointers.size();

    while(--p){
        int i = rand() % (nAddresses);
        webserver *w = webserverPointers[i];

        if(w->calculateServerLoad()>loadThreshold){
            request r;
            r = w->migrateRequestOnLoad();
            addRequest(r);
            cout << "Server Underloaded : Migrated task from : "<<w->getName() << endl;
            return 1;
        }
    }
    cout<<"No Servers Overloaded. Nothing to migrate."<<endl;
    return 0;
}

//simpluy add to buffer
void webserver::addRequest(request req){

    if(requestQueue.size()==(int)REQUEST_BUFFER_SIZE){
        cout<<"Server Full. Cannot add Task"<<endl;
        return;
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
{   if(requestQueue.empty()){
        cout<<"No requests to Remove"<<endl;
    }
    else{
        requestQueue.pop();
        float serverLoad = calculateServerLoad();
        if(serverLoad<=loadThreshold)
            receiverInitiatedLoadBalancing();  
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

//handle for populating webserver addresses
void webserver:: addWebserverAddress(webserver *webserverPointer){
    webserverPointers.push_back(webserverPointer);
    
}
//helper function for debugging
void webserver::displayWebserverAddress(){
    for(int i=0;i<webserverPointers.size();i++){
        webserverPointers[i]->displayData();
        cout<<endl;
    }
}
//display data
void webserver::displayData(){
    cout<<"Server Name: " <<getName()<<" Load: "<<(float)calculateServerLoad()<<endl;
}
//helpre : returns queue size
int webserver::getRequestQueueSize(){
    return requestQueue.size();
}


