#include <iostream>
#include <vector>
#include <string>

class User;

class Message {
private:
    User* from;
    User* to;
    std::string message;
public:
    Message(User* from, User* to, std::string message) {
        this->from = from;
        this->to = to;
        this->message = message;
    }
    User* getFrom() {
        return from;
    }
    User* getTo() {
        return to;
    }
    std::string getMessage() {
        return message;
    }
};

class User {
private:
    std::string username;
    std::vector<Message*> messages;
public:
    User(std::string username) {
        this->username = username;
    }
    std::string getUsername() {
        return username;
    }
    void sendMessage(User* to, std::string message) {
        Message* newMessage = new Message(this, to, message);
        to->receiveMessage(this, message);
        messages.push_back(newMessage);
    }
    void receiveMessage(User* from, std::string message) {
        Message* newMessage = new Message(from, this, message);
        messages.push_back(newMessage);
    }
    std::vector<Message*> getMessages() {
        return messages;
    }
};

class MessageApp {
private:
    std::vector<User*> users;
public:
    void registerUser(std::string username) {
        User* newUser = new User(username);
        users.push_back(newUser);
    }
    void sendMessage(User* from, User* to, std::string message) {
        from->sendMessage(to, message);
    }
    void receiveMessage(User* from, User* to, std::string message) {
        to->receiveMessage(from, message);
    }
    std::vector<User*> getUsers() {
        return users;
    }
};

int main() {
    MessageApp app;
    app.registerUser("Alice");
    app.registerUser("Bob");

    std::vector<User*> users = app.getUsers();
    User* alice = users[0];
    User* bob = users[1];

    alice->sendMessage(bob, "Hello Bob!");
    bob->sendMessage(alice, "Hi Alice, how are you?");

    std::vector<Message*> aliceMessages = alice->getMessages();
    std::vector<Message*> bobMessages = bob->getMessages();

    std::cout << "Alice's messages:" << std::endl;
    for (Message* message : aliceMessages) {
        std::cout << message->getFrom()->getUsername() << ": " << message->getMessage() << std::endl;
    }

    std::cout << "Bob's messages:" << std::endl;
    for (Message* message : bobMessages) {
        std::cout << message->getFrom()->getUsername() << ": " << message->getMessage() << std::endl;
    }

    return 0;
}
