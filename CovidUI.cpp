#include <windows.h>
#include <WinInet.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <process.h>
#include "resource.h"

#define BtnSearch 	2001

#define TxtBox 		3001
#define BigTxtBox 	3002

#define MenuExit 	1001
#define MenuHelp 	1010
#define MenuRefresh 1009
#define MenuPass 	1002
#define MenuReg 	1003
#define MenuWHO 	1004
#define MenuAbout 	1005
#define MenuAdd 	1006
#define MenuUpdate 	1007
#define MenuDel 	1008

#define COVID 310

using namespace std;

static HWND hwndTxtBox,hwndBigTxtBox;


class state
{
private:
    string name, state_id, active_cases, recovered_cases, death_cases, total_cases, disp;
    string* z = new string[100];
    int zlen;

public:
	void SetName(string n){
		name = n;
	};
	
	string GetName(){
		return name;
	};
	
	void SetID(string id){
		state_id = id;
	};
	
	string GetID(){
		return state_id;
	};
	
	void SetActive(string act){
		active_cases = act;
	};
	
	string GetActive(){
		return active_cases;
	};
	
	void SetRecovered(string rec){
		recovered_cases = rec;
	};
	
	string GetRecovered(){
		return recovered_cases;
	};
	
	void SetDeaths(string det){
		death_cases = det;
	};
	
	string GetDeaths(){
		return death_cases;
	};
	
	void SetTotal(string tot){
		total_cases = tot;
	};
	
	string GetTotal(){
		return total_cases;
	};
	
    void insert(string statename, string id, string active, string recovered, string deaths, string total){
    	string str;
    	int count = 0;
    	
		fstream file;
    	file.open("bin/COVID19_Records.txt", ios::in);
    	getline(file,str);
    		
    	    while (!file.eof())
			{
        	    istringstream ss(str);
        	    getline(ss, name, '|');
        	    getline(ss, state_id, '|');
        	    getline(ss, active_cases, '|');
        	    getline(ss, recovered_cases, '|');
        	    getline(ss, death_cases, '|');
        		getline(ss, total_cases);
            	if (statename == name) {
					MessageBox(NULL,"State with same Name already exists!","Attention",MB_ICONEXCLAMATION);
            		count = 1;
            	}
            	if (id == state_id){
            		MessageBox(NULL,"State with same ID already exists!","Attention",MB_ICONEXCLAMATION);
            		count = 1;
            	}
            	getline(file,str);
        	}
        	file.close();
        	
        	if (count == 0){
        		file.open("bin/COVID19_Records.txt", ios::app | ios::out);
        		file << statename << '|' << id << '|' << active << '|' << recovered << '|' << deaths << '|' << total << "\n";
        		MessageBox(NULL, "New State Data Added Succesfully!","Attention", MB_ICONINFORMATION);
        		file.close();
        	}
    			
    	
	};
    void display(){
    	string str, sh, dname, did, dactive, drecovered, ddeaths, dtotal;
    	
    	int total = 0;
    	
    	disp = "";
    	SendMessage(hwndTxtBox,CB_RESETCONTENT,0,0);
    	for(int i = 0; i <= zlen; i++)
    		z[i] = "";
    	
    	fstream file;
    	
		file.open("bin/COVID19_Records.txt", ios::in);
    	if (!file)
    		disp = "No data to Display...#";
    	else
    	{
    		getline(file,str);
    		
    	    while (!file.eof())
			{
        	    istringstream ss(str);
        	    getline(ss, dname, '|');
        	    getline(ss, did, '|');
        	    getline(ss, dactive, '|');
        	    getline(ss, drecovered, '|');
        	    getline(ss, ddeaths, '|');
        		getline(ss, dtotal);
            	fstream file1("bin/temp1.txt", ios::out);
				file1 << "State\t\t: " << dname << "\r\nState ID\t\t: " << did <<"\r\nActive cases\t: " << dactive <<"\r\nTotal Recovered\t: " << drecovered <<"\r\nTotal Deaths\t: " << ddeaths <<"\r\nTotal cases\t: " << dtotal;
				file1.close();
				SendMessage(hwndTxtBox,CB_ADDSTRING,0,(LPARAM)dname.c_str());
				z[total] = dname;
				zlen = total;
				file1.open("bin/temp1.txt", ios::in);
				getline(file1,sh);
				while (!file1.eof()){
					disp.append(sh);
					disp.append("\n");
					getline(file1,sh);
				}
				disp.append(sh);
				disp.append("\n#");
				file1.close();
				total++;
            	getline(file,str);
        	}
    	}
    	file.close();
		remove("bin/temp1.txt");
    	
    	if (total == 0)
    		disp = "No data to Display...#";
    	
    };
    
    string GetDisplay(){
    	return disp;
    };
    
    string *GetZ(){
    	return z;
    };
    
    int GetZlen(){
    	return zlen;
    };
    
