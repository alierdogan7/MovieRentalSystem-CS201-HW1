#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

#include "MovieRentalSystem.h"

MovieRentalSystem::MovieRentalSystem( string mFile = "movies.txt", string sFile = "subscribers.txt")
{
    this->balance = new int[12]; //for keeping monthly balances

    //LOADING MOVIES
    ifstream movieFile;
    movieFile.open(mFile.c_str());
    string line;

    getline(movieFile, line);
    this->numMovies = atoi( line.c_str() );
    this->movies = new Movie*[numMovies];
    //cout << "/DEBUG/ numMovies " << numMovies<< endl;

    int counter = 0;
    while( !movieFile.eof() && counter < this->numMovies)
    {
        getline(movieFile, line);

        int pos = line.find_first_of(" ");
        //cout << pos << endl;

        int movieId, movieAmount;
        movieId = atoi( line.substr(0, pos).c_str() );
        movieAmount = atoi( line.substr(pos+1).c_str() );
        //cout << "/DEBUG/ movie " << movieId  << ", " << movieAmount <<  endl;

        movies[counter] = new Movie(movieId, movieAmount);
        counter++;
    }

    movieFile.close();

    //LOADING SUBSCRIBERS
    ifstream subsFile;
    subsFile.open(sFile.c_str() );

    getline(subsFile, line);
    this->numSubscribers = atoi( line.c_str() );
    this->subscribers = new Subscriber*[numSubscribers];

    counter = 0;
    while( !subsFile.eof() && counter < this->numSubscribers)
    {
        getline(subsFile, line);

        int pos = line.find_first_of(" ");

        int subsId, subsType;
        subsId = atoi( line.substr(0, pos).c_str() );
        subsType = atoi( line.substr(pos+1).c_str() );

        //cout << "/DEBUG/ subsID " << subsId << " subsType " << subsType << endl;
        subscribers[counter] = new Subscriber(subsId, subsType, this);
        counter++;
    }

    subsFile.close();
}


void MovieRentalSystem::rentMovie( const int subscriberId, const int movieId, Months month )
{
    //check whether movie exists or not
    bool movieExists = false;
    int movieIndex;
    for(int i = 0; i < numMovies; i++)
    {
        if( movies[i]->getId() == movieId && !movies[i]->checkDeleted() ) { //if the pointer of this movie exists and the movie is not in "deleted" status
            movieExists = true;
            movieIndex = i;
            break;
        }
    }

    //check whether subscriber exists or not
    bool subsExists = false;
    int subsIndex;
    for(int i = 0; i < numSubscribers; i++)
    {
        if( subscribers[i]->getId() == subscriberId ) {
            subsExists = true;
            subsIndex = i;
            break;
        }
    }

    if( !movieExists && !subsExists)
    {
        cout << "The subscriber " << subscriberId << " and the movie " << movieId << " doesn't exist!" << endl;
        return;
    }
    if( !subsExists)
    {
        cout << "The subscriber " << subscriberId << " doesn't exist!" << endl;
        return;
    }
    if( !movieExists)
    {
        cout << "The movie " << movieId << " doesn't exist!" << endl;
        return;
    }

    //if both exist control whether there is available copy
    if( movies[movieIndex]->getNumCopies() > 0 )
    {
        int monthIndex = month;
        bool isSuccesful = movies[movieIndex]->rentBy(subscribers[subsIndex], monthIndex);
        if ( !isSuccesful)
        {
            cout << "Another copy of this movie " << movieId << " has already been rented by " << subscriberId << endl;
            return;
        }

        cout << "The movie " << movieId << " is rent by subscriber " << subscriberId << " in " << giveMonthName(monthIndex) << endl;
    }
    else cout << "There is no copy left for " << movieId << endl;

}

void MovieRentalSystem::deleteMovie(const int movieId)
{
    //check whether movie exists or not
    bool movieExists = false;
    int movieIndex;
    for(int i = 0; i < numMovies; i++)
    {
        if( movies[i]->getId() == movieId ) {
            movieExists = true;
            movieIndex = i;
            break;
        }
    }

    if(!movieExists)
    {
        cout << "The movie " << movieId << " doesn't exist!" << endl;
        return;
    }

    movies[movieIndex]->deleteMovie();
}

