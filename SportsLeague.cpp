#include "SportsLeague.h"

// need to add the stuff so that the strings returned by the parser are stored in a vector<string>
// or whatever the instructions talk about

SportsLeague::SportsLeague( ) {
	// open files
	// create the 5 relations

	// somehow check if files exist bc if they don't then the relations need to be created
	// ifstream gamesFile( "games.db" );
	// ifstream playersFile( "players.db" );
	// ifstream refereesFile( "referees.db" );
	// ifstream sportsFile( "sports.db" );
	// ifstream teamsFile( "teams.db" );
	
	// maybe change open file so it returns something if the file is empty

	// if empty then create the relation

	database.execute( "OPEN games" );
	database.execute( "OPEN players" );
	database.execute( "OPEN referees" );
	database.execute( "OPEN sports" );
	database.execute( "OPEN teams" );
}


void SportsLeague::addGame( ) {
	// InsertInto

	for ( ;; ) {
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
			return;
		}
		else {
			cout << "Invalid data entered - Game was not added to the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::addMenu( ) {
	int userChoice;
	for ( ;; ) {
		cout << "Enter '1' to add to the game relation.\n";
		cout << "Enter '2' to add to the player relation.\n";
		cout << "Enter '3' to add to the referee relation.\n";
		cout << "Enter '4' to add to the sports relation.\n";
		cout << "Enter '5' to add to the team relation.\n";
		cin >> userChoice;
		switch ( userChoice ) {
		case '1':
			addGame( );
			break;
		case '2':
			addPlayer( );
			break;
		case '3':
			addReferee( );
			break;
		case '4':
			addSport( );
			break;
		case '5':
			addTeam( );
			break;
		default:
			"Invalid choice. Please try again.\n";
		}
	}
}


void SportsLeague::addPlayer( ) {
	// InsertInto
	// Firstname
	// Lastname
	// Net-ID
	// Sport ID
	for ( ;; ) {
		string parserCommand = "INSERT INTO players VALUES FROM";

		cout << "Please enter the first name of the player.\n";
		string firstName;
		cin >> firstName;

		parserCommand += " (\"" + firstName + "\", ";

		cout << "Please enter the last name of the player.\n";
		string lastName;
		cin >> lastName;

		parserCommand += "\"" + lastName + "\", ";

		cout << "Please enter the Net-ID of the player.\n";
		string netID; // should this be of type int??
		cin >> netID;

		parserCommand += "\"" + netID + "\", ";

		cout << "Please enter the sport ID that the player plays.\n";
		int sportID; 
		cin >> sportID;

		parserCommand += "\"" + to_string( sportID ) + "\");";

		if ( database.execute( parserCommand ) == 1 ) {
			cout << "Player successfully added to the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Player was not added to the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::addReferee( ) {
	// InsertInto
	// first name
	// last name
	// sport id
	for ( ;; ) {
		string parserCommand = "INSERT INTO referees VALUES FROM";

		cout << "Please enter the first name of the referee.\n";
		string firstName;
		cin >> firstName;

		parserCommand += " (\"" + firstName + "\", ";

		cout << "Please enter the last name of the referee.\n";
		string lastName;
		cin >> lastName;

		parserCommand += "\"" + lastName + "\", ";


		cout << "Please enter the sport ID that the referee refs.\n";
		int sportID; 
		cin >> sportID;

		parserCommand += "\"" + to_string( sportID ) + "\");";

		if ( database.execute( parserCommand ) == 1 ) {
			cout << "Referee successfully added to the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Referee was not added to the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::addSport( ) {
	// InsertInto
	// name
	// sport id
	// season
	for ( ;; ) {
		string parserCommand = "INSERT INTO sports VALUES FROM";

		cout << "Please enter the name of the sport.\n";
		string name;
		cin >> name;

		parserCommand += " (\"" + name + "\", ";

		cout << "Please enter the ID of the sport.\n";
		int sportID;
		cin >> sportID;

		parserCommand += "\"" + to_string( sportID ) + "\", ";


		cout << "Please enter the season associated with the sport.\n";
		string season;
		cin >> season;

		parserCommand += "\"" + season + "\");";

		if ( database.execute( parserCommand ) == 1 ) {
			cout << "Sport successfully added to the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Sport was not added to the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::addTeam( ) {
	// InsertInto
	// name
	// id
	for ( ;; ) {
		string parserCommand = "INSERT INTO teams VALUES FROM";

		cout << "Please enter the name of the team.\n";
		string name;
		cin >> name;

		parserCommand += " (\"" + name + "\", ";

		cout << "Please enter the ID of the team.\n";
		int teamID;
		cin >> teamID;

		parserCommand += "\"" + to_string( teamID ) + "\");";

		if ( database.execute( parserCommand ) == 1 ) {
			cout << "Team successfully added to the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Team was not added to the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
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
	// write files
	database.execute( "WRITE games;" );
	database.execute( "WRITE players;" );
	database.execute( "WRITE referees;" );
	database.execute( "WRITE sports;" );
	database.execute( "WRITE teams;" );

	// close file
	database.execute( "CLOSE games;" );
	database.execute( "CLOSE players;" );
	database.execute( "CLOSE referees;" );
	database.execute( "CLOSE sports;" );
	database.execute( "CLOSE teams;" );
	
	// exit
	database.execute( "EXIT;" );

	cout << "Thank you for using the Sports League management program.\n";
	cout << "Have a nice day.\n";

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
	cout << "Sports League Manager Menu:\n";
	cout << "Enter '1' to add to a relation.\n";
	cout << "Enter '2' to remove from a relation.\n";
	cout << "Enter '3' to show information from a relation.\n";
	cout << "Enter '4' to display the games associated with a specific sport.\n";
	cout << "Enter '5' to display the sports that a player plays.\n";
	cout << "Enter '6' to display games in which a team could participate.\n";
	cout << "Enter '7' to change the location of a game.\n";
	cout << "Enter '8' to change the time of a game.\n";
	cout << "Enter '9' to change a sport's season.\n";
	cout << "Enter '10' to exit.\n";
}


void SportsLeague::removeGame( ) {
	// delete
}


void SportsLeague::removeMenu( ) {
	int userChoice;
	for ( ;; ) {
		cout << "Enter '1' to remove from the game relation.\n";
		cout << "Enter '2' to remove from the player relation.\n";
		cout << "Enter '3' to remove from referee relation.\n";
		cout << "Enter '4' to remove from the sports relation.\n";
		cout << "Enter '5' to remove from the team relation.\n";
		cin >> userChoice;
		switch ( userChoice ) {
		case '1':
			removeGame( );
			break;
		case '2':
			removePlayer( );
			break;
		case '3':
			removeReferee( );
			break;
		case '4':
			removeSport( );
			break;
		case '5':
			removeTeam( );
			break;
		default:
			"Invalid choice. Please try again.\n";
		}
	}
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
	cout << "The input you entered was invalid.\n";
	cout << "Would you like to try again?\n";

	string answer;

	for ( ;; ) {
		
		cout << "Please enter 'y' to try again or 'n' to return to the main menu.\n";

		cin >> answer;

		if ( answer == "y" ) {
			return true;
		}
		else if ( answer == "n" ) {
			return false;
		}
		cout << "Invalid choice.\n";
	}

}


void SportsLeague::run( ) {
	cout << "Welcome to the Sports League managing program.\n";

	int userChoice;
	for ( ;; ) {

		printMenu( );

		cin >> userChoice;

		// change to numbers
		switch ( userChoice ) {
		// adds
		case 1:
			addMenu( );
			break;

		// removes
		case 2:
			removeMenu( );
			break;

		// shows
		case 3:
			showMenu( );
			break;

		// display sports games
		case 4:
			displaySportsGames( );
			break;

		// display sports played
		case 5:
			displaySportsPlayed( );
			break;

		case 6:
			gamesWhenTeamCouldPlay( );
			break;

		case 7:
			changeGameLocation( );
			break;

		case 8:
			changeGameTime( );
			break;

		case 9:
			changeSportSeason( );
			break;
	
		// exit
		case 10:
			exit( );
			return;
			break;

			//etc
		default:
			cout << "Invalid choice, please try again.\n";
		}
	}


	/*
		Functions not called in root menu or obviously called in other functions:
		void getAllReferees( );

		void getNonReferees( );

		void listNamesOfSports( );

		void listPlayersOnTeam( );
	*/


}


void SportsLeague::showGames( ) {
	string command = "SHOW games;";
	if ( database.execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


void SportsLeague::showMenu( ) {
	int userChoice;
	for ( ;; ) {
		cout << "Enter '1' to show the game relation.\n";
		cout << "Enter '2' to show the player relation.\n";
		cout << "Enter '3' to show the referee relation.\n";
		cout << "Enter '4' to show the sports relation.\n";
		cout << "Enter '5' to show the team relation.\n";
		cin >> userChoice;
		switch ( userChoice ) {
		case '1':
			showGames( );
			break;
		case '2':
			showPlayers( );
			break;
		case '3':
			showReferees( );
			break;
		case '4':
			showSports( );
			break;
		case '5':
			showTeams( );
			break;
		default:
			"Invalid choice. Please try again.\n";
		}
	}
}


void SportsLeague::showPlayers( ) {
	string command = "SHOW players;";
	if ( database.execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


void SportsLeague::showReferees( ) {
	string command = "SHOW referees;";
	if ( database.execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


void SportsLeague::showSports( ) {
	string command = "SHOW sports;";
	if ( database.execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


void SportsLeague::showTeams( ) {
	string command = "SHOW games;";
	if ( database.execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}
