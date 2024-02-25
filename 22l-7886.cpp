#include<iostream>
#include<fstream>
using namespace std;

void getdata(char*& arr, int& s)
{
	cout << "ENTER 4 TO 5 SENTENCES: ";
	cin.getline(arr, s);

	//ifstream fr;
	//fr.open("data.txt");
	//char temp, i = 0;
	//while (!fr.eof())
	//{
	//	fr >> temp;
	//	arr[i] = temp;
	//	i++;
	//}
	//fr.close();

}

void print(const char* const* const& datadictionary, int& rows)
{
	cout << "the tokenized data is: " << endl;
	int j;
	for (int i = 0; i < rows; i++)
	{
		j = 0;
		while (datadictionary[i][j] != '\0')
		{
			cout << datadictionary[i][j];
			j++;
		}
		cout << endl;
	}
	cout << "---" << endl;
}

bool duplication(char*& temp, char*& filtered, int t_count)
{
	bool flag = true;
	int c = 0;
	for (int i = 0; filtered[i] != '\0'; i++)
	{
		if (filtered[i] == temp[0] && (filtered[i - 1] == '#' || i == 0))
		{
			if (t_count == 1)
			{
				if (filtered[i + 1] == '#')
				{
					flag = false;
				}
				if (filtered[i + 1] != '#')
				{
					flag = true;
				}
			}
			else
			{
				int k = 1;
				c = 1;
				for (int j = i + 1; filtered[j] != '\0'; j++)
				{
					if (temp[k] == filtered[j])
					{
						c++;
					}
					k++;
				}
				if (c == t_count)
				{
					flag = false;
				}
			}
		}
	}

	return flag;
}

void Tokenize(char*& arr, char**& datadictionary, int& row)
{
	int size = strlen(arr);
	char* filtered = new char[2500];
	char* temp = new char[100];
	int f_count = 0, t_count = 0;
	filtered[f_count] = '\0';

	for (int i = 0; i < size; i++) // filteration of unique words in another array. 
	{
		if (arr[i] != ' ' && arr[i] != '.')
		{
			temp[t_count] = arr[i];
			t_count++;
		}
		if (arr[i] == ' ' || (arr[i] == '.' && arr[i + 1] != ' '))
		{
			bool flag = duplication(temp, filtered, t_count);
			if (flag == true)
			{
				for (int i = 0; i < t_count; i++)
				{
					filtered[f_count] = temp[i];
					f_count++;
				}
				filtered[f_count] = '#';
				f_count++;
				filtered[f_count] = '\0';
			}
			for (int i = 0; i < t_count; i++)
			{
				temp[i] = '\0';
			}
			t_count = 0;
		}
	}

	delete[] temp;
	temp = nullptr;
	delete[] arr;
	arr = filtered;
	filtered = nullptr;
	size = f_count;

	int word_count = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == '#')
			word_count++;
	}
	datadictionary = new char* [word_count];
	row = word_count;

	int letter_count = 0, k = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] != '#')
		{
			letter_count++;
		}
		if (arr[i] == '#')
		{
			datadictionary[k] = new char[letter_count + 1];
			k++;
			letter_count = 0;
		}
	}

	int r = 0, c = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] != '#')
		{
			datadictionary[r][c] = arr[i];
			c++;
		}
		if (arr[i] == '#')
		{
			datadictionary[r][c] = '\0';
			r++;
			c = 0;
		}
	}
}

void store(char***& synonyms, int i)
{
	int number;
	cout << "how many numbers do you want to store: ";
	cin >> number;
	synonyms[i] = new char* [number + 1];
	string k;
	int j;
	for (j = 0; j < number; j++)
	{
		cout << "ENTER SYNONYM NUMBER [" << j + 1 << "] : ";
		cin >> k;
		int s = k.length() + 1, u;
		synonyms[i][j] = new char[s];
		for (u = 0; u < s - 1; u++)
		{
			synonyms[i][j][u] = k[u];
		}
		synonyms[i][j][u] = '\0';
	}
	synonyms[i][j] = new char[1];
	synonyms[i][j][0] = '\0';

}

void synonymsStore(char***& synonyms, char**& datadictionary,int rows)

