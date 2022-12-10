#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "struct_mapping/struct_mapping.h"
using namespace std;
using namespace nlohmann;
#define N 2

struct WorkInWorkshop
{
	int orderNumber[4];
	string performerServiceNumber[6];
	int jobСode[3];
	string unit[5];
	float normOfTime[3];
	float price[3];
	int numberCompletedUnitsMeasure[3];
	float costWork;
};

void menu();
string getFileName();
void addNote(WorkInWorkshop workshopData[N], string nameFile);
void closeProgram(WorkInWorkshop workshopData[N], string nameFile);
void createOrOpenWorkInWorkshop(WorkInWorkshop workshopData[N], string nameFile = "Work in workshop.json");
void openWorkInWorkshop(string nameFile = "Work in workshop.json");
json getWorkInWorkshop(string nameFile);
void serializeWorkInWorkshop(WorkInWorkshop workshopData[N], json workInWorkshop, int i);
void addFromJsonToWorkInWorkshop(int key, string item); //???
void createWorkInWorkshop(WorkInWorkshop workshopData[N], string nameFile);
string requestPerformerServiceNumberForCreateWorkshopData(int index);
void menu();
string getRandomStr(int sizeStr);
void createJsonFile(json jsonData, string nameFile);
void printWorkInWorkshop(WorkInWorkshop workshopData[N]);
void requestPerformerServiceNumber(WorkInWorkshop workshopData[N],
                                   WorkInWorkshop dataOfSelectedPerformers[N]);
void findCopyAndPrintSelectedArtist(WorkInWorkshop workshopData[N],
                                    WorkInWorkshop dataOfSelectedPerformers[N],
                                    string requestedServiceNumber);
void copySelectedArtist(WorkInWorkshop* workshopData,
                        WorkInWorkshop* dataOfSelectedPerformers,
                        int numberOfLoopExecution,
                        int i);
void printSelectedArtist(WorkInWorkshop dataOfSelectedPerformers[N],
                         string previousPerformerServiceNumber,
                         int index);
void printRecords(WorkInWorkshop dataOfSelectedPerformers[N], int serialNumber);
void printTotalCostOfWork(float totalCostOfWork);
void printServiceNumberFieldsAndRecords(WorkInWorkshop dataOfSelectedPerformers[N], int serialNumber);
void printServiceNumberAndFields(WorkInWorkshop dataOfSelectedPerformers[N], int serialNumber);
void printTimeOfExecutionOfListedWorks(float timeOfExecutionOfListedWorks);

void (*action[3])(WorkInWorkshop[N], string) = {createOrOpenWorkInWorkshop, addNote, closeProgram};

int main()
{
	WorkInWorkshop workshopData[N], dataOfSelectedPerformers[N];
	json jsonData;

	srand(time(NULL));
	setlocale(LC_ALL, "ru");

	menu();

	//createOrOpenWorkInWorkshop(workshopData);
	//json jsonData = createWorkInWorkshop(workshopData);
	//openWorkInWorkshop();
	//jsonData = getWorkInWorkshop();
	//createJsonFile(jsonData);


	//printWorkInWorkshop(workshopData);
	//requestPerformerServiceNumber(workshopData, dataOfSelectedPerformers);

	system("PAUSE");
	return 0;
}

void menu()
{
	int menuNumber;
	bool isValidMenuNumber;
	WorkInWorkshop workshopData[N];
	string fileName = getFileName();

	while (1)
	{
		while (1)
		{
			cout << "1 - Посмотреть файл" << endl;
			cout << "2 - Добавить запись" << endl;
			cout << "3 - Закрыть программу" << endl;
			cout << "Введите номер пункта меню: ";
			cin >> menuNumber;

			isValidMenuNumber = menuNumber >= 1 && menuNumber <= 3;
			if (isValidMenuNumber) break;
			cout << "\nОшибка в номере!!! Повторите ввод!";
		}
		action[menuNumber - 1](workshopData, fileName);
	}
}