    void modify(string rollno, string act, string rec, string det, string tot){
    	string str;
    	fstream file, file1;
    	file.open("bin/COVID19_Records.txt", ios::in);
    	if (!file)
    	{
        	MessageBox(NULL,"File Not Found!","Attention",MB_ICONERROR);
    	}
    	else if(rollno == "")
    		MessageBox(NULL,"Search the State Name before Updating or Deleting","Attention",MB_ICONERROR);
    	else
    	{
        	file1.open("bin/record.txt", ios::app | ios::out);
        
        	getline(file,str);
        	while (!file.eof())
        	{
        		istringstream ss(str);
            	getline(ss, name, '|');
            	getline(ss, state_id, '|');
            	getline(ss, active_cases, '|');
            	getline(ss, recovered_cases, '|');
            	getline(ss, death_cases, '|');
            	getline(ss, total_cases);
            
            	if (rollno != state_id)

                	file1 << name << '|' << state_id << '|' << active_cases << '|' << recovered_cases << '|' << death_cases << '|' << total_cases << "\n";
            	else
            	{
                	file1 << name << '|' << state_id << '|' << act << '|' << rec << '|' << det << '|' << tot << "\n";
                	MessageBox(NULL,"Data Updated Successfully!","Attention",MB_ICONINFORMATION);
            	}
            	getline(file,str);
        	}	

        	file1.close();
        	file.close();
        	remove("bin/COVID19_Records.txt");
        	rename("bin/record.txt", "bin/COVID19_Records.txt");
    	}
    };
    int search(string rollno){
    	string str;
    	fstream file;
    	int found = 0;
    	file.open("bin/COVID19_Records.txt", ios::in);
    	if (!file)
    	{
        	MessageBox(NULL,"Data Not Found!","Attention",MB_ICONERROR);
    	}
    	else
    	{
        	getline(file,str);
        	while (!file.eof())
        	{
        		istringstream ss(str);
        	    getline(ss, name, '|');
        	    getline(ss, state_id, '|');
        	    getline(ss, active_cases, '|');
        	    getline(ss, recovered_cases, '|');
        	    getline(ss, death_cases, '|');
        	    getline(ss, total_cases);
            
        	    if (rollno == state_id || rollno == name)
            	{             
            	    found++;
            	    break;
            	}
            	getline(file,str);
        	}
        	
        	file.close();
    	}
    	return found;
    };
    void deleted(string rollno, string act, string rec, string det, string tot){
    	string str;
    	fstream file, file1;
    	
    	file.open("bin/COVID19_Records.txt", ios::in);
    	if (!file)
    	{
        	MessageBox(NULL,"File Not Found!","Attention",MB_ICONERROR);
    	}
    	else if (rollno == "")
    		MessageBox(NULL,"Search the State Name before Deleting","Attention",MB_ICONERROR);
    	else
    	{
        	file1.open("bin/record.txt", ios::app | ios::out);
        
        	getline(file,str);
        	while (!file.eof())
        	{
        		istringstream ss(str);
            	getline(ss, name, '|');
            	getline(ss, state_id, '|');
            	getline(ss, active_cases, '|');
            	getline(ss, recovered_cases, '|');
            	getline(ss, death_cases, '|');
            	getline(ss, total_cases);
            
            	if (rollno != state_id)
                	file1 << name << '|' << state_id << '|' << active_cases << '|' << recovered_cases << '|' << death_cases << '|' << total_cases << "\n";
            	else
            		MessageBox(NULL,"Data deleted Successfully!","Attention",MB_ICONINFORMATION);
            	getline(file,str);
        	}	

        	file1.close();
        	file.close();
        	remove("bin/COVID19_Records.txt");
        	rename("bin/record.txt", "bin/COVID19_Records.txt");
    	}
    	
    };
}s;

class user
{
private:
	int author;
	bool usearch;
	string amnesia;
	
public:
	bool GetFirstUser(){
		bool first;
		string str;
		fstream file("bin/database.txt", ios::in);
		if (!file)
			first = TRUE;
		else{
			getline(file,str);
			if(file.eof())
				first = TRUE;
			else	
				first = FALSE;
		}
			
		file.close();
		return first;
	};
	
	void login(string user_name, string password){
		author = 1;
    	string u,p,str;
    		    	
    	fstream input("bin/database.txt", ios::in);
    
    	if(!input){
    		MessageBox(NULL,"No Users Found! Go to 'Register New User' in 'Admin' menu to Register First User","Attention",MB_ICONERROR);
    		author = 0;
    	}
    		
    	while(input)
    	{
   			getline(input,str);
    	   	istringstream ss(str);
   	    	getline(ss, u, '|');
   	    	getline(ss, p);
  	     	if(u==user_name && p==password)
   	    		author = 2;
  	     	if (input.eof())
    	   		break;
    	}
	};
	
	int GetAuthorization(){
		return author;
	};
	
	void SetAuthorization(int au){
		author = au;
	};
	
	int registr(string ru, string rp, string rrp){ 
        string reguser,regpass,str;
        int ucount = 0,r = 0;
        
        fstream reg("bin/database.txt",ios::in);
        
    	while(reg)
    	{
   			getline(reg,str);
    	   	istringstream ss(str);
   	    	getline(ss, reguser, '|');
   	    	getline(ss, regpass);
  	     	if(ru.compare(reguser) == 0 && ru != "")
   	    		ucount = 1;
   	    	if(ru == "")
   	    		ucount = 2;
  	     	if (reg.eof())
    	   		break;
    	}
    	reg.close();
    	
    	if(ucount == 2)
    		MessageBox(NULL,"Enter Valid Values!","Attention",MB_ICONEXCLAMATION);
    	else if(ucount == 1)
    		MessageBox(NULL,"Username already exists. Try some other Username","Attention",MB_ICONEXCLAMATION);
    	else{
    		if(rp == "" | rrp == "")
    			MessageBox(NULL,"Enter Valid Values!","Attention",MB_ICONEXCLAMATION);
			else if(rp == rrp){
    			fstream reg("bin/database.txt",ios::app | ios::out);
    			reg<<ru<<'|'<<rp<<"\n";
    			reg.close();
    			MessageBox(NULL,"New user registration successful!","Attention",MB_ICONINFORMATION);
    			r = 2;
    		}
    		else{
    			MessageBox(NULL,"Make sure the passwords match","Attention",MB_ICONEXCLAMATION);
    			r = 1;
    		}
    	}
    	return r;
	};
	
