#ifndef WEBSERVER_H
#define WEBSERVER_H

#ifndef REQUEST_CPP
#include "request.cpp"
#endif

#include <queue>
#include <vector>
using namespace std;

class webserver{
    public:
            webserver();
            webserver(char name);
            char getName();
            void addRequest(request req); //can be used to migrate request on overload
            void migrateRequestOnLoad(request req);
            request getRequest();
            void removeRequest();
            float calculateServerLoad();
            void addWebserverAddress(webserver *webserverPointer);//for polling
            void displayData();
            int getRequestQueueSize();
            void displayWebserverAddress();
            int getWebServerPointersSize();
            void ServerInitiatedLoadBalancing(request req);
        private : queue<request> requestQueue;
            vector<webserver*> webserverPointers;
            char serverName;
            float serverLoad = 0;
};

#endif
#include "webserver.cpp"