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

	synth->initAudio();
	synth->masterMixer.setAmplitude(0.02f);

	components["osc1"] = make_unique<Oscillator>();
	components["osc2"] = make_unique<Oscillator>();
	components["osc3"] = make_unique<Oscillator>();
	components["lp"] = make_unique<FilterLP>();

	components["osc1"]->setOutput(components["lp"].get());
	dynamic_cast<Oscillator*>(components["osc1"].get())->setFrequency(220.0f);
	dynamic_cast<Oscillator*>(components["osc1"].get())->setAmplitude(0.1f);
	dynamic_cast<Oscillator*>(components["osc1"].get())->setPhase(0.0f);
	dynamic_cast<Oscillator*>(components["osc1"].get())->setWave(Oscillator::Wave::Saw);

	components["osc2"]->setOutput(components["lp"].get());
	dynamic_cast<Oscillator*>(components["osc2"].get())->setFrequency(440.0f);
	dynamic_cast<Oscillator*>(components["osc2"].get())->setAmplitude(0.3f);
	dynamic_cast<Oscillator*>(components["osc2"].get())->setPhase(0.0f);
	dynamic_cast<Oscillator*>(components["osc2"].get())->setWave(Oscillator::Wave::Saw);

	components["osc3"]->setOutput(components["lp"].get());
	dynamic_cast<Oscillator*>(components["osc3"].get())->setFrequency(880.0f);
	dynamic_cast<Oscillator*>(components["osc3"].get())->setAmplitude(1.0f);
	dynamic_cast<Oscillator*>(components["osc3"].get())->setPhase(0.0f);
	dynamic_cast<Oscillator*>(components["osc3"].get())->setWave(Oscillator::Wave::Saw);

    /*for (size_t i = 4; i < 20; i++)
    {
        components["osc" + i] = make_unique<Oscillator>();
        components["osc" + i]->setOutput(components["lp"].get());
        dynamic_cast<Oscillator*>(components["osc" + i].get())->setFrequency(880.0f);
        dynamic_cast<Oscillator*>(components["osc" + i].get())->setAmplitude(1.0f);
        dynamic_cast<Oscillator*>(components["osc" + i].get())->setPhase(0.0f);
        dynamic_cast<Oscillator*>(components["osc" + i].get())->setWave(Oscillator::Wave::Saw);
    }*/
	
	components["lp"]->setOutput(reinterpret_cast<Component*>(&synth->masterMixer));
	dynamic_cast<FilterLP*>(components["lp"].get())->setCutoff(10000.0f);
	
	std::cin.get();//TestLoop(components);

	for (const auto& component : components)
		component.second->setOutput(nullptr);

	/*for (auto itr = components.begin(); itr != components.end(); ++itr)
		components.erase(itr);*/

	return 0;
}