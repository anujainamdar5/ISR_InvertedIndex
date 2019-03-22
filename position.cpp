#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

class model
{

private:
	ifstream rfile,fluff_is;
	ofstream wfile,fluff_os;
	string word,fluff_word;
	int i;

public:

string remove_puntuations()  //Removes puntuations and spearates out the words onto single line
{
	int pos=0,word_pos=0;
	char c;
	if(rfile.is_open())
		{
			while(rfile.get(c))
			{
			if(!(c>32&&c<65)) 
				wfile<<c;	
				pos++;
			if(c==' ')
			{				
				wfile<<" "<<word_pos; 	
				wfile<<endl;
				word_pos=pos;
			}			
			}
			return "Words extracted successfully.\n";
		}
		else
			return "ERROR: Couldn't open the files.\n";
}

string open_files(char input_file[25], char output_file[25])  //Initializes the file I/O streams
{
	rfile.open(input_file);
	wfile.open(output_file);
	return "Files opened successfully.\n";
}

string remove_stop_words()  //Removes Fluff Words
{
	int flag=0,times_scanned=0;
	if(rfile.is_open())
	{
		while(!rfile.eof())
		{
			rfile>>word;
		 	if(rfile.eof())
					{
						rfile.close();
						wfile.close();
						break;
					}	
			cout<<word<<endl;
			fluff_is.open("fluff_words.txt");
			if(fluff_is.is_open())
			{
				while(!fluff_is.eof())
				{
				fluff_is>>fluff_word;
				if(strcmp(word.c_str(),fluff_word.c_str())==0)
					{
					flag=1;
					cout<<word<<" in fluff loop"<<endl;					
					rfile>>word;
					if(rfile.eof())
					{
						rfile.close();
						wfile.close();
					}
					break;
					}
				}
				if(flag==0)
				{
					wfile<<word<<"\t";
					rfile>>word;
					if(rfile.eof())
					{
						rfile.close();
						wfile.close();
						break;
					}						
					wfile<<word;
					
					wfile<<endl;
				}
					fluff_is.close();
			}
				
				flag=0;
				
			if(rfile.eof())
			{
				rfile.close();
				wfile.close();
			}	
		}
		
		
		return "Fluff words removed successfully.\n";
	}
	else
		return "ERROR: Couldn't open the files.\n";
}

string close_files()
{
	rfile.close();
	wfile.close();
	return "Files closed successfully.\n";	
}
	
};

int main()
{
model m1;

// Extracting words and removing puntuations and assigning positions
char source_file[]="inv1.txt", destination_file[]="inv1_pos.txt";
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_puntuations();
cout<<m1.close_files();
//Stop word removal
strcpy(source_file,"inv1_pos.txt"); 
strcpy(destination_file,"i1.txt");
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_stop_words();
cout<<m1.close_files();

strcpy(source_file,"inv_doc2.txt");
strcpy(destination_file,"inv2.txt");
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_puntuations();
cout<<m1.close_files();
//Stop word removal
strcpy(source_file,"inv2.txt"); 
strcpy(destination_file,"i2.txt");
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_stop_words();
cout<<m1.close_files();

strcpy(source_file,"inv_doc3.txt");
strcpy(destination_file,"inv3.txt");
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_puntuations();
cout<<m1.close_files();
//Stop word removal
strcpy(source_file,"inv3.txt"); 
strcpy(destination_file,"i3.txt");
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_stop_words();
cout<<m1.close_files();

strcpy(source_file,"inv_doc4.txt");
strcpy(destination_file,"inv4.txt");
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_puntuations();
cout<<m1.close_files();
//Stop word removal
strcpy(source_file,"inv4.txt"); 
strcpy(destination_file,"i4.txt");
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_stop_words();
cout<<m1.close_files();

strcpy(source_file,"inv_doc5.txt");
strcpy(destination_file,"inv5.txt");
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_puntuations();
cout<<m1.close_files();
//Stop word removal
strcpy(source_file,"inv5.txt"); 
strcpy(destination_file,"i5.txt");
cout<<m1.open_files(source_file,destination_file);
cout<<m1.remove_stop_words();
cout<<m1.close_files();

return 0;
}
