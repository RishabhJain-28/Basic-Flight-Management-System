#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<iomanip>

using namespace std;

fstream fio;
int staff_menu();
int pass();
int menu();
void iint(int &a) ;

int ch=0;

void iint(int &a){

	while(	!(cin>>a)){

		cout<<"Enter again: ";

		cin.clear(); 

		while (cin.get() !='\n') continue;

	}

	

}

class Ticket{
	char cname[20];
	int age;
	char phone[11];
	char type;
	int ticket_no;
	int fair;


public:	int flight_no;
	int get_details();
	void assign_ticket();
	
	int book_ticket();
	int dele_booking();
	int mod_booking();
	void disp_bookings();
	
	void set_fair(){
	
	if(type=='b')fair=6000;
	else if(type=='e')fair=2500;
	else {fair=4000;
		type='r';
		}
	}
};
Ticket t;

class Flight{
	
	char to[10];
	char from[10];
	int capacity;
	int flight_no;
	char date[11],time[6];
	

	
public:int pass_count;
	Flight(){capacity=10;
	pass_count=0;
	}


	void get_details();
	void disp_flights(int flag);
	int cap_check();
	int delete_flight();
	int modify_flights();
	void create_flight();
	int reduce_pass(int );
};

Flight f;
void Flight::create_flight(){
	


	fio.open("flights.dat",ios::app| ios::binary);
	pass_count=0;

	fio.write((char *)&f,sizeof(f));

	fio.close();

}
void Flight::disp_flights(int flag=1){

	fio.open("flights.dat",ios::in | ios::binary);

	cout<<"Flight Number"<<"\t\t"<<"From"<<"\t\t"
		<<"To"<<"\t\t "<<" Passenger count"<<"\t   "<<"Capacity\t"
		<<"Date\t\t"<<" Time\n";

	while(fio.read((char *)&f,sizeof(f))){

		
		if(flag || !(pass_count == capacity) ){
		
			cout<<flight_no<<"\t\t\t"
				<<setw(10)<<left<<from<<"\t"
				<<setw(10)<<left<<to<<"\t\t\t"
				<<pass_count<<"\t\t"
				<<capacity<<"\t"
				<<setw(10)<<left<<date<<"\t "
				<<time
				<<endl;

		}
		
	}

	fio.close();

	cout<<endl;

	

}

void Flight::get_details(){
	int a=1,flag=1;
		
			fio.open("flights.dat",ios::in|ios::binary);
		while(1){
		
			while(fio.read((char *)&f,sizeof(f))){
			
			if(a ==flight_no)
			{
				flag=0;
				break;
			}else flag=1;
		
			}
			if(flag)break;
		
		a++;
		fio.seekg(0);
		
		
	}
	fio.close();
		flight_no=a;
	
	
		cout<<"From(Max !0 charecters): ";
		cin.ignore();
		gets(from);
		cout<<"To(Max !0 charecters): ";
		
		gets(to);

		cout<<"Capacity: ";
		iint(capacity);
		while(capacity<=0){
			cout<<"Capacity can not be negative\nEnter again:";
			iint(capacity);
			
		}
		cin.ignore();
		cout<<"Enter Date:";
		gets(date);	
		cout<<"Enter Time:";
		gets(time);
	
		cout<<"Flight number: ";
		cout<<flight_no<<endl;
	
	}
	
int Flight::cap_check(){
	
		int flag=1;
	
		fio.open("flights.dat",ios::in|ios::out| ios::binary);
		
		while(fio.read((char *)&f,sizeof(f)))
		{
			if(flight_no== t.flight_no && pass_count<capacity ){
				pass_count++;
				long pos;
				
				pos=fio.tellg();
				pos-=sizeof(f);
				fio.seekg(pos);
	
					fio.write((char *)&f,sizeof(f));
				
				flag=0;
			}
		}
		

		fio.close();
		pass_count=0;
	return flag;
}
int Flight::modify_flights(){
	fstream fiot;
		int n;
	cout<<"Enter Flight Number to be modified:";
	
	iint(n);
	
	
	fiot.open("flights.dat",ios::in | ios::out| ios::binary);
	
	int i;
	while(fiot.read((char*)&f,sizeof(f))){
		if(n==flight_no){
		cout<<"Enter new capacity:";
		
		
		iint(capacity);
		while(capacity<=0 || capacity<pass_count){
			cout<<"Enter again:";
			iint(capacity);
			
		}
		
		long pos;			
	pos=fiot.tellg();
	pos-=sizeof(f);
	fiot.seekg(pos);
	fiot.write((char *)&f,sizeof(f));
	fiot.close();
	cout<<"flight modified\n";
	
	return 0;
		
		}
	}

	cout<<"flight not found\n";
}

