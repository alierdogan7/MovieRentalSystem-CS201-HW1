#ifndef MOVIERENTALSYSTEM_H
#define MOVIERENTALSYSTEM_H

#include "Movie.h"
#include "Subscriber.h"

class Movie;
class Subscriber;


class MovieRentalSystem {
public:
    MovieRentalSystem(const string mFile, const string sFile);
    ~MovieRentalSystem();

    enum Months {JANUARY = 0, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY,
    AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};
    enum SubscriptionType {ALLYOUCANWATCH = 0, PAYPERMOVIE};

    const static int ALLYOUCANWATCH_COST = 30;
    const static int PAYPERMOVIE_COST = 4;

    void deleteMovie( const int movieId );
    void rentMovie( const int subscriberId, const int movieId, Months month );
    void returnMovie( const int subscriberId, const int movieId, Months month );
    void showMoviesRentedBy( const int subscriberId );
    void showSubscribersWhoRentedMovie( const int movieId );
    void showBalance( Months month );
    void increaseBalance( int amount, int month);
    static string giveMonthName(int month);

    void showAllSubscribers();
    void showAllMovies();

private:
    Movie **movies; //the array that holds the movie pointers
    Subscriber **subscribers; //the array that holds the subscriber pointers
    int numMovies;
    int numSubscribers;
    int* balance; //the balances for 12 months
};

#endif
