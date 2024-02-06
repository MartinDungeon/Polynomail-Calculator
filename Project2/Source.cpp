#include "Poly.h"
#include <fstream>
using namespace std;
vector<PolyData>Poly1, Poly2;
vector<SavedOperation>fileData;
Poly poly;

struct Strings
{
	string s1, s2;
	int operation;
}userInput;

void readFile()
{
	ifstream File("Data.txt"), size("Size.txt");
	int fileSize;
	size >> fileSize;
	fileData.resize(fileSize);
	if (File.good())
	{
		for (int i=0 ; i<fileData.size() ; i++)
		{
			SavedOperation savedOperation;
			File >> savedOperation.poly1 >> savedOperation.poly2 >> savedOperation.operation >> savedOperation.ans;
			fileData[i]=savedOperation;
		}
	}
	else
	{
		ofstream newFile("Data.txt"), size("Size.txt");
		newFile.close();
	}
	File.close();
}

bool checkAnsInFile()
{
	for (auto i : fileData)
	{
		if ( ( (userInput.s1 == i.poly1 && userInput.s2 == i.poly2) || (userInput.s1 == i.poly2 && userInput.s2 == i.poly1) ) && userInput.operation == i.operation)
		{
			cout << i.ans << endl;
			return true;
		}
	}
	return false;
}

void saveDataInFile()
{
	ofstream File("Data.txt"), size("Size.txt");
	size << fileData.size();
	for (auto i : fileData)
		File << i.poly1 << endl << i.poly2 << endl << i.operation << endl << i.ans << endl;
	File.close();
}

void takeInput()
{
	cout << "Enter the first Polynomial: ";
	cin >> userInput.s1;
	cout << "Enter the second Polynomial: ";
	cin >> userInput.s2;
}

void selectOperation()
{
	cout << "Choose the Operation (eg. 1 -> Addition, 2 ->Subtraction, 3 -> Multiplication): ";
	cin >> userInput.operation;

	if (!checkAnsInFile())
	{
		SavedOperation newSavedOperation;
		newSavedOperation.poly1 = userInput.s1;
		newSavedOperation.poly2 = userInput.s2;
		newSavedOperation.operation = userInput.operation;

		Poly1 = poly.stringDeclaration(userInput.s1);
		Poly2 = poly.stringDeclaration(userInput.s2);
		string ans;
		if (userInput.operation == 1) ans = poly.add(Poly1, Poly2);
		else if (userInput.operation == 2) ans = poly.subtract(Poly1, Poly2);
		else if (userInput.operation == 3) ans = poly.multiply(Poly1, Poly2);
		newSavedOperation.ans = ans;
		fileData.push_back(newSavedOperation);
	}
}

void exitOrContinue()
{
	cout << "Press enter key to continue or Enter 0 to exit: ";
	string choice;
	cin.ignore();
	getline(cin, choice);
	if (choice == "0")
	{
		saveDataInFile();
		exit(1);
	}
}

void main()
{
	while (true)
	{
		system("cls");
		readFile();
		takeInput();
		selectOperation();
		exitOrContinue();
	}
	system("pause");
}