#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

using namespace std;

typedef struct query_word
{
	char word[10];
	int doc_list[5];
}query_word;


class node
{

	string doc_pos[10][2];
	node *child[20];
	int total;
	char letter;
	char word[12];
	int internal_counter;
public:	
	void insert(node* head, char nword[10], string doc, string pos)
	{
		int i=0,j=0,cno=0;
		node* previous;
		int found=0,letters_matched=0;
		int m=0,ptr_is_blank=0;
		while(i<strlen(nword)&&j<10)
		{
			if(head->child[j]!=NULL)
				if(head->child[j]->letter==nword[i])
				{	
					letters_matched++;
					i++;
					//cout<<endl<<head->child[j]<<" letter is found "<<head->child[j]->letter;
					head=head->child[j];
					j=0;					
					if(head==NULL)
						break;
				}
				else
					j++;
			else
				break;
		}

		while(i<strlen(nword))
		{
			for(j=0;head->child[j]!=NULL&&j<10;j++);
				head->child[j]=new_node();
			head->child[j]->letter=nword[i];
			i++;
			//cout<<endl<<head->child[j]<<" letter is added "<<head->child[j]->letter;	
			previous=head->child[j];
			head=previous;
			ptr_is_blank=0;
		}
		previous=head;
		int written=0;
		for(i=0;previous->doc_pos[i][0]!="\0";i++)
		{
			if(previous->doc_pos[i][0]==doc)
			{
				previous->doc_pos[i][1]=previous->doc_pos[i][1]+','+pos;
				written=1;
				break;
			}
		}
		if(written==0)
		{
			previous->doc_pos[i][0]=doc;
			previous->doc_pos[i][1]=pos;
			strcpy(previous->word,nword);
		}
		previous->total=previous->total+1;
	}

	node* new_node() //Returns address of the new node
	{
		node* pval=NULL;
		pval=new node;
		pval->word[0]='\0';
		for(int i=0;i<10;i++)
			pval->child[i]=NULL;
		pval->internal_counter=0;
		pval->total=0;
		pval->word[0]='\0';
		pval->doc_pos[0][0]="\0";
		return	pval;
	}

	void print_ptr_array(node* head)
	{
		for(int i=0;i<10 && head->child[i]!=NULL;i++)
		{
			if(head->child[i]==NULL)
				break;
		}
	}


	void read_add(node* head,string doc_name)
	{
		string word1, position;
		char word[10];
		ifstream rfile;
		rfile.open(doc_name.c_str());
		if(rfile.is_open())
		{
			while(!rfile.eof())  
			{
				rfile>>word1;
				if(rfile.eof())
					break;
				rfile>>position;
				strcpy(word,word1.c_str());		
				this->insert(head,word,doc_name,position);
			}
			rfile.close();
		}
	}


	node* inverted_index(node* root)
	{
		if(root==NULL)
			return root;
		if(root->word[0]!='\0')
		{
			cout<<"\n"<<root->word;
			for(int j=0; root->doc_pos[j][0]!="\0";j++)
				cout<<"\t "<<root->doc_pos[j][0]<<" "<<root->doc_pos[j][1];
		}
		for(int i=0;root->child[i]!=NULL;i++)
			inverted_index(root->child[i]);
	}

	node* search_word(node* head, char nword[10])
	{
		int i=0,j=0;	
		while(i<strlen(nword)&&j<10)
		{
		if(head->child[j]!=NULL)
			if(head->child[j]->letter==nword[i])
			{	
				//letters_matched++;
				i++;
				head=head->child[j];
				j=0;					
				if(head==NULL)
					break;
			}
			else
				j++;
		else
			break;
		}
		if(strcmp(nword,head->word));
			return head;
	}

