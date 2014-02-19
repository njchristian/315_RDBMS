#include "DBCell.h"

class SportsLeague {

	DBCell database;

public:
	SportsLeague( ) {
		// open file
		// create relations
	}

	void run( ) {
		// infinite loop until exit
	}

	void exit( ) {
		// write file
		// close file
		// exit
	}

	void showPlayers( );

	void showGames( );

	void showTeams( );

	void showReferees( );

	void showSports( );

	void addPlayer( );

	void addSport( );

	void addTeam( );

	void addGame( );

	void addReferee( );

	void removePlayer( );

	void removeSport( );

	void removeTeam( );

	void removeGame( );

	void removeReferee( );

	void displaySportsPlayed( );

	void gamesWhenTeamCouldPlay( );

	void getReferees( );

	void getNonReferees( );

	void changeGameLocation( );

	void changeGameTime( );

	void changeSportSeason( );

	void displaySportsGames( );

	void listPlayersOnTeam( );

};