#include "tournament_round.h"
#include "music_band.h"

// TournamentRound functions goes here

TournamentRound::TournamentRound() {
    // Default constructor implementation
}

TournamentRound::TournamentRound(std::vector<MusicBand*> _bands) : bands(_bands.begin(), _bands.end()) {
    // Constructor implementation with vector input
    //bands = _bands.begin(), _bands.end()
}

TournamentRound::TournamentRound(std::list<MusicBand*> _bands) /*: bands(std::move(_bands))*/ {
    bands = std::move(_bands);
    // Constructor implementation with list input
}

std::size_t TournamentRound::size() 
{ 
    return bands.size(); 
}
    
TournamentRound::TournamentRound(TournamentRound& other) /*: bands(other.bands)*/ {
    // Copy constructor implementation
    bands = other.bands;
}

TournamentRound::TournamentRound(TournamentRound&& other) /*: bands(std::move(other.bands))*/ {
    bands = std::move(other.bands);
}

TournamentRound& TournamentRound::operator=(TournamentRound&& other) 
{ 
    if (this == &other) 
    {
        return *this;
    } 
}

TournamentRound& TournamentRound::get_next_round() 
{ 
    TournamentRound nextRound;
    
    while (bands.size() > 1) {
        MusicBand* firstBand = bands.front();
        MusicBand* lastBand = bands.back();
        
        // Play the match between frontBand and backBand
        int scoreFirst = firstBand->play(lastBand);
        int scoreLast = lastBand->play(firstBand);
        
        // Determine the winner and fan change
        MusicBand* winner = (scoreFirst > scoreLast) ? firstBand : lastBand;
        MusicBand* loser = (scoreFirst > scoreLast) ? lastBand : firstBand;
        
        int fanChange = std::min(std::abs(scoreFirst - scoreLast), loser->get_fan_count());
        
        // Update fans for the winner and loser
        winner->set_fan_count(winner->get_fan_count() + fanChange);
        loser->set_fan_count(loser->get_fan_count() - fanChange);
        
        // Add the winner to the next round
        nextRound.bands.push_back(winner);
        
        // Remove the matched bands from the current round
        bands.pop_front();
        bands.pop_back();
    }
    
    // Handle the case when there is an odd number of bands
    if (!bands.empty()) {
        nextRound.bands.push_back(bands.front());
        bands.pop_front();
    }
    
    return nextRound;
}

std::ostream& operator<< (std::ostream &os, TournamentRound &other) 
{ 
    for (std::list<MusicBand*>::iterator it = other.bands.begin(); it != other.bands.end(); ++it) 
    {
        os << (*it)->get_name() << '\t';
    }
    return os; 
}