string getFileName()
{
	string fileName = "Work in workshop",
	       fileType = ".json",
	       changeFileName;

	while (1)
	{
		cout << "По умолчанию имя файла \"" << fileName << "\"\nХотите его изменить? y/n: ";
		cin >> changeFileName;

		if (changeFileName == "y")
		{
			cout << "\nВведите новое имя файла: ";
			cin >> fileName;
			fileName += fileType;
			break;
		}
		if (changeFileName == "n")
			break;
		if (changeFileName != "y" && changeFileName != "n")
			cout << "Не корректный ввод" << endl;
	}
	return fileName;
}

void addNote(WorkInWorkshop workshopData[N], string nameFile)
{
	cout << "Запись успешно добавлена" << endl;
}

void closeProgram(WorkInWorkshop workshopData[N], string nameFile)
{
	cout << "Программа завершилась";
	exit(0);
}

void createOrOpenWorkInWorkshop(WorkInWorkshop workshopData[N], string nameFile)
{
	ifstream jsonFile(nameFile, ifstream::binary);
	bool isOpen = jsonFile.is_open();

	if (isOpen)
		openWorkInWorkshop(nameFile);
	else
		createWorkInWorkshop(workshopData, nameFile);
}

void openWorkInWorkshop(string nameFile)
{
	WorkInWorkshop workshopData[N];
	json workInWorkshop = getWorkInWorkshop(nameFile);
	int amountWorkInWorkshop = workInWorkshop.size();

	for (int i = 0; i < amountWorkInWorkshop; i++)
		serializeWorkInWorkshop(workshopData, workInWorkshop, i);
	printWorkInWorkshop(workshopData);
}

json getWorkInWorkshop(string nameFile)
{
	ifstream jsonFile(nameFile, ifstream::binary);
	json jsonData = json::parse(jsonFile);
	return jsonData;
}

void serializeWorkInWorkshop(WorkInWorkshop workshopData[N], json workInWorkshop, int i)
{
	*workshopData[i].orderNumber = workInWorkshop[i]["orderNumber"].get<int>();
	*workshopData[i].performerServiceNumber = workInWorkshop[i]["performerServiceNumber"].get<string>();
	*workshopData[i].jobСode = workInWorkshop[i]["jobCode"].get<int>();
	*workshopData[i].unit = workInWorkshop[i]["unit"].get<string>();
	*workshopData[i].normOfTime = workInWorkshop[i]["normOfTime"].get<float>();
	*workshopData[i].price = workInWorkshop[i]["price"].get<float>();
	*workshopData[i].numberCompletedUnitsMeasure = workInWorkshop[i]["numberCompletedUnitsMeasure"].get<int>();
	workshopData[i].costWork = workInWorkshop[i]["costWork"].get<float>();
}

void addFromJsonToWorkInWorkshop(int key, string item)
{
}

void createWorkInWorkshop(WorkInWorkshop workshopData[N], string nameFile)
{
	string performerServiceNumber;
	json jsonData{};

	for (int i = 0; i < N; i++)
	{
		*workshopData[i].orderNumber = rand() % 9999;

		performerServiceNumber = requestPerformerServiceNumberForCreateWorkshopData(i);
		*workshopData[i].performerServiceNumber = performerServiceNumber;

		*workshopData[i].jobСode = rand() % 999;
		*workshopData[i].unit = getRandomStr(5);
		*workshopData[i].normOfTime = (float)(rand()) / ((float)(RAND_MAX / 9));
		*workshopData[i].price = (float)(rand()) / ((float)(RAND_MAX / 9));
		*workshopData[i].numberCompletedUnitsMeasure = rand() % 999;
		workshopData[i].costWork = *workshopData[i].price * *workshopData[i].numberCompletedUnitsMeasure;

		jsonData[i]["orderNumber"] = *workshopData[i].orderNumber;
		jsonData[i]["performerServiceNumber"] = performerServiceNumber;
		jsonData[i]["jobCode"] = *workshopData[i].jobСode;
		jsonData[i]["unit"] = *workshopData[i].unit;
		jsonData[i]["normOfTime"] = *workshopData[i].normOfTime;
		jsonData[i]["price"] = *workshopData[i].price;
		jsonData[i]["numberCompletedUnitsMeasure"] = *workshopData[i].numberCompletedUnitsMeasure;
		jsonData[i]["costWork"] = workshopData[i].costWork;
	}
	createJsonFile(jsonData, nameFile);
}

