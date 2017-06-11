//
// Created by tommy on 11.06.17.
//

#include "Messenger.h"
#include "Serializer.h"

void Messenger::send(Message::SharedPtr message) {
    std::stringstream stringstreamMsg = Serializer::serialize(message);
    Packet packet(stringstreamMsg, message->rank, message->tag);
    monitor.send(packet);
}

Message::SharedPtr Messenger::receive() {
    return receive(Monitor::ANY_SOURCE, Monitor::ANY_TAG);
}

Message::SharedPtr Messenger::receive(int source, int tag) {
    Packet packet = monitor.receive(source, tag);
    auto message = Serializer::deserialize(packet.stringstreamMessage);
    message->rank = packet.rank;
    message->tag = packet.tag;
    return message;
}

int Messenger::getRank() {
    return monitor.rank;
}

int Messenger::getSize() {
    return monitor.size;
}
