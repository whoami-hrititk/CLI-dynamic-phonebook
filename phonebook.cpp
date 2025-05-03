#include <vector>
#include <string>
#include <ncurses.h>
#include <ctype.h>

int x,y;

class PhoneBook{
private:
	std::string name;
	std::string number;
public:
	PhoneBook(std::string name, std::string number): name(name), number(number){}

	std::string displayContactName(){
		return name;
	}
	std::string displayContactNumber(){
		return number;
	}
};

std::vector<PhoneBook> phonebook;

char menu[4][19] = {"Create new Contact",
				 "   Edit Contact   ",
				 "  Search Contact  ",
				 "  Remove Contact  "};

void createContact(){
	clear();
	char temp_name[30];
	char temp_num[12];
	echo();
	curs_set(1);
	mvprintw(y/3,x/3,"Enter the Name: ");
	getnstr(temp_name, sizeof(temp_name)-1);
	mvprintw(y/3+2, x/3, "Enter Mobile Number: ");
	getnstr(temp_num, sizeof(temp_num)-1);

	mvprintw(y/3+5,x/3, "Name: %s",temp_name);
	mvprintw(y/3+6,x/3, "Number: %s",temp_num);
	mvprintw(y/3+10,x/3+2, "Press Any Key To Save..");
	refresh();
	noecho();
	curs_set(0);
	getch();
	PhoneBook contact{std::string(temp_name), std::string(temp_num)};
	phonebook.push_back(contact);
	clear();
	return;
}

void findContact(char* findName){
	echo();
	int i = 0;
	bool isFound = false;
	std::string query(findName);
	
	if (query.empty()) return;

	for(auto c : phonebook){
		std::string searchName = c.displayContactName();
		if(searchName.find(query) != std::string::npos){
			mvprintw(y/3+4+i, y/3, "Search Result: %s, Contact Info: %s ",
				c.displayContactName().c_str(), c.displayContactNumber().c_str());
			i++;
			isFound = true;
		}
	}

	if(!isFound)
		mvprintw(y/3+4, y/3,"Search Result: Not Found!");
}

void searchContact() {
	int c, i = 0;
	char findName[30] = "";

	while (true) {
		clear();
		echo();
		curs_set(1);

		
		mvprintw(y / 3, x / 3, "Search Contacts:");
		mvprintw(y / 3 + 2, x / 3, "Enter Name: ");
		clrtoeol();
		printw("%s", findName);

		
		findContact(findName);

		refresh(); 

		c = getch(); 

		// ESC key to exit
		if (c == 27) break;

		// Backspace to clear the input
		if ((c == 8) && i > 0) {
			i--;
			findName[i] = '\0';
		}
		
		else if (std::isprint(c) && i < 29) {
			findName[i++] = static_cast<char>(c);
			findName[i] = '\0';
		}
	}
}





void showMenu(int opt){
	for(int i = 0; i<4; i++){
		for(int j =0; menu[i][j] != '\0'; j++){
			if(i == opt){
				attron(COLOR_PAIR(1));
					mvaddch((i+y/2)-5, (j+x/2)-10, menu[i][j]);
				attroff(COLOR_PAIR(1));
			} 
			else mvaddch((i+y/2)-5, (j+x/2)-10, menu[i][j]);  
		}
	}
	refresh();
	return;
}

void controls(int c, int &opt){
	if(c == KEY_UP && opt > 0) opt--;
	else if(c == KEY_DOWN && opt < 3) opt++;
	if(c == 10 && opt == 0) 
		createContact();
	else if(c== 10 && opt == 2)
		searchContact();
	return;
}

int main(){
	int c, opt =0;
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	start_color();
	init_pair(1, COLOR_RED, COLOR_YELLOW);
	getmaxyx(stdscr, y,x);
	while(true){
		c = getch();
		if(c == 27) break;
		controls(c, opt);
		showMenu(opt);
	}
	getch();
	refresh();
	endwin();
	return 0;
}

