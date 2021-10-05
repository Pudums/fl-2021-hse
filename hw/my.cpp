#include "my.h"
#include <set>
#include <algorithm>
using namespace std;

vector<bool> alph(256, false);
vector<map<char, Station*> > g;
map<int, Station*> st_min_id;
Station start(-1, 0);

bool operator<(const Station &lhs, const Station &rhs) {
	return lhs.id < rhs.id;
}

Station::Station(int a, char b) : id(a), type(b) {
}

Edges::Edges(int a, int b, vector<char> &c): id1(a), id2(b), edges(std::move(c)) {
}

void resave(const vector<char> &symbs, vector<Station> &sts, const vector<Edges> &eds) {
	for(unsigned char c: symbs) {
		alph[c] = true;
	}

	sort(sts.begin(), sts.end());
	for(int i = 0; i < sts.size() - 1; i++) {
		if(sts[i].id == sts[i+1].id) {
			cerr << "same index of q\n";
			return;
		}

		if(sts[i].type == 's') {
			if(start.id != -1) {
				cerr << "Double start\n";
				return;
			}
			start = Station(i, sts[i].type);
		}

		st_min_id[sts[i].id] = new Station(i, sts[i].type);
	}
		int i = sts.size()-1;
		if(sts[i].type == 's') {
			if(start.id != -1) {
				cerr << "Double start\n";
				return;
			}
			start = Station(i, sts[i].type);
		}

		st_min_id[sts[i].id] = new Station(i, sts[i].type);

	g.resize(sts.size());
	for(auto edges: eds) {
		auto v = st_min_id[edges.id1], 
			u = st_min_id[edges.id2];
		for(char edge: edges.edges) {
			if(g[v->id].count(edge) > 0) {
				cerr << "same edges\n";
				return;
			}
			g[v->id][edge] = u;
		}
	}
}

bool check(const string &s) {
	if(start.id == -1) {
		cerr << "no start\n";
	}

	for(auto c: s) {
		if(g[start.id].find(c) == g[start.id].end()) {
			cerr << "No edge " << c << '\n';
			return false;
		}

		start = *g[start.id][c];
	}
	return start.type == 't';
}