int Flight::reduce_pass(int n ){
	fio.open("flights.dat",ios::in | ios::out| ios::binary);
	
	while(fio.read((char*)&f,sizeof(f))){
	if(f.flight_no==n){
	
	if(f.pass_count)
	f.pass_count--;
	
	long pos;		
	pos=fio.tellg();
	pos-=sizeof(f);
	fio.seekg(pos);
	
	fio.write((char *)&f,sizeof(f));
	
		fio.close();
	break;
	
			} 
		}

	
}
	

int Flight::delete_flight(){
	int n,flag=1 ,i=0;
	ofstream fo;
	fio.open("flights.dat",ios::in | ios::binary);
	fo.open("temp.dat",ios::out | ios::binary);
	
	cout<<"Enter flight number to be deleted: ";
	iint(n);
	cout<<"Are you sure(y/n):";
	
	char ch;
	while(1)
	{	
		cin.ignore();
		ch=getchar();
		if(ch=='y'||ch=='Y')break;
	else if(ch=='n'||ch=='N'){
		fo.close();
			remove("temp.dat");
	fio.close();
		return 1;
	}
	cout<<"Invalid\nEnter Again:";
	while (cin.get() !='\n') continue; 

	}
	
	while(fio.read((char *)&f,sizeof(f))){
		
	if(n==flight_no )
		{	if(pass_count)
			{	cout<<"Flight already booked by a passenger so can not be deleted\n";
				flag =0;
				i=2;
				break;
				}else
				i=1;
		}else{
			fo.write((char *)&f,sizeof(f));
		}
	}
	
	fo.close();
	fio.close();
	if(flag){
	remove("flights.dat");
	rename("temp.dat","flights.dat");
		}
		if(i==1)cout<<"Flight Deleted\n";
		else if(i==0) cout<<"Flight not found\n";

		
	
}
		

int Ticket::book_ticket(){
assign_ticket();
	
	if(get_details())return 1;
	
	
	fio.open("tickets.dat",ios::app| ios::binary);
	

	fio.write((char *)&t,sizeof(t));
			

	fio.close();
	

}

void Ticket::assign_ticket(){
	int a=1,flag=1;
	fio.open("tickets.dat",ios::in|ios::binary);
	while(1){
		
	while(fio.read((char *)&t,sizeof(t))){
			
		if(a ==ticket_no)
		{
		flag=0;
		break;
		}else flag=1;
		}
		if(flag)break;
		a++;
		fio.seekg(0);
	}
	fio.close();
		ticket_no=a;
	}
	
void Ticket::disp_bookings(){

	fio.open("tickets.dat",ios::in | ios::binary);

	cout<<"Ticket Number"<<"\t"<<"Name"<<"\t\t\t"<<"Age    "<<"\t"
		<<"Phone Number"<<"\t"<<"Flight number"<<"\t"<<"Type\t"<<"Fair\n";

	while(fio.read((char *)&t,sizeof(t))){

		cout<<ticket_no<<"\t\t"
			<<setw(20)<<left<<cname<<"\t"
			<<age<<" Yrs   "
			<<setw(11)<<left<<phone<<"\t\t    "
			<<flight_no<<"\t "
			<<type<<"\t"
			<<fair<<endl;


	}

	fio.close();

	cout<<endl;

}
int Ticket::get_details(){;
	
		cout<<"Enter Passenger Name: ";
		cin.ignore();
		gets(cname);
		cout<<"Enter Age: ";
		iint(age);
		cout<<"Enter Phone Number:";cin.ignore();
		gets(phone);
		cout<<"b - Buisness Class(Rs. 6000)\n"
			<<"r - Regular(Rs. 4000)\n"
			<<"e - Economy(Rs. 2500)\n"
			<<"Enter class:";
		cin.get(type);
		set_fair();
		
		cout<<"Available Flights:\n";

		f.disp_flights(0);
		
		cout<<"Select flight:";
		
		iint(flight_no);
		
		int i=f.cap_check();
			while( i && !(flight_no == -1)){
			
			cout<<"Enter again(-1 to quit):";
			iint(flight_no);
			cout<<endl;
			i=f.cap_check();
		}
		if(flight_no == -1){
			return 1;
			}
				cout<<"Ticket number: "<<ticket_no<<endl;
				cout<<"Fair: "<<fair<<endl;
				
		cout<<"ticket saved\n\n";
		return 0;
	
	}

