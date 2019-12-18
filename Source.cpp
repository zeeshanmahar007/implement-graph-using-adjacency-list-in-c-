#include<iostream>
#include<string>
#include<fstream>
using namespace std;
static int counter = 0;
struct Egde
{
	float edge_weight = 0.0;
	string Vertex_name;
	Egde* Enext = NULL;
};

struct Vertex
{
	string vertex_data;
	int degree_of_vertex = 1;
	Vertex* Vnext = NULL;
	Egde* Etail = NULL;
	Egde* Ehead = NULL;
};

Vertex* head = NULL;
Vertex* tail = NULL;

Egde* insert_Edge(Vertex* head,string str, float weight)
{
	Egde* ptr = new Egde;
	ptr->Enext = NULL;
	ptr->Vertex_name = str;
	ptr->edge_weight = weight;
	if (head->Ehead == NULL)
	{
		head->Ehead= ptr;
	}
	else
	{
		ptr->Enext = head->Ehead;
		head->Ehead = ptr;
	}

	return ptr;
}

Vertex* insert_vertex(string n)
{
	counter++;
	Vertex* ptr = new Vertex;
	ptr->vertex_data = n;
	ptr->Ehead = NULL;
	ptr->Vnext = NULL;
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->Vnext = ptr;
		tail = ptr;
	}
	return tail;

}
void save_to_file()
{
	ofstream myfile;
	myfile.open("example.txt");
	Egde* p = head->Ehead;
	Vertex* pt = head;
	Vertex* ptr = head;
	myfile << "Vertex  Edge" << endl;
	while (ptr != NULL)
	{
		myfile << ptr->vertex_data << "->\t";
		while (p != NULL)
		{
			myfile <<"("<< p->Vertex_name <<" "<<p->edge_weight <<")"<< " -> ";
			p = p->Enext;
		}

		pt = pt->Vnext;
		if (pt != NULL)
		{
			p = pt->Ehead;
		}
		ptr = ptr->Vnext;
		myfile << endl;
	}
	myfile << endl;
	myfile.close();
}

void display_degree_of_Vertex()
{
	Vertex* ptr = head;
	cout << "Vertex  Edge" << endl;
	while (ptr != NULL)
	{
		cout <<ptr->vertex_data<<"  "<< ptr->degree_of_vertex<< endl;
		ptr = ptr->Vnext;
	}
	cout << endl;
}

Vertex* search_vertex(string n)
{
	Vertex* ptr = head;
	while (ptr != NULL)
	{
		if (ptr->vertex_data == n)
		{
			return ptr;
		}
		else
		{
			ptr = ptr->Vnext;
		}
	}
	return NULL;
}
Egde* search_Egde(Vertex *p)
{
	Egde* ptr = p->Ehead;
	while (ptr != NULL)
	{
		if (ptr == NULL)
		{
			return ptr;
		}
		else
		{
			ptr = ptr->Enext;
		}
	}
	return ptr;
}
void create_adjancy_list(fstream &myReadFile)
{
	Egde* ptr = NULL;
	Vertex* p = NULL;
	myReadFile.open("Protiens.txt");
	string V1, V2;
	float E;
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			myReadFile >> V1 >> V2 >> E;
			Vertex* ptr = NULL;
			Vertex* p = search_vertex(V1);
			Vertex* pt = search_vertex(V2);
			if (p == NULL)
			{
				ptr = insert_vertex(V1);
				insert_Edge(ptr, V2, E);
			}
			else
			{
				p->degree_of_vertex++;
				insert_Edge(p, V2, E);
			}

			if (pt == NULL)
			{
				ptr = insert_vertex(V2);
				insert_Edge(ptr, V1, E);
			}
			else
			{
				pt->degree_of_vertex++;
				insert_Edge(pt, V1, E);
			}
		}
		myReadFile.close();
	}
	else
	{
		cout << "File Not open!!!" << endl;
	}
}
void update_weight_of_edge()
{
	int count=0;
	Vertex* ptr = head;
	Egde* ptr1 = head->Ehead;
	Egde* ptr2 = NULL;
	ptr2 = search_vertex(ptr1->Vertex_name)->Ehead;


	while (ptr != NULL)
	{
		while (ptr1!=NULL)
		{
			while (ptr2 != NULL)
			{
				if (ptr1->Vertex_name == ptr2->Vertex_name)
				{
					count++;
				}
				else
				{
					if (ptr2->Enext != NULL)
					{
						ptr2 = ptr2->Enext;
					}
				}
			}
			ptr1 = ptr1->Enext;
		}
		ptr = ptr->Vnext;
	}






}
int main()
{
	fstream myReadFile;
	create_adjancy_list(myReadFile);

	display_degree_of_Vertex();
	save_to_file();

	system("pause");
}
