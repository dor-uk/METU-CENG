:- module(main, [is_vote_wasted/2, is_candidate_elected/2, candidate_count_from_city/3, all_parties/1, all_candidates_from_party/2, all_elected_from_party/2, election_rate/2, council_percentage/2, alternative_debate_setups/2]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE


%------------------------------------------Part A----------------------------------------------


is_vote_wasted(City, PoliticalParty) :-
    \+ (elected(City, PoliticalParty, _)).
    
is_candidate_elected(Name, PoliticalParty) :-
    candidate(Name, PoliticalParty, City, Row),
    elected(City, PoliticalParty, ElectedCount),
    Row =< ElectedCount.
    
candidate_count_from_city([], _, 0).
candidate_count_from_city([Candidate|Rest], City, Count) :-
    ((candidate(Candidate, _, City, _), candidate_count_from_city(Rest, City, SubCount), Count is SubCount + 1);
    (\+ candidate(Candidate, _, City, _), candidate_count_from_city(Rest, City, Count))).


    
    
%----------------------------------------------------------------------------------------------


%------------------------------------------Part B----------------------------------------------

all_parties(ListOfPoliticalParties) :-
    findall(PoliticalParty, party(PoliticalParty, _), ListOfPoliticalParties).
    
all_candidates_from_party(PoliticalParty, ListOfCandidates) :-
    findall(Candidate, candidate(Candidate, PoliticalParty, _, _), ListOfCandidates).
    
all_elected_from_party(PoliticalParty, ListOfCandidates) :-
    findall(Candidate, (candidate(Candidate, PoliticalParty, _, _), is_candidate_elected(Candidate, PoliticalParty)), ListOfCandidates).
    
election_rate(PoliticalParty, Percentage) :-
    all_candidates_from_party(PoliticalParty, AllCandidates),
    all_elected_from_party(PoliticalParty, ElectedCandidates),
    length(AllCandidates, Total),
    length(ElectedCandidates, Elected),
    Percentage is (Elected / Total).
    %format('~2f', [Percentage]).
    
council_percentage(PoliticalParty, Percentage) :-
    all_elected_from_party(PoliticalParty, Elected_Candidates),
    to_elect(TotalElect),
    length(Elected_Candidates, Elected),
    Percentage is (Elected / TotalElect).
    %format('~2f', Percentage).



%-------------------------------------------------------------------------------------------------


%----------------------------------------Part C---------------------------------------------------


alternative_debate_setups(DescriptionString, OrderedListOfCandidates) :-
    atom_chars(DescriptionString, [Initial|Rest]),
    party(Party_name, Initial),
    all_candidates_from_party(Party_name, Party_list),
    member(Candidate, Party_list),
    debate_setup(Rest, Others, [Candidate]),
    append([Candidate], Others, OrderedListOfCandidates).


debate_setup([],[], _).
debate_setup([Initial|Rest], Candidate_l, Prev) :-
    party(Party_name, Initial),
    all_candidates_from_party(Party_name, Party_list),
    member(Candidate, Party_list),
    \+ member(Candidate, Prev),
    append(Prev, [Candidate], ForbiddenList),
    debate_setup(Rest, Rest_l, ForbiddenList),
    append([Candidate], Rest_l, Candidate_l).






