//
// Created by tommy on 10.06.17.
//

#define CATCH_CONFIG_MAIN

#include <catch/catch.hpp>
#include "../src/Monitor.h"
#include "../src/Message.h"
#include "../src/Serializer.h"
#include "../src/Messenger.h"
#include "../src/DerivedMessage.h"

TEST_CASE("Sending and receiving packets", "[monitor]") {

    Monitor monitor;

    const int TAG = 0;
    std::string stringMessage("Hello!");
    auto stringStreamMessage = std::make_shared<std::stringstream>(stringMessage);
    if (monitor.rank == 0) {
        for (int i = 1; i < monitor.size; i++) {
            auto packet = Packet::Create(stringStreamMessage, i, TAG);
            monitor.send(packet);
        }
    } else {
        auto packet = monitor.receive();
        REQUIRE(packet->stringstreamMessage->str().compare(stringMessage) == 0);
    }
}

TEST_CASE("Message serializing and deserializing", "[serializer]") {
    auto message = Message::Create();
    message->clock = 5;
    message->word.assign("Hello");

    auto stringstream = Serializer::serialize(message);

    auto deserializedMessage = Serializer::deserialize(stringstream);

    REQUIRE(message->clock == deserializedMessage->clock);
    REQUIRE(message->word.compare(deserializedMessage->word) == 0);
}

TEST_CASE("Test Messenger", "[messenger]") {

    Messenger messenger;

    auto message = Message::Create();
    message->clock = 5;
    message->word.assign("Hello");
    message->tag = 0;

    if (messenger.getRank() == 0) {
        for (int i = 1; i < messenger.getSize(); i++) {
            message->rank = i;
            messenger.send(message);
        }
    } else {
        auto receivedMessage = messenger.receive();
        REQUIRE(message->clock == receivedMessage->clock);
        REQUIRE(message->word.compare(receivedMessage->word) == 0);
        REQUIRE(message->tag == receivedMessage->tag);
    }
}

TEST_CASE("Test passing derived messages", "[polymorphism]") {
    Messenger messenger;

    auto derivedMessage = DerivedMessage::Create();
    derivedMessage->word = "Hello";
    derivedMessage->myword = "My Hello";
    derivedMessage->clock = 10;
    derivedMessage->tag = 0;
    Message::SharedPtr message = derivedMessage;

    if (messenger.getRank() == 0) {
        for(int i = messenger.getRank(); i < messenger.getSize(); i++) {
            message->rank = i;
            messenger.send(message);
        }
    } else {
        Message::SharedPtr receivedMessage = messenger.receive();

        receivedMessage->sayWord();
        REQUIRE(message->clock == receivedMessage->clock);
        REQUIRE(message->tag == receivedMessage->tag);
        REQUIRE(message->word.compare(receivedMessage->word) == 0);
        auto derivedMessage = std::dynamic_pointer_cast<DerivedMessage>(message);
        auto receivedDerivedMessage = std::dynamic_pointer_cast<DerivedMessage>(receivedMessage);
        REQUIRE(derivedMessage->myword.compare(receivedDerivedMessage->myword) == 0);
    }
}