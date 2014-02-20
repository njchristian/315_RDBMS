#include "SportsLeague.h"

SportsLeague::SportsLeague( ) {
	
	// open file
	// create the 5 relations
}


void SportsLeague::addGame( ) {
	// InsertInto

	string parserCommand = "INSERT INTO games VALUES FROM";

	cout << "Please enter the location of the new game.\n";
	string location;
	cin >> location;

	parserCommand += " (\"" + location + "\", ";

	cout << "Please enter the date of the game.\n";
	string date;
	cin >> date;

	parserCommand += "\"" + date + "\", ";

	cout << "Please enter the time of the game.\n";
	string time;
	cin >> time;

	parserCommand += "\"" + time + "\", ";

	cout << "Please enter the game's associated sport.\n";
	string sport;
	cin >> sport;

	parserCommand += "\"" + sport + "\");";

	if ( database.execute( parserCommand ) == 1 ) {
		cout << "Game successfully added to the database.\n";
	}
	else {
		cout << "Invalid data entered - Game was not added to the database.\n";
		cout << "Please try again.\n";
	}
}


void SportsLeague::addMenu( ) {

}


void SportsLeague::addPlayer( ) {
	// InsertInto
}


void SportsLeague::addReferee( ) {
	// InsertInto
}


void SportsLeague::addSport( ) {
	// InsertInto
}


void SportsLeague::addTeam( ) {
	// InsertInto
}


void SportsLeague::changeGameLocation( ) {
	// update
}

void SportsLeague::changeGameTime( ) {
	// update
}

void SportsLeague::changeSportSeason( ) {
	// update
}

void SportsLeague::displaySportsGames( ) {
	// select
}


void SportsLeague::displaySportsPlayed( ) {

}


void SportsLeague::exit( ) {
	// write file
	// close file
	// exit
}


void SportsLeague::getAllReferees( ) {
	// union
}


void SportsLeague::getNonReferees( ) {
	// difference
}


void SportsLeague::gamesWhenTeamCouldPlay( ) {
	// cross product
}


void listNamesOfSports( ) {
	// project
}


void SportsLeague::listPlayersOnTeam( ) {
	// select
}


void SportsLeague::printMenu( ) {

}


void SportsLeague::removeGame( ) {
	// delete
}


void SportsLeague::removeMenu( ) {

}


void SportsLeague::removePlayer( ) {
	// delete
}


void SportsLeague::removeReferee( ) {
	// delete
}


void SportsLeague::removeSport( ) {
	// delete
}


void SportsLeague::removeTeam( ) {
	// delete
}


// an idea for allowing the user to try again if there
// was bad input so they don't have to navigate the menu again
bool SportsLeague::retry( ) {
	// ask user if they want to retry
	// return yes or no
}


void SportsLeague::run( ) {
	cout << "Welcome to the Sports League managing program.\n";

	char userChoice;
	for ( ;; ) {
		printMenu( );
		cin >> userChoice;

		switch ( userChoice ) {
		// adds
		case 'a':
			addMenu( );
			break;

		// removes
		case 'b':
			removeMenu( );
			break;

		// shows
		case 'c':
			showMenu( );
			break;

		// display sports games
		case 'd':
			displaySportsGames( );
			break;

		// exit
		case 'e':
			exit( );
			return;
			break;

		// display sports played
		case 'f':
			displaySportsPlayed( );
			break;

		case 'g':
			changeGameLocation( );
			break;

		case 'h':
			changeGameTime( );
			break;

		case 'i':
			changeSportSeason( );
			break;

		case 'j':
			getAllReferees( );
			break;

			//etc
		default:
			cout << "Invalid choice, please try again.\n";
		}
	}

}


void SportsLeague::showGames( ) {
	// uses SHOW
}


void SportsLeague::showMenu( ) {

}


void SportsLeague::showPlayers( ) {
	// uses SHOW
}


void SportsLeague::showReferees( ) {
	// uses SHOW
}


void SportsLeague::showSports( ) {
	// SHOW
}


void SportsLeague::showTeams( ) {
	// uses SHOW
}