string requestPerformerServiceNumberForCreateWorkshopData(int index)
{
	string performerServiceNumber;
	cout << "Введите Таб. № испол. " << index + 1 << endl;
	cin >> performerServiceNumber;
	return performerServiceNumber;
}

string getRandomStr(int sizeStr)
{
	const char POOL[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789";
	std::string randomStr = "";
	int poolSize = sizeof(POOL) - 1;

	for (int i = 0; i < sizeStr; i++)
		randomStr += POOL[rand() % poolSize];

	return randomStr;
}

void createJsonFile(json jsonData, string nameFile)
{
	ofstream jsonFile(nameFile);
	jsonFile << jsonData;
	jsonFile.close();

	cout << "Файл " << nameFile << " успешно создан" << endl;
}

void printWorkInWorkshop(WorkInWorkshop workshopData[N])
{
	cout
		<< "\n"
		<< left
		<< setw(4) << "|ID#"
		<< setw(10) << "|№ наряда|"
		<< setw(15) << "|Таб. № испол.|"
		<< setw(12) << "|Код работы|"
		<< setw(10) << "|Ед. изм.|"
		<< setw(13) << "|Норма t (ч)|"
		<< setw(16) << "|Расценка (р/к)|"
		<< setw(32) << "|Кол. выпол. без брака Ед. изм.|"
		<< setw(34) << "|Стоимость работы (р/к)|"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout
			<< setw(4) << i + 1
			<< setw(10) << *workshopData[i].orderNumber
			<< setw(15) << *workshopData[i].performerServiceNumber
			<< setw(12) << *workshopData[i].jobСode
			<< setw(10) << *workshopData[i].unit
			<< setw(13) << *workshopData[i].normOfTime
			<< setw(16) << *workshopData[i].price
			<< setw(32) << *workshopData[i].numberCompletedUnitsMeasure
			<< setw(34) << workshopData[i].costWork
			<< endl;
	}
}

void requestPerformerServiceNumber(WorkInWorkshop workshopData[N], WorkInWorkshop dataOfSelectedPerformers[N])
{
	string requestedServiceNumber;
	bool isEnd;

	cout << "\nВведите запрашиваемые табельные номера исполнителей через строчку. По завершению ввода введите end:\n";
	while (true)
	{
		cin >> requestedServiceNumber;
		isEnd = requestedServiceNumber == "end";
		if (isEnd) break;
		findCopyAndPrintSelectedArtist(workshopData,
		                               dataOfSelectedPerformers,
		                               requestedServiceNumber);
	}
}

void copySelectedArtist(WorkInWorkshop workshopData[N],
                        WorkInWorkshop dataOfSelectedPerformers[N],
                        int numberOfLoopExecution,
                        int i)
{
	*dataOfSelectedPerformers[numberOfLoopExecution].orderNumber = *workshopData[i].orderNumber;
	*dataOfSelectedPerformers[numberOfLoopExecution].performerServiceNumber = *workshopData[i].
		performerServiceNumber;
	*dataOfSelectedPerformers[numberOfLoopExecution].jobСode = *workshopData[i].jobСode;
	*dataOfSelectedPerformers[numberOfLoopExecution].unit = *workshopData[i].unit;
	*dataOfSelectedPerformers[numberOfLoopExecution].normOfTime = *workshopData[i].normOfTime;
	*dataOfSelectedPerformers[numberOfLoopExecution].price = *workshopData[i].price;
	*dataOfSelectedPerformers[numberOfLoopExecution].numberCompletedUnitsMeasure =
		*workshopData[i].numberCompletedUnitsMeasure;
	dataOfSelectedPerformers[numberOfLoopExecution].costWork = workshopData[i].costWork;
}