	void boolean_model(node* head)
	{
		int pos,i,j,k;
		node* q_ans;
		string input_query[10];
		char buff[12];
		int query_length=0;
		query_word query[5];
		cout<<"\nEnter your query in uppercase:"<<endl;
		for(i=0;i<10;i++)
		{
			cin>>input_query[i];
			if(input_query[i]==".")
				break;
		}
		
		//for(i=0;input_query[i]!="\0";i++)
		//	cout<<"\nINPUT QUERY"<<input_query[i];

		for(i=0;input_query[i]!="\0";i++)
		{
			if(input_query[i]!="AND" && input_query[i]!=".")
			{
				strcpy(query[query_length++].word,input_query[i].c_str());
		//		cout<<"\ncondition true";
			}
		}

		//for(i=0;i<query_length;i++)
		//	cout<<"\nqUERY"<<query[i].word;
		
		//cout<<"\nQuery length = "<<query_length<<" QUERY = "<<query;
		for(i=0;i<query_length;i++)
		{
			q_ans=head->search_word(head,query[i].word);
			for(j=0;j<5;j++)
				query[i].doc_list[j]=0;
			for(j=0;j<q_ans->total;j++)
			{
				strcpy(buff,q_ans->doc_pos[j][0].c_str());
				query[i].doc_list[(int)buff[1]-49]=1;
			}
			
		}
		
		int max_coordination_level=query_length,x=0,wrote=0,co_map[query_length][5];

		for(i=0;i<query_length;i++)
		for(j=0;j<5;j++)
		co_map[i][j]=0;

		while(max_coordination_level>0)
		{
			for(i=0;i<5;i++) //DOCUMENT 
			{
				for(j=0;j<query_length;j++)
				{
					if(query[j].doc_list[i]==1)
						x++;
					if(x==max_coordination_level)
						{
						co_map[max_coordination_level-1][i]=1;											
						
						}
				}
				x=0;
			}
			max_coordination_level--;
		}

		int flag;
		for(j=0;j<5;j++)
		{
			flag=0;
			for(i=query_length-1;i>=0;i--)
			{
				if(flag==0 && co_map[i][j]==1)
					flag=1;
				else if(flag==1 && co_map[i][j]==1)
					co_map[i][j]=0;
			}
		}

	for(i=query_length-1;i>=0;i--)
		{cout<<"\n "<<i+1;
		for(j=0;j<5;j++)
			{
				if(co_map[i][j]==1)
					cout<<"\ti"<<j+1<<".txt";
		
			}
		}
}
};

int main()
{
	node *head,root;
	head=head->new_node();
	head->read_add(head,"i1.txt");
	head->read_add(head,"i2.txt");
	head->read_add(head,"i3.txt");
	head->read_add(head,"i4.txt");
	head->read_add(head,"i5.txt");
	cout<<"________________________________________________________\n INVERTED INDEX \n_________________________________________________";
	cout<<head->inverted_index(head);
	cout<<"\n________________________________________________________";
	cout<<"\n\nMODIFIED BOOLEAN SEARCH\n";
	head->boolean_model(head);
	cout<<endl;
	return 0;
}



/* OUTPUT:

anuja@anuja-Lenovo:~$ g++ boolean.cpp
anuja@anuja-Lenovo:~$ ./a.out
________________________________________________________
 INVERTED INDEX 
_________________________________________________
BEAUTIFUL	 i1.txt 10,52,73,89	 i2.txt 2	 i3.txt 25	 i4.txt 8	 i5.txt 27
BUILT	 i2.txt 45
BLESSED	 i3.txt 0,107	 i4.txt 257	 i5.txt 144
DAY	 i1.txt 20	 i4.txt 23
DAILY	 i2.txt 51
DO	 i1.txt 138
DOING	 i1.txt 164
DOES	 i2.txt 17
DOESNT	 i4.txt 173
DONE	 i5.txt 225
DOUBT	 i5.txt 248
DID	 i1.txt 196
DEAR	 i5.txt 89
SUN	 i1.txt 25	 i4.txt 278
SHINING	 i1.txt 32	 i4.txt 288
SACRIFICE	 i2.txt 78
SEE	 i3.txt 21,78
SPEAK	 i4.txt 122
SMILE	 i4.txt 156
STOPS	 i4.txt 288
EYES	 i1.txt 46	 i2.txt 148
ENTIRE	 i4.txt 81
NATURE	 i1.txt 62
MAKES	 i1.txt 83
MORNING	 i2.txt 126
MEASURE	 i3.txt 122
MEAN	 i4.txt 181
MEANS	 i4.txt 209
MINUTE	 i4.txt 45
LIFE	 i1.txt 99	 i2.txt 12	 i4.txt 0,88,189	 i5.txt 37,236
LOVELY	 i4.txt 128
LOSE	 i5.txt 67
LEARN	 i5.txt 47
PERSEVERANCE	 i1.txt 105
PERSON	 i4.txt 144
PERFECT	 i4.txt 197
PEOPLE	 i3.txt 71,96
PRAYER	 i2.txt 60	 i5.txt 267
PLACES	 i3.txt 52
POWER	 i5.txt 258
HARD	 i1.txt 174
HARDWORK	 i1.txt 125	 i2.txt 92
HAPPEN	 i2.txt 31
HUMILITY	 i2.txt 68
HUMBLE	 i3.txt 45
HOUR	 i4.txt 32
HEALTHY	 i5.txt 120
GET	 i1.txt 151	 i5.txt 81
GIFTS	 i2.txt 115
GOD	 i4.txt 249	 i5.txt 94
GRATEFUL	 i5.txt 199
TRULY	 i5.txt 1930
________________________________________________________

MODIFIED BOOLEAN SEARCH

Enter your query in uppercase:
LIFE     
AND
DAY
AND
BEAUTIFUL
.

 3	i1.txt	i4.txt
 2	i2.txt	i5.txt
 1	i3.txt
anuja@anuja-Lenovo:~$ 





*/
