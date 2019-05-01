#include "liga.h"
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<queue>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<unordered_map>
using namespace std;
map<pair<string, string>, match>liga_matches;
map<string, team>liga_teams;
map<string, player>liga_players;
liga::liga() {
}
person::person() {}
void person::get_data() {
	cout << "enter player name : ";
	cin >> name;
	while (true) {
		cout << "enter player age : ";
		cin >> age;
		if (numbers(age))break;
		puts("wrong..! the age should be contain only numbers");
	}
}
match::match() {
	obj_score.first = '?';
	obj_score.ay7aga = ' : ';
	obj_score.second = '?';
}
player::player() {
	all = new string[4];
	all[0] = "forward";
	all[1] = "midfilder";
	all[2] = "defender";
	all[3] = "goalkeeper";
	score = 0;
};
team::team() {};
void player::display_player_role() {
	player p;
	p = player::search_player();
	cout << p.name << " role is " << p.position << "\n\n";
}
void player::add() {
	system("cls");
	puts("\t\t\t---------------------------------");
	puts("\t\t\t\tteams id and name   ");
	puts("\t\t\t---------------------------------");
	for (auto it = liga_teams.begin(); it != liga_teams.end(); it++)
		cout << it->first << " " << it->second.team_name << "\n";
	puts("Enter team id ");
	string team_id;
	cin >> team_id;
	while (liga_teams.find(team_id) == liga_teams.end()) {
		puts("wrong..! this team id not exist");
		puts("Enter another team id : ");
		cin >> team_id;
	}
	system("cls");
	person::get_data();
	while (true) {
		cout << "enter player id : ";
		cin >> player_id;
		if (numbers(player_id) && !liga_players.count(player_id))break;
		if (liga_players.count(player_id))puts("this player id is already exist ");
		else puts("wrong..! player id should contain only numbers");
	}
	cout << "enter player number : ";
	cin >> number;
	int player_position;
	cout << "prees [1] to forward \n";
	cout << "prees [2] to midfilder \n";
	cout << "prees [3] to defender \n";
	cout << "prees [4] to goalkeeper \n";
	while (true) {
		cin >> player_position;
		if (player_position == 1 || player_position == 2 || player_position == 3 || player_position == 4) break;
		else cout << "wrong choice .. please enter a number from (1) to (4) only \n";
	}
	position = all[player_position - 1];
	/*cout << "enter player score : ";
	cin >> score;*/
	string tmp;
	while (true) {
		cout << "enter player rank : ";
		cin >> tmp;
		if (numbers(tmp))break;
		else puts("wrong..! rank should contain only numbers");
	}
	rank = general::convert_to_int(tmp);
	liga_teams[team_id].players.insert(pair<int, player>(number, *this));
	liga_players.insert(pair<string, player>(player_id, *this));
	add_to_file_(team_id);
}
void player::display_player() {
	cout << "player name     : " << name << "\n";
	cout << "player age      : " << age << "\n";
	cout << "player id       : " << player_id << "\n";
	cout << "player number   : " << number << "\n";
	cout << "player position : " << position << "\n";
	cout << "player score    : " << score << "\n";
	cout << "player rank     : " << rank << "\n";
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
}
void player::display_all_players() {
	int i = 0;
	system("cls");
	for (auto it = liga_players.begin(); it != liga_players.end(); it++) {
		printf("player (%d) \n", ++i);
		it->second.display_player();
	}
}
void player::update_player() {
	char tmp;
	player p;
	p = p.search_player();
	//get team id of player  order(size of map (liga_teams)) 
	// needed to change data in file and map of liga_teams 
	string team_id;
	for (auto it = liga_teams.begin(); it != liga_teams.end(); it++)
		if (it->second.players.find(p.number) != it->second.players.end()) {
			team_id = it->first;
		}
	do {
		system("cls");
		cout << "what do you to update" << endl;
		cout << "press  [1] to name \n";
		cout << "press  [2] to position \n";
		cout << "press  [3] to rank \n";
		cin >> tmp;
	} while (!(tmp == '1' || tmp == '2' || tmp == '3'));
	switch (tmp)
	{
	case ('1'): {
		system("cls");
		string new_name;
		cout << "enter new name : ";
		getline(cin, new_name);
		getline(cin, new_name);
		p.name = new_name;
		break;
	}
	case ('2'): {
		system("cls");
		int new_position;
		cout << "enter new position \n";
		cout << "prees [1] to forward \n";
		cout << "prees [2] to midfilder \n";
		cout << "prees [3] to defender \n";
		cout << "prees [4] to goalkeeper \n";
		while (true) {
			cin >> new_position;
			if (new_position == 1 || new_position == 2 || new_position == 3 || new_position == 4) break;
			else cout << "wrong choice .. please enter a number from (1) to (4) only \n";
		}
		p.position = all[new_position - 1];
		break;
	}
	case('3'): {
		system("cls");
		double new_rank;
		cout << "enter new rank \n";
		cin >> new_rank;
		p.rank = new_rank;
		break;
	}
	}
	liga_players[p.player_id] = p; //update data of player in map players;
	liga_teams[team_id].players[p.number] = p; //update data of player in map liga_teams 
	replace_data_of_file(team_id); //change data in file;
}
void team::add() {                   //DONE
	cout << "enter team name : ";
	getline(cin, team_name);
	getline(cin, team_name);
	cout << "enter team id : ";
	cin >> id;
	while (liga_teams.count(id) || !numbers(id)) {
		if (numbers(id))
			puts("this id is already exist, please enter another one");
		else
			puts("id should be contaions only numbers, please enter another one");
		cin >> id;
	}
	cout << "enter team captain : ";
	getline(cin, captain);
	getline(cin, captain);
	/*cout << "enter team score : ";
	cin >>team_score;
	while(!numbers(team_score)){
	puts("wrong ..! team score should contain only numbers, please enter another one");
	cin>>team_score;
	}*/
	//char choice;
	liga_teams.insert(pair<string, team>(this->id, *this));
	add_to_file(1);
}
void team::display_team_info() {  //DONE
	display_team_name_id();
	printf("Enter team id : ");
	string tmp; //id of team 
	while (true) {
		cin >> tmp;
		system("cls");
		if (liga_teams.find(tmp) == liga_teams.end()) {
			puts("this team id is not exist..!");
			puts("Enter another team id : ");
		}
		else break;
	}
	cout << "team name : " << liga_teams[tmp].team_name << "\n";
	cout << "team id : " << liga_teams[tmp].id << "\n";
	cout << "team captain : " << liga_teams[tmp].captain << "\n";
	cout << "team score : " << liga_teams[tmp].point << "\n";
}
void team::update_team() {
	char choice;
	cout << "press  [1] to update team name \n";
	cout << "press  [2] to update team captain \n";
	cout << "press  [3] to update team score \n";
	cout << "press  [4] to update team players \n";
	cin >> choice;
	while (!(choice == '1' || choice == '2' || choice == '3' || choice == '4')) {
		puts("wrong..! ");
		cin >> choice;
	}
	string tmp;   //team id to update
	switch (choice) {
	case ('1'): {
		display_team_name_id();
		while (true) {
			puts("Enter team id : ");
			cin >> tmp;
			if (liga_teams.find(tmp) != liga_teams.end())break;
			puts("wrong..! this team id is not exist ");
		}
		system("cls");
		string new_name;
		cout << "enter new name : ";
		getline(cin, new_name);
		getline(cin, new_name);
		liga_teams[tmp].team_name = new_name;
		system("cls");
		puts("updated succefully");
		replace_data_of_file(tmp);
		break;
	}
	case ('2'): {
		display_team_name_id();
		while (true) {
			puts("Enter team id : ");
			cin >> tmp;
			if (liga_teams.find(tmp) != liga_teams.end())break;
			puts("wrong..! this team id is not exist ");
		}
		system("cls");
		string captain_name;
		cout << "enter new captain name : ";
		getline(cin, captain_name);
		getline(cin, captain_name);
		liga_teams[tmp].captain = captain_name;
		system("cls");
		puts("updated succefully");
		replace_data_of_file(tmp);
		break;
	}
	case ('3'): {
		display_team_name_id();
		while (true) {
			puts("Enter team id : ");
			cin >> tmp;
			if (liga_teams.find(tmp) != liga_teams.end())break;
			puts("wrong..! this team id is not exist ");
		}
		string score_string;
		while (true) {
			system("cls");
			cout << "enter new score : ";
			cin >> score_string;
			if (numbers(score_string))break;
			cout << "score should be contain number only , ";
		}
		int new_score = convert_to_int(score_string);
		liga_teams[tmp].point = new_score;
		system("cls");
		puts("updated succefully");
		replace_data_of_file(tmp);
		break;
	}
	case('4'): {
		system("cls");
		bool first = true;      //break condition 
		while (true) {
			if (first)cout << "press [1] to add \npress [2] to delete\n";
			first = false;
			cin >> tmp;
			while (!(tmp == "1" || tmp == "2" || tmp == "3"))cout << "press [1] to add \npress [2] to delete\n";
			if (tmp == "3")break;
			if (tmp == "1") {
				player p1;
				p1.add(); //add to file in function add player
				system("cls");
			}
			else {
				display_team_name_id();
				while (true) {
					puts("Enter team id : ");
					cin >> tmp;
					if (liga_teams.find(tmp) != liga_teams.end())break;
					puts("wrong..! this team id is not exist ");
				}
				system("cls");
				puts("\t\t\t---------------------------------");
				puts("\t\t\t     players number and name   ");
				puts("\t\t\t---------------------------------");
				for (auto it = liga_teams[tmp].players.begin(); it != liga_teams[tmp].players.end(); it++)
					cout << it->first << " " << it->second.name << endl;
				int number_delete;
				while (true) {
					cout << "enter player number : ";
					cin >> number_delete;
					if (liga_teams[tmp].players.find(number_delete) != liga_teams[tmp].players.end())break;
					puts("wrong..! this player id is not exist ");
				}
				if (liga_teams[tmp].players.find(number_delete) != players.end()) {
					liga_players.erase(liga_teams[tmp].players[number_delete].player_id);
					liga_teams[tmp].players.erase(number_delete);
					system("cls");
					puts("the player is deleted from the team list");
				}
				replace_data_of_file(tmp);
			}
			cout << "press [1] to add \npress [2] to delete\npress [3] to break\n";
		}
		system("cls");
		puts("updated succefully");
		break;
	}
	}
}
void team::display_team_players() {
	display_team_name_id();
	string team_search_id;
	while (true) {
		cout << "Enter team id : ";
		cin >> team_search_id;
		if (liga_teams.find(team_search_id) != liga_teams.end())break;
		puts("this team id id not exist");
	}
	int i = 1;
	system("cls");
	for (auto it = liga_teams[team_search_id].players.begin(); it != liga_teams[team_search_id].players.end(); it++) {
		if (i != 1)printf("\n");
		printf("player(%d)\n", i++);
		printf("-----------------\n");
		it->second.display_player();
	}
}
void team::search_team() {
	while (true) {
		puts("Enter team id or team name : ");
		string IORN;
		cin >> IORN;
		bool find = false;
		for (auto it = liga_teams.begin(); it != liga_teams.end(); it++) {
			if (it->first == IORN || it->second.team_name == IORN) {
				system("cls");
				cout << "team name :" << it->second.team_name << endl;
				cout << "team id   :" << it->first << endl;
				cout << "team captian name : " << it->second.captain << endl;
				cout << "team score : " << it->second.point << endl;
				find = true;
			}
		}
		if (find)break;
		puts("not found..!");
	}
}
rank_team::rank_team() {
	matches_played = 0;
	won = 0;
	lost = 0;
	Drawn = 0;
	point = 0;
	goal_difference = 0;
	goal_for = 0;
	goals_against = 0;
}
void team::display_team_matches()
{
	display_team_name_id();
	cout << "Enter team id : ";
	string team_id;
	while (true) {
		cin >> team_id;
		if (liga_teams.find(team_id) != liga_teams.end())break;
		puts("this team id is not exist..! Enter another team id : ");
	}
	system("cls");
	for (auto it = liga_teams[team_id].team_matches.begin(); it != liga_teams[team_id].team_matches.end(); it++) {
		cout << "match id : " << it->match_id << endl;
		cout << "match stadium : " << it->match_id << endl;
		cout << "match referee : " << it->match_referee.name << endl;
		cout << "match date : " << it->date << endl;
		if (it->held)cout << "the match is held\n";
		else {
			cout << liga_teams[it->teams_id.first].team_name << " ( " << it->obj_score.first << " : " << it->obj_score.second << " ) " << liga_teams[it->teams_id.second].team_name << endl;
			for (int i = 0; i<it->players_goal[it->teams_id.first].size() || i<it->players_goal[it->teams_id.second].size(); i++) {//it->access match->map of players goal []first team
				if (i<it->players_goal[it->teams_id.first].size())cout << it->players_goal[it->teams_id.first][i];
				cout << "               ";
				if (i<it->players_goal[it->teams_id.second].size()) cout << it->players_goal[it->teams_id.second][i];
				cout << endl;
			}
		}
		printf("-----------------------------------------------\n");
	}
}
void team::display_rank_team() {
	display_team_name_id();
	cout << "Enter team id : ";
	string team_id;
	while (true) {
		cin >> team_id;
		if (liga_teams.find(team_id) != liga_teams.end())break;
		puts("this team id is not exist..! Enter another team id : ");
	}
	cout << "team points : " << liga_teams[team_id].point << "   point\n";
	cout << "team played : " << liga_teams[team_id].matches_played << "    match\n";
	cout << "team WON  : " << liga_teams[team_id].won << "      match\n";
	cout << "team LOSE : " << liga_teams[team_id].lost << "     match\n";
	cout << "team Drawn : " << liga_teams[team_id].Drawn << "     match\n";
	cout << "Goal for : " << liga_teams[team_id].goal_for << "    GOAL\n";
	cout << "Goal against : " << liga_teams[team_id].goals_against << "    GOAL\n";
	cout << "GOAL difference : " << liga_teams[team_id].goal_difference << "  GOAL\n";
}
void match::change_score() {
	while (true) {
		cout << "enter match score ( ? : ? )  ";
		string tmp, tmp1;
		cin >> tmp;
		cin >> obj_score.ay7aga;
		cin >> tmp1;
		if (!numbers(tmp) || !numbers(tmp1)) {
			continue;
		}
		obj_score.second = convert_to_int(tmp1);
		obj_score.first = convert_to_int(tmp);
		break;
	}
	//rank teams
	if (this->obj_score.first == this->obj_score.second) {
		liga_teams[this->teams_id.first].point++;
		liga_teams[this->teams_id.second].point++;
		liga_teams[this->teams_id.first].Drawn++;
		liga_teams[this->teams_id.second].Drawn++;
	}
	else if (this->obj_score.first>this->obj_score.second) {
		liga_teams[this->teams_id.first].point += 3;
		liga_teams[this->teams_id.first].won++;
		liga_teams[this->teams_id.second].lost++;
	}
	else {
		liga_teams[this->teams_id.second].won++;
		liga_teams[this->teams_id.first].lost++;
		liga_teams[this->teams_id.second].point += 3;
	}
	if (this->obj_score.first>0) { //player who scored goals from first team
		system("cls");
		puts("\t\t\t------------------------------------------------------");
		puts("\t\t         number and name of players of the first team   ");
		puts("\t\t\t------------------------------------------------------");
		for (auto it = liga_teams[this->teams_id.first].players.begin(); it != liga_teams[this->teams_id.first].players.end(); it++)
			cout << it->first << "  " << it->second.name << "\n";
		unsigned short int number_of_goals = this->obj_score.first;
		//change team information ...
		liga_teams[this->teams_id.first].goal_for += number_of_goals;
		liga_teams[this->teams_id.second].goals_against += number_of_goals;
		liga_teams[this->teams_id.first].goal_difference += (this->obj_score.first - this->obj_score.second);
		for (int i = 0; i<number_of_goals; i++) {
			cout << "enter the number of player who scored goal number (" << i + 1 << ") : ";
			int tmp;
			cin >> tmp;
			while (liga_teams[this->teams_id.first].players.find(tmp) == liga_teams[this->teams_id.first].players.end()) {
				cout << "this id is not found ..! \n";
				cout << "enter the id of player who scored goal number (" << i + 1 << ") : ";
				cin >> tmp;
			}
			liga_teams[this->teams_id.first].players[tmp].score++;
			liga_players[liga_teams[this->teams_id.first].players[tmp].player_id].score++;//get player id using player number from map liga_team;
																						  //string player_name=liga_teams[this->teams_id.first].players[tmp].name;
			this->players_goal[this->teams_id.first].push_back(liga_teams[this->teams_id.first].players[tmp].name);  //get player name from team -> player using id;
		}
	}
	if (this->obj_score.second>0) { //player who scored goals from second team
		system("cls");
		puts("\t\t\t------------------------------------------------------");
		puts("\t\t         number and name of players of the second team   ");
		puts("\t\t\t------------------------------------------------------");
		for (auto it = liga_teams[this->teams_id.second].players.begin(); it != liga_teams[this->teams_id.second].players.end(); it++)
			cout << it->first << "  " << it->second.name << "\n";
		unsigned short int number_of_goals = this->obj_score.second;
		// change team intformation ...
		liga_teams[this->teams_id.second].goal_for += number_of_goals;
		liga_teams[this->teams_id.first].goals_against += number_of_goals;
		liga_teams[this->teams_id.second].goal_difference += (this->obj_score.second - this->obj_score.first);
		for (int i = 0; i<number_of_goals; i++) {
			cout << "enter the id of player who scored goal number (" << i + 1 << ") : ";
			int tmp;
			cin >> tmp;
			while (liga_teams[this->teams_id.second].players.find(tmp) == liga_teams[this->teams_id.second].players.end()) {
				cout << "this id is not found ..! \n";
				cout << "enter the id of player who scored goal number (" << i + 1 << ") : ";
				cin >> tmp;
			}
			this->players_goal[this->teams_id.second].push_back(liga_teams[this->teams_id.second].players[tmp].name);
			liga_teams[this->teams_id.second].players[tmp].score++;
			liga_players[liga_teams[this->teams_id.second].players[tmp].player_id].score++;//get player id using player number from map liga_team;
		}
	}
	liga_teams[this->teams_id.first].matches_played++;
	liga_teams[this->teams_id.second].matches_played++;
	//change data in file file (team)
	liga_teams[this->teams_id.first].add_to_file(0);
	liga_teams[this->teams_id.second].add_to_file(0);
	//change data in file file (players)
	for (auto it = liga_teams[this->teams_id.first].players.begin(); it != liga_teams[this->teams_id.first].players.end(); it++)
		it->second.add_to_file_(this->teams_id.first);
	for (auto it = liga_teams[this->teams_id.second].players.begin(); it != liga_teams[this->teams_id.second].players.end(); it++)
		it->second.add_to_file_(this->teams_id.second);
}
void match::add()
{
	do {
		system("cls");
		display_team_name_id();
		cout << "Enter id for the first team : ";
		while (true) {
			cin >> teams_id.first;
			if (liga_teams.find(teams_id.first) != liga_teams.end())break;
			printf("this team id is not exist..! Enter another team id : ");
		}
		cout << "Enter id for the second team : ";
		while (true) {
			cin >> teams_id.second;
			if (liga_teams.find(teams_id.second) != liga_teams.end())break;
			printf("this team id is not exist..! Enter another team id : ");
		}
	} while (liga_matches.find(make_pair(teams_id.first, teams_id.second)) != liga_matches.end() || teams_id.first == teams_id.second);
	cout << "enter match id : ";
	while (true) {
		bool v = true;
		cin >> match_id;
		if (!numbers(match_id))
			printf("match id should contain only numbers, Enter another id : "), v = false;
		for (auto it = liga_matches.begin(); it != liga_matches.end(); it++)
			if (it->second.match_id == match_id)
				cout << "this match id is Exist, Enter another one : ", v = false;
		if (v)break;
	}
	cout << "enter match date : ";
	while (true) {
		cin >> date;
		if (valid_date(date))break;
		printf("Not vaild data, Enter valid match date : ");
	}
	cout << "enter match stadium : ";
	getline(cin, stadium);
	getline(cin, stadium);
	cout << "enter match referee name :  ";
	/*	getline(cin,match_referee.name);        not work
	getline(cin,match_referee.name);*/
	cin >> match_referee.name;
	cout << "held (Y/N) : ";
	while (true) {
		char ch;
		cin >> ch;
		if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n') {
			if (ch == 'Y' || ch == 'y')held = true;
			else held = false;
			break;
		}
		else
			cout << "enter (Y/N) only \n";
	}
	if (held == false)
		change_score();
	add_to_file(false); //add match to file;
	liga_matches.insert(make_pair(make_pair(this->teams_id.first, this->teams_id.second), *this));
	liga_teams[teams_id.first].team_matches.push_back(*this);
	liga_teams[teams_id.second].team_matches.push_back(*this);
}
void match::display_match() {
	cout << "id : " << this->match_id << endl;
	cout << "stadium : " << this->stadium << endl;
	cout << "date : " << this->date << endl;
	cout << "referee name : " << this->match_referee.name << endl;
	if (this->held)cout << "Did not held\n";
	else cout << liga_teams[this->teams_id.first].team_name << " (" << this->obj_score.first << " : " << this->obj_score.second << ") " << liga_teams[this->teams_id.second].team_name << endl;
}
player player::search_player() {
	while (true) {
		system("cls");
		string team_name;
		display_team_name_id();
		cout << "enter team name : ";
		getline(cin, team_name);        // error get_line not work
		getline(cin, team_name);
		for (auto it = liga_teams.begin(); it != liga_teams.end(); it++)
			if (it->second.team_name == team_name) {
				system("cls");
				puts("\t\t\t---------------------------------------------------");
				cout << "\t\t               number and name of " << it->second.team_name << " players \n";
				puts("\t\t\t---------------------------------------------------");
				for (auto it1 = it->second.players.begin(); it1 != it->second.players.end(); it1++)
					cout << it1->second.number << "     " << it1->second.name << endl;
				string player_name;
				cout << "enter player name : ";
				cin >> player_name;
				cout << "enter player number : ";
				string tmp;
				cin >> tmp;
				unsigned int number = convert_to_int(tmp);
				//cout << "enter player number : ";
				//cin >> number;
				if (it->second.players.find(number) != it->second.players.end() && it->second.players[number].name == player_name) {
					system("cls");
					return it->second.players[number];
					break;
				}
			}
	}
}
unsigned short int general::convert_to_int(string ss)
{
	unsigned short int score = 0;
	for (int i = 0; i<ss.size(); i++) {
		score *= 10;
		score += ss[i] - '0';
	}
	return score;
}
bool general::numbers(string s) {
	for (int i = 0; i<s.length(); i++)
		if (!(s[i] >= '0'&&s[i] <= '9'))
			return false;
	return true;
}
void team::add_to_file(int n) {
	if (n) {
		ofstream teams_name;
		teams_name.open("teams_id", ios::in | ios::app);
		teams_name << id << "\n";
	}
	ofstream new_file;
	//new_file.open(id,ios::in|ios::app);
	new_file.open(id, ofstream::out | ofstream::trunc);
	new_file << team_name << "\n" << id << "\n" << captain << "\n" << won << "\n" << lost << "\n" << Drawn << "\n" << point << "\n" << goal_difference << "\n" << goal_for << "\n" << goals_against << "\n";
	new_file.close();
}
void player::add_to_file_(string file_name) {
	ofstream file;
	file.open(file_name, ios::out | ios::app);
	file << name << "\n" << age << "\n" << player_id << "\n" << number << "\n" << position << "\n" << rank << "\n" << score << "\n";
	file.close();
}
void load() {
	ifstream team_name;
	team_name.open("teams_id", ios::out | ios::app);
	while (team_name.good()) {
		string new_team;
		getline(team_name, new_team);
		ifstream teami;
		teami.open(new_team, ios::out | ios::app);
		team tmp;
		getline(teami, tmp.team_name);
		getline(teami, tmp.id);
		getline(teami, tmp.captain);
		teami >> tmp.won;
		teami >> tmp.lost;
		teami >> tmp.Drawn;
		teami >> tmp.point;
		teami >> tmp.goal_difference;
		teami >> tmp.goal_for;
		teami >> tmp.goals_against;
		liga_teams.insert(pair<string, team>(tmp.id, tmp));
		string eof;
		while (teami >> eof) {
			player p;
			//teami>>p.name;
			p.name = eof;
			teami >> p.age;
			getline(teami, p.player_id);
			teami >> p.player_id;
			teami >> p.number;
			teami >> p.position;
			teami >> p.rank;
			teami >> p.score;
			liga_teams[tmp.id].players.insert(pair<int, player>(p.number, p));
			liga_players.insert(pair<string, player>(p.player_id, p));
		}
	}
	//LOAD MATCHES DATA;
	ifstream match_file;
	match_file.open("liga_matches.txt", ios::in | ios::app);
	string tmp;   /// while(geting data)
	while (match_file >> tmp) {
		match m;
		m.teams_id.first = tmp;
		match_file >> m.teams_id.second;
		match_file >> m.match_referee.name;
		match_file >> m.held;
		match_file >> m.match_id;
		match_file >> m.date;
		match_file >> m.stadium;
		match_file >> m.obj_score.first;
		match_file >> m.obj_score.second;
		for (int i = 0; i<m.obj_score.first; i++) { //players who scored goals from first team
			match_file >> tmp;
			m.players_goal[m.teams_id.first].push_back(tmp);
		}
		for (int i = 0; i<m.obj_score.second; i++) {  //players who scored goals from second team
			match_file >> tmp;
			m.players_goal[m.teams_id.second].push_back(tmp);
		}
		liga_matches.insert(make_pair(make_pair(m.teams_id.first, m.teams_id.second), m));
		liga_teams[m.teams_id.first].team_matches.push_back(m);
		liga_teams[m.teams_id.second].team_matches.push_back(m);
	}
}
void match::add_to_file(bool replace) {
	ofstream match_file;
	if (replace)match_file.open("liga_matches.txt", ios::out | ios::trunc);//clear file;
	match_file.close();
	match_file.open("liga_matches.txt", ios::out | ios::app);
	if (replace) {
		for (auto it = liga_matches.begin(); it != liga_matches.end(); it++) {
			match_file << it->second.teams_id.first << "\n" << it->second.teams_id.second << "\n" << it->second.match_referee.name << "\n" << it->second.held << "\n" << it->second.match_id << "\n" << it->second.date << "\n" << it->second.stadium << "\n" << it->second.obj_score.first << "\n" << it->second.obj_score.second << "\n";
			for (auto it1 = it->second.players_goal.begin(); it1 != it->second.players_goal.end(); it1++)
				for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
					match_file << *it2 << "\n";
		}
	}
	else {
		match_file << teams_id.first << "\n" << teams_id.second << "\n" << match_referee.name << "\n" << held << "\n" << match_id << "\n" << date << "\n" << stadium << "\n" << obj_score.first << "\n" << obj_score.second << "\n";
		//add player who scored goals 
		for (auto it = this->players_goal.begin(); it != players_goal.end(); it++)
			for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++)
				match_file << *it1 << "\n";
	}
	match_file.close();
}
void general::display_team_name_id() {
	system("cls");
	puts("\t\t\t---------------------------------");
	puts("\t\t\t\tteams id and name   ");
	puts("\t\t\t---------------------------------");
	for (auto it = liga_teams.begin(); it != liga_teams.end(); it++)
		cout << it->first << " " << it->second.team_name << "\n";
}
void general::replace_data_of_file(string file_name) {
	ofstream ofs;
	ofs.open(file_name, std::ofstream::out | std::ofstream::trunc); //team file
	ofs.close();
	liga_teams[file_name].add_to_file(0);
	for (auto it = liga_teams[file_name].players.begin(); it != liga_teams[file_name].players.end(); it++)
		it->second.add_to_file_(file_name);
}
bool general::valid_date(string &date) {
	if (date.length()>10 || date.length()<8)return false;
	if (!(date[0] >= 48 && date[0] <= 57 && date[1] >= 48 && date[1] <= 57))
		date.insert(0, "0");
	if (!(date[3] >= 48 && date[3] <= 57 && date[4] >= 48 && date[4] <= 57))
		date.insert(3, "0");
	string int_only = date;
	int_only.erase(2, 1);
	int_only.erase(4, 1);
	if (!numbers(int_only))return false;
	date[2] = date[5] = '-';
	int day = ((date[0] - 48) * 10) + (date[1] - 48);
	int month = ((date[3] - 48) * 10) + (date[4] - 48);
	int year = (((date[6] - 48) * 1000) + ((date[7] - 48) * 100) + ((date[8] - 48) * 10) + (date[9] - 48));
	if (day > 31 || day<1 || month>12 || month < 1 || year<2018)
		return false;
	return true;
}
void general::display_team_ordered_by_point() {
	priority_queue<pair<int, string>>teams_sorted;  //string = team id
	for (auto it = liga_teams.begin(); it != liga_teams.end(); it++)
		teams_sorted.push(make_pair(it->second.point, it->first));
	for (int i = 0; i<3; i++) {
		cout << liga_teams[teams_sorted.top().second].team_name << "   " << teams_sorted.top().first << endl;
		teams_sorted.pop();
	}
}
void general::display_top_players() {
	priority_queue<pair<int, string>>players_sorted; //string = player_id
	for (auto it = liga_players.begin(); it != liga_players.end(); it++)
		players_sorted.push(make_pair(it->second.score, it->first));
	for (int i = 0; i<3; i++) {
		cout << liga_players[players_sorted.top().second].name << "  " << players_sorted.top().first << endl;
		players_sorted.pop();
	}
}
void general::display_top_goals() {
	set<pair<int, string>>goals_sorted;
	for (auto it = liga_teams.begin(); it != liga_teams.end(); it++)
		for (auto it1 = it->second.players.begin(); it1 != it->second.players.end(); it1++)
			if (it1->second.position == it1->second.all[3])
				goals_sorted.insert(make_pair(it->second.goals_against, it1->second.player_id));
	for (auto it = goals_sorted.begin(); it != goals_sorted.end(); it++)
		cout << liga_players[it->second].name << "  " << it->first << endl;
}
void general::display_top_rank_player() {
	priority_queue<pair<int, string>>players_sorted; //string player_id
	for (auto it = liga_players.begin(); it != liga_players.end(); it++)
		players_sorted.push(make_pair(it->second.rank, it->first));
	for (int i = 0; i<3; i++) {
		cout << liga_players[players_sorted.top().second].name << "   " << players_sorted.top().first << endl;
		players_sorted.pop();
	}
}
void general::sort_teams_by_goals() {
	priority_queue<pair<int, string>>teams_sorted; //string = team id;
	for (auto it = liga_teams.begin(); it != liga_teams.end(); it++)
		teams_sorted.push(make_pair(it->second.goal_for, it->first));
	for (int i = 0; i<3; i++) {
		cout << liga_teams[teams_sorted.top().second].team_name << "   " << teams_sorted.top().first << endl;
		teams_sorted.pop();
	}
}
void match::update_match() {
	system("cls");
	puts("\t\t\t---------------------------------");
	puts("\t\t\t    matches id and teams name   ");
	puts("\t\t\t---------------------------------");
	for (auto it = liga_matches.begin(); it != liga_matches.end(); it++)
		cout << it->second.match_id << "    " << " [ " << liga_teams[it->second.teams_id.first].team_name << " : " << liga_teams[it->second.teams_id.second].team_name << " ]\n";
	cout << "Enter match id : ";
	string id_update;
	while (true) {   //make sure that the id is exist 
		bool find = false;
		cin >> id_update;
		for (auto it = liga_matches.begin(); it != liga_matches.end(); it++)
			if (it->second.match_id == id_update) {
				find = true;
				break;
			}
		if (find)break;
		printf("this match id is not exist, Enter another match id : ");
	}
	char choice;
	while (true) {
		system("cls");
		puts("press  [1] to update match teams name ");
		puts("press  [2] to update match referee name ");
		puts("press  [3] to update match Stadium name ");
		puts("press  [4] to update match date ");
		puts("press  [5] to update status of match (Enter score) ");
		puts("press  [6] to update match score ");
		cin >> choice;
		if ((choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6'))
			break;
	}
	//get iterator to update data of match 
	auto it = liga_matches.begin();
	for (; it != liga_matches.end(); it++)
		if (it->second.match_id == id_update)
			break;
	switch (choice) {
	case ('1'): { //update match teams
		delete_match_score(it->second);
		//get teams 
		string id_first_team, id_second_team;
		do {
			system("cls");
			display_team_name_id();
			cout << "Enter id for the first team : ";
			while (true) {
				cin >> id_first_team;
				if (liga_teams.find(id_first_team) != liga_teams.end())break;
				printf("this team id is not exist..! Enter another team id : ");
			}
			cout << "Enter id for the second team : ";
			while (true) {
				cin >> id_second_team;
				if (liga_teams.find(id_second_team) != liga_teams.end())break;
				printf("this team id is not exist..! Enter another team id : ");
			}
		} while (liga_matches.count(make_pair(id_first_team, id_second_team)));
		it->second.teams_id.first = id_first_team;
		it->second.teams_id.second = id_second_team;
		it->second.change_score();
		break;
	}
	case ('2'): { //update match referee
		cout << "Enter new referee name : ";
		cin >> it->second.match_referee.name;
		it->second.add_to_file(true);
		break;
	}
	case ('3'): { //update match Stadium
		system("cls");
		cout << "Enter new Stadium name : ";
		cin >> it->second.stadium;
		it->second.add_to_file(true);
		break;
	}
	case ('4'): { //update match date
		system("cls");
		cout << "Enter new date : ";
		while (true) {
			cin >> it->second.date;
			if (valid_date(it->second.date))break;
			cout << "Error not valid date ..! Enter new date ";
		}
		it->second.add_to_file(true);
		break;
	}
	case ('5'): { //update status
		it->second.held = false;
		system("cls");
		it->second.change_score();
		it->second.add_to_file(true);
		break;
	}
	case ('6'): { //update match score
		system("cls");
		delete_match_score(it->second);
		it->second.change_score();
		it->second.add_to_file(true);
		break;
	}
	}
}
void match::delete_match_score(match &m) {
	if (!this->held) {
		//change rank of two teams
		if (m.obj_score.first == m.obj_score.second) {
			liga_teams[m.teams_id.first].point--;
			liga_teams[m.teams_id.second].point--;
			liga_teams[m.teams_id.first].Drawn--;
			liga_teams[m.teams_id.second].Drawn--;
		}
		else if (m.obj_score.first>m.obj_score.second) {
			liga_teams[m.teams_id.first].point -= 3;
			liga_teams[m.teams_id.first].won--;
			liga_teams[m.teams_id.second].lost--;
		}
		else {
			liga_teams[m.teams_id.second].won++;
			liga_teams[m.teams_id.first].lost++;
			liga_teams[m.teams_id.second].point += 3;
		}
		//change data of teams { goals for ..against.. .. }
		//change score of playes who scored goals in this match 
		if (m.obj_score.first>0) {
			unsigned short int number_of_goals = m.obj_score.first;
			liga_teams[m.teams_id.first].goal_for -= number_of_goals;
			liga_teams[m.teams_id.second].goals_against -= number_of_goals;
			liga_teams[m.teams_id.first].goal_difference += (m.obj_score.first - m.obj_score.second);
			for (int i = 0; i<number_of_goals; i++) { //first team
				string player_name = m.players_goal[m.teams_id.first][i];
				// get id of player to change his score 
				for (auto it1 = liga_teams[m.teams_id.first].players.begin(); it1 != liga_teams[m.teams_id.first].players.end(); it1++) //get id of first team from teams id in match and search for player name
					if (it1->second.name == player_name) {
						liga_teams[m.teams_id.first].players[it1->second.number].score--;
						liga_players[it1->second.player_id].score--;
						break;
					}
			}
		}
		if (m.obj_score.second>0) {
			unsigned short int number_of_goals = m.obj_score.second;
			liga_teams[m.teams_id.second].goal_for -= number_of_goals;
			liga_teams[m.teams_id.first].goals_against -= number_of_goals;
			liga_teams[m.teams_id.second].goal_difference += (m.obj_score.second - m.obj_score.first);
			for (int i = 0; i<number_of_goals; i++) {
				string player_name = m.players_goal[m.teams_id.second][i];
				// get id of player to change his score 
				for (auto it1 = liga_teams[m.teams_id.second].players.begin();; it1++) //get id of first team from teams id in match and search for player name
					if (it1->second.name == player_name) {
						liga_teams[m.teams_id.second].players[it1->second.number].score--;
						liga_players[it1->second.player_id].score--;
						break;
					}
			}
		}
		replace_data_of_file(m.teams_id.first); //replace data of first team file;
		replace_data_of_file(m.teams_id.second); //replace data of second team file;
												 /*this->add_to_file();*/
	}
}
void match::display_match_in_date() {
	system("cls");
	cout << "Enter date : ";
	string date_search;
	cin >> date_search;
	while (!valid_date(date_search)) {
		cout << "Error ..! invalid date, Enter another date : ";
		cin >> date_search;
	}
	bool find = false;
	for (auto it = liga_matches.begin(); it != liga_matches.end(); it++)
		if (it->second.date == date_search) {
			it->second.display_match();
			find = true;
			cout << "--------------------------------------------------------------\n";
		}
	if (!find)puts("No matches played in this date");
}
void general::display_teams_sorted_by_age() {
	set<pair<double, string>>teams_sorted;
	for (auto it = liga_teams.begin(); it != liga_teams.end(); it++) {
		double team_age = 0.0;
		for (auto it1 = it->second.players.begin(); it1 != it->second.players.end(); it1++) {
			team_age += convert_to_int(it1->second.age);
		}
		team m = it->second;
		teams_sorted.insert(pair<double, string>(team_age / it->second.players.size(), m.id));
	}
	for (auto it = teams_sorted.begin(); it != teams_sorted.end(); it++)
		cout << liga_teams[it->second].team_name << endl;
}
void team::display_team_matches_date()
{
	general::display_team_name_id();
	cout << "Enter team id : ";
	string id;
	cin >> id;
	set<pair<long long, pair<string, string>>>st;
	for (int i = 0; i<liga_teams[id].team_matches.size(); i++) {
		long long tmp = 0;
		string date = liga_teams[id].team_matches[i].date;
		tmp += ((date[0] - 48) * 10) + (date[1] - 48);
		tmp += (((date[3] - 48) * 10) + (date[4] - 48)) * 30;
		int year = ((((date[6] - 48) * 1000) + ((date[7] - 48) * 100) + ((date[8] - 48) * 10) + (date[9] - 48))) * 365;
		st.insert(make_pair(tmp, make_pair(liga_teams[id].team_matches[i].teams_id.first, liga_teams[id].team_matches[i].teams_id.second)));
	}
	cout << st.size() << endl;
	cout << st.begin()->first << endl;
	for (auto it = st.begin(); it != st.end(); it++)
		liga_matches[it->second].display_match();
}
void match::display_all_matches() {

	for (auto it = liga_matches.begin(); it != liga_matches.end(); it++) {
		it->second.display_match();
		cout << "--------------------------------------\n";
	}
}
void general::display_liga() {
	priority_queue<pair<int, string>>teams_sorted;  //string = team id
	for (auto it = liga_teams.begin(); it != liga_teams.end(); it++)
		teams_sorted.push(make_pair(it->second.point, it->first));
	for (int i = 0; i<liga_teams.size(); i++) {
		cout << liga_teams[teams_sorted.top().second].team_name; //name
		for (int i = liga_teams[teams_sorted.top().second].team_name.size(); i<10; i++)
			cout << " ";
		cout << "\xB2 ";
		cout << liga_teams[teams_sorted.top().second].point;
		if (liga_teams[teams_sorted.top().second].point>9)cout << "    ";
		else cout << "     ";
		cout << "\xB2 ";
		cout << liga_teams[teams_sorted.top().second].matches_played;
		if (liga_teams[teams_sorted.top().second].matches_played>9)cout << "    ";
		else cout << "     ";
		cout << "\xB2 ";
		cout << liga_teams[teams_sorted.top().second].won;
		if (liga_teams[teams_sorted.top().second].won>9)cout << "    ";
		else cout << "     ";
		cout << "\xB2 ";
		cout << liga_teams[teams_sorted.top().second].Drawn;
		if (liga_teams[teams_sorted.top().second].Drawn>9)cout << "    ";
		else cout << "     ";
		cout << "\xB2 ";
		cout << liga_teams[teams_sorted.top().second].lost;
		if (liga_teams[teams_sorted.top().second].lost>9)cout << "    ";
		else cout << "     ";
		cout << "\xB2 ";
		cout << liga_teams[teams_sorted.top().second].goal_for;
		if (liga_teams[teams_sorted.top().second].goal_for>9)cout << "    ";
		else cout << "     ";
		cout << "\xB2 ";
		cout << liga_teams[teams_sorted.top().second].goals_against;
		if (liga_teams[teams_sorted.top().second].goals_against>9)cout << "    ";
		else cout << "     ";
		cout << "\xB2 ";
		cout << liga_teams[teams_sorted.top().second].goal_difference << "\n";
		teams_sorted.pop();
	}
}