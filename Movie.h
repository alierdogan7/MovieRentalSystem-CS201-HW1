#ifndef MOVIE_H_
#define MOVIE_H_

#include "Subscriber.h"

class Subscriber;

class Movie {
public:
	Movie(int id, int numCopies);
	~Movie();
	void show();
	void showPeopleRent();
	int getId();
	int getNumCopies();

	//if in that specific month, the subscriber has already rented a copy of this movie, return false
	// also calls the rentMovie function of Subscriber class and adds the pointer of this movie to the moviesRent array
	bool rentBy(Subscriber* subs, int month);

    //if in that specific month, the subscriber has rented a copy of this movie, return the movie and return true
    // if there is no such a transaction, return false
	bool returnBy(Subscriber* subs, int month);
    bool isAllCopiesReturned();
    void deleteMovie();
    bool checkDeleted();

private:
	int id;
	int numCopies;
	bool isDeleted; //for making the movie unavailable for renting if it is deleted from program
	int originalNumCopies; //for identifying if there is a copy which has not been returned or not
	Subscriber ***peopleRent; //The first dimension is for 12 months, the second dimension is for the Subscriber pointer array
	int *countPeopleRent; //holds the counts of the arrays that holds the subscriber pointers
    static const int DEFAULT_SIZE = 20; //default size for Subscriber pointer arrays
};

#endif