{
	synonyms = new char** [rows];
	for (int i = 0; i < rows; i++)
	{
		int choice;
		cout << "DO YOU WANT TO STORE SYNONYMS FOR: ";
		int c = 0;
		while (datadictionary[i][c] != '\0')
		{
			cout << datadictionary[i][c];
			c++;
		}
		cout << ". (press 1 for yes OR 0 for no)  ";
		cin >> choice;
		if (choice != 1 && choice != 0)
		{
			do {
				cout << "(press 1 for yes OR 0 for no) ";
				cin >> choice;
			} while (choice != 1 && choice != 0);
		}
		if (choice == 0)
		{
			synonyms[i] = new char* [1];
			synonyms[i][0] = new char[1];
			synonyms[i][0][0] = '\0';
			continue;
		}
		if (choice == 1)
		{
			store(synonyms, i);
		}


	}

}

void printsynonyms(const char* const* const* const& synonyms, const char* const* const& datadictionary, int r)
{
	cout << "THE STORED SYNONYMS ARE: " << endl;
	for (int i = 0; i < r; i++)
	{
		int c = 0, b = 0, a = 0;
		while (datadictionary[i][c] != '\0')
		{
			cout << datadictionary[i][c];
			c++;
		}
		cout << ": ";
		while (synonyms[i][a][b] != '\0')
		{
			while (synonyms[i][a][b] != '\0')
			{
				cout << synonyms[i][a][b];
				b++;
			}
			cout << " ";
			a++;
			b = 0;
		}
		cout << endl;
	}
}

void matched(char*& usecase, char**& datadictionary, int rows)
{
	char* temp = new char[100];
	int size = strlen(usecase);
	int t_count = 0;
	int m_count[100], mc = 0;
	m_count[mc] = -1;

	for (int i = 0; i < size; i++)
	{
		if (usecase[i] != ' ' && usecase[i] != '.')
		{
			temp[t_count] = usecase[i];
			t_count++;
		}
		if (usecase[i] == ' ' || (usecase[i] == '.' && usecase[i + 1] != ' '))
		{
			int k = 0, c = 0, j;
			for (j = 0; j < rows; j++)
			{
				k = 0;
				while (datadictionary[j][k] != '\0')
				{
					if (datadictionary[j][k] == temp[k])
					{
						c++;
					}
					k++;
				}
				if (c == t_count)
				{
					m_count[mc] = j;
					mc++;
					m_count[mc] = -1;
				}
				c = 0;
			}
			t_count = 0;
			for (int i = 0; i < t_count; i++)
			{
				temp[i] = '\0';
			}
		}
	}
	for (int i = 0; i < mc; ++i)
	{
		for (int j = i + 1; j < mc;)
		{
			if (m_count[i] == m_count[j])
			{
				for (int k = j; k < mc - 1; ++k)
					m_count[k] = m_count[k + 1];
				--mc;
			}
			else
				++j;
		}
	}

	int y = 0;
	for (int i = 0; i < mc; i++)
	{
		if (m_count[i] != -1)
		{
			y++;
		}
		else
			break;
	}
	cout << "THERE ARE [" << mc << "] WORDS FOUND IN DICTIONARY: " << endl;
	for (int k = 0; k < mc; k++)
	{
		int	j = m_count[k], n = 0;
		while (datadictionary[j][n] != '\0')
		{
			cout << datadictionary[j][n];
			n++;
		}
		cout << endl;
	}
	cout << endl;


	delete[] temp;
	temp = nullptr;

}

void unmatched(char*& usecase, char**& datadictionary, int rows) 
{
	int s = strlen(usecase);
	char* temp = new char[100];
	int t_count = 0;

	cout << "THE UNMATCHED WORDS ARE: " << endl;
	for (int i = 0; i < s; i++)
	{
		if (usecase[i] != ' ' && usecase[i] != '.')
		{
			temp[t_count] = usecase[i];
			t_count++;
		}
		if (usecase[i] == ' ' || (usecase[i] == '.' && usecase[i + 1] != ' '))
		{
			int k = 0, c = 0, j;
			bool flag = false;
			for (j = 0; j < rows; j++)
			{
				k = 0;
				while (datadictionary[j][k] != '\0')
				{
					if (datadictionary[j][k] != temp[k])
					{
						flag = true;
					}
					k++;
				}
				if (flag == true)
				{
					c++;
				}
				flag = false;
			}
			if (c == rows)
			{
				for (int i = 0; i < t_count; i++)
				{
					cout << temp[i];
				}
				cout << endl;
			}
			t_count = 0;
			for (int i = 0; i < t_count; i++)
			{
				temp[i] = '\0';
			}
		}
	}

	delete[] temp;
	temp = nullptr;

}

