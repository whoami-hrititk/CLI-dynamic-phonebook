#include <vector>
#include <string>
#include <ncurses.h>
#include <ctype.h>

int x,y;
bool isEdit = false;
bool isRemove = false;

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
	void updateName(std::string new_name){
		name = new_name;
	}
	void updateNumber(std::string new_num){
		number = new_num;
	}
};

std::vector<PhoneBook> phonebook;

char menu[4][19] = {"Create new Contact",
				 "   Edit Contact   ",
				 "  Search Contact  ",
				 "  Remove Contact  "};




int findContact(char* findName, int count, int &select, bool &isSelect){
	echo();
	int i = 0;
	bool isFound = false;
	std::string query(findName);
	
	if (query.empty()) return 0;

	char new_name[30] ;
	char new_num[12];

	for(auto &c : phonebook){
		std::string searchName = c.displayContactName();
		if(searchName.find(query) != std::string::npos){
			if(isSelect && i == select && isEdit){
				clear();
				mvprintw(y/3+4, x/3, "Current Name: %s", c.displayContactName().c_str());
				mvprintw(y/3+5, x/3, "Current Name: %s", c.displayContactNumber().c_str());

				mvprintw(y/3+7, x/3, "New Name: ");
				getnstr(new_name, sizeof(new_name)-1);
				mvprintw(y/3+8, x/3, "New Number: ");
				getnstr(new_num, sizeof(new_num)-1);

				c.updateName(new_name);
				c.updateNumber(new_num);

				mvprintw(y/3+10, x/3-6, "Contact Updated Sucessfully! Press Any KEY to go back..");
				getch();
				clear();
				isSelect = false;
				
				nodelay(stdscr, true);
				return 0;
				
			}
			if(i == select && isRemove && isSelect){
				phonebook.erase(phonebook.begin()+select);
				mvprintw(y/3+10, x/3-6, "Contact Removed Sucessfully! Press Any KEY to go back..");
				getch();
				clear();
				isSelect = false;
				
				nodelay(stdscr, true);
				return 0;
			}
			if(i == select){
			
				attron(COLOR_PAIR(1));
				mvprintw(y/3+4+i, y/3, "Search Result: %s, Contact Info: %s ",
					c.displayContactName().c_str(), c.displayContactNumber().c_str());
				attroff(COLOR_PAIR(1));

			}else
				mvprintw(y/3+4+i, y/3, "Search Result: %s, Contact Info: %s ",
					c.displayContactName().c_str(), c.displayContactNumber().c_str());

			i++;
			isFound = true;
		}
	}

	if(!isFound)
		mvprintw(y/3+4, y/3,"Search Result: Not Found!");
	move(y/3+2, x/3+12+count);
	refresh();
	return i; //Total match found
}



void searchControl(int c, int &select, int match, bool &isSelect){
	if(c == KEY_UP && select > 0) select--;
	else if(c == KEY_DOWN && select < match-1) select++;
	else if((c == 10 || c == KEY_ENTER) && (isEdit || isRemove)) isSelect = true;
	return;
}


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


void searchContact() {
	int c, i = 0;
	int count = 0;
	int select = 0;
	char findName[30] = "";
	bool isSelect = false;

	while (true) {
		
		clear();
		echo();
		curs_set(1);
		attron(A_BOLD);
		mvprintw(y / 3-2, x / 3, "PRESS ESC TO GO BACK..");
		attroff(A_BOLD);
		
		mvprintw(y / 3, x / 3, "Search Contacts:");
		mvprintw(y / 3 + 2, x / 3, "Enter Name: ");
		clrtoeol();
		printw("%s", findName);

		int match = findContact(findName, count, select, isSelect);

		refresh(); 

		c = getch(); 
		nodelay(stdscr, false);
		// ESC key to exit
		if (c == 27) break;

		// Backspace to clear the input
		if ((c == 127 || c == KEY_BACKSPACE) && i > 0) {
			i--;
			findName[i] = ' ';
			count--;
		}
		else if(c == KEY_DOWN || c == KEY_UP || c == KEY_ENTER || c == 10){
			searchControl(c, select, match, isSelect);
		}
		
		else if (std::isprint(c) && i < 29) {
			findName[i++] = static_cast<char>(c);
			findName[i] = '\0';
			count++;
		}
	}
	noecho();
	curs_set(0);
	clear();
	return;
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

void editContact(){
	isEdit = true;
	searchContact();
	isEdit = false;
	return;
}

void removeContact(){
	isRemove = true;
	searchContact();
	isRemove = false;
	return;
}

void controls(int c, int &opt){
	if(c == KEY_UP && opt > 0) opt--;
	else if(c == KEY_DOWN && opt < 3) opt++;
	if(c == 10 && opt == 0) 
		createContact();
	else if(c== 10 && opt == 1)
		editContact();
	else if(c== 10 && opt == 2)
		searchContact();
	else if(c== 10 && opt == 3)
		removeContact();
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
		nodelay(stdscr, false);
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

