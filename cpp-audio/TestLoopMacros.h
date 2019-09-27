#pragma once

#define COMPLOOKUP																												\
cout << "Enter Component Name." << endl;																						\
cin >> command;																													\
																																\
if (command == "exit") break;																									\
																																\
auto it = components.find(command);																								\
																																\
if (it == components.end())																										\
	cout << "Could Not Find Component: " << command << "." << endl;																\
else


#define CREATOR(COMP, LNAME)																										\
else if (command == "CompAdd"#COMP)																								\
{																																\
	cout << "Enter Name For Component." << endl;																				\
																																\
	cin >> command;																												\
																																\
	if (command == "exit") break;																								\
																																\
	auto it = components.find(command);																							\
	if (it == components.end())																									\
	{																															\
		components[command] = CompAdd##COMP();																					\
		cout << "Created "#LNAME " " << command << endl;																		\
	}																															\
	else																														\
	{																															\
		cout << "Component With Name " << command << " Already Exist" << endl;													\
	}																															\
}


#define GETTER(COMP, PARAM, LCOMP, LPARAM)																						\
else if (command == #COMP"Get"#PARAM)																							\
{																																\
	COMPLOOKUP																													\
		cout << #LCOMP": " << it->first << " "#LPARAM": " << COMP##Get##PARAM(it->second) << "." << endl;						\
}


#define SETTER(COMP, PARAM, LCOMP, LPARAM, TYPE, MESSAGE)																		\
else if (command == #COMP"Set"#PARAM)																							\
{																																\
	COMPLOOKUP																													\
	{																															\
		string subcommand;																										\
		TYPE val;																												\
		cout << "Enter New "#LCOMP" "#LPARAM" "#MESSAGE"." << endl;																\
		cin >> subcommand;																										\
		if (subcommand == "exit") break;																						\
																																\
		try																														\
		{																														\
			string t = #TYPE;																									\
			if (t == "double")																									\
				val = (TYPE)stod(subcommand);																					\
			else if (t == "int")																								\
				val = (TYPE)stoi(subcommand);																					\
			else																												\
			{																													\
				cout << "Invalid Conversion" << endl;																			\
				break;																											\
			}																													\
			COMP##Set##PARAM(it->second, val);																					\
			cout << #LCOMP" " << it->first << " "#LPARAM" Set To: " << COMP##Get##PARAM(components[it->first]) << "." << endl;	\
		}																														\
		catch (invalid_argument)																								\
		{																														\
			cout << "Invalid Input Value. Expected "#TYPE"." << endl;															\
		}																														\
	}																															\
}