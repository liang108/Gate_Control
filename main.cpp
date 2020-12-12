
#include	<iostream>

#include	"GateControl.hpp"

using namespace std;


string	gCurrentDate;

string	gCurrentTime;


bool	CompareAuthorizations(AuthorizationVector& actualVector,
							  AuthorizationVector& expectedVector,
							  ostream& stream);

bool	CompareTransactions(TransactionVector& actualVector,
							TransactionVector& expectedVector,
							ostream& stream);

void	ShowAuthorizations(ostream& stream, AuthorizationVector& authorizationVector);

void	ShowTransactions(ostream& stream, TransactionVector& transactionVector);

void	TestAccess();

void	TestAdd();

void	TestCard();

void	TestChange();

void	TestDelete();

//****************************************************************************************
//
//	MAIN PROGRAM
//
//****************************************************************************************
int main (int argc, char * const argv[])
{
	
		

	TestAdd();

	TestDelete();

	TestChange();

	TestCard();

	TestAccess();

	

	cout << endl << "** Finished **" << endl;

	return(0);
}

//****************************************************************************************
//
//	CompareAuthorizations
//
//****************************************************************************************
bool	CompareAuthorizations(AuthorizationVector& actualVector,
							  AuthorizationVector& expectedVector,
							  ostream& stream)
{
	//************************************************************************************
	//	LOCAL DATA
	bool	good;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	good = true;
	if (actualVector.size() == expectedVector.size())
	{
		for (size_t i = 0; i < actualVector.size(); ++i)
		{
			if ((actualVector[i].number_ != expectedVector[i].number_)
				||
				(actualVector[i].name_ != expectedVector[i].name_)
				||
				(actualVector[i].startTime_ != expectedVector[i].startTime_)
				||
				(actualVector[i].endTime_ != expectedVector[i].endTime_))
			{
				stream << "Authorizations don't match" << endl;
				good = false;
			}
		}
	}
	else
	{
		stream << "Sizes don't match" << endl;
		good = false;
	}

	if (!good)
	{
		stream << "Actual:"<< endl;
		ShowAuthorizations(stream, actualVector);

		stream << "Expected:"<< endl;
		ShowAuthorizations(stream, expectedVector);
	}

	return(good);
}

//****************************************************************************************
//
//	CompareTransactions
//
//****************************************************************************************
bool	CompareTransactions(TransactionVector& actualVector,
							TransactionVector& expectedVector,
							ostream& stream)
{
	//************************************************************************************
	//	LOCAL DATA
	bool	good;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	good = true;
	if (actualVector.size() == expectedVector.size())
	{
		for (size_t i = 0; i < actualVector.size(); ++i)
		{
			if ((actualVector[i].number_ != expectedVector[i].number_)
				||
				(actualVector[i].name_ != expectedVector[i].name_)
				||
				(actualVector[i].date_ != expectedVector[i].date_)
				||
				(actualVector[i].time_ != expectedVector[i].time_))
			{
				stream << "Transactions don't match" << endl;
				good = false;
			}
		}
	}
	else
	{
		stream << "Sizes don't match" << endl;
		good = false;
	}

	if (!good)
	{
		stream << "Actual:"<< endl;
		ShowTransactions(stream, actualVector);

		stream << "Expected:"<< endl;
		ShowTransactions(stream, expectedVector);
	}

	return(good);
}

//****************************************************************************************
//
//	ShowAuthorizations
//
//****************************************************************************************
void	ShowAuthorizations(ostream& stream, AuthorizationVector& authorizationVector)
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	if (!authorizationVector.empty())
	{
		for (size_t i = 0; i < authorizationVector.size(); ++i)
		{
			stream << i << ": "
			<< " " << authorizationVector[i].number_
			<< " " << authorizationVector[i].name_
			<< " " << authorizationVector[i].startTime_
			<< " " << authorizationVector[i].endTime_ << endl;
		}
	}
	else
	{
		stream << "<empty>" << endl;
	}

	stream << endl;

	return;
}

//****************************************************************************************
//
//	ShowTransactions
//
//****************************************************************************************
void	ShowTransactions(ostream& stream, TransactionVector& transactionVector)
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	if (!transactionVector.empty())
	{
		for (size_t i = 0; i < transactionVector.size(); ++i)
		{
			stream << i << ": "
			<< " " << transactionVector[i].number_
			<< " " << transactionVector[i].name_
			<< " " << transactionVector[i].date_
			<< " " << transactionVector[i].time_
			<< " " << boolalpha << transactionVector[i].accessAllowed_ << endl;
		}
	}
	else
	{
		stream << "<empty>" << endl;
	}

	stream << endl;

	return;
}


