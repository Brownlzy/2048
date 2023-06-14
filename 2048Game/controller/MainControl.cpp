#include "MainControl.h"
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
	opl=move(control,matrix,&score,&isNew);
	qDebug() << score;
	if(isNew)
	addNewNumber(matrix,opl);
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
		addNewNumber(matrix, opl);
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
		if (pair.second > largest) 
			largest = pair.second;
		total += pair.second;
		average = total/ pair.first;
		file << pair.first << ','<< pair.second << ',' << largest<< ',' << average<<  '\n';
	}
	file.close();
}

void MainControl::addNewNumber(Matrix* matrix, OperateList* opl)
{

	srand(uint(QTime(0, 0, 0).secsTo(QTime::currentTime())));

	int i = 0,j = 0;
	//找空格数
	struct Ns n[15];
	int ni = 0;
	for (int x = 0; x < 4; x++)
	{
		int* ano = matrix->getLineOnX(x);
		for (int i = 0; i < 4; i++)
		{
			if (ano[i] == 0)
			{
				n[ni].i = x;
				n[ni].j = i;
				ni++;
			}
		}
	}

	int randx = rand() % ni;
	double temp = QRandomGenerator::global()->generateDouble();
	if (temp <= 0.9) {
		qDebug() << temp << '\n';
		matrix->setNumberIn(n[randx].i, n[randx].j, 2);
		opl->addOperate(new NewIn(n[randx].i, n[randx].j, 2));
	}
	else {
		qDebug() << temp << '\n';
		matrix->setNumberIn(n[randx].i, n[randx].j, 4);
		opl->addOperate(new NewIn(n[randx].i, n[randx].j, 4));
	}
	return;

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
			if (temp > maxs) 
				maxs = temp;
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

OperateList* MainControl::move(Direction direction, Matrix* matrix, int* score, bool* isNew)
{
	*isNew = false;
	OperateList* oplist = new OperateList();
	for (int no = 0; no < 4; no++)
	{
		int* ano = matrix->getLineOn(direction, no);
		for (int i = 0; i < 4; i++) {
			int j, k;
			for (j = i; j < 4; j++) {
				if (ano[j] != 0)
					break;
			}
			for (k = j + 1; k < 4; k++) {
				if (ano[k] != 0)
					break;
			}
			if (j < 4 && k < 4 && ano[j] == ano[k]) {
				int temp = ano[j] * 2;
				ano[j] = 0;
				ano[k] = 0;
				ano[i] = temp;
				*score += temp;
				switch (direction)
				{
				case UP:
					oplist->addOperate(new MergeTo(j, no, k, no, i, no, temp));
					*isNew = true;
					break;
				case LEFT:
					oplist->addOperate(new MergeTo(no, j, no, k, no, i, temp));
					*isNew = true;
					break;
				case RIGHT:
					oplist->addOperate(new MergeTo(no, 3 - j, no, 3 - k, no, 3 - i, temp));
					*isNew = true;
					break;
				case DOWN:
					oplist->addOperate(new MergeTo(3 - j, no, 3 - k, no, 3 - i, no, temp));
					*isNew = true;
					break;
				default:
					break;
				}
			}
			else if (j < 4)
			{
				int temp = ano[j];
				ano[j] = 0;
				ano[i] = temp;
				switch (direction)
				{
				case UP:
					oplist->addOperate(new MoveTo(j, no, i, no, temp));
					if (j != i)
						*isNew = true;
					break;
				case LEFT:
					oplist->addOperate(new MoveTo(no, j, no, i, temp));
					if (j != i)
						*isNew = true;
					break;
				case DOWN:
					oplist->addOperate(new MoveTo(3 - j, no, 3 - i, no, temp));
					if ((3 - j) != (3 - i))
						*isNew = true;
					break;
				case RIGHT:
					oplist->addOperate(new MoveTo(no, 3 - j, no, 3 - i, temp));
					if ((3 - j) != (3 - i))
						*isNew = true;
					break;
				default:
					break;
				}
			}
		}
		ano;
		matrix->setLineOn(direction, no, ano);
	}
	return oplist;
}
