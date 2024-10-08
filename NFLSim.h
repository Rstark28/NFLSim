#ifndef NFLSIM_H
#define NFLSIM_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Game.h"

class NFLSim
{
public:
    // Constructor and Destructor
    NFLSim(const std::string &filename);
    ~NFLSim();

private:
    // Core Simulation Functions
    void runSimulation();
    void handleRunCommand(bool print);
    void simulateRegularSeason();
    void simulatePlayoffs();
    void simulateMultipleSeasons(int numSeasons, bool print);
    void saveScheduelAsCSV(const std::string &filename) const;

    // Schedule and Team Management
    void readSchedule(const std::string &filename);
    void readTeams(const std::string &filename);
    void processAllGames();
    void processTeamGames(int teamIndex);
    std::vector<std::string> parseGameInfo(const std::string &teamName, const std::string &gameInfo, int week);
    void resetSeason();

    // Playoff Management
    void determinePlayoffTeams();
    void determineDivisionWinners();
    void determineWildCardTeams();
    std::shared_ptr<Team> resolveTiebreaker(const std::shared_ptr<Team> &team1, const std::shared_ptr<Team> &team2);
    std::shared_ptr<Team> simulatePlayoffGame(std::shared_ptr<Team> homeTeam, std::shared_ptr<Team> awayTeam);

    // Elo Rating and Game Processing
    void manualGameResults();
    void updateEloRatings(std::shared_ptr<Game> gamePtr);
    void calculateHomeOdds(std::shared_ptr<Game> &game);
    double calculateFieldAdvantage(const City &homeCity, const City &awayCity);
    double adjustEloForByes(const Game &game, const Team &homeTeam, const Team &awayTeam);
    double calculateHomeOddsFromEloDiff(double eloDiff);

    // Output Functions
    void printSchedule() const;
    void printTeamHeader(const std::shared_ptr<Team> &team, int teamColumnWidth, int weekColumnWidth, int gameColumnWidth) const;
    void printTeamGames(const std::shared_ptr<Team> &team, const std::vector<std::shared_ptr<Game>> &games, int teamColumnWidth, int gameColumnWidth) const;
    void printSeasonResults(const std::map<std::string, std::vector<int>> &teamWins, int season) const;
    void printFinalResults(const std::map<std::string, std::vector<int>> &teamWins, const std::map<std::string, std::vector<int>> &playoffRounds, int numSeasons) const;

    // Data Members
    std::vector<std::vector<std::shared_ptr<Game>>> NFLSchedule;
    std::unordered_map<std::string, std::shared_ptr<Team>> teamMapByAbbreviation;
    std::map<std::string, std::map<std::string, std::vector<std::shared_ptr<Team>>>> leagueStructure;
    std::map<std::string, std::vector<std::shared_ptr<Team>>> playoffSeeding;
};

#endif // NFLSIM_H
