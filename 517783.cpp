#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
	Dung cai cmd nay de test
	g++ 517783.cpp | .\a.exe [may chu cai ghi lien nhau]
	g++ 517783.cpp | .\a.exe cape

	De ti chinh lai may chu cai ghi cach nhau giong trong file

	A` voi lai cai dem so tu` no bi nguoc xuong duoi, de ti xem cach chinh lai
*/

struct Node
{
	Node *child[26];
	bool terminal;
};

Node *CreateNode()
{
	Node *n = new Node();
	for (int i = 0; i < 26; i++)
	{
		n->child[i] = NULL;
	}
	n->terminal = false;
	return n;
}

void InsertNode(Node *&root, string key, int d = 0)
{
	if (root == NULL)
		root = CreateNode();
	int value = key[d] - 'a';
	if (d == key.length())
	{
		root->terminal = true;
		return;
	}
	InsertNode(root->child[value], key, d + 1);
}

bool FindNode(Node *root, string key, int d)
{
	if (root == NULL)
		return false;
	if (d == key.length())
		return true;
	int c = key[d] - 'a';
}

void PrintTrie(Node *root, string s = "")
{
	if (root->terminal)
	{
		cout << s << endl;
	}

	for (int i = 0; i < 26; i++)
	{
		if (root->child[i] != NULL)
		{
			char c = i + 'a';
			string newS = s + c;
			PrintTrie(root->child[i], newS);
		}
	}
}

void PrintWordRecursize(Node *root, bool *check, string s = "")
{
	if (root == NULL)
	{
		return;
	}
	if (root->terminal)
	{
		cout << s << endl;
	}

	for (int i = 0; i < 26; i++)
	{
		if (root->child[i] != NULL && check[i])
		{
			char c = i + 'a';
			string newS = s + c;
			PrintWordRecursize(root->child[i], check, newS);
		}
	}
}
void CountWord(Node *root, bool *check, int &num, string s = "")
{
	if (root == NULL)
		return;
	if (root->terminal)
	{
		num++;
	}

	for (int i = 0; i < 26; i++)
	{
		if (root->child[i] != NULL && check[i])
		{
			char c = i + 'a';
			string newS = s + c;
			CountWord(root->child[i], check, num, newS);
		}
	}
}
void PrintAllWord(Node *root, string words)
{
	bool *check = new bool[26]{false};
	int n = words.length();
	for (int i = 0; i < n; i++)
	{
		check[words[i] - 'a'] = true;
	}
	int Num = 0;
	CountWord(root, check, Num);
	cout << Num << endl;
	PrintWordRecursize(root, check);
}

void ReadDict(Node *&root, string file_name)
{
	ifstream file(file_name);
	if (!file.is_open())
	{
		return;
	}
	string s;
	while (!file.eof())
	{
		getline(file, s);
		InsertNode(root, s);
	}
}

int main(int argc, char *argv[])
{
	Node *root = NULL;
	ReadDict(root, "Dict1.txt");
	// PrintTrie(root);ay

	cout << "\n\n\n\n\n";
	string words;
	if (argc == 1)
	{
		cout << "Nhap cac ki tu : ";
		cin >> words;
	}
	else
	{
		words = argv[1];
	}
	PrintAllWord(root, words);
	system("pause");
}