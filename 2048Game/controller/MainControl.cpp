#include "MainControl.h"
#include "Move.h"
#include <QDebug>

int array[4][4]= {
0,2048,1024,0,
256,128,64,32,
2,2048,1024,512,
256,128,0,32
};

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
	//judgeEnd(*matrix);
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
	int sflag=0;
	for (int x = 0; x < 4; x++)
	{
		int* ax = matrix.getLineOnX(x);
		for (int i = 0; i < 4; i++)
		{
			if(isClassic&&ax[i] == 2048)
			{
				sflag = 1;
				break;
			}
			if (ax[i] == 0||ax[i] == matrix.getNumberIn(x+1,i)|| ax[i] == matrix.getNumberIn(x, i+1))
			{
				flag = -1;
				break;
			}
		}
	}
	if (isClassic&&sflag == 1) {
		SetAll();
		gui->setGameState(SUCCESS);
	}
	if(flag==0){
		SetAll();
		gui->setGameState(FAILED);
	}
}

void MainControl::quitGame() {
	if (round > 0)
	{
		SetAll();
		QDateTime time = QDateTime::currentDateTime();   //获取当前时间
		writeRecordsToFile(records, "records_" + QString::number(time.toMSecsSinceEpoch()) + ".txt");
	}
}
void MainControl::initGame() {
	if (matrix != nullptr)
		matrix->~Matrix();
	round++;
	score = 0;
#ifdef TEST_ARRAY
	matrix = new Matrix(array);
#else
	matrix = new Matrix();
#endif // TEST_ARRAY
	gui->setNowMatrix(matrix);
	gui->setLevel(round);
	gui->setNowScore(score);

	OperateList* opl = new OperateList();
	for (int i = 0; i < START_NUM_COUNT; i++) {
		gen.addNewNumber(matrix, opl);
	}
	gui->setNewMatrix(matrix);
	gui->operate(opl);
	matrix->printToConsole();

	gui->setGameState(GAMING);

}

void MainControl::onFuncControl(FuncControl control) {
	switch (control)
	{
	case START:
		initGame();
		break;
	case END:
		SetAll();
		break;
	case QUIT:
		quitGame();
		break;
	case CLASSIC:
		isClassic = true;
		break;
	case MINFINITY:
		isClassic = false;
		break;
	case ENABLEAI:
		break;
	case DISABLEAI:
		break;
	default:
		break;
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

void MainControl::writeRecordsToFile(const std::map<int, int>& data, const QString filename)
{

	std::ofstream file(filename.toLocal8Bit(), std::ios::app);
	if (!file.is_open()) {
		std::cerr << "Unable to open file: " << filename.toLocal8Bit() << std::endl;
		return;
	}

	int total = 0;
	int largest = 0;
	int average = 0;
	file << "局数,得分,最高分,平均分" << '\n';
	for (const auto& pair : data) {
		if (pair.second > largest) largest = pair.second;
		total += pair.second;
		average = total/ pair.first;
		file << pair.first << ','<< pair.second << ',' << largest << ',' << average<<  '\n';
	}
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
