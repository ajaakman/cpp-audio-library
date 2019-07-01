#include <iostream>
#include <string>

#include "API.h"

using namespace std;

int main(int argc, char** argv)
{
	string command;

	StartAudio();
	cout << "Audio Started. Enter Valid Command or \"Commands\" for List of Valid Commands..." << endl;

	while (command != "exit")
	{
		cin >> command;

		if (command == "exit")
		{
			break;
		}
		else if (command == "Commands")
		{
			cout << "Valid Commands:\n";
			cout << "GetAmplitude\n";
			cout << "SetAmplitude\n";
			cout << "Type \"exit\" to Exit." << endl;
		}
		else if (command == "GetAmplitude")
		{
			cout << "Current Amplitude: " << GetAmplitude() << endl;
		}
		else if (command == "SetAmplitude")
		{
			cout << "Enter New Amplitude (double)." << endl;
			cin >> command;

			if (command == "exit") break;

			try
			{
				SetAmplitude(stod(command));
				cout << "New Amplitude: " << GetAmplitude() << endl;
			}
			catch (invalid_argument)
			{
				cout << "Invalid Input Value. Expected Double." << endl;				
			}
		}
		else
		{
			cout << "Invalid Command. Enter \"Commands\" for List of Valid Commands..." << endl;
		}
	}

	return 0;
}