//Load Balancer header file
#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#ifndef REQUEST_CPP
#include "request.cpp"
#endif 

#include<queue>
using namespace std;


class loadBalancer{
    public:
        loadBalancer();    
        void addRequestToBuffer(request req);
        request getRequestFromBuffer();
        bool isRequestBufferEmpty();
    private:
        queue<request> requestBuffer;   
};

#endif

#include "loadbalancer.cpp"