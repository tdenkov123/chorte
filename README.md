# Chorte
Chorte is a project developed by tdenkov123 and Tim-abdullin

# Overview
Chorte is an analog of 4diac-forte and works with 4diac as an execution environment. It provides tools for creating and running programs using IEC61499 Function Blocks.

# Functional Blocks
Chorte includes a total of 4 functional blocks that can be used to create complex logical schema:
1. START
2. INT2INT
3. PrintFB
4. F_ADD

# Dependencies
1. pugixml - XML Parsing library
2. sockpp - ez posix sockets
3. argparse - argument parser

# Usage
1. git clone github.com/tdenkov123/chorte chorte && cd chorte
2. mkdir build && cd build
3. cmake .. && make -j
4. Get your .fboot file ready
5. ./main --file ./tdenkov_FORTE_PC.fboot

# Start parameters
  -h, --help          Shows help message and exits 
  -v, --version       Prints version information and exits 
  -f, --file          Path to the .fboot file [required]
  -h, --host          Host to open the socket on [default: "localhost"]
  -p, --port          Port to open the socket on [default: "61499"]
  -freq, --frequency  Frequency of the runtime environment in milliseconds [default: "50"]