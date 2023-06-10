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
	matrix=new Matrix(inita);
	gui->setNowMatrix(matrix);

	OperateList* opl = new OperateList();
	gen.addNewNumber(matrix,opl);
	gen.addNewNumber(matrix,opl);
	gui->setNewMatrix(matrix);
	gui->operate(opl);
	matrix->printToConsole();
}


MainControl::MainControl(GameUI* gui)
{
	this->gui = gui;
	init();
}

void MainControl::onArrowControl(Direction control) {
	OperateList* opl = new OperateList;
	opl=Move::move(control,matrix,&score);
	qDebug() << score;
	generate gen;
	gen.addNewNumber(matrix,opl);
	gui->setNowScore(score);
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
				records.insert(std::pair<int, int>(round,score));
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
	records.insert(std::pair<int, int>(round, score));
	}
}

void MainControl::onFuncControl(FuncControl control) {
	if (control == START)
	{
		round++;
		matrix->~Matrix();
		matrix = new Matrix(inita);
		gui->setNowMatrix(matrix);

		OperateList* opl = new OperateList();
		gen.addNewNumber(matrix, opl);
		gen.addNewNumber(matrix, opl);
		gui->setNewMatrix(matrix);
		gui->operate(opl);
		matrix->printToConsole();

	}
	else
		records.insert(std::pair<int, int>(round, score));
}

std::map<int, int> MainControl::readMapFromFile(const std::string& filename)
{
	std::map<int, int> data;

	//���ļ�
	std::ifstream file(filename);

	if (!file) {
		std::cerr << "Failed to open the file.\n";
		return data;
	}
	std::string line;//��ȡһ������
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		int key, value;
		if (!(iss >> key >> value)) {
			std::cerr << "Failed to parse line: " << line << '\n';
			continue;
		}

		data[key] = value;
	}
	return std::map<int, int>();
}

void MainControl::writeRecordsToFile(const std::map<int, int>& data, const std::string& filename)
{
	// ���ļ�
	std::ofstream file(filename, std::ios::app);

	// �ж��ܷ�ɹ���
	if (!file.is_open()) {
		std::cerr << "Unable to open file: " << filename << std::endl;
		return;
	}

	// ������д���ı��ļ���
	for (const auto& pair : data) {
		file << pair.first << ' ' << pair.second << '\n';
	}

	//�ر��ļ�
	file.close();

}

void MainControl::writeRecordsToFile(const std::map<int, double>& data, const std::string& filename)
{
	// ���ļ�
	std::ofstream file(filename, std::ios::app);

	// �ж��ܷ�ɹ���
	if (!file.is_open()) {
		std::cerr << "Unable to open file: " << filename << std::endl;
		return;
	}

	// ������д���ı��ļ���
	for (const auto& pair : data) {
		file << pair.first << ' ' << pair.second << '\n';
	}
	file << "=========================================================================================" << '\n';

	//�ر��ļ�
	file.close();

}

void MainControl::sum()
{

	if (records.empty()) {
		std::cout << "The map is empty.\n";
		return;
	}

	int max_value = 0;
	double sum = 0.0;

	for (const auto& pair : records) {
		if (pair.second > max_value) {
			max_value = pair.second;
		}
		sum += pair.second;
	}
	double average = sum / records.size();

	std::map<int, double> result = { {max_value,average} };

	writeRecordsToFile(result, "map.txt");

}