void deallocate(char*& t1, char*& t2, char*& t3, char**& data, char***& synon,int rows)
{
	delete[] t1;
	delete[] t2;
	delete[] t3;
	t1 = nullptr;
	t2 = nullptr;
	t3 = nullptr;

	for (int i = 0; i < rows; i++)
	{
		delete[] data[i];
	}
	delete[] data;
	data = nullptr;

	for (int i = 0; i < rows; i++)
	{
		int a = 0;
		while (synon[i][a][0] != '\0')
		{
			a++;
		}
		for (int j = 0; j <= a; j++)
		{
			delete[] synon[i][j];
		}
		delete[] synon[i];
	}
	delete[] synon;
	synon = nullptr;
}

void replacewithSynonym(char*& usecase, char**& datadictionary, char***& synonyms, int row)
{
	char* temp = new char[100];
	int size = strlen(usecase);
	int t_count = 0;
	char* changed = new char[2500];
	int changed_c = 0;

	for (int i = 0; i < size; i++)
	{
		if (usecase[i] != ' ' && usecase[i] != '.')
		{
			temp[t_count] = usecase[i];
			t_count++;
		}
		if (usecase[i] == ' ' || (usecase[i] == '.' && usecase[i + 1] != ' '))
		{
			int k = 0, c = 0, j;
			bool flag = true;
			for (j = 0; j < row; j++)
			{
				k = 0;
				while (datadictionary[j][k] != '\0')
				{
					if (datadictionary[j][k] == temp[k])
					{
						c++;
					}
					k++;
				}
				if (c == t_count)
				{
					flag = false;
					int z = 0;
					if (synonyms[j][0][0] != '\0')
					{
						flag = true;
						while (synonyms[j][0][z] != '\0')
						{
							changed[changed_c] = synonyms[j][0][z];
							changed_c++;
							z++;
						}
						changed[changed_c] = ' ';
						changed_c++;
					}
					break;
				}
				else
				{
					flag = false;
				}
				c = 0;
			}
			if (flag == false)
			{
				for (int i = 0; i < t_count; i++)
				{
					changed[changed_c] = temp[i];
					changed_c++;
				}
				changed[changed_c] = ' ';
				changed_c++;
			}
			t_count = 0;
			for (int i = 0; i < t_count; i++)
			{
				temp[i] = '\0';
			}
		}
	}

	cout << "THE SENTENCE WITH CHANGED SYNONYMS IS: " << endl;
	for (int i = 0; i < changed_c; i++)
	{
		cout << changed[i];
	}
	cout<<'.' << endl;

	delete[] changed;
	changed = nullptr;

	delete[] temp;
	temp = nullptr;
}


int main()
{
	int s = 2500;
	char* arr = new char[s];
	char** datadictionary = NULL;
	int rows;

	getdata(arr, s);
	Tokenize(arr, datadictionary, rows);
	print(datadictionary, rows);

	char*** synonyms = NULL;

	synonymsStore(synonyms, datadictionary, rows);
	printsynonyms(synonyms, datadictionary, rows);

	char* usecase = new char[s];

	cin.ignore();
	getdata(usecase, s);
	matched(usecase, datadictionary, rows);
	unmatched(usecase, datadictionary, rows);

	char* usecase2 = new char[s];

	getdata(usecase2, s);
	matched(usecase2, datadictionary, rows);
	replacewithSynonym(usecase2, datadictionary, synonyms, rows);

	deallocate(arr, usecase, usecase2, datadictionary, synonyms, rows);
	system("pause>0");
	return 0;
}