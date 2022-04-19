#include "client.cpp"
#include "image.cpp"



int main(int argc, char const *argv[])
{
    image testImageMan = image();
    client c = client();
    struct message request;

    request.ID = 25;
    request.instruction = 0;
    struct message* answer;
    answer = c.sendRequest(request);
    testImageMan.img = c.imageReceived;
    testImageMan.decodeImage();

    return 0;
}