	bool usersearch(string user){
		string u,p,str;
        int count = 0;
        
        fstream usr("bin/database.txt",ios::in);
        if(!usr){
    		MessageBox(NULL,"No Users Found! Go to 'Register New User' in 'Admin' menu to Register First User","Attention",MB_ICONERROR);
    	}
    	while(usr)
    	{
   			getline(usr,str);
    	   	istringstream ss(str);
   	    	getline(ss, u, '|');
   	    	getline(ss, p);
  	     	if(u.compare(user) == 0 && user != ""){
  	     		amnesia = u;
  	     		count = 1;
  	     	}
  	     	if (usr.eof())
    	   		break;
    	}
    	usr.close();
    	
    	if(count == 1)
    		usearch = TRUE;
    	else 
    		usearch = FALSE;
		return usearch;
	};

	bool GetUserSearch(){
		return usearch;
	};
	
	bool forgot(string pw, string rpw){
		string reguser, regpass, str;
		bool count;
        fstream file, file1;
        if(pw == rpw){
        	
        	file.open("bin/database.txt",ios::in);
        	file1.open("bin/base.txt",ios::app|ios::out);
        	
        	getline(file,str);
        	while(!file.eof())
    		{
    	   		istringstream ss(str);
   	    		getline(ss, reguser, '|');
   	    		getline(ss, regpass);
  	     		if(amnesia == reguser){
   	    			file1 << reguser << '|' << pw <<"\n";
   	    			MessageBox(NULL,"Password Changed Successfully!","Attention",MB_ICONINFORMATION);
   	    			count = TRUE;
   	    		}
   	    		else
   	    			file1 << reguser << '|' << regpass <<"\n";
   	    		getline(file,str);
    		}
    		file.close();
    		file1.close();
    		
    		remove("bin/database.txt");
    		rename("bin/base.txt","bin/database.txt");
        }
        else{
        	MessageBox(NULL,"Make sure the passwords match","Attention",MB_ICONEXCLAMATION);
        	count = FALSE;
        }
    	
    	return count;
	};
	bool userdelete(string ud){
		string reguser, regpass, str;
		int count = 0;
        fstream file, file1;
        file.open("bin/database.txt",ios::in);
        file1.open("bin/base.txt",ios::app|ios::out);
        	
        getline(file,str);
        while(!file.eof())
    	{
    	   	istringstream ss(str);
   	    	getline(ss, reguser, '|');
   	    	getline(ss, regpass);
  	     	if(ud == reguser){
   	    		MessageBox(NULL,"User Deleted Successfully!","Attention",MB_ICONINFORMATION);
   	    		count = 1;
   	    		}
   	    	else
   	    		file1 << reguser << '|' << regpass <<"\n";
   	    	getline(file,str);
    	}
    	file.close();
    	file1.close();
    		
    	remove("bin/database.txt");
    	rename("bin/base.txt","bin/database.txt");
    	if (count == 1)
    		return TRUE;
    	else
    		return FALSE;
	};
}u;

