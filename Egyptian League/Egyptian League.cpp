#include<iostream>
#include<fstream>
#include"liga.h"
using namespace std;
int main()
{
	load();
	while (true) {
		puts("press [1] to enter to team functions");    // -display held matches with date  display held matches  update match information
		puts("press [2] to enter to player functions "); //Done
		puts("press [3] to enter to match functions ");
		puts("press [4] to enter to liga functions ");
		char choice;
		cin >> choice;
		switch (choice) {
		case('1'): {
			bool exit_ = false;
			while (true) {
				system("cls");
				if (exit_)break;
				puts("press [1] to add team");
				puts("press [2] to display team informations");
				puts("press [3] to update team informations");
				puts("press [4] to search for a team using (ID or name)");
				puts("press [5] to display team players");
				puts("press [6] to display team detailed score");
				puts("press [7] to display team matches");
				puts("press [8] to display held matches");
				puts("press [0] to return");
				char choice;
				cin >> choice;
				switch (choice) {
				case('1'): {    //add team 
					while (true) {
						system("cls");
						team m;
						m.add();
						system("cls");
						puts("added successfully\n");
						puts("press [1] to add another team");
						puts("press [2] to return to team functions");
						char choice;
						cin >> choice;
						while (!(choice == '1' || choice == '2')) {
							system("cls");
							puts("wrong ..!");
							puts("press [1] to add another team");
							puts("press [2] to return to team functions");
							cin >> choice;
						}
						if (choice == '2')break;
					}
					break;
				}//case(1)
				case('2'): {        //display team information 
					while (true) {
						team m;
						m.display_team_info();
						puts("press [1] to search for another team");
						puts("press [2] to return to team functions ");
						string choice;
						cin >> choice;
						if (choice == "2")break;
					}
					break;
				}//case(2)
				case('3'): {          //update team
					while (true) {
						system("cls");
						team m;
						m.update_team();
						puts("press [1] to update another team");
						puts("press [2] to go on");
						string choice;
						cin >> choice;
						while (!(choice == "1" || choice == "2")) {
							puts("wrong..!");
							puts("press [1] to update another team");
							puts("press [2] to go on");
							cin >> choice;
						}
						if (choice == "2")break;
					}
					break;
				}//case(3)
				case('4'): {   //search for a team
					while (true) {
						system("cls");
						team m;
						m.search_team();
						puts("press [1] to search for another team ");
						puts("press [2] to go on ");
						string choice;
						while (true) {
							cin >> choice;
							if (choice == "1" || choice == "2")break;
							system("cls");
							puts("wrong..!");
							puts("press [1] to search for another team ");
							puts("press [2] to go on ");
						}
						if (choice == "2")break;
					}
					break;
				}//case(4)
				case('5'): {  //display team players
					while (true) {
						system("cls");
						team m;
						m.display_team_players();
						puts("press [1] to display another team players ");
						puts("press [2] to go on ");
						string choice;
						while (true) {
							cin >> choice;
							if (choice == "1" || choice == "2")break;
							system("cls");
							puts("wrong..!");
							puts("press [1] to search for another team ");
							puts("press [2] to go on ");
						}
						if (choice == "2")break;
					}
					break;
				}//case(5)
				case('6'): {    //display team detailed score
					while (true) {
						system("cls");
						team m;
						m.display_rank_team();
						puts("press [1] to display another team players ");
						puts("press [2] to go on ");
						string choice;
						while (true) {
							cin >> choice;
							if (choice == "1" || choice == "2")break;
							system("cls");
							puts("wrong..!");
							puts("press [1] to search for another team ");
							puts("press [2] to go on ");
						}
						if (choice == "2")break;
					}
					break;
				}//case(6)
				case('7'): {   //display team matches
					while (true) {
						system("cls");
						team m;
						m.display_team_matches();
						puts("press [1] to display another team players ");
						puts("press [2] to go on ");
						string choice;
						while (true) {
							cin >> choice;
							if (choice == "1" || choice == "2")break;
							system("cls");
							puts("wrong..!");
							puts("press [1] to search for another team ");
							puts("press [2] to go on ");
						}
						if (choice == "2")break;
					}
					break;
				}//case(7)
				case('8'): {
					system("cls");
					team t;
					t.display_team_matches_date();
					string tmp;
					cout << "press to continue";
					cin >> tmp;
					break;
				}//case(8)
				case('0'): {
					exit_ = true;
					break;
				}//case(0)
				default: {

				}//default
				}//switch(case(team))
			}//while(case(team))
			break;
		}//case team
		case('2'): {
			bool exit_ = false;
			while (true) {
				system("cls");
				if (exit_)break;
				puts("press [1] to add player");
				puts("press [2] to display player");
				puts("press [3] to display player role");
				puts("press [4] to update player information");
				puts("press [5] to Search for player using (Number+Name+Team).");
				puts("press [0] to return");
				char choice;
				cin >> choice;
				switch (choice) {
				case('1'): { //add player
					while (true) {
						player p;
						p.add();
						system("cls");
						puts("player added succefully");
						puts("press [1] to add another player ");
						puts("press [2] to go on ");
						string choice;
						cin >> choice;
						while (!(choice == "1" || choice == "2")) {
							system("cls");
							puts("wrong..!");
							puts("press [1] to add another player ");
							puts("press [2] to go on ");
							cin >> choice;
						}
						if (choice == "2")break;
					}
					break;
				}
				case('2'): { //display player
					player p;
					p.display_all_players();
					printf("press to continue : ");
					int tmp;
					cin >> tmp;
					break;
				}
				case('3'): { //display player role
					while (true) {
						player p;
						system("cls");
						p.display_player_role();
						puts("press [1] to display another player role ");
						puts("press [2] to go on ");
						string choice;
						cin >> choice;
						while (!(choice == "1" || choice == "2")) {
							system("cls");
							puts("wrong..!");
							puts("press [1] to display another player role ");
							puts("press [2] to go on ");
							cin >> choice;
						}
						if (choice == "2")break;
					}
					break;
				}
				case('4'): { //update player
					while (true) {
						system("cls");
						player p;
						p.update_player();
						puts("press [1] to update another player data");
						puts("press [2] to go on");
						string choice;
						cin >> choice;
						while (!(choice == "1" || choice == "2")) {
							puts("wrong..!");
							puts("press [1] to update another player data");
							puts("press [2] to go on");
							cin >> choice;
						}
						if (choice == "2")break;
					}
					break;
				}
				case('5'): { // search for player
					while (true) {
						player p;
						system("cls");
						p = p.search_player();
						p.display_player();
						//p.display_player(p.search_player());
						puts("press [1] to search for another player ");
						puts("press [2] to go on ");
						string choice;
						cin >> choice;
						while (!(choice == "1" || choice == "2")) {
							system("cls");
							puts("wrong..!");
							puts("press [1] to add another player ");
							puts("press [2] to go on ");
							cin >> choice;
						}
						if (choice == "2")break;
					}
					break;
				}
				case('0'): { //return
					exit_ = true;
					break;
				}
				}//switch(case(2))
			}//while(case(2))
			break;
		}//case player 
		case('3'): {
			bool exit_ = false;
			while (true) {
				system("cls");
				if (exit_)break;
				puts("press [1] to add match intformation");
				puts("press [2] to display all matches");
				puts("press [3] to display held matches");
				puts("press [4] to update match information");
				puts("press [0] to return");
				char choice;
				cin >> choice;
				switch (choice) {
				case('1'): {  //add match
					while (true) {
						match m;
						m.add();
						system("cls");
						puts("match added succefully");
						puts("press [1] to add another player ");
						puts("press [2] to go on ");
						string choice;
						cin >> choice;
						while (!(choice == "1" || choice == "2")) {
							system("cls");
							puts("wrong..!");
							puts("press [1] to add another player ");
							puts("press [2] to go on ");
							cin >> choice;
						}
						if (choice == "2")break;
					}
					break;
				}//case(1)case(3)
				case('2'): {  //display all matches
					system("cls");
					match m;
					m.display_all_matches();
					string tmp;
					puts("press to continue");
					cin >> tmp;
					break;
				}//case(2)case(3)
				case('3'): {  //display held matches
					break;
				}//case(3)case(3)
				case('4'): { //update match
					while (true) {
						system("cls");
						match m;
						m.update_match();
						puts("press [1] to update another match data");
						puts("press [2] to go on");
						string choice;
						cin >> choice;
						while (!(choice == "1" || choice == "2")) {
							puts("wrong..!");
							puts("press [1] to update another match data");
							puts("press [2] to go on");
							cin >> choice;
						}
						if (choice == "2")break;
					}
					break;
				}//case(4)case(3)
				case('0'): {
					exit_ = true;
					break;
				}//case(1)case(3)
				}//switch(case(3))
			}//while(case(3))
			break;
		}//case match
		case('4'): {
			bool exit_ = false;
			while (true) {
				system("cls");
				if (exit_)break;
				puts("press [1] to display teams ordered by their points");
				puts("press [2] to display top (3) players who score the greatest no of goals");
				puts("press [3] to display top (3) goalkeepers who have the fewest no of goals");
				puts("press [4] to display top (3) players ordered by their ranks");
				puts("press [5] to display teams ordered by no. of scored goals");
				puts("press [6] to display teams ordered by the average ages of its players");
				puts("press [7] to display matches in a certain date ");
				puts("press [8] to display liga ");
				puts("press [0] to return");
				char choice;
				cin >> choice;
				switch (choice) {
				case('1'): { //display teams ordered by their points
					general R;
					system("cls");
					R.display_team_ordered_by_point();
					string tmp;
					puts("press to continue");
					cin >> tmp;
					break;
				}//case(1)
				case('2'): { //display top (3) players who score the greatest no. of goals
					general R;
					system("cls");
					R.display_top_players();
					string tmp;
					puts("press to continue");
					cin >> tmp;
					break;
				} //case(2)
				case('3'): { //display top (3) goalkeepers who have the fewest no of goals
					general R;
					system("cls");
					R.display_top_rank_player();
					string tmp;
					puts("press to continue");
					cin >> tmp;
					break;
				}//case(3)
				case('4'): { // display top (3) players ordered by their ranks
					general R;
					system("cls");
					R.display_top_rank_player();
					string tmp;
					puts("press to continue");
					cin >> tmp;
					break;
				}//case(4)
				case('5'): { //to display teams ordered by no. of scored goals
					general R;
					system("cls");
					R.sort_teams_by_goals();
					string tmp;
					puts("press to continue");
					cin >> tmp;
					break;
				} //case(5)
				case('6'): { //display teams ordered by avg age
					system("cls");
					general R;
					R.display_teams_sorted_by_age();
					string tmp;
					puts("press to continue");
					cin >> tmp;
					break;
				}//case(6)
				case('7'): { //display matches in a certain date
					match m;
					system("cls");
					m.display_match_in_date();
					string tmp;
					puts("press to continue");
					cin >> tmp;
					break;
				}//case(7)
				case('8'): {
					system("cls");
					general R;
					R.display_liga();
					string tmp;
					puts("press to continue");
					cin >> tmp;
					break;
				}
				case('0'): {
					exit_ = true;
					break;
				}
				}//switch(case(4))
			}//while(case(4))	
		}//case liga functions
		default: {
			system("cls");
		}//default 
		}//main switch
	}//main while
	return 0;
}