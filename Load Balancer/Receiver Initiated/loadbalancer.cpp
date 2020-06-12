//loadbalancer main code

#include<iostream>

loadBalancer::loadBalancer(){
    cout<<endl<<"LoadBalancer is up and running..."<<endl;
}
//add request to loadbalancer buffer
void loadBalancer::addRequestToBuffer(request req){
    requestBuffer.push(req);
}
//get request from loadbalancer buffer
request loadBalancer::getRequestFromBuffer(){
    request r;
    r = requestBuffer.front();
    requestBuffer.pop();
    return r;
}
//check whether buffer is empty
bool loadBalancer::isRequestBufferEmpty(){
    return requestBuffer.empty();
}