/* This is where all the input to the window goes to */
BOOL CALLBACK AboutDlgProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG :
			
			for(int i = 0; i <= s.GetZlen(); i++){
				SendDlgItemMessage(hDlg,UPDATE_SEARCH_TXTBOX,CB_ADDSTRING,0,(LPARAM)(s.GetZ()[i].c_str()));
			}
			
			return TRUE ;
		case WM_COMMAND :
			switch (LOWORD (wParam))
			{
				case LOG_LOGIN :
					char us[100],ps[100];
					
					GetDlgItemText(hDlg, LOG_UN_TXTBOX, us, 200);
					GetDlgItemText(hDlg, LOG_PW_TXTBOX, ps, 200);
					
					u.login(us,ps);
					if (u.GetAuthorization() == 2){
						MessageBox(hDlg, "Login Success","Attention", MB_ICONINFORMATION);
						EndDialog (hDlg, 0);
					}
						
					else if (u.GetAuthorization() == 1){
						MessageBox(hDlg, "Username or Password is wrong! Try again.","Attention", MB_ICONERROR);
						SetDlgItemText(hDlg, LOG_UN_TXTBOX, "");
						SetDlgItemText(hDlg, LOG_PW_TXTBOX, "");
					}
					else{
						EndDialog (hDlg, 0) ;
						return TRUE ;
					}
					break;
				case LOG_CANCEL :
					u.SetAuthorization(1);
					EndDialog (hDlg, 0) ;
					return TRUE ;
					break;
				case DATA_ADD :
					char d1[100],d2[100],d3[100],d4[100],d5[100],d6[100];
					GetDlgItemText(hDlg, DATA_NAME_TXTBOX, d1, 200);
					GetDlgItemText(hDlg, DATA_ID_TXTBOX, d2, 200);
					GetDlgItemText(hDlg, DATA_ACTIVE_TXTBOX, d3, 200);
					GetDlgItemText(hDlg, DATA_RECOVERED_TXTBOX, d4, 200);
					GetDlgItemText(hDlg, DATA_DEATHS_TXTBOX, d5, 200);
					GetDlgItemText(hDlg, DATA_TOTAL_TXTBOX, d6, 200);
					if (strcmp(d1,"") == 0 ||strcmp(d2,"") == 0)
						MessageBox(hDlg, "Do not Leave the fields with * Empty","Attention", MB_ICONERROR);
					else{
						s.insert(d1,d2,d3,d4,d5,d6);
						
						SetDlgItemText(hDlg, DATA_NAME_TXTBOX, "");
						SetDlgItemText(hDlg, DATA_ID_TXTBOX, "");
						SetDlgItemText(hDlg, DATA_ACTIVE_TXTBOX, "");
						SetDlgItemText(hDlg, DATA_RECOVERED_TXTBOX, "");
						SetDlgItemText(hDlg, DATA_DEATHS_TXTBOX, "");
						SetDlgItemText(hDlg, DATA_TOTAL_TXTBOX, "");
						s.display();
					}
					
					break;
				case DATA_CLEAR :
					SetDlgItemText(hDlg, DATA_NAME_TXTBOX, "");
					SetDlgItemText(hDlg, DATA_ID_TXTBOX, "");
					SetDlgItemText(hDlg, DATA_ACTIVE_TXTBOX, "");
					SetDlgItemText(hDlg, DATA_RECOVERED_TXTBOX, "");
					SetDlgItemText(hDlg, DATA_DEATHS_TXTBOX, "");
					SetDlgItemText(hDlg, DATA_TOTAL_TXTBOX, "");
					return TRUE;
					break;
				case DATA_CANCEL :
					EndDialog (hDlg, 0) ;
					u.SetAuthorization(1);
					return TRUE ;
					break;
				case UPDATE_SEARCH :
					char data[100];
					GetDlgItemText(hDlg, UPDATE_SEARCH_TXTBOX, data, 200);
					if (s.search(data) == 1){
						char name[s.GetName().length() + 1], id[s.GetID().length() + 1], active[s.GetActive().length() + 1], recovered[s.GetRecovered().length() + 1], deaths[s.GetDeaths().length() + 1], total[s.GetTotal().length() + 1];
						strcpy(name, s.GetName().c_str());
						strcpy(id, s.GetID().c_str());
						strcpy(active, s.GetActive().c_str());
						strcpy(recovered, s.GetRecovered().c_str());
						strcpy(deaths, s.GetDeaths().c_str());
						strcpy(total, s.GetTotal().c_str());
						SetDlgItemText(hDlg, UPDATE_NAME_TXTBOX, name);
						SetDlgItemText(hDlg, UPDATE_ID_TXTBOX, id);
						SetDlgItemText(hDlg, UPDATE_ACTIVE_TXTBOX, active);
						SetDlgItemText(hDlg, UPDATE_RECOVERED_TXTBOX, recovered);
						SetDlgItemText(hDlg, UPDATE_DEATHS_TXTBOX, deaths);
						SetDlgItemText(hDlg, UPDATE_TOTAL_TXTBOX, total);
						SetDlgItemText(hDlg, UPDATE_SEARCH_TXTBOX, "");
					}
					else{
						MessageBox(hDlg,"Data with the details you searched was not found","Attention",MB_ICONEXCLAMATION);
						SetDlgItemText(hDlg, UPDATE_NAME_TXTBOX, "");
						SetDlgItemText(hDlg, UPDATE_ID_TXTBOX, "");
						SetDlgItemText(hDlg, UPDATE_ACTIVE_TXTBOX, "");
						SetDlgItemText(hDlg, UPDATE_RECOVERED_TXTBOX, "");
						SetDlgItemText(hDlg, UPDATE_DEATHS_TXTBOX, "");
						SetDlgItemText(hDlg, UPDATE_TOTAL_TXTBOX, "");
						SetDlgItemText(hDlg, UPDATE_SEARCH_TXTBOX, "");
					}
					break;
				case UPDATE_ADD :
					char id[100],act[100],rec[100],det[100],tot[100];
					
					GetDlgItemText(hDlg, UPDATE_ID_TXTBOX, id, 100);
					GetDlgItemText(hDlg, UPDATE_ACTIVE_TXTBOX, act, 100);
					GetDlgItemText(hDlg, UPDATE_RECOVERED_TXTBOX, rec, 100);
					GetDlgItemText(hDlg, UPDATE_DEATHS_TXTBOX, det, 100);
					GetDlgItemText(hDlg, UPDATE_TOTAL_TXTBOX, tot, 100);
					
					s.modify(id, act, rec,det, tot);
					
					SetDlgItemText(hDlg, UPDATE_NAME_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_ID_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_ACTIVE_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_RECOVERED_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_DEATHS_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_TOTAL_TXTBOX, "");
					s.display();
					break;
				case UPDATE_DELETE :
					
					GetDlgItemText(hDlg, UPDATE_ID_TXTBOX, id, 100);
					GetDlgItemText(hDlg, UPDATE_ACTIVE_TXTBOX, act, 100);
					GetDlgItemText(hDlg, UPDATE_RECOVERED_TXTBOX, rec, 100);
					GetDlgItemText(hDlg, UPDATE_DEATHS_TXTBOX, det, 100);
					GetDlgItemText(hDlg, UPDATE_TOTAL_TXTBOX, tot, 100);
					
					s.deleted(id, act, rec,det, tot);
					
					SetDlgItemText(hDlg, UPDATE_NAME_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_ID_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_ACTIVE_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_RECOVERED_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_DEATHS_TXTBOX, "");
					SetDlgItemText(hDlg, UPDATE_TOTAL_TXTBOX, "");
					s.display();
					
					SendDlgItemMessage(hDlg,UPDATE_SEARCH_TXTBOX,CB_RESETCONTENT,0,0);
					for(int i = 0; i <= s.GetZlen(); i++){
						SendDlgItemMessage(hDlg,UPDATE_SEARCH_TXTBOX,CB_ADDSTRING,0,(LPARAM)(s.GetZ()[i].c_str()));
					}
					break;
				case UPDATE_CANCEL :
					EndDialog (hDlg, 0) ;
					u.SetAuthorization(1);
					return TRUE ;
					break;
				case REG_REGISTER :
					char ru[100],rp[100],rrp[100];
					int comp;
					GetDlgItemText(hDlg, REG_UN_TXTBOX, ru, 100);
					GetDlgItemText(hDlg, REG_PW_TXTBOX, rp, 100);
					GetDlgItemText(hDlg, REG_RPW_TXTBOX, rrp, 100);
					comp = u.registr(ru,rp,rrp);
					if(comp == 2){
						EndDialog (hDlg, 0) ;
						return TRUE ;
					}
					else if(comp == 1){
						SetDlgItemText(hDlg, REG_PW_TXTBOX, "");
						SetDlgItemText(hDlg, REG_RPW_TXTBOX, "");
					}
					else{
						SetDlgItemText(hDlg, REG_UN_TXTBOX, "");
						SetDlgItemText(hDlg, REG_PW_TXTBOX, "");
						SetDlgItemText(hDlg, REG_RPW_TXTBOX, "");
					}
					
					break;
				case REG_CANCEL :
					EndDialog (hDlg, 0) ;
					u.SetAuthorization(1);
					return TRUE ;
					break;
				case USER_SEARCH :
					char uns[100];
					GetDlgItemText(hDlg, USER_SEARCH_TXTBOX, uns, 100);
					
					if(!u.usersearch(uns)){
						MessageBox(hDlg, "Username Not Found! Register as New User", "Attention", MB_ICONERROR);
						SetDlgItemText(hDlg, USER_SEARCH_TXTBOX, "");
					}
					else{
						EndDialog (hDlg, 0) ;
						return TRUE ;
					}
					break;
				case FOR_REGISTER :
					char pass[100],repass[100];
					GetDlgItemText(hDlg, FOR_PW_TXTBOX, pass, 100);
					GetDlgItemText(hDlg, FOR_RPW_TXTBOX, repass, 100);
					if (strcmp(pass,"") == 0 && strcmp(repass,"") == 0)
						MessageBox(hDlg, "Type Some New password in the Fields shown with *","Attention", MB_ICONERROR);
					else{
					
						if(u.forgot(pass,repass)){
							EndDialog (hDlg, 0) ;
							return TRUE ;
						}
						else{
							SetDlgItemText(hDlg, FOR_PW_TXTBOX, "");
							SetDlgItemText(hDlg, FOR_RPW_TXTBOX, "");
						}
					}
					break;
				case FOR_CANCEL :
					EndDialog (hDlg, 0) ;
					return TRUE ;
					break;
				case USER_DELETE :
					char ud[100];
					GetDlgItemText(hDlg, USER_DELETE_TXTBOX, ud, 100);
					
					if(!u.userdelete(ud)){
						MessageBox(hDlg, "Username Not Found!", "Attention", MB_ICONERROR);
						SetDlgItemText(hDlg, USER_DELETE_TXTBOX, "");
					}
					else{
						EndDialog (hDlg, 0) ;
						return TRUE ;
					}
					break;
				case ABOUT_CLOSE :
					EndDialog (hDlg, 0) ;
					return TRUE ;
					break;
			}
			break ;
			
		case WM_PAINT: {
			PAINTSTRUCT ps;
   			HDC hdc, hdcMem;
   			BITMAP bitmap;
   			HGDIOBJ oldBitmap;
   			HBITMAP hBitmap1 = (HBITMAP)LoadImage(NULL, "Corona.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
   			
   			hdc = BeginPaint(hDlg, &ps);
   				hdcMem = CreateCompatibleDC(hdc);
   				oldBitmap = SelectObject(hdcMem, hBitmap1);
   			
   				GetObject(hBitmap1, sizeof(bitmap), &bitmap);
				BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
			
				SelectObject(hdcMem, oldBitmap);
   	 			DeleteDC(hdcMem);
			
   			EndPaint(hDlg, &ps);
   			return TRUE;
   			break;
   		}
   		case WM_CTLCOLORSTATIC:{
   			WORD CtrlID = GetDlgCtrlID((HWND)lParam);
            if (CtrlID == IDC_STATIC){//         UPDATE_NAME_TXTBOX | UPDATE_ID_TXTBOX){
    			HDC hdcStatic = (HDC)wParam; // or obtain the static handle in some other way
    			SetTextColor(hdcStatic, RGB(255, 255, 255)); // text color
    			SetBkMode(hdcStatic, TRANSPARENT);
    			return (LRESULT)GetStockObject(NULL_BRUSH);
    		}
			break;
		}
		case WM_CLOSE :
			EndDialog (hDlg, 0) ;
			u.SetAuthorization(1);
			return TRUE ;
			break;
		case WM_DESTROY :
			EndDialog (hDlg, 0) ;
			return TRUE ;
			break;

	}
	return FALSE ;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

