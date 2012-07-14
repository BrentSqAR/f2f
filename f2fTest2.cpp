/*
 * f2fTest.cpp
 *
 *  Created on: 08.06.2012
 *      Author: sqar
 */

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <algorithm>

// #include <functional>
// #include <boost/lambda/lambda.hpp>

using namespace std;

class Track {
public:
	Track();
	Track(string m_name);
	string name;
	string content;
	void out();
};

Track::Track():
	name("")
{}

Track::Track(string m_name):
	name(m_name)
{}

void Track::out() {
	cout << name << ", " << content << endl;
}

class Line : public Track {
public:
	Line();
	Line(string m_name);
};

Line::Line()
: Track()
{content = "Ich bin eine Linie.";}

Line::Line(string m_name)
: Track(m_name)
{content = "Ich bin eine Linie.";}

class Sound : public Track {
public:
	Sound();
	Sound(string m_name);
};

Sound::Sound()
: Track()
{content = "Ich bin ein Sound.";}

Sound::Sound(string m_name)
: Track(m_name)
{content = "Ich bin ein Sound.";}

class Text : public Track {
public:
	Text();
	Text(string m_name);
};

Text::Text()
: Track()
{content = "Ich bin ein Text.";}

Text::Text(string m_name)
: Track(m_name)
{content = "Ich bin ein Text.";}

class Grid {
public:
	Grid();
	Grid(string m_name);
	list<Track> track;
	list<Track>::iterator iter;
	string name;
	bool active;
	void out();
	bool isName(const string &search);
};

Grid::Grid():
	name(""),
	active(true)
{}

Grid::Grid(string m_name):
	name(m_name),
	active(true)
{}

void Grid::out() {
	cout << name << ", " << active << endl;
}

class Layer {
public:
	Layer();
	Layer(string m_name);
	list<Grid> grid;
	list<Grid>::iterator iter;
	string name;
	bool active;
	void out();
	bool isName(const string &search);
    // bool operator<(Layer const &other) { return name < other.name; }
    // bool operator==(Layer const &other) { return name == other.name; }
};

Layer::Layer():
	name(""),
	active(true)
{}

Layer::Layer(string m_name):
	name(m_name),
	active(true)
{}

void Layer::out() {
	cout << name << ", " << active << endl;
}

bool Layer::isName(const string &search) {
	return name == search;
}

class Stack {
public:
	list<Layer> layer;
	list<Layer>::iterator iter;
	map<string, Layer> maplayer;
	map<string, Layer>::iterator mapiter;
};

class Manipulator {
public:
	Manipulator();
	Manipulator(string m_name);
};

class Modul {
public:
	Modul();
	Modul(string m_name);
	list<Manipulator> manipulator;
	list<Manipulator>::iterator iter;
	string name;
	int id;
	int getUniqueID();
	void out();
};

Modul::Modul():
	name("")
{id = getUniqueID();}

Modul::Modul(string m_name):
	name(m_name)
{id = getUniqueID();}

int Modul::getUniqueID()
{
    static int ID=0;
    return ++ID;
}

void Modul::out() {
	cout << name << ", " << id << endl;
}

class Scheme {
public:
	list<Modul> modul;
	list<Modul>::iterator iter;
};

class Tier{
public:
    virtual void iss() { std::cout << "Fresse wie ein Tier" << std::endl; };
//  void iss() { std::cout << "Fresse wie ein Tier" << std::endl; };
};

class Hund : public Tier{
public:
    void iss() { std::cout << "Wuff! Fresse gerade" << std::endl; };
};

class Mensch : public Tier{
public:
    void iss() { std::cout << "Esse gerade" << std::endl; };
};


int main() {
	Stack stack;
	stack.layer.emplace_back();
	stack.layer.emplace_back("snail");
	stack.layer.emplace_back("squirrel");
	stack.layer.emplace_back("crazycat");

	string search = "snail";
    for(stack.iter = stack.layer.begin(); stack.iter != stack.layer.end(); ++stack.iter) {
	    cout << (stack.iter)->isName(search) << endl;
	    (stack.iter)->out();
	}
    stack.layer.remove_if([search](Layer &s)->bool{ return s.isName(search); });
    for(stack.iter = stack.layer.begin(); stack.iter != stack.layer.end(); ++stack.iter) {
	    cout << (stack.iter)->isName(search) << endl;
	    (stack.iter)->out();
	}

    search = "crazycat";
    for(stack.iter = stack.layer.begin(); stack.iter != stack.layer.end(); ++stack.iter) {
	    if ((stack.iter)->isName(search)) {
			(stack.iter)->grid.emplace_back("left");
			(stack.iter)->grid.emplace_back("middle");
			(stack.iter)->grid.emplace_back("right");
	    }
	}
    search = "squirrel";
    for(stack.iter = stack.layer.begin(); stack.iter != stack.layer.end(); ++stack.iter) {
	    if ((stack.iter)->isName(search)) {
			(stack.iter)->grid.emplace_back("up");
			(stack.iter)->grid.emplace_back("down");
			(stack.iter)->grid.emplace_back("turn around");
	    }
	}

    // find and output all grids in crazycat, then in squirrel
    search = "crazycat";
    for(stack.iter = stack.layer.begin(); stack.iter != stack.layer.end(); ++stack.iter) {
	    if ((stack.iter)->isName(search)) {
	        for(list<Grid>::iterator iter = (stack.iter)->grid.begin(); iter != (stack.iter)->grid.end(); ++iter) {
	        	(iter)->out();
	        }
	    }
	}
    search = "squirrel";
    for(stack.iter = stack.layer.begin(); stack.iter != stack.layer.end(); ++stack.iter) {
	    if ((stack.iter)->isName(search)) {
	        for(list<Grid>::iterator iter = (stack.iter)->grid.begin(); iter != (stack.iter)->grid.end(); ++iter) {
	        	(iter)->out();
	        }
	    }
	}

    // make tracks in crazycat right and squirrel down
    search = "crazycat";
    for(stack.iter = stack.layer.begin(); stack.iter != stack.layer.end(); ++stack.iter) {
	    if ((stack.iter)->isName(search)) {
			(stack.iter)->grid.emplace_back("left");
			(stack.iter)->grid.emplace_back("middle");
			(stack.iter)->grid.emplace_back("right");
	    }
	}



    stack.maplayer["eins"];
    stack.maplayer["zwei"];
    stack.maplayer["drei"];
    search = "zwei";
	stack.maplayer.erase(search);

	Scheme scheme;
	scheme.modul.emplace_back();
	scheme.modul.emplace_back("eins");
	scheme.modul.emplace_back("zwei");

    for(scheme.iter = scheme.modul.begin(); scheme.iter != scheme.modul.end(); ++scheme.iter) {
	    (scheme.iter)->out();
	}

	Scheme scheme2;
	scheme2.modul.emplace_back();
	scheme2.modul.emplace_back("eins");
	scheme2.modul.emplace_back("zwei");

    for(scheme2.iter = scheme2.modul.begin(); scheme2.iter != scheme2.modul.end(); ++scheme2.iter) {
	    (scheme2.iter)->out();
	}

    list<Tier*> tiere;
    list<Tier*>::iterator iter;
    tiere.push_back(new Tier());
    tiere.push_back(new Hund());
    tiere.push_back(new Mensch());
/*
    for (iter = tiere.begin(); iter != tiere.end(); iter++){
        (*iter)->iss();
        delete *iter;
    }
*/
	return 0;
}
