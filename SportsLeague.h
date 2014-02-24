#include "DBCell.h"

class SportsLeague {

	// Data members
	vector<vector<string>> results;

	DBCell* database;

	bool firstTime;

	// Private member functions

	void addGame( );

	void addMenu( );

	void addPlayer( );

	void addReferee( );

	void addSport( );

	void addTeam( );

	void addWinningTeam( );

	void changeGameLocation( );

	void changeGameTime( );

	void changeSportSeason( );

	void displaySportsGames( );

	void displaySportsPlayed( );

	void exit( );

	void exitWithoutSave( );

	void firstTimeMess( );

	void getAllReferees( );

	void getLosingTeams( );

	void getNonReferees( );

	void gamesWhenTeamCouldPlay( );

	void inputPrompt( );

	void instructions( );

	void listNamesOfSports( );

	void listPlayersOnTeam( );

	void listPlayersWithTeamName( );

	void printMenu( );

	int readInt( );

	string readString( );

	void removeGame( );

	void removeMenu( );

	void removePlayer( );

	void removeReferee( );

	void removeSport( );

	void removeTeam( );

	void removeWinningTeam( );

	bool retry( );

	void save( );

	void showGames( );

	void showMenu( );

	void showPlayers( );

	void showReferees( );

	void showSports( );

	void showTeams( );

	void showWinningTeams( );

public:

	// Constructor
	SportsLeague( );

	// Member functions

	void run( );	

};