HWND hwnd;
/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	//HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG Msg; /* A temporary location for all messages */
 
	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(wc.hInstance, "CovidUI.ico"); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(wc.hInstance, "A"); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","COVID-19 Application",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		590, /* width */
		380, /* height */
		NULL,NULL,hInstance,NULL);
	//SendMessage(hwnd, WM_SETFONT, (WPARAM), TRUE);
	
	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&Msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&Msg); /* Translate key codes to chars if present */
		DispatchMessage(&Msg); /* Send it to WndProc */
	}
	return Msg.wParam;
}

//Parallel Thread to display cases
VOID Thread (PVOID pvoid)
{
	string d, str;
	s.display();
	
	while (TRUE)
	{	
		str = s.GetDisplay();
		istringstream ss(str);
		getline(ss,d,'#');
		while(!ss.eof()){
			SetWindowText(hwndBigTxtBox, d.c_str());
			Sleep(3000);
			getline(ss,d,'#');
		}
	}
}

HBITMAP MakeBitMapTransparent(HBITMAP hbmSrc)
{
	HDC hdcSrc, hdcDst;
    HBITMAP hbmOld, hbmNew;
    BITMAP bm;
    COLORREF clrTP, clrBK;

    if ((hdcSrc = CreateCompatibleDC(NULL)) != NULL) {
        if ((hdcDst = CreateCompatibleDC(NULL)) != NULL) {
            int nRow, nCol;
            GetObject(hbmSrc, sizeof(bm), &bm);
            hbmOld = (HBITMAP)SelectObject(hdcSrc, hbmSrc);
            hbmNew = CreateBitmap(bm.bmWidth, bm.bmHeight, bm.bmPlanes, bm.bmBitsPixel, NULL);
            SelectObject(hdcDst, hbmNew);

            BitBlt(hdcDst,0,0,bm.bmWidth, bm.bmHeight,hdcSrc,0,0,SRCCOPY);

            clrTP = GetPixel(hdcDst, 0, 0);// Get color of first pixel at 0,0
            clrBK = GetSysColor(COLOR_MENU);// Get the current background color of the menu
            for (nRow = 0; nRow < bm.bmHeight; nRow++)// work our way through all the pixels changing their color
                for (nCol = 0; nCol < bm.bmWidth; nCol++)// when we hit our set transparency color.
                    if (GetPixel(hdcDst, nCol, nRow) == clrTP)
                        SetPixel(hdcDst, nCol, nRow, clrBK);
            DeleteDC(hdcDst);
        }
        DeleteDC(hdcSrc);
    }
	return hbmNew;// return our transformed bitmap.
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	static HINSTANCE hInstance ;
	
	switch(Message) {
		
		case WM_CREATE: {
			hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;
			/* Menu*/
			HMENU hMenubar, hFile, hOptions, hAdmin, hAbout;
			HBITMAP Help, Refresh, Exit, Add, Update, Regi, Pass, Del, Who, About;
			
			Help = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_HELP)));
			Refresh = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_REFRESH)));
			Exit = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_EXIT)));
			Add = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_ADD)));
			Update = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_UPDATE)));
			Regi = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_REGI)));
			Pass = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_PASS)));
			Del = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_DEL)));
			Who = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_WHO)));
			About = MakeBitMapTransparent(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(BM_ABOUT)));
			
			
			
			hMenubar = CreateMenu ();	//Creating a Menu bar
			hFile = CreateMenu ();		//Creating one of the title Menus
			hOptions = CreateMenu();	//Creating one of the title Menus
			hAdmin = CreateMenu();		//Creating one of the title Menus
			hAbout = CreateMenu();		//Creating one of the title Menus
			
			//Initializing title Menu and text to display on Menu
			AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, "&File");
			/*Menu Items creation in 'File' title Menu*/
			AppendMenu(hFile, MF_STRING, MenuRefresh, "&Refresh Display");	SetMenuItemBitmaps(hFile, MenuRefresh, MF_BYCOMMAND, Refresh , Refresh);
			AppendMenu(hFile, MF_STRING, MenuHelp, "View &Help");			SetMenuItemBitmaps(hFile, MenuHelp, MF_BYCOMMAND, Help , Help);
			AppendMenu(hFile, MF_SEPARATOR, 0, NULL);
			AppendMenu(hFile, MF_STRING, MenuExit, "E&xit");				SetMenuItemBitmaps(hFile, MenuExit, MF_BYCOMMAND, Exit , Exit);
			
			//Initializing title Menu and text to display on Menu
			AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hOptions, "&Options");
			/*Menu Items creation in 'Options' title Menu*/
			AppendMenu(hOptions, MF_STRING, MenuAdd, "Add &New Data");		SetMenuItemBitmaps(hOptions, MenuAdd, MF_BYCOMMAND, Add , Add);
			AppendMenu(hOptions, MF_STRING, MenuUpdate, "&Update or Delete Existing Data"); SetMenuItemBitmaps(hOptions, MenuUpdate, MF_BYCOMMAND, Update , Update);
			
			//Initializing title Menu and text to display on Menu
			AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hAdmin, "&Admin");		
			/*Menu Items creation in 'Admin' title Menu*/
			AppendMenu(hAdmin, MF_STRING, MenuReg, "Register &New User");	SetMenuItemBitmaps(hAdmin, MenuReg, MF_BYCOMMAND, Regi , Regi);
			AppendMenu(hAdmin, MF_SEPARATOR, 0, NULL);		
			AppendMenu(hAdmin, MF_STRING, MenuPass, "&Forgot Password");	SetMenuItemBitmaps(hAdmin, MenuPass, MF_BYCOMMAND, Pass , Pass);
			AppendMenu(hAdmin, MF_STRING, MenuDel, "&Delete Existing User");SetMenuItemBitmaps(hAdmin, MenuDel, MF_BYCOMMAND, Del , Del);
			
			//Initializing title Menu and text to display on Menu
			AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hAbout, "&About");
			/*Menu Items creation in 'About' title Menu*/
			AppendMenu(hAbout, MF_STRING, MenuWHO, "WHO &Guidelines on COVID-19");SetMenuItemBitmaps(hAbout, MenuWHO, MF_BYCOMMAND, Who , Who);
			AppendMenu(hAbout, MF_STRING, MenuAbout, "&About COVID-19 Application");SetMenuItemBitmaps(hAbout, MenuAbout, MF_BYCOMMAND, About , About);
			
			SetMenu(hwnd, hMenubar); //Run Menu
			/*Menu end*/
			
			/*Button*/
			CreateWindow(TEXT("BUTTON"), TEXT("Search"), 
				WS_VISIBLE|WS_CHILD, 
				460, 240, 80, 25, 
				hwnd, (HMENU) BtnSearch, NULL, NULL);
			/*Button end*/
			
			/*Text*/
			CreateWindow(TEXT("STATIC"), TEXT("Search using State Name or State Code"), 
				WS_VISIBLE|WS_CHILD, 
				30, 220, 400, 25, 
				hwnd, NULL, NULL, NULL);
			CreateWindow(TEXT("STATIC"), TEXT("State wise COVID-19 Details"), 
				WS_VISIBLE|WS_CHILD, 
				30, 70, 400, 25, 
				hwnd, NULL, NULL, NULL);
			//HDC hdcStatic = GetDC(hwnder);
			/*Text*/	
				
			/*TextBox*/
			hwndTxtBox = CreateWindow(TEXT("COMBOBOX"), TEXT(""), 
				WS_VISIBLE|WS_CHILD|CBS_DROPDOWN|CBS_DISABLENOSCROLL|CBS_SORT|CBS_AUTOHSCROLL|WS_VSCROLL, 
				30, 240, 400, 90, 
				hwnd, (HMENU) TxtBox, NULL, NULL);
				
			hwndBigTxtBox = CreateWindow(TEXT("EDIT"), TEXT(""), 
				WS_VISIBLE|WS_CHILD|WS_BORDER|ES_READONLY|ES_MULTILINE|ES_AUTOHSCROLL, 
				30, 90, 280, 100, 
				hwnd, (HMENU) BigTxtBox, NULL, NULL);
			/*TextBox end*/
			
			_beginthread (Thread, 0, NULL) ;	//Parallel Thread initialization
			
			return 0 ;
			break;
		}
		
		case WM_COMMAND: {
			
			switch(LOWORD(wParam))
            {
            	//Menu
                case MenuExit:
					exit(0);
                	break;
                case MenuHelp:
                	ShellExecute(NULL, "Open", "help\\index.html", NULL, NULL, SW_SHOWNORMAL);
                	break;
                case MenuRefresh:
                	s.display();
                	MessageBox(NULL, "Display Window's Data Updated","Attention",MB_OK);
                	break;
                case MenuAdd:
                	if(u.GetFirstUser()){
                		MessageBox(hwnd,"No Users Found! Go to 'Register New User' in 'Admin' menu to Register First User","Attention",MB_ICONERROR);
                	}
                	else{
                	
                		DialogBox (hInstance, TEXT ("Login"), hwnd, AboutDlgProc);
                		if (u.GetAuthorization() == 2){
                			DialogBox (hInstance, TEXT ("DATA"), hwnd, AboutDlgProc);
                		}
                	}
                	break;
                case MenuUpdate:
                	if(u.GetFirstUser()){
                		MessageBox(hwnd,"No Users Found! Go to 'Register New User' in 'Admin' menu to Register First User","Attention",MB_ICONERROR);
                	}
                	else{
						DialogBox (hInstance, TEXT ("Login"), hwnd, AboutDlgProc);
                		if (u.GetAuthorization() == 2){
                			DialogBox (hInstance, TEXT ("Update"), hwnd, AboutDlgProc);
                		}
                	}
                	break;
                case MenuReg:
                	
                	if(!u.GetFirstUser()){
                		DialogBox (hInstance, TEXT ("Login"), hwnd, AboutDlgProc);
                	}
					
                	if (u.GetAuthorization() == 2 || u.GetFirstUser()){
                		DialogBox (hInstance, TEXT ("Registr"), hwnd, AboutDlgProc);
                	}
                	break;
                case MenuPass:
                	if(u.GetFirstUser()){
                		MessageBox(hwnd,"No Users Found! Go to 'Register New User' in 'Admin' menu to Register First User","Attention",MB_ICONERROR);
                	}
                	else{
                		DialogBox (hInstance, TEXT ("Usersearch"), hwnd, AboutDlgProc);
						if(u.GetUserSearch()){
							DialogBox (hInstance, TEXT ("Forgot"), hwnd, AboutDlgProc);
						}
					}
                	break;
                case MenuDel:
                	if(u.GetFirstUser()){
                		MessageBox(hwnd,"No Users Found! Go to 'Register New User' in 'Admin' menu to Register First User","Attention",MB_ICONERROR);
                	}
                	else{
                		DialogBox (hInstance, TEXT ("Login"), hwnd, AboutDlgProc);
                		if (u.GetAuthorization() == 2){
                			DialogBox (hInstance, TEXT ("Userdelete"), hwnd, AboutDlgProc);
                		}
                	}
                	break;
                case MenuWHO:
					ShellExecute(NULL, "open", "https://www.who.int/publications/who-guidelines", NULL, NULL, SW_SHOWNORMAL);
                	break;
                case MenuAbout:
                	DialogBox (hInstance, TEXT ("About"), hwnd, AboutDlgProc);
					break;
                //Button
                case BtnSearch:{
                	double len = GetWindowTextLength(hwndTxtBox) + 1;
					TCHAR search[] = _T("");		
					GetWindowText(hwndTxtBox, search, len);
					if (strcmp(search,"") == 0)
						MessageBox(hwnd,"Please Enter State name or ID before searching","Attention",MB_ICONEXCLAMATION);
					else if (s.search(search) == 1){
						char name[s.GetName().length() + 1], id[s.GetID().length() + 1], active[s.GetActive().length() + 1], recovered[s.GetRecovered().length() + 1], deaths[s.GetDeaths().length() + 1], total[s.GetTotal().length() + 1];
						strcpy(name, s.GetName().c_str());
						strcpy(id, s.GetID().c_str());
						strcpy(active, s.GetActive().c_str());
						strcpy(recovered, s.GetRecovered().c_str());
						strcpy(deaths, s.GetDeaths().c_str());
						strcpy(total, s.GetTotal().c_str());
						
						string st,sh;
						fstream file("bin/temp.txt", ios::out);
						file << "State\t\t: " << name << "\nState ID\t\t: " << id <<"\nActive cases\t: " << active <<"\nTotal Recovered\t: " << recovered <<"\nTotal Deaths\t: " << deaths <<"\nTotal cases\t: " << total;
						file.close();
						
						file.open("bin/temp.txt", ios::in);
						getline(file,sh);
						while (!file.eof()){
							st.append(sh);
							st.append("\n");
							getline(file,sh);
						}
						file.close();
						MessageBox(hwnd,st.c_str(),"Search Results:",MB_OK);
						remove("bin/temp.txt");
						SetWindowText(hwndTxtBox, "");
					}
					else
						MessageBox(hwnd,"Data with the details you searched was not found","Attention",MB_ICONEXCLAMATION);
						SetWindowText(hwndTxtBox, "");
                	break;
                }
                
                	
            }
			break;
		}
		
		case WM_PAINT: {
			
			PAINTSTRUCT ps;
			TCHAR greeting[] = _T("Welcome to COVID-19 Tracking Application");
   			HDC hdc, hdcMem;
   			HFONT hFont, hOldFont;
   			BITMAP bitmap;
   			HGDIOBJ oldBitmap;
   			HBITMAP hBitmap01 = (HBITMAP)LoadImage(NULL, "Covid.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
   			
   			hdc = BeginPaint(hwnd, &ps);
   			hdcMem = CreateCompatibleDC(hdc);
   			oldBitmap = SelectObject(hdcMem, hBitmap01);
   			
   			GetObject(hBitmap01, sizeof(bitmap), &bitmap);
			BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
			
			SelectObject(hdcMem, oldBitmap);
   	 		DeleteDC(hdcMem);
			
   			hFont = CreateFont (24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
							ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
							DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"));
   			hOldFont = (HFONT) SelectObject(hdc, hFont);
			SetTextColor(hdc,RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);
   			TextOut(hdc, 90, 20, greeting, _tcslen(greeting));
   			
   			EndPaint(hwnd, &ps);
   			break;
   			
			
   		}
   		
   		case WM_SETFONT: {
   			HFONT hFont = CreateFont (11, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, 
							ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
							DEFAULT_PITCH | FF_DONTCARE, TEXT("Times New Roman"));
   			break;
   		}
   		
   		case WM_CTLCOLORSTATIC:{
   			WORD CtrlEsitoID = GetDlgCtrlID((HWND)lParam);
            if (CtrlEsitoID != BigTxtBox){
    			HDC hdcStatic = (HDC)wParam; // or obtain the static handle in some other way
    			SetTextColor(hdcStatic, RGB(255, 255, 255)); // text color
    			SetBkMode(hdcStatic, TRANSPARENT);
    			return (LRESULT)GetStockObject(NULL_BRUSH);
    		}
			break;
			
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}

	return 0;
}
