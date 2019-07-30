#include "API.h"

#include <iostream>
#include <string>
#include <map>

int main(int argc, char** argv)
{
	using namespace std;

	string command;
	map<string, intptr_t> components;

	InitAudio();
	MasterSetAmp(0.1);

	components["osc1"] = CompAddOsc(0, 0.0);
	components["osc2"] = CompAddOsc(0, 0.0);
	components["osc3"] = CompAddOsc(0, 0.0);
	
	CompSetOut(components["osc1"], MasterComp());
	OscSetFreq(components["osc1"], 220.0);
	OscSetAmp(components["osc1"], 0.1);
		
	CompSetOut(components["osc2"], MasterComp());
	OscSetFreq(components["osc2"], 440.0);
	OscSetAmp(components["osc2"], 0.3);
		
	CompSetOut(components["osc3"], components["osc1"]);
	OscSetFreq(components["osc3"], 880.0);
	OscSetAmp(components["osc3"], 1.0);
	   
	cout << "--Audio Started. Enter Valid Command, \"commands\" For a List of Valid Commands or \"comps\" For List of Existing Components.--" << endl;

	while (command != "exit")
	{
		cin >> command;

		if (command == "exit")
		{
			break;
		}
		else if (command == "commands")
		{
			cout << "--Valid Commands:--\n";
			cout << "CompAddOsc\n";
			cout << "CompDelete\n";
			cout << "CompGetIn\n";
			cout << "CompGetOut\n";
			cout << "CompSetOut\n";
			cout << "MasterGetAmp\n";
			cout << "MasterSetAmp\n";
			cout << "OscGetAmp\n";
			cout << "OscSetAmp\n";
			cout << "OscGetFreq\n";
			cout << "OscSetFreq\n";
			cout << "--Type \"exit\" to Exit.--" << endl;
		}
		else if (command == "comps")
		{
			cout << "--Components:--\n";

			for (const auto& component : components)
				cout << component.first << "\n";

			cout << "--End--" << endl;
		}
		else if (command == "CompGetOut")
		{
			cout << "Enter Component Name." << endl;
			cin >> command;

			if (command == "exit") break;

			auto it = components.find(command);
			if (it == components.end())
				cout << "Could Not Find Component: " << command << "." << endl;
			else
			{
				if (MasterComp() == CompGetOut(it->second))
				{
					cout << "Component: " << command << " Output Component: Master Mixer." << endl;
				}

				auto it2 = components.begin();

				while (it2 != components.end())
				{
					if (it2->second == CompGetOut(it->second))
					{
						cout << "Component: " << command << " Output Component: " << it2->first << "." << endl;
					}
					it2++;
				}
			}
		}
		else if (command == "CompGetIn")
		{
			cout << "Enter Component Name or \"MasterComp\" For Master Output." << endl;
			cin >> command;

			if (command == "exit") break;

			if (command == "MasterComp")
			{ 
				for (const auto& input : CompGetIn(MasterComp()))
				{
					for (const auto& component : components)
					{
						if (component.second == input)
						{
							cout << "Component: Master Mixer Input Component: " << component.first << "." << endl;
						}
					}
				}
			}
			else
			{
				auto it = components.find(command);
				if (it == components.end())
					cout << "Could Not Find Component: " << command << "." << endl;
				else
				{
					for (const auto& input : CompGetIn(it->second))
					{
						for (const auto& component : components)
						{
							if (component.second == input)
							{
								cout << "Component: " << command << " Input Component: " << component.first << "." << endl;
							}
						}
					}
				}
			}
		}
		else if (command == "MasterGetAmp")
		{
			cout << "Current Amplitude: " << MasterGetAmp() << "." << endl;
		}
		else if (command == "MasterSetAmp")
		{
			cout << "Enter New Amplitude (double, 0.0 - 1.0)." << endl;
			cin >> command;

			if (command == "exit") break;

			try
			{
				MasterSetAmp(stod(command));
				cout << "New Amplitude: " << MasterGetAmp() << "." << endl;
			}
			catch (invalid_argument)
			{
				cout << "Invalid Input Value. Expected Double." << endl;
			}
		}
		else if (command == "CompDelete")
		{
			cout << "Enter Component Name." << endl;
			cin >> command;

			if (command == "exit") break;

			auto it = components.find(command);
			if (it == components.end())			
				cout << "Could Not Find Component: " << command << "." << endl;
			else
			{
				CompDelete(it->second);
				cout << "Component " << it->first << " Removed." << endl;
				components.erase(it);
			}
		}
		else if (command == "CompSetOut")
		{
			cout << "Enter Component Name." << endl;
			cin >> command;

			if (command == "exit") break;

			auto it = components.find(command);
			if (it == components.end())
				cout << "Could Not Find Component: " << command << "." << endl;
			else
			{
				cout << "Enter Component Name or \"MasterComp\" For Master Output or 0 For No Output." << endl;
				cin >> command;

				if (command == "exit") break;

				if (command == "MasterComp")
				{
					CompSetOut(it->second, MasterComp());
					cout << "Component " << it->second << " Output Connected To Master Mixer." << endl;;
				}
				else if (command == "0")
				{
					CompSetOut(it->second, 0);
					cout << "Component " << it->second << " Output Disconnected." << endl;
				}
				else
				{
					auto it2 = components.find(command);
					if (it2 == components.end())
						cout << "Could Not Find Component: " << command << "." << endl;
					else
					{						
						if (CompSetOut(it->second, (*it2).second))
							cout << "Connected " << it->second << " to " << (*it2).second << "." << endl;
					}
				}
			}
		}
		else if (command == "CompAddOsc")
		{
			cout << "Enter Name For Component." << endl;

			cin >> command;

			if (command == "exit") break;

			auto it = components.find(command);
			if (it == components.end())
			{
				string subcommand;
				double freq;
				cout << "Enter Oscillator Frequency (double, 0.0 - 20000.0)." << endl;
				cin >> subcommand;
				if (subcommand == "exit") break;

				try
				{
					freq = stod(subcommand);
					double amplitude;
					cout << "Enter Oscillator Frequency (double, 0.0 - 1.0)." << endl;
					cin >> subcommand;
					if (subcommand == "exit") break;

					try
					{
						amplitude = stod(subcommand);
						components[command] = CompAddOsc(freq, amplitude);
						cout << "Created Oscillator With Frequency: " << OscGetFreq(components[command]) << " And Amplitude: " << OscGetAmp(components[command]) << "." << endl;
					}
					catch (invalid_argument)
					{
						cout << "Invalid Input Value. Expected Double." << endl;
					}
				}
				catch (invalid_argument)
				{
					cout << "Invalid Input Value. Expected Double." << endl;
				}
			}
			else
				cout << "Component With Name " << command << " Already Exist" << endl;
		}
		else if (command == "OscSetFreq")
		{
			cout << "Enter Component Name." << endl;
			cin >> command;

			if (command == "exit") break;

			auto it = components.find(command);
			if (it == components.end())
				cout << "Could Not Find Component: " << command << "." << endl;
			else
			{		
				string subcommand;
				double freq;
				cout << "Enter New Oscillator Frequency (double, 0.0 - 20000.0)." << endl;
				cin >> subcommand;
				if (subcommand == "exit") break;

				try
				{
					freq = stod(subcommand);
					OscSetFreq(it->second, freq);
					cout << "Oscillator " << it->first <<" Frequency Set To: " << OscGetFreq(components[it->first]) << "." << endl;
				}
				catch (invalid_argument)
				{
					cout << "Invalid Input Value. Expected Double." << endl;
				}
			}
		}
		else if (command == "OscGetFreq")
		{
			cout << "Enter Component Name." << endl;
			cin >> command;

			if (command == "exit") break;

			auto it = components.find(command);
			if (it == components.end())
				cout << "Could Not Find Component: " << command << "." << endl;
			else
				cout << "Oscillator: " << it->first << " Frequency: " << OscGetFreq(it->second) << "." << endl;
		}
		else if (command == "OscSetAmp")
		{			
			cout << "Enter Component Name." << endl;
			cin >> command;

			if (command == "exit") break;

			auto it = components.find(command);
			if (it == components.end())
				cout << "Could Not Find Component: " << command << "." << endl;
			else
			{
				string subcommand;
				double amplitude;
				cout << "Enter New Oscillator Amplitude (double, 0.0 - 1.0)." << endl;
				cin >> subcommand;
				if (subcommand == "exit") break;

				try
				{
					amplitude = stod(subcommand);
					OscSetAmp(it->second, amplitude);
					cout << "Oscillator " << it->first << " Amplitude Set To: " << OscGetAmp(components[it->first]) << "." << endl;
				}
				catch (invalid_argument)
				{
					cout << "Invalid Input Value. Expected Double." << endl;
				}
			}			
		}
		else if (command == "OscGetAmp")
		{
			cout << "Enter Component Name." << endl;
			cin >> command;

			if (command == "exit") break;

			auto it = components.find(command);
			if (it == components.end())
				cout << "Could Not Find Component: " << command << "." << endl;
			else			
				cout << "Oscillator: " << it->first << " Amplitude: "<< OscGetAmp(it->second) <<"." << endl;
		}
		else
		{
			cout << "Invalid Command. ";
		}

		cout << "--Enter Valid Command or \"commands\" For a List of Valid Commands or \"comps\" For List of Existing Components.--" << endl;
	}

	for (const auto & component: components)	
		CompSetOut(component.second, NULL);
	
	for (const auto& component : components)
		CompDelete(component.second);		

	return 0;
}