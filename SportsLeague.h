#include "DBCell.h"

class SportsLeague {

	// Data members
	DBCell database;

public:

	// Constructor
	SportsLeague( );

	// Member functions
	void addGame( );

	void addMenu( );

	void addPlayer( );

	void addReferee( );

	void addSport( );

	void addTeam( );

	void changeGameLocation( );

	void changeGameTime( );

	void changeSportSeason( );

	void displaySportsGames( );

	void displaySportsPlayed( );

	void exit( );

	void getAllReferees( );

	void getNonReferees( );

	void gamesWhenTeamCouldPlay( );

	void listNamesOfSports( );

	void listPlayersOnTeam( );

	void printMenu( );

	void removeGame( );

	void removeMenu( );

	void removePlayer( );

	void removeReferee( );

	void removeSport( );

	void removeTeam( );	

	bool retry( );

	void run( );	

	void showGames( );

	void showMenu( );

	void showPlayers( );

	void showReferees( );

	void showSports( );

	void showTeams( );

};