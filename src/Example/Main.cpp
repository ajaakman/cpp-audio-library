#include "../API.h"
//#include "./TestLoop.h"

#include <map>
#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
	using namespace std;
	using namespace audio;

	map<string, unique_ptr<Component>> components;

#ifdef USING_SDL2
	unique_ptr<audio::SDL2Audio> synth = make_unique<audio::SDL2Audio>();
#endif

	synth->InitAudio();
	synth->masterMixer.SetAmplitude(0.02f);

	components["osc1"] = make_unique<Oscillator>();
	components["osc2"] = make_unique<Oscillator>();
	components["osc3"] = make_unique<Oscillator>();
	components["lp"] = make_unique<FilterLP>();

	components["osc1"]->SetOutput(components["lp"].get());
	dynamic_cast<Oscillator*>(components["osc1"].get())->SetFrequency(220.0f);
	dynamic_cast<Oscillator*>(components["osc1"].get())->SetAmplitude(0.1f);
	dynamic_cast<Oscillator*>(components["osc1"].get())->SetPhase(0.0f);
	dynamic_cast<Oscillator*>(components["osc1"].get())->SetWave(Oscillator::Wave::Saw);

	components["osc2"]->SetOutput(components["lp"].get());
	dynamic_cast<Oscillator*>(components["osc2"].get())->SetFrequency(440.0f);
	dynamic_cast<Oscillator*>(components["osc2"].get())->SetAmplitude(0.3f);
	dynamic_cast<Oscillator*>(components["osc2"].get())->SetPhase(0.0f);
	dynamic_cast<Oscillator*>(components["osc2"].get())->SetWave(Oscillator::Wave::Saw);

	components["osc3"]->SetOutput(components["lp"].get());
	dynamic_cast<Oscillator*>(components["osc3"].get())->SetFrequency(880.0f);
	dynamic_cast<Oscillator*>(components["osc3"].get())->SetAmplitude(1.0f);
	dynamic_cast<Oscillator*>(components["osc3"].get())->SetPhase(0.0f);
	dynamic_cast<Oscillator*>(components["osc3"].get())->SetWave(Oscillator::Wave::Saw);
	
	components["lp"]->SetOutput(reinterpret_cast<Component*>(&synth->masterMixer));
	dynamic_cast<FilterLP*>(components["lp"].get())->SetCutoff(10000.0f);
	
	std::cin.get();//TestLoop(components);

	for (const auto& component : components)
		component.second->SetOutput(nullptr);

	for (auto itr = components.begin(); itr != components.end(); ++itr)
		components.erase(itr);

	return 0;
}