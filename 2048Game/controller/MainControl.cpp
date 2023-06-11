#include "MainControl.h"
#include "Move.h"
#include <QDebug>



int array[4][4]= { 0,0,0,2,
				   2,0,0,2,
				   2,0,0,4,
				   0,0,4,8 };
int inita[4][4] = { 0,0,0,0,
				  0,0,0,0,
				  0,0,0,0,
				  0,0,0,0 };

int MainControl::round = 0;

void MainControl::init()
{
	gui->setControlListener(this);
	gui->setGameState(READY);
}


MainControl::MainControl(GameUI* gui)
{
	this->gui = gui;
	init();
}

void MainControl::onArrowControl(Direction control) {
	OperateList* opl = new OperateList;
	opl=Move::move(control,matrix,&score,&isNew);
	qDebug() << score;
	generate gen;
	if(isNew)
	gen.addNewNumber(matrix,opl);
	gui->setNowScore(score);
	if (score > maxs)
		gui->setMaxScore(score);

	else
		gui->setMaxScore(maxs);
	matrix->printToConsole();
	gui->setNewMatrix(matrix);
	gui->operate(opl);
	judgeEnd(*matrix);
}


void MainControl::judgeEnd(Matrix matrix)
{
	int flag=0;
	for (int x = 0; x < 4; x++)
	{
		if (flag != 0)
			break;
		int* ax = matrix.getLineOnX(x);
		for (int i = 0; i < 4; i++)
		{
			if(ax[i] == 2048)
			{
				gui->setGameState(SUCCESS);
				flag = -1;
				SetAll();
				break;
			}
			if (ax[i] == 0||ax[i] == matrix.getNumberIn(x+1,i)|| ax[i] == matrix.getNumberIn(x, i+1))
			{
				flag = -1;
				break;
			}
		}
	}
	if(flag==0)
	{
	gui->setGameState(FAILED);
	SetAll();
	}
}

void MainControl::onFuncControl(FuncControl control) {
	if (control == START)
	{
		
		if (matrix != nullptr)
			matrix->~Matrix();
		round++;
		score = 0;
		matrix = new Matrix(inita);
		gui->setNowMatrix(matrix);
		gui->setLevel(round);
		gui->setNowScore(score);

		OperateList* opl = new OperateList();
		gen.addNewNumber(matrix, opl);
		gen.addNewNumber(matrix, opl);
		gui->setNewMatrix(matrix);
		gui->operate(opl);
		matrix->printToConsole();

		gui->setGameState(GAMING);
	}
	else  if (control == END) {
		SetAll();
	}
	else{
		SetAll();
		writeRecordsToFile(records, "map.txt");
		writeRecordsToCSV(records,"map.csv");
	}
		
}

std::map<int, int> MainControl::readMapFromFile(const std::string& filename)
{
	std::map<int, int> data;
	std::ifstream file(filename);

	if (!file) {
		std::cerr << "Failed to open the file.\n";
		return data;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		int key, value;
		if (!(iss >> key >> value)) {
			std::cerr << "Failed to parse line: " << line << '\n';
			continue;
		}

		data[key] = value;
	}
	return data;
}

void MainControl::writeRecordsToFile(const std::map<int, int>& data, const std::string& filename)
{
	
	std::ofstream file(filename, std::ios::app);
	if (!file.is_open()) {
		std::cerr << "Unable to open file: " << filename << std::endl;
		return;
	}
	
	int total = 0;
	int largest = 0;
	int average = 0;
	int cnt = 0;
	for (const auto& pair : data) {
		
		file << "第" <<(++cnt) << "局" << '\n';
		file << "总分" << ' '<< "最高分" << ' '<< "平均分" << '\n';
		if (pair.second > largest) largest = pair.second;
		total += pair.second;
		average = total/cnt;
		
		file << pair.second << ' '<< largest<<' '<<average<<'\n';
	}
	file << "=====================================================================" << '\n';
	file.close();

}


void MainControl::writeRecordsToCSV(const std::map<int, int>& data, const std::string& filename)
{
	std::ofstream file(filename, std::ios::app);
	if (!file.is_open()) {
		std::cerr << "unable to open file: " << filename << std::endl;
		return;
	}
	int total = 0;
	int largest = 0;
	int average = 0;
	int cnt = 0;
	for (const auto& pair : data) {
		/*std::string str = "第" + std::to_string(++cnt) + "局";*/
		file << "第" + std::to_string(++cnt) + "局"<< '\n';
		file << "总分" << ', '<< "最高分" <<  ',' << "平均分" << '\n';
		if (pair.second > largest) largest = pair.second;
		total += pair.second;
		average = total / cnt;

		file << pair.second << ',' << largest << ',' << average << '\n';


	}
	file << "=====================================================================" << '\n';

	file.close();
}

void MainControl::getLargest()
{
	if (records.empty()) {
		std::cout << "The map is empty.\n";
		return;
	}

	for (int i = 0; i < round; i++) {
		std::map<int, int>::iterator it= records.find(i+1);
		if (it != records.end())
		{
			int temp= records.find(i+1)->second;
			if (temp > maxs) maxs = temp;
		}
	}
}

void MainControl::average()
{

	if (records.empty()) {
		std::cout << "The map is empty.\n";
		return;
	}

	int sum = 0;
	for (const auto& pair : records) {

		sum += pair.second;
	}
	aves = sum / round;
}

void MainControl::SetAll()
{
	records.insert(std::pair<int, int>(round, score));
	if (round>0) 
		  average();
	
	getLargest();
	
	gui->setAvgScore(aves);
	gui->setMaxScore(maxs);
}
