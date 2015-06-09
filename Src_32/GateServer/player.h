#ifndef PLAYER_H
#define PLAYER_H

#include <gce/actor/all.hpp>

class game_player
{
public:
	game_player();

	~game_player();

public:
	void start(gce::stackful_actor actor);


};

#endif