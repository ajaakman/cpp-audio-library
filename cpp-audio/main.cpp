#include "API.h"
#include "TestLoop.h"

#include <map>

int main(int argc, char** argv)
{
	using namespace std;
	
	map<string, intptr_t> components;

	InitAudio();
	MasterSetAmp(0.02);

	components["osc1"] = CompAddOsc();
	components["osc2"] = CompAddOsc();
	components["osc3"] = CompAddOsc();
	components["lp"] = CompAddLP();
	
	CompSetOut(components["osc1"], components["lp"]);
	OscSetFreq(components["osc1"], 220.0);
	OscSetAmp(components["osc1"], 0.1);
	OscSetPhase(components["osc1"], 0.0);
	OscSetWave(components["osc1"], 3);
		
	CompSetOut(components["osc2"], components["lp"]);
	OscSetFreq(components["osc2"], 440.0);
	OscSetAmp(components["osc2"], 0.3);
	OscSetPhase(components["osc2"], 0.0);
	OscSetWave(components["osc2"], 3);
		
	CompSetOut(components["osc3"], components["osc1"]);
	OscSetFreq(components["osc3"], 880.0);
	OscSetAmp(components["osc3"], 1.0);
	OscSetPhase(components["osc3"], 0.0);
	OscSetWave(components["osc3"], 3);

	CompSetOut(components["lp"], MasterComp());
	LPSetCutoff(components["lp"], 10000.0);
		   
	TestLoop(components);

	for (const auto & component: components)	
		CompSetOut(component.second, NULL);
	
	for (const auto& component : components)
		CompDelete(component.second);		

	return 0;
}