void MovieRentalSystem::returnMovie( const int subscriberId, const int movieId, Months month )
{
    //check whether movie exists or not
    bool movieExists = false;
    int movieIndex;
    for(int i = 0; i < numMovies; i++)
    {
        if( movies[i]->getId() == movieId && !movies[i]->checkDeleted() ) { //if the pointer of this movie exists and the movie is not in "deleted" status
            movieExists = true;
            movieIndex = i;
            break;
        }
    }

    //check whether subscriber exists or not
    bool subsExists = false;
    int subsIndex;
    for(int i = 0; i < numSubscribers; i++)
    {
        if( subscribers[i]->getId() == subscriberId ) {
            subsExists = true;
            subsIndex = i;
            break;
        }
    }

    if( !movieExists && !subsExists)
    {
        cout << "The subscriber " << subscriberId << " and the movie " << movieId << " doesn't exist!" << endl;
        return;
    }
    if( !subsExists)
    {
        cout << "The subscriber " << subscriberId << " doesn't exist!" << endl;
        return;
    }
    if( !movieExists)
    {
        cout << "The movie " << movieId << " doesn't exist!" << endl;
        return;
    }


    //CHECK WHETHER TRANSACTION EXISTS OR NOT
    int monthIndex = month;
    bool isSuccesful = movies[movieIndex]->returnBy(subscribers[subsIndex], monthIndex);
    if(!isSuccesful) cout << "There is no such a transaction: subscriber " << subscriberId
                        << " movie " << movieId << " in " << giveMonthName(monthIndex) << endl;
    else cout << "The movie " << movieId << " has been returned by subscriber " << subscriberId << " in " << giveMonthName(monthIndex) << endl;
}

void MovieRentalSystem::showMoviesRentedBy( const int subscriberId )
{
    //check whether subscriber exists or not
    bool subsExists = false;
    int subsIndex;
    for(int i = 0; i < numSubscribers; i++)
    {
        if( subscribers[i]->getId() == subscriberId ) {
            subsExists = true;
            subsIndex = i;
            break;
        }
    }

    if( !subsExists)
    {
        cout << "The subscriber " << subscriberId << " doesn't exist!" << endl;
        return;
    }

    subscribers[subsIndex]->showMoviesRent();
}

void MovieRentalSystem::showSubscribersWhoRentedMovie( const int movieId )
{
    //check whether movie exists or not
    bool movieExists = false;
    int movieIndex;
    for(int i = 0; i < numMovies; i++)
    {
        if( movies[i]->getId() == movieId && !movies[i]->checkDeleted() ) { //if the pointer of this movie exists and the movie is not in "deleted" status
            movieExists = true;
            movieIndex = i;
            break;
        }
    }

    if( !movieExists)
    {
        cout << "The movie " << movieId << " doesn't exist!" << endl;
        return;
    }

    movies[movieIndex]->showPeopleRent();
}

string MovieRentalSystem::giveMonthName(int month)
{
    switch(month)
    {
        case 0: return "JANUARY";
        case 1: return "FEBRUARY";
        case 2: return "MARCH";
        case 3: return "APRIL";
        case 4: return "MAY";
        case 5: return "JUNE";
        case 6: return "JULY";
        case 7: return "AUGUST";
        case 8: return "SEPTEMBER";
        case 9: return "OCTOBER";
        case 10: return "NOVEMBER";
        case 11: return "DECEMBER";
        default: return "UNKNOWN";
    }
}

void MovieRentalSystem::increaseBalance( int amount, int month)
{
    balance[month] += amount;
}

void MovieRentalSystem::showBalance(Months month)
{
    int monthInt = month;
    cout << giveMonthName(monthInt) << " balance is "<< balance[month] << endl;
}

void MovieRentalSystem::showAllSubscribers()
{
    for(int i = 0; i < this->numSubscribers; i++)
    {
        subscribers[i]->show();
    }
}

void MovieRentalSystem::showAllMovies()
{
    for(int i = 0; i < this->numMovies; i++)
    {
        movies[i]->show();
    }
}

MovieRentalSystem::~MovieRentalSystem()
{
	for(int i = 0; i < numMovies; i++)
	{
		delete movies[i];
	}
	delete []movies;
	
	for(int i = 0; i < numSubscribers; i++)
	{
		delete subscribers[i];
	}
	delete []subscribers;
}