//****************************************************************************************
//
//	TestAdd
//
//****************************************************************************************
void	TestAdd()
{
	//************************************************************************************
	//	LOCAL DATA
	AuthorizationVector	actualVector;

	AuthorizationVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl<<"Testing AddAuthorization" << endl;

	cout << "  Check Empty ";
	gateControl.getAllAuthorizations(actualVector);
	if (actualVector.empty())
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	cout << "  Add First ";
	expectedVector.push_back(Authorization(111, "Smith, John", "0800", "1700"));
	success = gateControl.addAuthorization(111, "Smith, John", "0800", "1700");
	if (success)
	{
		gateControl.getAllAuthorizations(actualVector);
		good = CompareAuthorizations(actualVector, expectedVector, cout);
		if (good)
		{
			cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
		}
		else
		{
			cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
		}
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	cout << "  Add Second ";
	expectedVector.push_back(Authorization(222, "Brown, William", "0100", "2300"));
	success = gateControl.addAuthorization(222, "Brown, William", "0100", "2300");
	if (success)
	{
		gateControl.getAllAuthorizations(actualVector);
		good = CompareAuthorizations(actualVector, expectedVector, cout);
		if (good)
		{
			cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
		}
		else
		{
			cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
		}
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	cout << "  Add Duplicate ";
	success = gateControl.addAuthorization(111, "Jones, Peter", "0800", "1700");
	if (!success)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	return;
}

//****************************************************************************************
//
//	TestDelete
//
//****************************************************************************************
void	TestDelete()
{
	//************************************************************************************
	//	LOCAL DATA
	AuthorizationVector	actualVector;

	AuthorizationVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl<<"Testing DeleteAuthorization" << endl;

	success = gateControl.addAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.addAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.addAuthorization(333, "Jones, Peter", "0333", "2333");

	cout << "  Existing Card ";
	success = gateControl.deleteAuthorization(222);

	expectedVector.push_back(Authorization(111, "Smith, John", "0800", "1700"));
	expectedVector.push_back(Authorization(333, "Jones, Peter", "0333", "2333"));

	gateControl.getAllAuthorizations(actualVector);
	good = CompareAuthorizations(actualVector, expectedVector, cout);
	if (good)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	cout << "  Non-existent Card ";
	success = gateControl.deleteAuthorization(444);
	if (!success)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	return;
}

//****************************************************************************************
//
//	TestChange
//
//****************************************************************************************
void	TestChange()
{
	//************************************************************************************
	//	LOCAL DATA
	AuthorizationVector	actualVector;

	AuthorizationVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl<<"Testing ChangeAuthorization" << endl;

	success = gateControl.addAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.addAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.addAuthorization(333, "Jones, Peter", "0333", "2333");

	cout << "  Existing Card ";
	success = gateControl.changeAuthorization(222, "Brown, Bill", "1234", "1356");

	expectedVector.push_back(Authorization(111, "Smith, John", "0800", "1700"));
	expectedVector.push_back(Authorization(222, "Brown, Bill", "1234", "1356"));
	expectedVector.push_back(Authorization(333, "Jones, Peter", "0333", "2333"));

	gateControl.getAllAuthorizations(actualVector);
	good = CompareAuthorizations(actualVector, expectedVector, cout);
	if (good)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	cout << "  Non-existent Card ";
	success = gateControl.changeAuthorization(444, "", "", "");
	if (!success)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	return;
}

//****************************************************************************************
//
//	TestCard
//
//****************************************************************************************
void	TestCard()
{
	//************************************************************************************
	//	LOCAL DATA
	TransactionVector	actualVector;

	Authorization		authorization;

	TransactionVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl<<"Testing Card-Specific Functions" << endl;

	success = gateControl.addAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.addAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.addAuthorization(333, "Jones, Peter", "0333", "2333");

	cout << "  GetCardAuthorization ";
	success = gateControl.getCardAuthorization(222, authorization);
	if ((authorization.name_ == "Brown, William")
		&&
		(authorization.startTime_ == "0100")
		&&
		(authorization.endTime_ == "2300"))
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	cout << "  GetCardTransactions ";
	gCurrentDate = "11092020";
	gCurrentTime = "0900";
	success = gateControl.accessAllowed(111);
	gCurrentTime = "0901";
	success = gateControl.accessAllowed(222);
	gCurrentTime = "0902";
	success = gateControl.accessAllowed(333);
	gCurrentTime = "0903";
	success = gateControl.accessAllowed(111);
	gCurrentTime = "0904";
	success = gateControl.accessAllowed(222);
	gCurrentTime = "0905";
	success = gateControl.accessAllowed(333);

	expectedVector.push_back(Transaction(222, "Brown, William", "11092020", "0901", true));
	expectedVector.push_back(Transaction(222, "Brown, William", "11092020", "0904", true));
	gateControl.getCardTransactions(222, actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	return;
}


//****************************************************************************************
//
//	TestAccess
//
//****************************************************************************************
void	TestAccess()
{
	//************************************************************************************
	//	LOCAL DATA
	TransactionVector	actualVector;

	TransactionVector	expectedVector;

	GateControl			gateControl;

	bool				good;

	bool				success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << endl<<"Testing Access" << endl;

	success = gateControl.addAuthorization(111, "Smith, John", "0800", "1700");
	success = gateControl.addAuthorization(222, "Brown, William", "0100", "2300");
	success = gateControl.addAuthorization(333, "Jones, Peter", "0333", "2333");

	cout << "  Allowed 1 ";
	gCurrentDate = "11092020";
	gCurrentTime = "0100";
	success = gateControl.accessAllowed(222);

	expectedVector.push_back(Transaction(222, "Brown, William", "11092020", "0100", true));
	gateControl.getAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);

	if (good)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	cout << "  Allowed 2 ";
	gCurrentDate = "11092020";
	gCurrentTime = "2300";
	success = gateControl.accessAllowed(222);

	expectedVector.push_back(Transaction(222, "Brown, William", "11092020", "2300", true));
	gateControl.getAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	cout << "  Denied 1 ";
	gCurrentDate = "11092020";
	gCurrentTime = "0059";
	success = gateControl.accessAllowed(222);

	expectedVector.push_back(Transaction(222, "Brown, William", "11092020", "0059", false));
	gateControl.getAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	cout << "  Denied 2 ";
	gCurrentDate = "11092020";
	gCurrentTime = "2312";
	success = gateControl.accessAllowed(444);

	expectedVector.push_back(Transaction(444, "***", "11092020", "2312", false));
	gateControl.getAllTransactions(actualVector);
	good = CompareTransactions(actualVector, expectedVector, cout);
	if (good)
	{
		cout << "\033[32m" << "Pass. " << "\033[0m" << endl;
	}
	else
	{
		cout << "\033[31m" << "Fail. " << "\033[0m" << endl;
	}

	return;
}
