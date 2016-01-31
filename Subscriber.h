#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

#include "Movie.h"
#include "MovieRentalSystem.h"

class Movie;
class MovieRentalSystem;

class Subscriber {
public:
	Subscriber(int id, int type, MovieRentalSystem* system);
	~Subscriber();
	void show();
	int getId();
	int getType();
	void addMovieToMoviesRent( Movie* mov, int month);
	void showMoviesRent();

private:
	int id;
    int type;
    MovieRentalSystem* system; //necessary for updating the balance of the MovieRentalSystem
	Movie ***moviesRent; //The first dimension is for 12 months, the second dimension is for the Movie pointer array
	int *countMoviesRent; //holds the counts of the arrays that holds the movie pointers
    static const int DEFAULT_SIZE = 20; //default size for the Movie pointer arrays
};

#endif