int Ticket::dele_booking(){
fstream temp,fiot;
	fiot.open("tickets.dat",ios::in | ios::out| ios::binary);
	temp.open("temp.dat",ios::out| ios::binary);
	
	int n,flag=1;
	cout<<"enter ticket no. to be deleted:";
	iint(n);
	cout<<"Are you sure(y/n):";
	
		char ch;
	while(1)
	{	
		cin.ignore();
		ch=getchar();
		if(ch=='y'||ch=='Y')break;
	else if(ch=='n'||ch=='N'){
		temp.close();
			remove("temp.dat");
	fio.close();
		return 1;
	}
	cout<<"Invalid\nEnter Again:";
	while (cin.get() !='\n') continue; 

	}
	while(fiot.read((char*)&t,sizeof(t))){
	if(n==ticket_no){
	
	f.reduce_pass(flight_no);
	flag=0;
	}else{
		temp.write((char *)&t,sizeof(t));
	} 
	
	
	
}
fiot.close();
	temp.close();
	remove("tickets.dat");
	rename("temp.dat","tickets.dat");
if(flag)	
cout<<"Ticket not found\n";
	else cout<<"Ticket Deleted\n";
	
}

int Ticket::mod_booking(){
fstream fiot;
	int n;
	cout<<"Enter Ticket Number to be modified:";
	
	iint(n);
	
	
	fiot.open("tickets.dat",ios::in | ios::out| ios::binary);
	
	
	while(fiot.read((char*)&t,sizeof(t))){
	if(n==ticket_no){
	

	f.reduce_pass(flight_no);
	
			
	
	cout<<"Enter New Details:\n";
	ticket_no=n;
	
	get_details();
	
	long pos;			
	pos=fiot.tellg();
	pos-=sizeof(t);
	fiot.seekg(pos);
	fiot.write((char *)&t,sizeof(t));
	fiot.close();
	cout<<"ticket modified\n";
	
	return 0;
	}
}
	cout<<"ticket not found\n";
	
}


int menu(){
int i=1;
	iint(ch);

	switch(ch){
	case 1:	t.book_ticket();
			
			system("pause");
			break;
	case 2:t.dele_booking();
				system("pause");
			break;
	case 3:f.disp_flights();
			break;
	case 4:t.disp_bookings();
			break;
	case 5:t.mod_booking(); 
				system("pause");
			break;
	case 6:cout<<"Enter Password:";
			while(pass()){
			cout<<"Wrong Password\nEnter again:";
	
			}
			do{

			cout<<"Staff Menu:\n"

			<<"1 - Create Flight\n"

			<<"2 - Modify Flight Capacity\n"

			<<"3 - Delete Flights\n"

			<<"4 - Return\n\n"
	
			<<"Enter Choice: ";


			i=staff_menu();


			}while(i);

			break;
	case 7:return 0;
			break;
	
	default: cout<<"Invalid choice!\nEnter again: ";	
			menu();
			break;	
	};

	

return 1;	

}

int staff_menu(){
	
	iint(ch);

	switch(ch){
	
	case 1:f.get_details();
			f.create_flight();
			cout<<"flight saved\n\n";
			system("pause");
			break;
	case 2: f.modify_flights(); 
			system("pause");
			break;
	case 3: f.delete_flight();
			system("pause");
			break;
	
	case 4:return 0;
			break;
	
	default: cout<<"Invalid choice!\nEnter again: ";	
			staff_menu();
			break;	
	};

	

return 1;	

}


int pass(){
	char pass[10],tar[10]="abc123";
	int i=0;
	char a;
	for(;;){
		a=getch();
		
			if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9')){
			pass[i]=a;
			++i;
			cout<<"*";
			}
		if(a=='\b'&&i>=1){
			cout<<"\b \b";
		--i;
		}
		if(a=='\r'){
			pass[i]='\0';
			break;
		}
		
	}
	cout<<endl;
	if(strcmp(tar,pass)){
		return 1;
	}else return 0;
}

int main(){
	cout<<"Created by Rishabh Jain.\nClass XII\n\n";
int ch=1,i=1;
do{

cout<<"Main Menu:\n"

	<<"1 - Book Flight\n"
	<<"2 - Cancel Booking\n"
	<<"3 - see flights\n"
	<<"4 - see tickets\n"
	<<"5 - Modify bookings\n"
	<<"6 - Staff Menu\n"
	<<"7 - Exit\n"<<endl
	<<"Enter Choice: ";


i=menu();


}while(i);
system("pause");

}



