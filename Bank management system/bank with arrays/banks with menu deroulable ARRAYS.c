#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>

int demarage=0;
int yann=100;
int counting=0;
void new_acct();				//to create new account
void back2menu();				//propose to continue or back to menu
void depot(int it);				//to initialise deposit
void retrait(int it);			//To initialise withdrawal
void virement(int it);			//to initialise transfer
void transac();					//To asked transaction wished
void update();					//to update acct information
int Menu(int x,int y,int c);	//to display menu
void gotoxy(int x, int y);		//move to a point
void color(int t, int f);		//to color a text and its background
void customer();				//ask the customer to contact the customer service after 3 login trials
float interest(float amount,int t);			//to calculate interest
float montant(float amount, int t);			//To calculate amt to refund
void loan();					//Display when customer asks for a loan
void cadre(int x1, int x2, int y1, int y2, int c,int t, char m[30]);			//Display borders
int current_day();				//return current day
int current_month();			//return current month
int current_year();				//return current year
void historywrite(int i, char trans[15], float monte);			//write transactions details in a text file
void historyread(int i);		//read transaction details from a text file
void history();					//display history of account
int login();					//Login to account before any operation
void disp_acct_info(int i);		//display acccount information
void acct_info();				//same as disp_acct_info
void enter_update(int i);		//To change account information
void acct_del();


struct date {
	int day;
	int month;
	int year;
};

struct client {
	char name[50];
	double tel;
	struct date age;
	char profession[15];
	unsigned int acct_no;
	char passwd[10];
	char chk_passwd[10];
	float amt;
} pipo[5000];

int main() {
	if(demarage==0) {
	system("cls");
	cadre(30,80,1,25,1,0,"");
	color(15,0);
	gotoxy(45,5); puts("        $$$");
	gotoxy(45,6); puts("     $$$$$$$$$");
	gotoxy(45,7); puts("   $$$  $$$  $$$");
	gotoxy(45,8); puts("  $$$   $$$   $$$");
	gotoxy(45,9); puts(" $$$    $$$   $$$");
	gotoxy(45,10);puts("  $$$   $$$  $$$");
	gotoxy(45,11);puts("    $$$ $$$");
	gotoxy(45,12);puts("     $$$$$$");
	gotoxy(45,13);puts("        $$$$$$$");
	gotoxy(45,14);puts("        $$$  $$$");
	gotoxy(45,15);puts("$$$     $$$   $$$");
	gotoxy(45,16);puts(" $$$    $$$  $$$");
	gotoxy(45,17);puts("  $$$   $$$ $$$");
	gotoxy(45,18);puts("    $$$$$$$$$$");
	gotoxy(45,19);puts("        $$$");
	gotoxy(1,28);color(4,0);system("pause");
	}
	system("cls");
	demarage++;
	int choice;
	while(yann==100) {
		system("cls");
		cadre(5, 50, 1, 28, 9, 0, "Menu" );
		cadre(55, 115, 1, 19, 9, 0, "");
		choice=Menu(10,3,7);
		switch(choice) {
			case 0:
				new_acct();//TODO
				break;
			case 1:
				acct_info();//TODO
				break;
			case 2:
				transac();
				break;
			case 3:
				history();
				break;
			case 4:
				update();
				break;
			case 5:
				acct_del();
				break;
			case 6:
				exit(1);
				break;
			default:
				puts("please select among the alternatives\n\n");
				system("pause");
				system("cls");
				main();//TODO
				break;
		}
	}
	return 0;
}

