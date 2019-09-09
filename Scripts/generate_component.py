LongName = raw_input("Enter Class Name... ")
ShortName = raw_input("Enter Short Name... ")

hcontents = """#pragma once

#include "Component.h"

namespace audio
{
	class """+LongName+""" : public Component
	{
	public:
		"""+LongName+"""();
		virtual void CalcSample(double& dSample) override;
	};

}
"""

f=open("../cpp-audio/"+LongName + ".h","a+")
f.write(hcontents)
f.close()

# -------------------------------------------------------------------------------------------------------------------------------------------

cppcontents = """#include \""""+LongName+""".h\"

namespace audio {

	"""+LongName+"""::"""+LongName+"""()		
	{}

	void """+LongName+"""::CalcSample(double& dSample)
	{	
	}

}
"""

f=open("../cpp-audio/"+LongName + ".cpp","a+")
f.write(cppcontents)
f.close()

# -------------------------------------------------------------------------------------------------------------------------------------------

compileContent1 = """"cpp-audio/"""+LongName+""".cpp" \\"""

inputfile = open('../compile.sh', 'r').readlines()
write_file = open('../compile.sh','wb')
for line in inputfile:
    write_file.write(line)
    if '"cpp-audio/API.cpp"' in line:               
        write_file.write(compileContent1 + "\n") 
write_file.close()

# -------------------------------------------------------------------------------------------------------------------------------------------

compileContent2 = """"_CompAdd"""+ShortName+"""", """

inputfile = open('../compile.sh', 'r').readlines()
write_file = open('../compile.sh','wb')
for line in inputfile:
    write_file.write(line)
    if 'EXPORTED_FUNCTIONS=\'["_InitAudio",' in line:               
        write_file.write(compileContent2 + "\n") 
write_file.close()

# -------------------------------------------------------------------------------------------------------------------------------------------

apihcontent = """
const intptr_t CompAdd"""+ShortName+"""(); """

inputfile = open('../cpp-audio/API.h', 'r').readlines()
write_file = open('../cpp-audio/API.h','w')
for line in inputfile:
    write_file.write(line)
    if 'const std::vector<intptr_t> CompGetIn(const intptr_t component);' in line:               
        write_file.write(apihcontent + "\n") 
write_file.close()

# -------------------------------------------------------------------------------------------------------------------------------------------

apicppcontent1 = """#include \""""+LongName+""".h\""""

inputfile = open('../cpp-audio/API.cpp', 'r').readlines()
write_file = open('../cpp-audio/API.cpp','w')
for line in inputfile:
    write_file.write(line)
    if '#include "Component.h"' in line:               
        write_file.write(apicppcontent1 + "\n") 
write_file.close()

# -------------------------------------------------------------------------------------------------------------------------------------------

apicppcontent2 = """
const intptr_t CompAdd"""+ShortName+"""()
{
	return reinterpret_cast<intptr_t>(new """+LongName+"""());
}"""

inputfile = open('../cpp-audio/API.cpp', 'r').readlines()
write_file = open('../cpp-audio/API.cpp','w')
for line in inputfile:
    write_file.write(line)
    if '// New components get inserted here with python script.' in line:               
        write_file.write(apicppcontent2 + "\n") 
write_file.close()