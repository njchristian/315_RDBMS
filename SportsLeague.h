#include "DBCell.h"

class SportsLeague {

	DBCell database;

public:
	SportsLeague( ) {
		// open file
		// create relations
	}

	void exit( ) {
		// write file
		// close file
		// exit
	}

	void showRelation( string relationName );

	addPlayer( );

	addSport( );

	addTeam( );

	addGame( );

	addCaptain( );

	removePlayer( );

	removeSport( );

	removeTeam( );

	removeGame( );

	removeCaptain( );

	displaySportsPlayed( string playerName );

	listSports( );

	gamesWhenTeamCouldPlay( string teamName );

	getCaptains( );



};