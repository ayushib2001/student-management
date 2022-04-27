#include <iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

class Student{
	int roll;
	char name[20];
	int maths, eng, phy, chem, phed;
	int sum;
	float per;
	public:
		void getdata();
		void showdata() const;
		void calculate();
		int retroll();
};
void Student :: calculate(){
	sum = maths + eng + phy + chem + phed;
	per = (maths + eng + phy + chem + phed)/5.0 ; 
}
void Student :: getdata(){
	cout<<"Enter roll no : ";
	cin>>roll;
	cout<<"Enter name : ";
	cin.ignore();
	cin.getline(name,20);
	cout<<"Enter marks in maths : ";
	cin>>maths;
	cout<<"Enter marks in physics : ";
	cin>>phy;
	cout<<"Enter marks in chemistry : ";
	cin>>chem;
	cout<<"Enter marks in english : ";
	cin>>eng;
	cout<<"Enter marks in physical education : ";
	cin>>phed;
	calculate();
	cout<<"\n\nStudent record created...";
}
void Student :: showdata() const{
	cout<<"\nRoll no            : "<<roll;   
	cout<<"\nName               : "<<name;
	cout<<"\n-----------------------------------";
	cout<<"\nMarks in following subjects are :";
	cout<<"\nMaths              : "<<maths;
	cout<<"\nPhysics            : "<<phy;
	cout<<"\nChemistry          : "<<chem;
	cout<<"\nEnglish            : "<<eng;
	cout<<"\nPhysical Education : "<<phed;
	cout<<"\nSum                : "<<sum;
	cout<<"\nPercentage         : "<<per<<endl;
	cout<<"____________________________________________\n";
}
int Student :: retroll(){
	return roll;
}

void createRecord();
void search(int);
void display_all();
void deleteRecord(int);
void modify(int);

int main(){
	int num;
	char ch;
	do{
		system("cls");
		cout<<"\n\t MENU"<<endl;
		cout<<"\n\t 1. Create New Record"<<endl;
		cout<<"\t 2. Search a student record"<<endl;
		cout<<"\t 3. Display Record of Students"<<endl;
		cout<<"\t 4. Delete a record"<<endl;
		cout<<"\t 5. Modify a record"<<endl;
		cout<<"\t 6. Exit"<<endl;
		cout<<"\n\t Enter your choice : ";
		cin>>ch;
		system("cls");
		 
		switch(ch){
			case '1' : createRecord();
					 break;
			case '2' : cout<<"\nEnter roll no of student : ";
					 cin>>num; 
					 search(num);
					 break;
			case '3' : display_all(); break;
			case '4' : cout<<"\nEnter roll no of student : ";
					 cin>>num; 
					 deleteRecord(num);
					 break;
			case '5' : system("cls"); 
					  cout<<"\nEnter roll no of student : ";
					  cin>>num; 
					  modify(num);
					  break;
			case '6' : cout<<"thank you !"; exit(0);
		}
		cin.ignore();
		cin.get();
	}while(ch!='6');
}
// Write student details to file
void createRecord(){
	Student s;
	ofstream outfile;
	outfile.open("student.dat",ios::binary|ios::app);
	s.getdata();
	outfile.write(reinterpret_cast<char *> (&s), sizeof(Student));
	outfile.close();
	
}
// read from file
void display_all(){
	system("CLS");
	Student s;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile){
		cout<<"\nFile could not be opened !\n press any key to exit";
		return;
	}
	cout<<"\n\n\tDISPLAYING ALL RECORDS\n\n";
	while(inFile.read(reinterpret_cast<char *> (&s), sizeof(Student)))
	{
		s.showdata();
		cout<<"\n\n*****************************************************\n";
	}	
	inFile.close();
}
// Read specific record based on roll no
void search(int num){
	Student s;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile){
		cout<<"\nFile could not be opened ...\nPress any key to exit";
		return;
	}
	
	bool flag = false;
	while(inFile.read(reinterpret_cast<char *>(&s), sizeof(Student)))
	{
		if(s.retroll()==num){
			
			s.showdata();
			flag = true;
		}	
	}
	inFile.close();
	if(flag == false)
	cout<<"\nRecord does not exist ";
}
// Modify a record
void modify(int num){
	Student s;
	bool flag = false;
	fstream f1;
	f1.open("student.dat", ios::binary | ios::in | ios::out);
	if(!f1){
		cout<<"\nFile could not be opened ...\nPress any key to exit";
		return;
	}
	while(!f1.eof() && flag == false){
		f1.read(reinterpret_cast<char *>(&s), sizeof(Student));
		if(s.retroll() == num){
			s.showdata();
			cout<<"\nEnter new details :"<<endl;
			s.getdata();
			int pos = (-1)*static_cast<int>(sizeof(s));
			f1.seekp(pos, ios::cur);
			f1.write(reinterpret_cast<char *>(&s), sizeof(Student));
			cout<<"\n\nRecord updated"<<endl;
			flag = true;
		}
	}
	f1.close();
}

void deleteRecord(int num){
	Student s;
	ifstream inFile;
	ofstream outFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile){
		cout<<"\nFile could not be opened...\nPress any key to exit";
		return;
	}
	outFile.open("temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *>(&s), sizeof(Student)))
	{
		if(s.retroll()!= num){
			outFile.write(reinterpret_cast<char *>(&s), sizeof(Student));
		}	
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("temp.dat","student.dat");
	cout<<"Record is deleted...";
}
