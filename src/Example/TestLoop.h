#pragma once

#include "./TestLoopMacros.h"

#include <iostream>
#include <string>
#include <map>

void TestLoop(std::map<std::string, intptr_t>& components)
{
	using namespace std;

	string command;

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
			cout << "IsOutClipping\n";
			cout << "CompDelete\n";
			cout << "CompGetIn\n";
			cout << "CompGetOut\n";
			cout << "CompSetOut\n";
			// Creators
			cout << "CompAddLP\n",
			cout << "CompAddOsc\n",
			// Getters
			cout << "LPGetCutoff\n",
			cout << "OscGetPhase\n",
			cout << "OscGetWave\n",
			cout << "OscGetFreq\n",
			cout << "OscGetAmp\n",
			cout << "MasterGetAmp\n",
			// Setters
			cout << "LPSetCutoff\n",
			cout << "OscSetWave\n",
			cout << "OscSetPhase\n",
			cout << "OscSetFreq\n",
			cout << "OscSetAmp\n",
			cout << "MasterSetAmp\n",
			cout << "--Type \"exit\" to Exit.--" << endl;
		}
		else if (command == "comps")
		{
			cout << "--Components:--\n";

			for (const auto& component : components)
				cout << component.first << "\n";

			cout << "--End--" << endl;
		}
		else if (command == "IsOutClipping")
		{
			if (IsOutClipping())
				cout << "Yes" << endl;
			else
				cout << "No" << endl;
		}
		else if (command == "CompDelete")
		{
			COMPLOOKUP
			{
				CompDelete(it->second);
				cout << "Component " << it->first << " Removed." << endl;
				components.erase(it);
			}
		}
		else if (command == "CompGetOut")
		{
			COMPLOOKUP
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
		else if (command == "CompSetOut")
		{
			COMPLOOKUP
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
		else if (command == "MasterGetAmp")
		{
			cout << "Current Amplitude: " << MasterGetAmp() << "." << endl;
		}
		else if (command == "MasterSetAmp")
		{
			cout << "Enter New Amplitude (float, 0.0f - 1.0f)." << endl;
			cin >> command;

			if (command == "exit") break;

			try
			{
				MasterSetAmp(stof(command));
				cout << "New Amplitude: " << MasterGetAmp() << "." << endl;
			}
			catch (invalid_argument)
			{
				cout << "Invalid Input Value. Expected float." << endl;
			}
		}
		CREATOR(Osc, Oscillator)
		CREATOR(LP, LP Filter)

		GETTER(Osc, Amp, Oscillator, Amplitude)
		GETTER(Osc, Freq, Oscillator, Frequency)
		GETTER(Osc, Phase, Oscillator, Phase)
		GETTER(Osc, Wave, Oscillator, Wave)
		GETTER(LP, Cutoff, LP Filter, Cutoff Frequency)

		SETTER(Osc, Freq, Oscillator, Frequency, float, (float, 0.0f - 20000.0f))
		SETTER(Osc, Phase, Oscillator, Phase, float, (float, 0.0f - 1.0f))
		SETTER(Osc, Amp, Oscillator, Amplitude, float, (float, 0.0f - 1.0f))
		SETTER(Osc, Wave, Oscillator, Wave, int, (int, 0 - 4 : Sine, Square, Triangle, Saw, Noise))
		SETTER(LP, Cutoff, LP Filter, Cutoff Frequency, float, (float, 1.0f - 20000.0f))
		else
		{
			cout << "Invalid Command. ";
		}

		cout << "--Enter Valid Command or \"commands\" For a List of Valid Commands or \"comps\" For List of Existing Components.--" << endl;
	}
}
