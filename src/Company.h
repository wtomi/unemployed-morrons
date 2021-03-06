//
// Created by tommy on 12.06.17.
//

#ifndef UNEMPLOYED_MORRONS_COMPANY_H
#define UNEMPLOYED_MORRONS_COMPANY_H


#include "AgentRequest.h"
#include "RequestsQueue.h"

class Company {
public:
    typedef std::shared_ptr<Company> SharedPtr;

    static SharedPtr Create(int companyId, int maxNumberOfMorons, int maxDamegeLevel, int agentId);

    int getCompanyId();

    void addRequest(int agentId, long agentClock, int requestedPlaces);

    void addRequestOfCurrentAgent(long agentClock, int requestedPlaces);

    void removeRequest(int agentId, long agentClock);

    void removeLastRequestOfCurrentAgent();

    AgentRequest::SharedPtr getLastRequestOfCurrentAgent();

    void addReply(long requestClock);

    int getNumberOfReplies();

    int getNumberOfFreePlacesForLastRequestOfCurrentAgent();

    bool isChangedLastRequestOfCurrentAgent();

    void updateRequest(int agentId, long agentClock, int numberOfRequestedPlaces);

    void updateLastRequestOfCurrentAgent();

    void placeMoronsInCompany(int numberOfMoronsPlaced);

    int getNumberOfMoronsPlaced();

    bool isUsed();

    void breakCompany();

    void repairCompany();

    bool isBroken();

    int getBreakCount();

    int getRepairCount();

    void resetLastRequestOfCurrentAgent();

    void damage(double damageValue);

    bool isDamageExceeded();

    int getNumberOfOccupiedPlacesToLastRequest();

private:
    Company(int companyId, int maxDamageLevel, int maxNumberOfMorons, int agentId);

    int companyId;
    int maxNumberOfMorons;
    int maxDamageLevel;
    int agentId;

    double actualDamageLevel = 0.0;
    RequestsQueue requestsQueue;
    AgentRequest::SharedPtr lastRequest = nullptr;
    int numberOfReplies = 0;
    int numberOfMoronsPlaced = 0;
    int breakCount = 0;
    int repairCount = 0;
    bool broken = false;
};


#endif //UNEMPLOYED_MORRONS_COMPANY_H
