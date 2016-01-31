#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Subscriber.h"

Subscriber::Subscriber(int id, int type, MovieRentalSystem* system)
{
    this->id = id;
    this->type = type;
    this->system = system;
    //cout << "/DEBUG/ Subs " << id << " " << type << endl;

    moviesRent = new Movie**[12];
    countMoviesRent = new int[12];

    for(int i = 0; i < 12; i++)
    {
        moviesRent[i] = new Movie*[DEFAULT_SIZE]; //creates Movie pointer arrays for each month
    }

    // if subscription is monthly, pay for all 12 months when the subscriber is created
    if ( type == MovieRentalSystem::ALLYOUCANWATCH)
    {
        int amount = MovieRentalSystem::ALLYOUCANWATCH_COST;
        for(int i = 0; i < 12; i++)
            this->system->increaseBalance( amount, i);
    }
}

//this function is only called after the movie is rent in Movie class with rentBy() function
void Subscriber::addMovieToMoviesRent(Movie* mov, int month)
{
    //IMPORTANT!!! add code for the cases that count passes the length of the array

    int countOfMonth = countMoviesRent[month]++; //increment the count, because if this function is called it is certain that the movie has been rent
    moviesRent[month][countOfMonth] = mov;

    //if subscription type is PayPerMovie give money, else do nothing since this user has already paid for all months
    if ( type == MovieRentalSystem::PAYPERMOVIE )
    {
        int amount = MovieRentalSystem::PAYPERMOVIE_COST;
            this->system->increaseBalance( amount, month);
    }

}

void Subscriber::showMoviesRent()
{
    bool noMoviesRent = true;
    for(int i = 0; i < 12; i++)
    {
        if( countMoviesRent[i] > 0)
        {
            noMoviesRent = false;
            break;
        }
    }

    if(noMoviesRent)
    {
        cout << "Subscriber " << this->getId() << " has not rented any movies!" << endl;
        return;
    }
    else cout << "Subscriber " << this->getId() << " has rented the following movies:" << endl;

    for(int i = 0; i < 12; i++)
    {
        int countOfMonth = countMoviesRent[i];
        for(int j = 0; j < countOfMonth; j++)
        {
            cout << moviesRent[i][j]->getId() << " in " << MovieRentalSystem::giveMonthName(i) << endl;
        }
    }

}

void Subscriber::show()
{
    cout << "Subscriber ID: " << id << " , Type: ";
    if ( this->type == MovieRentalSystem::ALLYOUCANWATCH) cout << "AllYouCanWatch";
    else cout << "PayPerMovie";
    cout << endl;
}

int Subscriber::getId(){ return this->id; }
int Subscriber::getType(){ return this->type; }

Subscriber::~Subscriber()
{
	
	for(int i = 0; i < 12; i++)
	{
		delete [] moviesRent[i];
	}
	delete []moviesRent;
	delete []countMoviesRent;
	

}
