#include "DBCell.h"

class SportsLeague {

	// Data members
	DBCell database;

public:

	// Constructor
	SportsLeague( );

	// Member functions
	void addGame( );

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

	void getNonReferees( );

	void getReferees( );

	void gamesWhenTeamCouldPlay( );

	void listPlayersOnTeam( );

	void printMenu( );

	void removeGame( );

	void removePlayer( );

	void removeReferee( );

	void removeSport( );

	void removeTeam( );	

	bool retry( );

	void run( );	

	void showGames( );

	void showPlayers( );

	void showReferees( );

	void showSports( );

	void showTeams( );

};