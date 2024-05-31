#include <cmath>
#include<iostream>
#include<vector>
#include<memory>

using std::iostream;
using std::vector;
using std::cout;
using std::endl;

class Boy
{
public:
	Boy(int _num):number(_num),isOver(false){}
	~Boy(){cout << "Boy::~Boy() is game over, num:"<< number<< endl;}
	void set(int _num) {
		number = _num;
	}
	int get(void) const {return number;}
	void checkGameOver(int _magicNum) {
		if (pollNumber == _magicNum) {
			isOver = true;
		} else { 
			isOver = false;
		}
	}
	void poll(int idx) {
		pollNumber = idx;
	}
	bool selfIsGameOver(void) {
		return isOver;
	}
private:
	int number;
	int pollNumber;
	bool isOver;
};
typedef std::shared_ptr<Boy> PBoy;

class Ring
{
public:
	Ring(){}
	~Ring(){
		cout << "Ring::~Ring() is game over" << endl;
	}
	void inRing(PBoy boy);
	int OutRing(int idx);
	int run(int _index, int _magic);
	void getWinner(void);
private:
	
	vector<PBoy> boyRing;
};
typedef std::shared_ptr<Ring>PRing;

void Ring::inRing(PBoy boy)
{
	this->boyRing.push_back(boy);
}

int Ring::run(int _pollMax, int _magic)
{
	int idx = 1;
	vector<PBoy>::iterator it;
	while (boyRing.size() >= _pollMax) {
		for(it = boyRing.begin(); it != boyRing.end(); ++it) {
			(*it)->poll(idx);
			(*it)->checkGameOver(_magic);
			idx = (idx++)%_pollMax+1;
		}
		for (it = boyRing.begin(); it != boyRing.end(); ) {
			if ((*it)->selfIsGameOver()) {
				cout << "number: " << (*it)->get() << " is game over now ..." << endl;
				it = boyRing.erase(it);
				cout << "boyRing size: " << boyRing.size() << endl;
			} else {
				++it;
			}
		}
		idx = 1;
	}
	return 0;
}

void Ring::getWinner(void)
{
	vector<PBoy>::iterator it = boyRing.begin();

	for (; it != boyRing.end(); ++it) {
		cout << "winner number: " << (*it)->get() << endl;
	}
}

class JoseGame
{
public:
	JoseGame(int _total):boyNum(_total) {
		int i;
		int ret = 0;
		gameRing = std::make_shared<Ring>();
		for(i=1; i <= boyNum; i++) {
			gameRing->inRing(std::make_shared<Boy>(i));
			cout << "succ to push into ring , number: " << i << endl;
		}
	}
	~JoseGame();
	void run(int _pollMax, int _unluckNumber);
	void getWinner(void);
private:
	int magicNum;
	int boyNum;
	int winnerIdx;
	PRing gameRing;

};

JoseGame::~JoseGame()
{
	cout << "JoseGame::~JoseGame() game over" << endl;
}
void JoseGame::run(int _pollMax, int _unluckNumber)
{
	gameRing->run(_pollMax, _unluckNumber);

}

void JoseGame::getWinner(void)
{
	gameRing->getWinner();
}

int main(int argc, char *argv[])
{
	JoseGame jose(20);
	jose.run(5, 3);
	
	jose.getWinner();
	return 0;
}
