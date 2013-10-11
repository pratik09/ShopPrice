all:
	g++ -L./libraries -llibcurl.so.4.2.0 Parser.cpp -o parse