//fxn to create new account
void new_acct() {
	unsigned int r;
	cadre(55, 115, 1, 19, 9, 0, "Create_an_account");
	color(15,0);
	gotoxy(58,3);printf("Enter your name please: "); //Enter name
	scanf("%s", pipo[counting].name);
	gotoxy(58,4);printf("Enter your phone number: "); //phone number
	scanf("%f", &pipo[counting].tel);
	gotoxy(58,5);printf("Enter profession: "); //enter profession
	scanf("%s", pipo[counting].profession);
	gotoxy(58,6);printf("Please enter date of birth (dd/mm/yy): "); //date of birth
	scanf("%d/%d/%d", &pipo[counting].age.day, &pipo[counting].age.month, &pipo[counting].age.year);
verifagain:
	gotoxy(58,7);printf("Enter a password: ");
	scanf("%s", pipo[counting].passwd);
	if(counting!=0) {			//to verify if password entered is unique
		for(int i=counting-1; i>=0; i--) {
			if(strcmp(pipo[counting].passwd,pipo[i].passwd)==0) {
				gotoxy(58,8);printf("Password already taken, please enter another one\n");
				system("pause");
				goto verifagain;
			}
		}
	}
	gotoxy(58,8);printf("Please enter the same password for verification: ");	//To verify password
	scanf("%s", pipo[counting].chk_passwd);
	if(strcmp(pipo[counting].passwd, pipo[counting].chk_passwd)!=0) {   //to verify if password and verification match
		gotoxy(58,9);printf("The password and the verification don't match! Try again!\n");
		goto verifagain;
	}
	gotoxy(58,9);printf("Now enter your first deposit (25000 mininum): ");
	scanf("%f", &pipo[counting].amt);
	while(pipo[counting].amt<25000) {    //first deposit is minim 25000
		gotoxy(58,10);printf("deposit is below what required, try another amount: ");
		scanf("%f", &pipo[counting].amt);
	}
	srand((unsigned)time(NULL));
verifno:
	r=rand();
	r=(r%100000000)+1;  //generates random account number
	for(int i=counting; i>=0; i--) {   	//ensures account number is unique
		if(r==pipo[i].acct_no) {
			goto verifno;
		}
	}
	pipo[counting].acct_no=r;
	historywrite(counting, "First_Deposit", pipo[counting].amt);		//stores first deposit in record
	gotoxy(58,10);printf("Account number is: %u", pipo[counting].acct_no);
	gotoxy(58,11);puts("Account created!!");
	gotoxy(1,29);color(4,0);system("pause");
	counting++;
	system("cls");
	main();
}

//asks if customer wants to continue or go back to menu
void back2menu() {
	printf("\n_______Continue? (y/n): ");
	char response;
	scanf("%s", &response);
	if (response == 'n') {
		main();
	}
}

//fxn to do a deposit
void depot(int it) {
	system("cls");
	cadre(55, 115, 1, 19, 9, 0, "Deposit");
	cadre(55, 115, 21, 28, 9, 0, "Info");
	color(15,0);
	float moni;
	gotoxy(58,5);printf("Please enter the amount you want to deposit: ");
	scanf("%f", &moni);
	pipo[it].amt+=moni;			//add amount entered to amount in account
	gotoxy(58,23);printf("Amount deposited");
	gotoxy(58,25);printf("Your new account now contains: %.2f", pipo[it].amt);
	historywrite(it, "deposit", moni);			//stores transaction in record
	gotoxy(1,29);color(4,0);system("pause");
}

//fxn to do a withdrawal
void retrait(int it) {
	float moni;
back:
	system("cls");
	cadre(55, 115, 1, 19, 9, 0, "Withdrawal");
	cadre(55, 115, 21, 28, 9, 0, "Info");
	color(15,0);
	gotoxy(58,5);printf("Please enter the amount you want to retrieve: ");
	scanf("%f", &moni);
	if(moni>pipo[it].amt) {
		gotoxy(58,25);printf("Can't withdraw; not enough in account");	//not enough in account
		gotoxy(1,29);color(4,0);system("pause");
		system("cls");
		gotoxy(58,7);back2menu();
		system("cls");
		goto back;
	}
	pipo[it].amt=pipo[it].amt-moni;			//reduce amount entered to one in account
	gotoxy(58,25);printf("Your new account now contains: %.2f", pipo[it].amt);		//display new account balance
	historywrite(it, "withdrawal", moni);			//stores transaction in record
	gotoxy(1,29);color(4,0);system("pause");
}

