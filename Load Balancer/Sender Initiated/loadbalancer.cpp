//loadbalancer main code

#include<iostream>

loadBalancer::loadBalancer(){
    cout<<endl<<"LoadBalancer is up and running..."<<endl;
}

void loadBalancer::addRequestToBuffer(request req){
    requestBuffer.push(req);
}

request loadBalancer::getRequestFromBuffer(){
    request r;
    if (requestBuffer.empty())
    {
        cout<<"request buffer empty";
    }
    else
    {
        //cout task removed from server requestBuffer.front()
        r = requestBuffer.front();
        requestBuffer.pop();
    }
    return r;
}
bool loadBalancer::isRequestBufferEmpty(){
    return requestBuffer.empty();
}
