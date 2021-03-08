#include <iostream>
using namespace std;


struct scoped{
	scoped() { cout <<"created"<< endl;
	}
	~scoped() { cout << "destroyed" <<endl;}

};
struct scoped_nodiscard{
	[[nodiscard]] scoped_nodiscard() { cout <<"nodiscard created"<< endl;
	}
	~scoped_nodiscard() { cout << "nodiscard destroyed" <<endl;}

};

[[nodiscard]]
 struct nodiscard_scoped{
	nodiscard_scoped() { cout <<"nodiscard_scoped created"<< endl;

	}
	~nodiscard_scoped(){ cout << "nodiscard_scoped destroyed" << endl;}
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	{ scoped_nodiscard ok{};
	  nodiscard_scoped ok2{};
	  scoped {};
	}
	{
		scoped_nodiscard{}; // should warn and warns
		nodiscard_scoped{}; // does not warn, should it?
		scoped{};
	}
}