//fxn to do a transfer
void virement(int it) {
	float moni;
	char verifname[50];
	unsigned int verifnum;
	system("cls");
	cadre(55, 115, 1, 19, 9, 0, "Transfer");
	cadre(55, 115, 21, 28, 9, 0, "Info");
	color(15,0);
	gotoxy(58,3);printf("How much do you want to transfer? ");
	scanf("%f", &moni);
	while(moni>pipo[it].amt) {
		gotoxy(58,4);printf("Can't withdraw; not enough in account");		//not enough in account
		gotoxy(58,5);printf("Try again: ");
		scanf("%f", &moni);
	}
score:
	gotoxy(58,6);printf("Enter the name of the destinating account: ");		//entering account ID of destinator
	scanf("%s", verifname);
	gotoxy(58,7);printf("Enter the number of destinating account: ");		//entering account ID of destinator
	scanf("%u", &verifnum);
	int cnt=0;
	for(int i=0; i<=5000-1; i++) {		//checking correct account ID of destinator
		if(strcmp(verifname, pipo[i].name)==0) {
			cnt=cnt+1;
		}
		if(verifnum==pipo[i].acct_no) {
			cnt=cnt+1;
		}
		if(cnt==2) {
			pipo[it].amt=pipo[it].amt-moni;		//tranfering money to other account
			pipo[i].amt+=moni;
			gotoxy(58,23);puts("Transaction Done!!");
			gotoxy(58,5);printf("Your new balance is %.2f", pipo[it].amt);		//displaying account balance
			historywrite(it, "transfer", moni);
			historywrite(i, "transfer", moni);
			gotoxy(1,29);color(4,0);system("pause");
			system("cls");
			main();
		}
	}
	gotoxy(58,23);puts("wrong identifiants!!");
	Sleep(2000);
	gotoxy(58,7);back2menu();
	system("cls");
	goto score;
}

//fxn to do a transaction
void transac() {
	int choice;
	int i;
	system("cls");
	cadre(55, 115, 1, 19, 9, 0, "Transactions");
	cadre(55, 115, 21, 28, 9, 0, "Info");
	color(15,0);
	gotoxy(58,3);puts("What transaction do you want to do? ");
	gotoxy(58,4);puts("1.Do a Deposit");
	gotoxy(58,5);puts("2.Do a withdrawal");
	gotoxy(58,6);puts("3.Do a Transfer");
	gotoxy(58,7);puts("4.Take a loan");
	gotoxy(58,8);printf("Your choice: ");
	scanf("%d", &choice);
	if(choice==1) {
		system("cls");
		i=login();			//login into account
		system("cls");
		depot(i);			//initialise transaction
		system("cls");
		main();
	} else if(choice==2) {
		system("cls");
		i=login();			//login into account
		system("cls");
		retrait(i);			//initialise transaction
		system("cls");
				main();
	} else if(choice==3) {
		system("cls");
		i=login();			//login into account
		system("cls");
		virement(i);		//initialise transaction
		system("cls");
				main();
	}
	else if(choice==4){
		system("cls");
		i=login();			//login into account
		system("cls");
		loan();				//initialise transaction
		system("cls");
				main();
	}
	else {
		gotoxy(58,9);("PLease select among the alternatives!");
		gotoxy(1,29);color(4,0);system("pause");
		system("cls");
		transac();
	}
}

void update() {
	system("cls");
	int i=login();		//login into account
	enter_update(i);	//update account info
}

void color(int t,int f) {
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,f*16+t);
}

