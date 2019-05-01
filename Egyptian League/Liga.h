#pragma once
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;
class team;
class player;
class match;
class liga {
protected:
	map<string, team>liga_teams;
	map<string, player>liga_players;
public:
	liga();
};
class general {
public:
	void sort_teams_by_goals();
	void display_top_goals();
	void display_team_ordered_by_point();
	void display_top_players();
	void display_top_rank_player();
	unsigned short int convert_to_int(string);
	bool numbers(string);
	void display_teams_sorted_by_age();
	void display_team_name_id();
	void display_liga();
	bool valid_date(string &date);
	void replace_data_of_file(string); //file_name
};
class person : public general
{
protected:
public:
	string age;
	string name; //  referee -> match 
	person();
	void get_data();
};
class player : public person
{
	friend class match;  // to access score of player and incress it after matches 
	string *all;
	int rank;
	string player_id;
	string position;
	int score;
protected:
public:
	friend void general::display_top_goals();
	friend void general::display_top_players();
	friend void general::display_top_rank_player();
	player search_player(); //return player to display it or update
	friend void load();
	friend class team;
	int number;
	player();
	void add();
	void display_all_players();
	void display_player();
	void display_player_role();
	void update_player();
	void add_to_file_(string);
};
class rank_team
{
protected:
	unsigned int matches_played;
	unsigned int won;
	unsigned int lost;
	unsigned int Drawn;
	unsigned int point;
	int goal_difference;
	unsigned int goal_for;
	unsigned int goals_against;
public:
	rank_team();
};
class team : public rank_team, general
{
	string team_name;
	string id;
	string captain;
	map<int, player>players;       //int -> player number 
	friend class match;
	friend class general;
	vector<match>team_matches;
	friend player player::search_player(); //search(team name+player_name + player_id)
public:
	friend void player::update_player();
	void display_rank_team();
	friend void load();
	friend void player::add();   //display teams id an
	team();
	void add();
	void display_team_info();
	void update_team();
	void display_team_players();
	void search_team();
	bool display_player_role(int);
	void display_team_matches();
	void display_team_matches_date();
	void add_to_file(int); //int (add team or update team)
};
class referee : public person
{
};
class match :public general
{
	pair<string, string>teams_id;
	referee match_referee;
	bool held;
	string match_id;
	string date;
	string stadium;
	struct match_score {
		unsigned short int first;
		unsigned short int second;
		char ay7aga;
	};
	unordered_map<string, vector<string> >players_goal; // id of two teams and players name  
	match_score obj_score;
	friend unsigned short convert_to_int(string);
	friend void team::display_team_matches();
	friend void load();
	friend void team::display_team_matches_date();
public:
	match();
	void add();
	void change_score();
	void delete_match_score(match &); //update match 
	void display_match();
	void display_all_matches();
	void display_held_matches();
	void add_to_file(bool replace);
	void update_match();
	void display_match_in_date();
};