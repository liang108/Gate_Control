#pragma once


#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

typedef size_t CardNumber;

typedef size_t GateNumber;


struct Authorization
{
	Authorization() { }
	
	Authorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
	: number_(number), name_(name), startTime_(startTime), endTime_(endTime) { }

	CardNumber number_;

	string name_;
	
	string startTime_;
	
	string endTime_;
};

typedef map<CardNumber, Authorization> AuthorizationMap;
typedef	AuthorizationMap::iterator AuthorizationMapIterator;

typedef	vector<Authorization> AuthorizationVector;

struct Transaction
{
	Transaction() { }

	Transaction(CardNumber number, const string& name, const string& date, const string& time, bool accessAllowed)
	: number_(number), name_(name), date_(date), time_(time), accessAllowed_(accessAllowed) { }

	CardNumber number_;
	
	string name_;
	
	string date_;

	string time_;
	
	bool accessAllowed_;
};

typedef	vector<Transaction> TransactionVector;
typedef	TransactionVector::iterator TransactionVectorIterator;

class	GateControl
{
	public:
		bool accessAllowed(CardNumber number);
	
		bool addAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime);
		
		bool changeAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime);
		
		bool deleteAuthorization(CardNumber number);
		
		void getAllAuthorizations(AuthorizationVector& authorizationVector);
		
		void getAllTransactions(TransactionVector& transactionVector);
	
		bool getCardAuthorization(CardNumber number, Authorization& authorization);

		void getCardTransactions(CardNumber number, TransactionVector& transactionVector);

	private:
		AuthorizationMap authorizationMap_;
		
		TransactionVector transactionVector_;
};



extern string gCurrentDate;

extern string gCurrentTime;



//****************************************************************************************
//
//	TO DO
//
//****************************************************************************************


bool GateControl::accessAllowed(CardNumber number)
{
	for (AuthorizationMapIterator iter = authorizationMap_.begin(); iter != authorizationMap_.end(); ++iter) {
		if (number == iter->first)
		{
			Transaction new_transaction(number, iter->second.name_, gCurrentDate, gCurrentTime, true);
			transactionVector_.push_back(new_transaction);
			return true;
		}
	}

	Transaction new_transaction(number, "***", gCurrentDate, gCurrentTime, false);
	transactionVector_.push_back(new_transaction);
	return false;
}


bool GateControl::addAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{
	//Authorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
	for (AuthorizationMapIterator iter = authorizationMap_.begin(); iter != authorizationMap_.end(); ++iter)
	{
		if (iter->first == number)
		{
			std::cout << "Authentication already exists" << std::endl;
			return false;
		}
	}
	Authorization new_auth(number, name, startTime, endTime);
	authorizationMap_.insert(std::pair<CardNumber, Authorization>(number, new_auth));
	return true;
}


bool GateControl::changeAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{
	
	for (AuthorizationMapIterator iter = authorizationMap_.begin(); iter != authorizationMap_.end(); ++iter)
	{
		if (iter->first == number){
			iter->second.name_ = name;
			iter->second.startTime_ = startTime;
			iter->second.endTime_ = endTime;
			return true;
		}
	}
	return false;
}

bool GateControl::deleteAuthorization(CardNumber number)
{
	for (AuthorizationMapIterator iter = authorizationMap_.begin(); iter != authorizationMap_.end(); ++iter) {
		if (iter->first == number)
		{
			authorizationMap_.erase(iter);
			return true;
		}
	}
	return false;
}


void GateControl::getAllAuthorizations(AuthorizationVector& authorizationVector)
{
	authorizationVector.clear();
	for (AuthorizationMapIterator iter = authorizationMap_.begin(); iter != authorizationMap_.end(); ++iter)
	{
		authorizationVector.push_back(iter->second);
	}
}


void GateControl::getAllTransactions(TransactionVector& transactionVector)
{
	transactionVector.clear();
	for (TransactionVectorIterator iter = transactionVector_.begin(); iter != transactionVector_.end(); ++iter) {
		transactionVector.push_back(*iter);
	}
}


bool GateControl::getCardAuthorization(CardNumber number, Authorization& authorization)
{

	for (AuthorizationMapIterator iter = authorizationMap_.begin(); iter != authorizationMap_.end(); ++iter){
		if (iter->first == number)
		{
			authorization.name_ = iter->second.name_;
			authorization.number_ = iter->second.number_;
			authorization.startTime_ = iter->second.startTime_;
			authorization.endTime_ = iter->second.endTime_;
			return true;
		}
	}
	return false;
}


void GateControl::getCardTransactions(CardNumber number, TransactionVector& transactionVector)
{
	bool found = false;
	for (TransactionVectorIterator iter = transactionVector_.begin(); iter != transactionVector_.end(); ++iter)
	{
		if (iter->number_ == number)
		{
			transactionVector.push_back(*iter);
			found = true;
		}
	}

	if (found == false)
	{
		transactionVector.clear();
	}
}