void gotoxy(int x, int y) {
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	//cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

int Menu(int x,int y,int c) {
	char M[7][100]= {"1.Create a new account				\n","2.Check Account Information				\n","3.Do a transaction				\n","4.View account listing				\n","5.Update account info				\n", "6.Delete Account				\n", "7.EXIT				"};
	int i,k=0,t;
	do {
		for(i=0; i<7; i++) {
			if(i==k) {
				color(15,9);		//color of present cursor
			} else {
				color(15,0);		//color of other options
			}
			gotoxy(x+1,y+1+i);
			puts(M[i]);
		}
		t=getch();
		if(t==80) {
			k++;
			k=k%7;
		}
		if(t==72) {
			if(k==0) {
				k=6;
			} else {
				k--;
			}
		}
	} while(t!=13);
	return k;
}

void customer() {
	printf("Any problem accessing account or forgot account ID? Please contact customer service\n");
	system("pause");
	main();
}

float interest(float amount,int t){
	float r=10.5;
    float SI;
	    SI=(r*amount)/100.0;		//calculates interest per month
	    return (SI/(12.0));
}

float montant(float amount, int t){
	int peri;
	peri=12*t;
	return (amount/peri);
}

void loan(){
	system("cls");
	cadre(55, 115, 1, 19, 9, 0, "Loan");
	cadre(55, 115, 21, 28, 9, 0, "Info");
	color(15,0);
	float somme;
	int period;
	float remboursement;
	gotoxy(58,3);printf("How much do you want as credit: ");
	scanf("%f", &somme);
	gotoxy(58,4);printf("This loan is over a period of how many years: ");
	scanf("%d", &period);
	remboursement=interest(somme, period)+montant(somme, period);
	gotoxy(58,23);printf("Your request has been taken into account ");
	gotoxy(58,24);printf("and will be forwarded to the database for treatment");
	gotoxy(58,25);printf("In case your request is fulfilled, for ");
	gotoxy(58,25);printf("your loan you will be charged %.2f per months for %d years", remboursement, period);
	gotoxy(1,29);color(4,0);system("pause");
}

void cadre(int x1, int x2, int y1, int y2, int c,int t, char m[30]){
    color(c, t);
    for (int i = x1; i < x2; i++)
    {
        gotoxy(i, y1);
        printf("%c", 220);
        gotoxy(i, y2);
        printf("%c", 223);
    }
    for (int i = y1; i < y2 + 1; i++)
    {
        gotoxy(x1, i);
        printf("%c", 219);
        gotoxy(x2, i);
        printf("%c", 219);
    }

    gotoxy(x1 + 2, y1);
    printf("%s", m);

    gotoxy(x1, y1);
    printf("%c", 220);
    gotoxy(x2, y1);
    printf("%c", 220);
    gotoxy(x1, y2);
    printf("%c", 223);
    gotoxy(x2, y2);
    printf("%c", 223);
    color(c, t);
}

int current_day(){
	time_t t = time(NULL);
	    struct tm tm = *localtime(&t);
	    int year = tm.tm_year + 1900;
	    int month = tm.tm_mon + 1;
	    int day = tm.tm_mday;
	    return day;
}

int current_month(){
	time_t t = time(NULL);
	    struct tm tm = *localtime(&t);
	    int year = tm.tm_year + 1900;
	    int month = tm.tm_mon + 1;
	    int day = tm.tm_mday;
	    return month;
}

int current_year(){
	time_t t = time(NULL);
	    struct tm tm = *localtime(&t);
	    int year = tm.tm_year + 1900;
	    int month = tm.tm_mon + 1;
	    int day = tm.tm_mday;
	    return year;
}

void historywrite(int i, char trans[15], float monte){
	FILE *fptr;
	    char usrID[15];

	    sprintf(usrID, "%u.txt", pipo[i].acct_no);		//creates text file with account number of user as name

	    fptr = fopen(usrID, "a+");

	    if (fptr == NULL) {
	        printf("Error opening file!");
	        exit(1);
	    }
	    //writes user transactions information to file
	    fprintf(fptr, "\t%s\t%.2f\t%d-%d-%d\n", trans, monte, current_day(), current_month(), current_year());

	    fclose(fptr);
}

void historyread(int i){
	FILE *fptr;
		    char usrID[15], transi[15];
		    int day, month, year;
		    float monte;
		    system("cls");
			cadre(55, 115, 1, 28, 9, 0, "History");
			color(15,0);

		    sprintf(usrID, "%u.txt", pipo[i].acct_no);

		    fptr = fopen(usrID, "r");

		    if (fptr == NULL) {
		        printf("Error opening file!");
		        exit(1);
		    }
		    gotoxy(58,3);printf("User: %u", pipo[i].acct_no);
		    gotoxy(58,4);printf("\ttransaction\tamount  \tdate");
			int line=1;
			//read content of text file till the end of the file
		    while(fscanf(fptr, "%s %f %d-%d-%d", transi, &monte, &day, &month, &year)!=EOF) {
			gotoxy(58,4+line);printf("\t%s  \t%.2f\t%d-%d-%d", transi, monte, day, month, year);	//print each line
			line++;
			}
		    fclose(fptr);
		    gotoxy(1,29);color(4,0);system("pause");
			system("cls");
			main();
}

void history(){
	int i;
	i=login();			//login into account
	system("cls");
	historyread(i);		//display account history
}

int login(){
	char nameverif[50];
		unsigned int numverif;
		char passverif[10];
		int conteur=0;
	markeur:
		system("cls");
		cadre(55, 115, 1, 19, 9, 0, "Login");
		cadre(55, 115, 21, 28, 9, 0, "Info");
		color(15,0);
		gotoxy(58,3);printf("Please enter the account name: ");		// the login into account
		scanf("%s", nameverif);
		gotoxy(58,4);printf("please enter your account number: ");
		scanf("%u", &numverif);
		gotoxy(58,5);printf("Please enter password: ");
		scanf("%s", passverif);
		int cnt=0;
		for(int i=0; i<=5000-1; i++) {			//check if entered info correspond to an account
			if(strcmp(nameverif, pipo[i].name)==0) {
				cnt=cnt+1;
			}
			if(numverif==pipo[i].acct_no) {
				cnt=cnt+1;
			}
			if(strcmp(passverif, pipo[i].passwd)==0) {
				cnt=cnt+1;
			}
			if(cnt==3) {		//if all info are correct
				return i;
			}
		}
		gotoxy(58,23);puts("wrong identifiants!!");
		Sleep(2000);
		system("cls");
		conteur++;
		if(conteur==3) {		//if wrong ID entered thrice, go to menu
			customer();
		}
		gotoxy(58,7);back2menu();
		system("cls");
		goto markeur;

}

void disp_acct_info(int i){
gotoxy(58,23);printf("welcome user: %s", pipo[i].name);
			gotoxy(58,24);printf("Account number: %u", pipo[i].acct_no);
			gotoxy(58,25);printf("You have %.2f $ left", pipo[i].amt);
			gotoxy(1,29);color(4,0);system("pause");
			system("cls");
}

void acct_info(){
	int i;
	i=login();		//login into account
	disp_acct_info(i);		//displays account info
}

void enter_update(int i){
	system("cls");
				cadre(55, 115, 1, 19, 9, 0, "Update");
				cadre(55, 115, 21, 28, 9, 0, "Info");
				color(15,0);
				int cho;
				char check[10];
				gotoxy(58,3);puts("What do you want to change?");
				gotoxy(58,4);puts("1.The name of account");
				gotoxy(58,5);puts("2.The password account");
				gotoxy(58,6);printf("3.Owner phone number; Your choice:");
				scanf("%d", &cho);
				if(cho==2) {
					gotoxy(58,7);printf("Enter old password: ");
					scanf("%s", check);
					while(strcmp(check, pipo[i].passwd)!=0) {		//checks if what entered is the same
						gotoxy(58,8);printf("Wrong entry try again: ");
						scanf("%s", check);
					}
					gotoxy(58,9);printf("Enter new password: ");
					scanf("%s", pipo[i].passwd);
					gotoxy(58,23);puts("Congrats, password changed");
					gotoxy(1,29);color(4,0);system("pause");
					system("cls");
					main();
				} else if(cho==1) {
					char namverif[50];
					color(15,0);
					gotoxy(58,7);printf("Enter old name: ");
					scanf("%s", namverif);
					while(strcmp(namverif, pipo[i].name)!=0) {
						gotoxy(58,8);printf("\nWrong entry try again: ");
						scanf("%s", namverif);
					}
					gotoxy(58,9);printf("Enter new name: ");
					scanf("%s", pipo[i].name);
					gotoxy(58,23);puts("Congrats name changed!");
					gotoxy(1,29);color(4,0);system("pause");
					system("cls");
					main();
				} else if(cho==3) {
					double telverif;
					color(15,0);
					gotoxy(58,7);printf("Enter old phone number: ");
					scanf("%f", &telverif);
					while(telverif!=pipo[i].tel) {
						gotoxy(58,8);printf("Wrong entry try again: ");
						scanf("%f", &telverif);
					}
					gotoxy(58,9);printf("Enter new phone number: ");
					scanf("%f", pipo[i].tel);
					gotoxy(58,23);puts("Congrats phone number  changed!");
					gotoxy(1,29);color(4,0);system("pause");
					system("cls");
					main();
				} else {
					color(15,0);
					gotoxy(58,7);puts("Enter among alternatives please: ");
					system("cls");
					update();
				}
}

void acct_del(){
	int i;
	char resp;
	i=login();
	system("cls");
	cadre(55, 115, 1, 19, 9, 0, "Delete_account");
	cadre(55, 115, 21, 28, 9, 0, "Info");
	color(15,0);
	gotoxy(58,5);printf("Are you sure you want to delete? ");
	scanf("%s", &resp);
	if(resp=='y') {
		pipo[i].acct_no=0;
		pipo[i].amt=0.00;
	gotoxy(58,25);printf("Account deleted successfully!!");
	Sleep(2000);
	}
	system("cls");
	main();
}