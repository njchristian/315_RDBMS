#include "SportsLeague.h"


// Constructor
SportsLeague::SportsLeague( ) {

	database = new DBCell( results );

	// check if the files exist, if they do exist then open them; if they 
	// do not exist then create and open them
	if ( ifstream( "games.db" ) ) {
		//file exists
		database->execute( "OPEN games;" );
	}
	else {
		database->execute( "OPEN games;" );
		database->execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sportID INTEGER, gameID INTEGER ) PRIMARY KEY (gameID);" );
	}

	if ( ifstream( "players.db" ) ) {
		//file exists
		database->execute( "OPEN players;" );
	}
	else {
		database->execute( "OPEN players;" );
		database->execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, teamID INTEGER, sportID INTEGER, isRef INTEGER ) PRIMARY KEY (netID);" );
	}

	if ( ifstream( "referees.db" ) ) {
		//file exists
		database->execute( "OPEN referees;" );
	}
	else {
		database->execute( "OPEN referees;" );
		database->execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
	}


	//Our firstTime flag really wants to know if we have sports in the database, since the other operations
	//need sports
	if ( ifstream( "sports.db" ) ) {
		//file exists
		database->execute( "OPEN sports;" );
		firstTime = false;
	}
	else {
		database->execute( "OPEN sports;" );
		database->execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
		firstTime = true;
	}

	if ( ifstream( "teams.db" ) ) {
		//file exists
		database->execute( "OPEN teams;" );
	}
	else {
		database->execute( "OPEN teams;" );
		database->execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);" );
	}

	if ( ifstream( "winningTeams.db" ) ) {
		//file exists
		database->execute( "OPEN winningTeams;" );
	}
	else {
		database->execute( "OPEN winningTeams;" );
		database->execute( "CREATE TABLE winningTeams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);" );
	}
}


