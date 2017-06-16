//
// Created by tommy on 16.06.17.
//

#ifndef UNEMPLOYED_MORRONS_GOOUTOFQUEUEMESSAGE_H
#define UNEMPLOYED_MORRONS_GOOUTOFQUEUEMESSAGE_H


#include "Message.h"

class GoOutOfQueueMessage : public Message {
public:
    typedef std::shared_ptr<GoOutOfQueueMessage> SharedPtr;
    static SharedPtr Create(int rank, int tag, int companyId);
private:
    friend class cereal::access;
    GoOutOfQueueMessage(): Message() {}
    GoOutOfQueueMessage(int rank, int tag, int companyId);
    int companyId;

    template<class Archive>
    void serializa(Archive &ar) {
        ar(cereal::base_class<Message>(this), companyId);
    }
};


#endif //UNEMPLOYED_MORRONS_GOOUTOFQUEUEMESSAGE_H
