#include "Team.h"

int Team::numberOfPlayers() const
{
    return ids.size();
}

Team::Team(Games* games, Country* country, Sport* sport, string discipline, string type, string medal, vector<int> ids) : Competitor(games,country,sport,discipline,type,medal)
{
    this->ids = ids;
}

vector<int> Team::getPlayerIds()
{
    return ids;
}

