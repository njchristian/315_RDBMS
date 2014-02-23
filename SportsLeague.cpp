#include "SportsLeague.h"

// need to add the stuff so that the strings returned by the parser are stored in a vector<string>
// or whatever the instructions talk about

// possible add an isRef int to players - might need to rethink the getAllRefs and getNonRefs...seems like one of them needs to change
// waiting on that decision before altering the players relation

// the games relation should hold a sportID, not a sport name so this has been changed

SportsLeague::SportsLeague( ) {
	// open files
	// create the 5 relations

	database = new DBCell( results );

	// somehow check if files exist bc if they don't then the relations need to be created
	if( ifstream( "games.db" ) ) {
		//file exists
		database->execute( "OPEN games;" );
	}
	else {
		database->execute( "OPEN games;" );
		database->execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sportID INTEGER, gameID INTEGER ) PRIMARY KEY (gameID);" );
	}

	if( ifstream( "players.db" ) ) {
		//file exists
		database->execute( "OPEN players;" );
	}
	else {
		database->execute( "OPEN players;" );
		database->execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
	}

	if( ifstream( "referees.db" ) ) {
		//file exists
		database->execute( "OPEN referees;" );
	}
	else {
		database->execute( "OPEN referees;" );
		database->execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
	}

	if( ifstream( "sports.db" ) ) {
		//file exists
		database->execute( "OPEN sports;" );
	}
	else {
		database->execute( "OPEN sports;" );
		database->execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);");
	}

	if( ifstream( "teams.db" ) ) {
		//file exists
		database->execute( "OPEN teams;" );
	}
	else {
		database->execute( "OPEN teams;" );
		database->execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);" );
	}

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
		//how to check a correct date
		parserCommand += "\"" + date + "\", ";

		cout << "Please enter the time of the game.\n";
		string time;
		cin >> time;
		//how to check a correct time
		parserCommand += "\"" + time + "\", ";

		cout << "Please enter the game's associated sport ID.\n";
		int sportID;
		cin >> sportID;

		parserCommand += "\"" + to_string( sportID ) + "\", ";

		cout << "Please enter the game's ID.\n";
		int gameID;
		cin >> gameID;

		parserCommand += "\"" + to_string( gameID ) + "\");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Game successfully added to the database->\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Game was not added to the database->\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::addMenu( ) {
	int userChoice;
	bool backToMenu = false;
	while ( backToMenu == false ) {
		cout << "Add Menu:\n";
		cout << "Enter '1' to add to the game relation.\n";
		cout << "Enter '2' to add to the player relation.\n";
		cout << "Enter '3' to add to the referee relation.\n";
		cout << "Enter '4' to add to the sports relation.\n";
		cout << "Enter '5' to add to the team relation.\n";
		cout << "Enter '6' to go back to main menu.\n";
		cin >> userChoice;
		switch ( userChoice ) {
		case 1:
			addGame( );
			backToMenu = true;
			break;
		case 2:
			addPlayer( );
			backToMenu = true;
			break;
		case 3:
			addReferee( );
			backToMenu = true;
			break;
		case 4:
			addSport( );
			backToMenu = true;
			break;
		case 5:
			addTeam( );
			backToMenu = true;
			break;
		case 6:
			backToMenu = true;
			break;
		default:
			cin.clear();
			cin.sync();
			"Invalid choice. Please try again.\n";
			break;
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
		int netID;
		cin >> netID;

		parserCommand += "\"" + to_string( netID ) + "\", ";

		cout << "Please enter the sport ID that the player plays.\n";
		int sportID; 
		cin >> sportID;

		parserCommand += "\"" + to_string( sportID ) + "\");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Player successfully added to the database->\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Player was not added to the database->\n\n";
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
	// netID
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

		cout << "Please enter the Net-ID of the referee.\n";
		int netID;
		cin >> netID;

		parserCommand += to_string( netID ) + ", ";


		cout << "Please enter the sport ID that the referee refs.\n";
		int sportID; 
		cin >> sportID;

		parserCommand += "\"" + to_string( sportID ) + "\");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Referee successfully added to the database->\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Referee was not added to the database->\n\n";
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

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Sport successfully added to the database->\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Sport was not added to the database->\n\n";
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

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Team successfully added to the database->\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Team was not added to the database->\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::changeGameLocation( ) {
	// update
	//find game
	//find location 
	//change location

	for ( ;; ) {
		string parserCommand = "UPDATE games SET location = ";

		cout << "Please enter in the gameID \n";
		int gameID;
		cin >> gameID;

		cout<< "Please enter the game's new location\n";
		string newLocation;
		cin >> newLocation;

		parserCommand += "\"" + newLocation + "\" WHERE (gameID == " + to_string( gameID ) + ");";


		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Changed game's location successfully.\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - location was not changed.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}

void SportsLeague::changeGameTime( ) {
	// update
	//find game
	//find time 
	//change time

	for ( ;; ) {
		string parserCommand = "UPDATE games SET time = ";

		cout << "Please enter in the gameID \n";
		int gameID;
		cin >> gameID;

		cout<< "Please enter the game's new time\n";
		string newTime;
		cin >> newTime;

		parserCommand += "\"" + newTime + "\" WHERE (gameID == " + to_string( gameID ) + ");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Changed game's time successfully.\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - time was not changed.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}

void SportsLeague::changeSportSeason( ) {
	// update
	//find sport
	//find season
	//change season
	for ( ;; ) {

		string parserCommand = "UPDATE sports SET season = ";

		cout << "Please enter in the sportID \n";
		int sportID;
		cin >> sportID;

		cout<< "Please enter the sport's new season\n";
		string newSeason;
		cin >> newSeason;

		parserCommand += "\"" + newSeason + "\" WHERE (sportID == " + to_string( sportID ) + ");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Changed sport's season successfully.\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - season was not changed.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}

void SportsLeague::displaySportsGames( ) {
	// select
	//find the sport
	//find all of the games
	//print that relation

	for ( ;; ) {
	 	string parserCommand = "DROP TABLE newView;"; //if newView exists delete it
		database->execute( parserCommand );

		parserCommand = "newView <- select";

		cout << "Please enter in the sports ID number \n";
		string sport;
		cin >> sport;

		parserCommand += " (sportID == " + sport + ") games;";

		if ( database->execute( parserCommand ) == 1 ) {
			parserCommand = "SHOW newView;";
			database->execute( parserCommand );
			return;
		}
		else {
			cout << "Invalid data entered - can not display that sport's games.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::displaySportsPlayed( ) {
	//find the player
	//find the sports
	//print relation
	for ( ;; ) {
		string parserCommand = "DROP TABLE playerPlays;"; //if playerPlays exists delete it
		database->execute( parserCommand );
		parserCommand = "playerPlays <- select";

		cout << "Please enter the player's netID \n";
		int netID;
		cin >> netID;

		parserCommand += " (netID == " + to_string(netID) +") players;";

		if ( database->execute( parserCommand ) == 1 ) {
			parserCommand = "SHOW playerPlays;";
			database->execute( parserCommand );
			return;
		}
		else {
			cout << "Invalid data entered - can not display the player's sports.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::exit( ) {
	// write files
	database->execute( "WRITE games;" );
	database->execute( "WRITE players;" );
	database->execute( "WRITE referees;" );
	database->execute( "WRITE sports;" );
	database->execute( "WRITE teams;" );

	// close file
	database->execute( "CLOSE games;" );
	database->execute( "CLOSE players;" );
	database->execute( "CLOSE referees;" );
	database->execute( "CLOSE sports;" );
	database->execute( "CLOSE teams;" );
	
	// exit
	database->execute( "EXIT;" );

	cout << "Thank you for using the Sports League management program.\n";
	cout << "Have a nice day.\n";

}


void SportsLeague::getAllReferees( ) {
	// union

	// delete the playerRefs relation
	string parserCommand = "DROP TABLE playerRefs;";
	database->execute( parserCommand );

	// delete the allRefs relation
	parserCommand = "DROP TABLE allRefs;";
	database->execute( parserCommand );

	// get the player refs in a relation that is union compatible with refs
	parserCommand = "playerRefs <- project (firstName, lastName, netID, sportID) (select (isRef == 1) players);";
	database->execute( parserCommand );

	// get the union of player refs and non player refs
	parserCommand = "allRefs <- playerRefs + referees;";
	database->execute( parserCommand );

	// display allRefs
	parserCommand = "SHOW allRefs;";
	database->execute( parserCommand );
}


void SportsLeague::getNonReferees( ) {
	// difference

	// delete the temporary relation
	string parserCommand = "DROP TABLE nonRefPlayers;";
	database->execute( parserCommand );

	// get the non ref players
	parserCommand = "nonRefPlayers <- (project (firstName, lastName, netID, sportID) players) - referees;";
	database->execute( parserCommand );

	// display the non ref players
	parserCommand = "SHOW nonRefPlayers;";
	database->execute( parserCommand );

	
}


void SportsLeague::gamesWhenTeamCouldPlay( ) {
	// cross product

	// remove the temporary list
	string parserCommand = "DROP TABLE gamesTeamsPlay;";
	database->execute( parserCommand );

	// get the list of games and teams
	parserCommand = "gamesTeamsPlay <- teams * games;";
	database->execute( parserCommand );

	// show the list
	parserCommand = "SHOW gamesTeamsPlay;";
	database->execute( parserCommand );

}


void SportsLeague::listNamesOfSports( ) {
	// project
	for ( ;; ) {
		string parserCommand = "DROP TABLE sportNames;"; //if sportNames exists delete it
		database->execute( parserCommand );

		parserCommand = "sportNames <- project (name) sports;";

		if ( database->execute( parserCommand ) == 1 ) {
			parserCommand = "SHOW sportNames;";
			database->execute( parserCommand );
			return;
		}
		else {
			cout << "Invalid data entered - can not display the list of sports.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}

}


void SportsLeague::listPlayersOnTeam( ) {
	// select based on team ID
	for ( ;; ) {
		cout << "Please enter a team ID to display the players on that team.\n";
		int teamID;
		cin >> teamID;

		string parserCommand = "DROP TABLE playersOnTeam;"; //if playersOnTeam exists delete it
		database->execute( parserCommand );

		parserCommand = "playersOnTeam <- select (teamID == ";

		parserCommand += to_string( teamID );
		parserCommand += ") teams;";

		if ( database->execute( parserCommand ) == 1 ) {
			parserCommand = "SHOW playersOnTeam;";
			database->execute( parserCommand );
			return;
		}
		else {
			cout << "Invalid data entered - can not display the list of players on the team.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::printMenu( ) {
	cout << "Main Menu:\n";
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
	// delete game based on its name
	for ( ;; ) {
		string parserCommand = "DELETE FROM games WHERE (gameID == ";

		int gameID;
		cout << "Please enter the game ID you would like to remove.\n";
		cin >> gameID;

		parserCommand += to_string( gameID );
		parserCommand += ");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Game successfully removed from the database->\n";
			return;
		}
		else {
			cout << "Invalid data entered - Game was not removed from the database->\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::removeMenu( ) {
	int userChoice;
	bool backToMenu = false;
	while ( backToMenu == false ) {
		cout << "Remove Menu:\n";
		cout << "Enter '1' to remove from the game relation.\n";
		cout << "Enter '2' to remove from the player relation.\n";
		cout << "Enter '3' to remove from referee relation.\n";
		cout << "Enter '4' to remove from the sports relation.\n";
		cout << "Enter '5' to remove from the team relation.\n";
		cout << "Enter '6' to go back to main menu.\n";
		cin >> userChoice;
		switch ( userChoice ) {
		case 1:
			removeGame( );
			backToMenu = true;
			break;
		case 2:
			removePlayer( );
			backToMenu = true;
			break;
		case 3:
			removeReferee( );
			backToMenu = true;
			break;
		case 4:
			removeSport( );
			backToMenu = true;
			break;
		case 5:
			removeTeam( );
			backToMenu = true;
			break;
		case 6:
			backToMenu = true;
			break;
		default:
			cin.clear();
			cin.sync();
			"Invalid choice. Please try again.\n";
			break;
		}
	}
}


void SportsLeague::removePlayer( ) {
	// delete player based on netID
	for ( ;; ) {
		string parserCommand = "DELETE FROM players WHERE (netID == ";

		// get the net ID
		int netID;
		cout << "Please enter the netID of the player you would like to remove.\n";
		cin >> netID;

		parserCommand += netID;
		parserCommand += ");";

		// pass the command to the parser; if it fails ask the user if they want
		// to retry
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Player successfully removed from the database->\n";
			return;
		}
		else {
			cout << "Invalid data entered - Player was not removed from the database->\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::removeReferee( ) {
	// delete referee based on netID

	for ( ;; ) {
		string parserCommand = "DELETE FROM referees WHERE (netID == ";

		// get the net ID
		int netID;
		cout << "Please enter the netID of the referee you would like to remove.\n";
		cin >> netID;

		parserCommand += netID;
		parserCommand += ");";

		// pass the command to the parser; if it fails ask the user if they want
		// to retry
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Referee successfully removed from the database->\n";
			return;
		}
		else {
			cout << "Invalid data entered - Referee was not removed from the database->\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::removeSport( ) {
	// delete sport based on sport ID

	for ( ;; ) {
		string parserCommand = "DELETE FROM sports WHERE (sportID == ";

		// get the sport ID
		int sportID;
		cout << "Please enter the ID of the sport you would like to remove.\n";
		cin >> sportID;

		parserCommand += sportID;
		parserCommand += ");";

		// pass the command to the parser; if it fails ask the user if they want
		// to retry
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Sport successfully removed from the database->\n";
			return;
		}
		else {
			cout << "Invalid data entered - Sport was not removed from the database->\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


void SportsLeague::removeTeam( ) {
	// delete based on team ID

	for ( ;; ) {
		string parserCommand = "DELETE FROM teams WHERE (teamID == ";

		// get the Team ID
		int teamID;
		cout << "Please enter the ID of the team you would like to remove.\n";
		cin >> teamID;

		parserCommand += teamID;
		parserCommand += ");";

		// pass the command to the parser; if it fails ask the user if they want
		// to retry
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Team successfully removed from the database->\n";
			return;
		}
		else {
			cout << "Invalid data entered - Team was not removed from the database->\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
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
		else {
			cout << "Invalid choice.\n";
			cin.clear( );
			cin.sync( );
		}
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
			//return;
			break;

		// removes
		case 2:
			removeMenu( );
			//return;
			break;

		// shows
		case 3:
			showMenu( );
			//return;
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
			cin.clear();
			cin.sync();
			"Invalid choice. Please try again.\n";
			break;
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
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


void SportsLeague::showMenu( ) {
	int userChoice;
	bool backToMenu = false;
	while ( backToMenu == false ) {
		cout << "Show Menu:\n";
		cout << "Enter '1' to show the game relation.\n";
		cout << "Enter '2' to show the player relation.\n";
		cout << "Enter '3' to show the referee relation.\n";
		cout << "Enter '4' to show referees and player referees.\n";
		cout << "Enter '5' to show only players who are not referees.\n";
		cout << "Enter '6' to show the sports relation.\n";
		cout << "Enter '7' to display just the names of the sports.\n";
		cout << "Enter '8' to show the team relation.\n";
		cout << "Enter '9' to list the players on a team.\n";
		cout << "Enter '10' to go back to main menu.\n";
		cin >> userChoice;
		switch ( userChoice ) {
		case 1:
			showGames( );
			backToMenu = true;
			break;
		case 2:
			showPlayers( );
			backToMenu = true;
			break;
		case 3:
			showReferees( );
			backToMenu = true;
			break;
		case 4:
			getAllReferees( );
			backToMenu = true;
			break;
		case 5:
			getNonReferees( );
			backToMenu = true;
			break;
		case 6:
			showSports( );
			backToMenu = true;
			break;
		case 7:
			listNamesOfSports( );
			backToMenu = true;
			break;
		case 8:
			showTeams( );
			backToMenu = true;
			break;
		case 9:
			listPlayersOnTeam( );
			backToMenu = true;
			break;
		case 10:
			backToMenu = true;
			break;
		default:
			cin.clear();
			cin.sync();
			"Invalid choice. Please try again.\n";
			break;
		}
	}
}


void SportsLeague::showPlayers( ) {
	string command = "SHOW players;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


void SportsLeague::showReferees( ) {
	string command = "SHOW referees;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


void SportsLeague::showSports( ) {
	string command = "SHOW sports;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


void SportsLeague::showTeams( ) {
	string command = "SHOW teams;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}
