#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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

void PrintWordRecursive(Node *root, bool *check, string s = "")
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
			PrintWordRecursive(root->child[i], check, newS);
		}
	}
}
int CountWord(Node *root, bool *check, string s = "")
{
	int count = 0;
	if (root == NULL)
		return count;
	if (root->terminal)
	{
		count ++;
	}

	for (int i = 0; i < 26; i++)
	{
		if (root->child[i] != NULL && check[i])
		{
			char c = i + 'a';
			string newS = s + c;
			count += CountWord(root->child[i], check, newS);
		}
	}

	return count;
}
void PrintAllWord(Node *root, string words)
{
	//SETUP
	bool *check = new bool[26]{false};
	int n = words.length();
	for (int i = 0; i < n; i += 2)
	{
		check[words[i] - 'a'] = true;
	}

	cout << CountWord(root, check) << endl;

	PrintWordRecursive(root, check);
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
	ReadDict(root, "Dic.txt");
	string words;
	cout << "Nhap cac ki tu : ";
	getline(cin, words);
	PrintAllWord(root, words);
}