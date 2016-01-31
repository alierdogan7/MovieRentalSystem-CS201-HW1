#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

#include "MovieRentalSystem.h"
int main(int argc, char *argv[] ) {

	for(int i = 0; i < 50000; i++)
	{   
		MovieRentalSystem* myMovieRentalSystem = new MovieRentalSystem( "movies.txt", "subscribers.txt" );
		delete myMovieRentalSystem;
	}   
   
   return 0;
}