// Add a game to the games relation
void SportsLeague::addGame( ) {

	for ( ;; ) {

		string parserCommand = "INSERT INTO games VALUES FROM";

		// get the location
		cout << "Please enter the location of the new game.\n";
		string location = readString( );


		parserCommand += " (" + location + ", ";

		// get the date
		cout << "Please enter the date of the game.\n";
		string date = readString( );


		parserCommand += "" + date + ", ";

		// get the time
		cout << "Please enter the time of the game.\n";
		string time = readString( );


		parserCommand += "" + time + ", ";

		// get the sport ID
		cout << "Please enter the game's associated sport ID.\n";
		int sportID = readInt( );

		parserCommand += to_string( ( long long ) sportID ) + ", ";

		// get the game ID
		cout << "Please enter the game's ID.\n";
		int gameID = readInt( );

		parserCommand += to_string( ( long long ) gameID ) + ");";

		// Try to execute the command. If it is invalid, see if the user
		// wants to retry.
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Game successfully added to the database.\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Game was not added to the database.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// Menu for the add operations
void SportsLeague::addMenu( ) {
	int userChoice;
	bool backToMenu = false;

	while ( backToMenu == false ) {
		cout << "Add Menu:\n";
		cout << "Enter '1' to add to the game relation.\n";
		cout << "Enter '2' to add to the player relation.\n";
		cout << "Enter '3' to add to the referee relation.\n";
		cout << "Enter '4' to add to the sports relation.\n";
		cout << "Enter '5' to add to the teams relation.\n";
		cout << "Enter '6' to add to the winning teams relation.\n";
		cout << "Enter '7' to go back to main menu.\n";
		inputPrompt( );

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
			addWinningTeam( );
			backToMenu = true;
			break;
		case 7:
			backToMenu = true;
			break;
		default:
			cin.ignore( 1024, '\n' );
			cin.clear( );
			cin.sync( );
			cout << "Invalid choice. Please try again.\n";
			break;
		}
	}
}


// Add a player to the players relation
void SportsLeague::addPlayer( ) {

	bool validInput = false;

	for ( ;; ) {
		validInput = false;
		string parserCommand = "INSERT INTO players VALUES FROM";

		// get the first name
		cout << "Please enter the first name of the player.\n";
		string firstName = readString( );

		parserCommand += " (" + firstName + ", ";

		// get the last name
		cout << "Please enter the last name of the player.\n";
		string lastName = readString( );

		parserCommand += "" + lastName + ", ";

		// get the net ID
		cout << "Please enter the Net-ID of the player.\n";
		int netID = readInt( );

		parserCommand += to_string( ( long long ) netID ) + ", ";

		// get the team ID
		cout << "Please enter the Team ID of the player.\n";
		int teamID = readInt( );

		parserCommand += to_string( ( long long ) teamID ) + ", ";

		// get the sport ID
		cout << "Please enter the sport ID that the player plays.\n";
		int sportID = readInt( );

		parserCommand += to_string( ( long long ) sportID ) + ", ";

		// get isRef
		cout << "Please enter '1' if the player is a referee also, or '0' if the player is not.\n";
		int isRef;
		while ( !validInput ) {
			inputPrompt( );
			cin >> isRef;
			if ( !cin.fail( ) && ( isRef == 0 || isRef == 1 ) ) {
				validInput = true;
			}
			else {
				cin.ignore( 1024, '\n' );
				cin.clear( );
				cin.sync( );
				cout << "Invalid input, please try again. The input must be '1' or '0'.\n";
			}
		}

		parserCommand += to_string( ( long long ) isRef ) + ");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Player successfully added to the database.\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Player was not added to the database.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// add a full-time referee to the referees relation
void SportsLeague::addReferee( ) {

	for ( ;; ) {

		string parserCommand = "INSERT INTO referees VALUES FROM";

		// get the first name
		cout << "Please enter the first name of the referee.\n";
		string firstName = readString( );

		parserCommand += " (" + firstName + ", ";

		// get the last name
		cout << "Please enter the last name of the referee.\n";
		string lastName = readString( );

		parserCommand += "" + lastName + ", ";

		// get the net ID
		cout << "Please enter the Net-ID of the referee.\n";
		int netID = readInt( );

		parserCommand += to_string( ( long long ) netID ) + ", ";

		// get the sport ID
		cout << "Please enter the sport ID that the referee refs.\n";
		int sportID = readInt( );

		parserCommand += to_string( ( long long ) sportID ) + ");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Referee successfully added to the database.\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Referee was not added to the database.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// add a sport to the sports relation
void SportsLeague::addSport( ) {

	for ( ;; ) {

		string parserCommand = "INSERT INTO sports VALUES FROM";

		// get the sport name
		cout << "Please enter the name of the sport.\n";
		string name = readString( );

		parserCommand += " (" + name + ", ";

		// get the sport ID
		cout << "Please enter the ID of the sport.\n";
		int sportID = readInt( );

		parserCommand += to_string( ( long long ) sportID ) + ", ";

		// get the sport's season
		cout << "Please enter the season associated with the sport.\n";
		string season = readString( );

		parserCommand += "" + season + ");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Sport successfully added to the database.\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Sport was not added to the database.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}

// add a team to the teams relation
void SportsLeague::addTeam( ) {

	for ( ;; ) {

		string parserCommand = "INSERT INTO teams VALUES FROM";

		// get the team name
		cout << "Please enter the name of the team.\n";
		string name = readString( );

		parserCommand += " (" + name + ", ";

		// get the team ID
		cout << "Please enter the ID of the team.\n";
		int teamID = readInt( );

		parserCommand += to_string( ( long long ) teamID ) + ");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Team successfully added to the database.\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Team was not added to the database.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// add a team to the winning teams relation
void SportsLeague::addWinningTeam( ) {

	for ( ;; ) {

		string parserCommand = "INSERT INTO winningTeams VALUES FROM";

		// get the team's name
		cout << "Please enter the name of the winning team.\n";
		string name = readString( );

		parserCommand += " (" + name + ", ";

		// get the team ID
		cout << "Please enter the ID of the winning team.\n";
		int teamID = readInt( );

		parserCommand += to_string( teamID ) + ");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Winning team successfully added to the database.\n\n";
			return;
		}
		else {
			cout << "Invalid data entered - Winning team was not added to the database.\n\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// Change the location of a game
void SportsLeague::changeGameLocation( ) {

	for ( ;; ) {

		string parserCommand = "UPDATE games SET location = ";

		// get the game ID
		cout << "Please enter in the gameID \n";
		int gameID = readInt( );

		// get the new location
		cout << "Please enter the game's new location\n";
		string newLocation = readString( );

		parserCommand += newLocation + " WHERE (gameID == " + to_string( ( long long ) gameID ) + ");";

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


// change the time of a game
void SportsLeague::changeGameTime( ) {

	for ( ;; ) {

		string parserCommand = "UPDATE games SET time = ";

		// get the game ID
		cout << "Please enter in the gameID \n";
		int gameID = readInt( );

		// get the new time for the game
		cout << "Please enter the game's new time\n";
		string newTime = readString( );

		parserCommand += newTime + " WHERE (gameID == " + to_string( ( long long ) gameID ) + ");";

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


// change the season of a sport
void SportsLeague::changeSportSeason( ) {

	for ( ;; ) {

		string parserCommand = "UPDATE sports SET season = ";

		// get the sport ID
		cout << "Please enter in the sportID \n";
		int sportID = readInt( );

		// get the new season
		cout << "Please enter the sport's new season\n";
		string newSeason = readString( );

		parserCommand += newSeason + " WHERE (sportID == " + to_string( ( long long ) sportID ) + ");";

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


// display the games associated with a specific sport
void SportsLeague::displaySportsGames( ) {

	for ( ;; ) {

		string parserCommand = "DROP TABLE sportsGames;"; //if sportsGames exists delete it
		database->execute( parserCommand );

		parserCommand = "sportsGames <- select";

		// get the sport ID
		cout << "Please enter in the sports ID number \n";
		int sportID = readInt( );

		parserCommand += " (sportID == " + to_string( ( long long ) sportID ) + ") games;";

		if ( database->execute( parserCommand ) == 1 ) {
			parserCommand = "SHOW sportsGames;";
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


// display the sports a player plays
void SportsLeague::displaySportsPlayed( ) {

	for ( ;; ) {

		string parserCommand = "DROP TABLE playerPlays;"; //if playerPlays exists delete it
		database->execute( parserCommand );

		parserCommand = "playerPlays <- select";

		// get the player's netID
		cout << "Please enter the player's netID \n";
		int netID = readInt( );

		parserCommand += " (netID == " + to_string( ( long long ) netID ) + ") players;";

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


// first time printing
void SportsLeague::firstTimeMess( ) {

	cout << "\nWe see that this is your first time using this application.\n"
		<< "We will first direct you to add your first Sport!\n\n"
		<< "Enter '1' to Continue to Application\n"
		<< "Enter '2' for Further Instructions/Description\n";

	bool repeat = false;

	do {

		int userChoice;
		inputPrompt( );
		cin >> userChoice;

		switch ( userChoice ) {

		case 1:
			addSport( );
			break;
		case 2:
			instructions( );
			cout << "Below, you will see a prompt for creating your first sport.\n"
				<< "Just follow the instructions, and enjoy!\n\n";
			addSport( );
			break;
		default:
			repeat = true;
			cout << "Invalid choice. Please try again.\n";
		}

	} while ( repeat );

}


// Write files, close files and then exit
void SportsLeague::exit( ) {

	save( );

	exitWithoutSave( );

}


// close files and then exit
void SportsLeague::exitWithoutSave( ) {
	
	// close file
	database->execute( "CLOSE games;" );
	database->execute( "CLOSE players;" );
	database->execute( "CLOSE referees;" );
	database->execute( "CLOSE sports;" );
	database->execute( "CLOSE teams;" );
	database->execute( "CLOSE winningTeams;" );
	
	// exit
	database->execute( "EXIT;" );

	cout << "Thank you for using the Sports League management program.\n";
	cout << "Have a nice day.\n";

}


// Get the full-time referees and the player-refs
void SportsLeague::getAllReferees( ) {
	// union playerRefs with referees

	// delete the playerRefs relation
	string parserCommand = "DROP TABLE playerRefs;";
	database->execute( parserCommand );

	// delete the allRefs relation
	parserCommand = "DROP TABLE allRefs;";
	database->execute( parserCommand );

	// get the player refs in a relation that is union compatible with refs
	parserCommand = "playerRefs <- project (firstname, lastname, netID, sportID) (select (isRef == 1) players);";
	database->execute( parserCommand );

	// get the union of player refs and non player refs
	parserCommand = "allRefs <- playerRefs + referees;";
	database->execute( parserCommand );

	// display allRefs
	parserCommand = "SHOW allRefs;";
	database->execute( parserCommand );
}


// get the losing teams
void SportsLeague::getLosingTeams( ) {
	// difference

	// delete the temporary relation
	string parserCommand = "DROP TABLE losingTeams;";
	database->execute( parserCommand );

	// get the losing teams
	parserCommand = "losingTeams <- teams - winningTeams;";
	database->execute( parserCommand );

	// display the losing teams
	parserCommand = "SHOW losingTeams;";
	database->execute( parserCommand );

}


// get the players who are not player-refs
void SportsLeague::getNonReferees( ) {

	// delete the temporary relation
	string parserCommand = "DROP TABLE nonRefPlayers;";
	database->execute( parserCommand );

	// get the non ref players
	parserCommand = "nonRefPlayers <- (select (isRef == 0) players);";
	database->execute( parserCommand );

	// display the non ref players
	parserCommand = "SHOW nonRefPlayers;";
	database->execute( parserCommand );

}


// get the games when a team could play using cross product
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


// displays the input prompt
void SportsLeague::inputPrompt( ) {
	cout << ">: ";
}


// prints the instructions
void SportsLeague::instructions( ) {

	cout << "\tThis application will allow you to keep track of everything you \n"
		<< "need for running an efficient intramural league.\n\n"
		<< "\tThe first thing you will need to do is start identifying sports that\n"
		<< "you are interested in managing in your league. Everything else (games,\n"
		<< "players etc.) will be connected to a sport. Furthermore, we will prompt for a\n"
		<< "a unique ID number to each entry you make. These must be unique within their \n"
		<< "context, so for example you may have a sport with an ID of '1', and a game with\n"
		<< "that same ID of '1', but could not have another sport with that ID number.\n\n"
		<< "\tWe leave the formatting of your entries up to you for the most part.\n"
		<< "For example, you may choose your preferred way of storing information \n"
		<< "such as dates times, and seasons.\n"
		<< "Besides sports, you may store players, referees, teams, and games in\n"
		<< "this database.\n"
		<< "\tWe truly hope it meets all of your intramural needs.\n\n";

}


// list the names of the sports
void SportsLeague::listNamesOfSports( ) {
	// project
	string parserCommand = "DROP TABLE sportNames;"; //if sportNames exists delete it
	database->execute( parserCommand );

	parserCommand = "sportNames <- project (name) sports;";
	database->execute( parserCommand );

	parserCommand = "SHOW sportNames;";
	database->execute( parserCommand );

}


// list the players on a team
void SportsLeague::listPlayersOnTeam( ) {

	for ( ;; ) {

		// get the team ID
		cout << "Please enter a team ID to display the players on that team.\n";
		int teamID = readInt( );

		string parserCommand = "DROP TABLE playersOnTeam;"; //if playersOnTeam exists delete it
		database->execute( parserCommand );

		parserCommand = "playersOnTeam <- select (teamID == ";

		parserCommand += to_string( ( long long ) teamID );
		parserCommand += ") players;";

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


void SportsLeague::listPlayersWithTeamName( ) {

	string parserCommand = "DROP TABLE playersTeamNames;";
	if ( database->execute( parserCommand ) < 0 ) {
		cout << "invalid parser command\n";
	}

	parserCommand = "playersTeamNames <- players JOIN teams;";
	if ( database->execute( parserCommand ) < 0 ) {
		cout << "invalid parser command\n";
	}

	parserCommand = "SHOW playersTeamNames;";
	if ( database->execute( parserCommand ) < 0 ) {
		cout << "invalid parser command\n";
	}
}


// Function to print the main menu
void SportsLeague::printMenu( ) {
	cout << "\nMain Menu:\n";
	cout << "Enter '1' to add to a relation.\n";
	cout << "Enter '2' to remove from a relation.\n";
	cout << "Enter '3' to show information from a relation.\n";
	cout << "Enter '4' to display the games associated with a specific sport.\n";
	cout << "Enter '5' to display the sport that a player plays.\n";
	cout << "Enter '6' to display games in which a team could participate.\n";
	cout << "Enter '7' to change the location of a game.\n";
	cout << "Enter '8' to change the time of a game.\n";
	cout << "Enter '9' to change a sport's season.\n";
	cout << "Enter '10' to display instructions.\n";
	cout << "Enter '11' to save\n";
	cout << "Enter '12' to save and exit.\n";
	cout << "Enter '13' to exit without saving.\n";
}


// Function for reading integer inputs from the user
int SportsLeague::readInt( ) {
	int input;
	bool validInput = false;

	while ( !validInput ) {
		inputPrompt( );
		cin >> input;

		// check for failure
		if ( !cin.fail( ) ) {
			validInput = true;
		}
		else {
			cin.ignore( 1024, '\n' );
			cin.clear( );
			cin.sync( );
			cout << "Invalid input, please try again.\n";
		}
	}

	return input;
}


// Function for reading multi-word string inputs from the user.
string SportsLeague::readString( ) {
	string input;
	bool validInput = false;

	cin.clear( );
	cin.sync( );

	// read in a line of input until it is a correctly formatted string 
	// enclosed by quotes
	while ( !validInput ) {
		inputPrompt( );
		getline( cin, input );

		if ( !cin.fail( ) ) {
			validInput = true;
		}
		else {
			cin.clear( );
			cin.sync( );
			cout << "Invalid input. Please try again.\n";
		}
	}

	// add quotes for the parser
	input = "\"" + input + "\"";

	return input;
}


// remove a game based on its game ID
void SportsLeague::removeGame( ) {

	for ( ;; ) {

		string parserCommand = "DELETE FROM games WHERE (gameID == ";

		// get the game ID
		cout << "Please enter the game ID you would like to remove.\n";
		int gameID = readInt( );

		parserCommand += to_string( ( long long ) gameID );
		parserCommand += ");";

		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Game successfully removed from the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Game was not removed from the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// menu for remove options
void SportsLeague::removeMenu( ) {
	int userChoice;
	bool backToMenu = false;
	while ( backToMenu == false ) {
		cout << "Remove Menu:\n";
		cout << "Enter '1' to remove from the game relation.\n";
		cout << "Enter '2' to remove from the player relation.\n";
		cout << "Enter '3' to remove from referee relation.\n";
		cout << "Enter '4' to remove from the sports relation.\n";
		cout << "Enter '5' to remove from the teams relation.\n";
		cout << "Enter '6' to remove from the winning teams relation.\n";
		cout << "Enter '7' to go back to main menu.\n";
		inputPrompt( );

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
			removeWinningTeam( );
			backToMenu = true;
			break;
		case 7:
			backToMenu = true;
			break;
		default:
			cin.ignore( 1024, '\n' );
			cin.clear( );
			cin.sync( );
			cout << "Invalid choice. Please try again.\n";
			break;
		}
	}
}


// remove player based on netID
void SportsLeague::removePlayer( ) {

	for ( ;; ) {

		string parserCommand = "DELETE FROM players WHERE (netID == ";

		// get the net ID
		cout << "Please enter the netID of the player you would like to remove.\n";
		int netID = readInt( );

		parserCommand += to_string( ( long long ) netID );
		parserCommand += ");";

		// pass the command to the parser; if it fails ask the user if they want
		// to retry
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Player successfully removed from the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Player was not removed from the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// remove a referee based on netID
void SportsLeague::removeReferee( ) {

	for ( ;; ) {

		string parserCommand = "DELETE FROM referees WHERE (netID == ";

		// get the net ID
		cout << "Please enter the netID of the referee you would like to remove.\n";
		int netID = readInt( );

		parserCommand += to_string( ( long long ) netID );
		parserCommand += ");";

		// pass the command to the parser; if it fails ask the user if they want
		// to retry
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Referee successfully removed from the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Referee was not removed from the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// remove a sport based on sport ID
void SportsLeague::removeSport( ) {

	for ( ;; ) {

		string parserCommand = "DELETE FROM sports WHERE (sportID == ";

		// get the sport ID
		cout << "Please enter the ID of the sport you would like to remove.\n";
		int sportID = readInt( );

		parserCommand += to_string( ( long long ) sportID );
		parserCommand += ");";

		// pass the command to the parser; if it fails ask the user if they want
		// to retry
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Sport successfully removed from the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Sport was not removed from the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// remove a team based on team ID
void SportsLeague::removeTeam( ) {

	for ( ;; ) {

		string parserCommand = "DELETE FROM teams WHERE (teamID == ";

		// get the Team ID
		cout << "Please enter the ID of the team you would like to remove.\n";
		int teamID = readInt( );

		parserCommand += to_string( ( long long ) teamID );
		parserCommand += ");";

		// pass the command to the parser; if it fails ask the user if they want
		// to retry
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Team successfully removed from the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Team was not removed from the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// remove a winning team based on team ID
void SportsLeague::removeWinningTeam( ) {

	for ( ;; ) {

		string parserCommand = "DELETE FROM winningTeams WHERE (teamID == ";

		// get the Team ID
		cout << "Please enter the ID of the winning team you would like to remove.\n";
		int teamID = readInt( );

		parserCommand += to_string( teamID );
		parserCommand += ");";

		// pass the command to the parser; if it fails ask the user if they want
		// to retry
		if ( database->execute( parserCommand ) == 1 ) {
			cout << "Winning team successfully removed from the database.\n";
			return;
		}
		else {
			cout << "Invalid data entered - Winning team was not removed from the database.\n";
			if ( retry( ) == false ) {
				return;
			}
		}
	}
}


// If a parser command fails then this is called which asks
// the user if they want to retry by using new input or not.
bool SportsLeague::retry( ) {
	cout << "The input you entered was invalid.\n";
	cout << "Would you like to try again?\n";

	string answer;

	for ( ;; ) {

		cout << "Please enter 'y' to try again or 'n' to return to the main menu.\n";
		inputPrompt( );
		cin >> answer;

		if ( answer == "y" ) {
			return true;
		}
		else if ( answer == "n" ) {
			return false;
		}
		else {
			cout << "Invalid choice.\n";
			cin.ignore( 1024, '\n' );
			cin.clear( );
			cin.sync( );
		}
	}

}


// function that runs the program and contains the main menu
void SportsLeague::run( ) {


	if ( firstTime ) {
		cout << "Welcome to the Sports League managing program.\n";
		firstTimeMess( );
	}
	else {
		cout << "Welcome back to the Sports League managing program.\n";
	}

	int userChoice;
	for ( ;; ) {

		printMenu( );

		inputPrompt( );
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
			instructions( );
			break;

		case 11:
			save( );
			break;

		case 12:
			exit( );
			return;
			break;

		case 13:
			exitWithoutSave( );
			return;
			break;

		default:
			cin.ignore( 1024, '\n' );
			cin.clear( );
			cin.sync( );

			cout << "Invalid choice. Please try again.\n";
			break;
		}
	}
}


// Write the relations to their files
void SportsLeague::save( ) {

	// write files
	database->execute( "WRITE games;" );
	database->execute( "WRITE players;" );
	database->execute( "WRITE referees;" );
	database->execute( "WRITE sports;" );
	database->execute( "WRITE teams;" );
	database->execute( "WRITE winningTeams;" );

	cout << "Files saved!\n";

}


// display the games relation
void SportsLeague::showGames( ) {
	string command = "SHOW games;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


// menu for show operations
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
		cout << "Enter '8' to show the teams relation.\n";
		cout << "Enter '9' to list the players on a team.\n";
		cout << "Enter '10' to show the winning teams relation.\n";
		cout << "Enter '11' to show the losing teams.\n";
		cout << "Enter '12' to display the list of players with their team names.\n";
		cout << "Enter '13' to go back to main menu.\n";
		inputPrompt( );

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
			showWinningTeams( );
			backToMenu = true;
			break;
		case 11:
			getLosingTeams( );
			backToMenu = true;
			break;
		case 12:
			listPlayersWithTeamName( );
			backToMenu = true;
			break;
		case 13:
			backToMenu = true;
			break;
		default:
			cin.ignore( 1024, '\n' );
			cin.clear( );
			cin.sync( );
			cout << "Invalid choice. Please try again.\n";
			break;
		}
	}
}


// display the players relation
void SportsLeague::showPlayers( ) {
	string command = "SHOW players;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


// display the referees relation
void SportsLeague::showReferees( ) {
	string command = "SHOW referees;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


// display the sports relation
void SportsLeague::showSports( ) {
	string command = "SHOW sports;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


// display the teams relation
void SportsLeague::showTeams( ) {
	string command = "SHOW teams;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}


// display the winning teams relation
void SportsLeague::showWinningTeams( ) {
	string command = "SHOW winningTeams;";
	if ( database->execute( command ) < 0 ) {
		cout << "An error occurred.\n";
	}
}
