#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Movie.h"

Movie::Movie(int id, int numCopies){
    this->id = id;
    this->numCopies = numCopies;
    this->originalNumCopies = numCopies;
    this->isDeleted = false;
    //cout << "/DEBUG/ Movie " << id << " " << numCopies << endl;

    peopleRent = new Subscriber**[12];
    countPeopleRent = new int[12];
    for(int i = 0; i < 12; i++)
    {
        peopleRent[i] = new Subscriber*[DEFAULT_SIZE];
    }
}

bool Movie::rentBy(Subscriber* subs, int month)
{
    //IMPORTANT!!! add code for the cases that count passes the length of the array

    int countOfGivenMonth = countPeopleRent[month];
    for(int i = 0; i < countOfGivenMonth; i++)
    {
        if( peopleRent[month][i] == subs ) return false; //if the given subscriber has already rent this movie in this specific month return false
    }

    peopleRent[month][countOfGivenMonth] = subs; //add the subscriber to the peopleRent array
    subs->addMovieToMoviesRent(this, month); //add this movie's pointer to that subscriber's moviesRent array
    numCopies--; //decrement the available number of copies
    countPeopleRent[month]++; //increment the count also
    return true;
}

bool Movie::returnBy(Subscriber* subs, int month)
{
    bool transactionExists = false;
    int countOfGivenMonth = countPeopleRent[month];
    for(int i = 0; i < countOfGivenMonth; i++)
    {
        if( peopleRent[month][i] == subs ) //if the movie is rent by this subscriber in this specific month
        {
            transactionExists = true;
            break;
        }
    }

    if(!transactionExists ) return false; //there is no such a transaction
    else
    {
        numCopies++; //increment the number of copies again
        return true;
    }
}

void Movie::showPeopleRent()
{
    bool noPeopleRent = true;
    for(int i = 0; i < 12; i++)
    {
        if( countPeopleRent[i] > 0)
        {
            noPeopleRent = false;
            break;
        }
    }

    if(noPeopleRent)
    {
        cout << "Movie " << this->getId() << " has not been rented by any subscribers!" << endl;
        return;
    }
    else cout << "Movie " << this->getId() << " has been rented by the following subscribers:" << endl;

    for(int i = 0; i < 12; i++)
    {
        int countOfMonth = countPeopleRent[i];
        for(int j = 0; j < countOfMonth; j++)
        {
            cout << peopleRent[i][j]->getId() << " in " << MovieRentalSystem::giveMonthName(i) << endl;
        }
    }
}

bool Movie::isAllCopiesReturned()
{
    return numCopies < originalNumCopies;
}

bool Movie::checkDeleted()
{
    return isDeleted;
}

void Movie::deleteMovie()
{
    if( isDeleted )
        cout << "The movie " << this->id << "has already been deleted" << endl;
    else if( isAllCopiesReturned() )
        cout << "The movie " << this->id << " has at least one copy  which has not been returned!" << endl;
    else
    {
        isDeleted = true;
        cout << "The movie " << this->id << "has been deleted successfully!" << endl;
    }
}

void Movie::show()
{
    cout << "Movie ID: " << id << " Remaining copies: " << numCopies << endl;
}

int Movie::getId(){ return this->id; }
int Movie::getNumCopies() { return this->numCopies; }

Movie::~Movie()
{
	
	for(int i = 0; i < 12; i++)
	{
		delete [] peopleRent[i];
	}
	delete []peopleRent;
	
	delete []countPeopleRent;
}