void findCopyAndPrintSelectedArtist(WorkInWorkshop workshopData[N],
                                    WorkInWorkshop dataOfSelectedPerformers[N],
                                    string requestedServiceNumber)
{
	bool isFoundPerformerServiceNumber;
	string performerServiceNumber,
	       previousPerformerServiceNumber;
	int numberOfLoopExecution = 0;
	float totalCostOfWork = 0,
	      timeOfExecutionOfListedWorks = 0;

	for (int i = 0; i < N; i++)
	{
		performerServiceNumber = *workshopData[i].performerServiceNumber;
		isFoundPerformerServiceNumber = requestedServiceNumber == performerServiceNumber;
		if (isFoundPerformerServiceNumber)
		{
			copySelectedArtist(workshopData, dataOfSelectedPerformers, numberOfLoopExecution, i);
			printSelectedArtist(dataOfSelectedPerformers, previousPerformerServiceNumber, numberOfLoopExecution);
			totalCostOfWork += workshopData[i].costWork;
			timeOfExecutionOfListedWorks += *workshopData[i].normOfTime;
			previousPerformerServiceNumber = performerServiceNumber;
			numberOfLoopExecution++;
		}
	}

	if (!numberOfLoopExecution)
	{
		cout << "Такого табельного номера исполнителя не существует\n";
		return;
	}
	printTotalCostOfWork(totalCostOfWork);
	printTimeOfExecutionOfListedWorks(timeOfExecutionOfListedWorks);
}

void printSelectedArtist(WorkInWorkshop dataOfSelectedPerformers[N],
                         string previousPerformerServiceNumber,
                         int index)
{
	string currentPerformerServiceNumber;
	bool isSameServiceNumber;

	currentPerformerServiceNumber = *dataOfSelectedPerformers[index].performerServiceNumber;
	isSameServiceNumber = currentPerformerServiceNumber == previousPerformerServiceNumber;
	if (isSameServiceNumber)
		printRecords(dataOfSelectedPerformers, index);
	else
		printServiceNumberFieldsAndRecords(dataOfSelectedPerformers, index);
}

void printRecords(WorkInWorkshop dataOfSelectedPerformers[N], int serialNumber)
{
	cout
		<< "\n"
		<< left
		<< setw(4) << serialNumber + 1
		<< setw(10) << *dataOfSelectedPerformers[serialNumber].orderNumber
		<< setw(12) << *dataOfSelectedPerformers[serialNumber].jobСode
		<< setw(10) << *dataOfSelectedPerformers[serialNumber].unit
		<< setw(13) << *dataOfSelectedPerformers[serialNumber].normOfTime
		<< setw(16) << *dataOfSelectedPerformers[serialNumber].price
		<< setw(32) << *dataOfSelectedPerformers[serialNumber].numberCompletedUnitsMeasure
		<< setw(34) << dataOfSelectedPerformers[serialNumber].costWork
		<< endl;
}

void printTotalCostOfWork(float totalCostOfWork)
{
	cout
		<< "\n"
		<< left
		<< setw(4 + 10 + 12 + 10 + 13 + 16 + 32) << "Итого:"
		<< setw(34) << totalCostOfWork
		<< endl;
}

void printServiceNumberFieldsAndRecords(WorkInWorkshop dataOfSelectedPerformers[N], int serialNumber)
{
	printServiceNumberAndFields(dataOfSelectedPerformers, serialNumber);
	printRecords(dataOfSelectedPerformers, serialNumber);
}

void printServiceNumberAndFields(WorkInWorkshop dataOfSelectedPerformers[N], int serialNumber)
{
	cout
		<< "\nСведения о прохождении нарядов для исполнителя с табельным номером "
		<< *dataOfSelectedPerformers[serialNumber].performerServiceNumber
		<< endl;
	cout
		<< left
		<< setw(4) << "|ID#"
		<< setw(10) << "|№ наряда|"
		<< setw(12) << "|Код работы|"
		<< setw(10) << "|Ед. изм.|"
		<< setw(13) << "|Норма t (ч)|"
		<< setw(16) << "|Расценка (р/к)|"
		<< setw(32) << "|Кол. выпол. без брака Ед. изм.|"
		<< setw(34) << "|Стоимость работы (р/к)|"
		<< endl;
}

void printTimeOfExecutionOfListedWorks(float timeOfExecutionOfListedWorks)
{
	cout << "\nВремя выполнения перечисленных работ (час.): " << timeOfExecutionOfListedWorks << endl;
}
