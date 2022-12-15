#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using namespace std;
using namespace nlohmann;

//используется при создании рандомных значений
#define numberOfRecords 2

struct WorkInWorkshop
{
	int orderNumber[4];
	int performerServiceNumber[6];
	int jobCode[3];
	int unit[5];
	float normOfTime[3];
	float price[3];
	int numberCompletedUnitsMeasure[3];
	float costWork;
};

void menu(WorkInWorkshop* workshopData, WorkInWorkshop* dataOfSelectedPerformers, string fileName);
string getFileName();
int getAmountWorkInWorkshop(string fileName);
void addNote(WorkInWorkshop* workshopData, string fileName);
void closeProgram();
void createOrOpenWorkInWorkshop(WorkInWorkshop* workshopData, string fileName);
void openWorkInWorkshop(WorkInWorkshop* workshopData, string fileName);
json getWorkInWorkshop(string fileName);
void serializeWorkInWorkshop(WorkInWorkshop* workshopData, json workInWorkshop, int i);
void addFromJsonToWorkInWorkshop(int key, string item); //???
void createWorkInWorkshop(WorkInWorkshop* workshopData, string fileName);
void generateRandomData(WorkInWorkshop* workshopData, json jsonData, int amountWorkInWorkshop);
int requestPerformerServiceNumberForCreateWorkshopData(int index);
string getRandomStr(int sizeStr);
void createJsonFile(json jsonData, string fileName);
void printWorkInWorkshop(WorkInWorkshop* workshopData, string fileName);
void requestPerformerServiceNumber(WorkInWorkshop* workshopData,
                                   WorkInWorkshop* dataOfSelectedPerformers,
                                   string fileName);
void findCopyAndPrintSelectedArtist(WorkInWorkshop* workshopData,
                                    WorkInWorkshop* dataOfSelectedPerformers,
                                    int requestedServiceNumber,
                                    string fileName);
void copySelectedArtist(WorkInWorkshop* workshopData,
                        WorkInWorkshop* dataOfSelectedPerformers,
                        int numberOfLoopExecution,
                        int i);
void printSelectedArtist(WorkInWorkshop* dataOfSelectedPerformers,
                         int previousPerformerServiceNumber,
                         int index);
void printRecords(WorkInWorkshop* dataOfSelectedPerformers, int serialNumber);
void printTotalCostOfWork(float totalCostOfWork);
void printServiceNumberFieldsAndRecords(WorkInWorkshop* dataOfSelectedPerformers, int serialNumber);
void printServiceNumberAndFields(WorkInWorkshop* dataOfSelectedPerformers, int serialNumber);
void printTimeOfExecutionOfListedWorks(float timeOfExecutionOfListedWorks);

int main()
{
	string fileName;
	int amountWorkInWorkshop;
	json jsonData;

	srand(time(NULL));
	setlocale(LC_ALL, "ru");

	fileName = getFileName();
	amountWorkInWorkshop = getAmountWorkInWorkshop(fileName);
	WorkInWorkshop *workshopData = new WorkInWorkshop[100],
	               *dataOfSelectedPerformers = new WorkInWorkshop[100];
	createOrOpenWorkInWorkshop(workshopData, fileName);
	menu(workshopData, dataOfSelectedPerformers, fileName);

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

//void (*action[4])(WorkInWorkshop , string) = {
//	openWorkInWorkshop,
//	requestPerformerServiceNumber,
//	addNote,
//	closeProgram
//};

void menu(WorkInWorkshop* workshopData, WorkInWorkshop* dataOfSelectedPerformers, string fileName)
{
	int menuNumber;
	//bool isValidMenuNumber;

	while (1)
	{
		/*while (1)
		{
			cout << "\n1 - Посмотреть файл" << endl;
			cout << "2 - Добавить запись" << endl;
			cout << "3 - Проанализировать исполнителей" << endl;
			cout << "4 - Закрыть программу" << endl;
			cout << "Введите номер пункта меню: ";
			cin >> menuNumber;

			isValidMenuNumber = menuNumber >= 1 && menuNumber <= 3;
			if (isValidMenuNumber) break;
			cout << "\nОшибка в номере!!! Повторите ввод!";
		}*/
		//action[menuNumber - 1](workshopData, fileName);
		cout << "\n1 - Посмотреть файл" << endl;
		//cout << "2 - Добавить запись" << endl;
		cout << "2 - Проанализировать исполнителей" << endl;
		cout << "3 - Закрыть программу" << endl;
		cout << "\nВведите номер пункта меню: ";
		cin >> menuNumber;

		switch (menuNumber)
		{
		case 1:
			createOrOpenWorkInWorkshop(workshopData, fileName);
			break;
		case 4:
			addNote(workshopData, fileName);
			break;
		case 2:
			requestPerformerServiceNumber(workshopData, dataOfSelectedPerformers, fileName);
			break;
		case 3:
			closeProgram();
			break;
		}
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
			break;
		}
		if (changeFileName == "n") break;
		if (changeFileName != "y" && changeFileName != "n")
			cout << "Не корректный ввод" << endl;
	}
	fileName += fileType;
	return fileName;
}

int getAmountWorkInWorkshop(string fileName)
{
	json workInWorkshop = getWorkInWorkshop(fileName);
	bool isErrorFileNotFound = workInWorkshop.contains("Error file not found");
	//cout << "Error in getAmountWorkInWorkshop?" << endl;
	int amountWorkInWorkshop;

	if (isErrorFileNotFound)
		return numberOfRecords;

	amountWorkInWorkshop = workInWorkshop.size();
	return amountWorkInWorkshop;
}

void addNote(WorkInWorkshop* workshopData, string fileName)
{
	int orderNumber[4];
	int performerServiceNumber[6];
	int jobCode[3];
	int unit[5];
	float normOfTime[3];
	float price[3];
	int numberCompletedUnitsMeasure[3];
	float costWork;

	json workInWorkshop = getWorkInWorkshop(fileName);

	cout << "Введите данные" << endl;

	cout << "Номер наряда (целые числа, небольше 4 символов):" << endl;
	cin >> *orderNumber;
	//scanf_s("%d", orderNumber);

	cout << "Табельный номер исполнителя (строка, небольше 6 символов):" << endl;
	cin >> *performerServiceNumber;
	//scanf_s("%s", performerServiceNumber);

	cout << "Код работы (целые числа, небольше 3 символов):" << endl;
	cin >> *jobCode;
	//scanf_s("%d", jobCode);

	cout << "Единица измерения (строка, небольше 5 символов):" << endl;
	cin >> *unit;
	//scanf_s("%s", unit);

	cout << "Норма времени ч. (вещественное число, небольше 3 символов):" << endl;
	cin >> *normOfTime;
	//scanf_s("%f", normOfTime);

	cout << "Расценка руб. коп. (вещественное число, небольше 3 символов):" << endl;
	cin >> *price;
	//scanf_s("%f", price);

	cout << "Расценка руб. коп. (целое число, небольше 3 символов):" << endl;
	cin >> *numberCompletedUnitsMeasure;
	//scanf_s("%d", numberCompletedUnitsMeasure);

	costWork = *price * *numberCompletedUnitsMeasure;

	//cout << workInWorkshop << endl;
	json enteredData{
		{"orderNumber", *orderNumber},
		{"performerServiceNumber", *performerServiceNumber},
		{"jobCode", *jobCode},
		{"unit", *unit},
		{"normOfTime", *normOfTime},
		{"price", *price},
		{"numberCompletedUnitsMeasure", *numberCompletedUnitsMeasure},
		{"costWork", costWork}
	};

	workInWorkshop.insert(workInWorkshop.end(), enteredData);
	createJsonFile(workInWorkshop, fileName);

	cout << workInWorkshop;


	//нужно ли это???!!!!!!!!!!!!!!!!!!
	cout << "\nФункция addNote\nfileName = " << fileName << endl;
	int indexNewWorkInWorkshop = getAmountWorkInWorkshop(fileName) - 1;
	cout << "indexNeWWorkInWorkshop = " << indexNewWorkInWorkshop << endl;
	serializeWorkInWorkshop(workshopData, workInWorkshop, indexNewWorkInWorkshop);

	cout << "workshopData: \n" << workshopData;

	/*ofstream
	ifstream jsonFile(fileName, ifstream::binary);
	jsonFile << workInWorkshop;*/
	//cout << enteredData;
	cout << "Запись успешно добавлена" << endl;
}

void addNoteInJsonFile()
{
}

void closeProgram()
{
	cout << "Программа завершилась";
	exit(0);
}

void createOrOpenWorkInWorkshop(WorkInWorkshop* workshopData, string fileName)
{
	ifstream jsonFile(fileName, ifstream::binary);
	bool isOpen = jsonFile.is_open();
	jsonFile.close();

	if (isOpen)
		openWorkInWorkshop(workshopData, fileName);
	else
		createWorkInWorkshop(workshopData, fileName);
	
}

void openWorkInWorkshop(WorkInWorkshop* workshopData, string fileName)
{
	int amountWorkInWorkshop = getAmountWorkInWorkshop(fileName);
	json workInWorkshop = getWorkInWorkshop(fileName);
	
	for (int i = 0; i < amountWorkInWorkshop; i++)
		serializeWorkInWorkshop(workshopData, workInWorkshop, i);
	cout << "openWorkInWorkshop: \n";
	printWorkInWorkshop(workshopData, fileName);
}

json getWorkInWorkshop(string fileName)
{
	ifstream jsonFile(fileName, ifstream::binary);
	bool isOpen = jsonFile.is_open();
	//jsonFile.close();

	if (isOpen)
	{
		json jsonData = json::parse(jsonFile);
		jsonFile.close();
		return jsonData;
	}
	jsonFile.close();
	return {{"Error file not found", true}};
}

void serializeWorkInWorkshop(WorkInWorkshop* workshopData, json workInWorkshop, int i)
{
	cout << "serializeWorkInWorkshop\nworkInWorkshop: \n\n" << workInWorkshop << endl;
	//workshopData пустой при добавлении записи?
	//ГДЕ ТУТ ОШИБКА?
	//cout << "json: \n" << workInWorkshop << endl;
	//cout << "i = " << i << endl;

	//int orderNumber = workInWorkshop[i]["orderNumber"].get<int>();
	//Ошибка: JSON_THROW(type_error::create(302, concat("type must be number, but is ", j.type_name()), &j));
	int performerServiceNumber = workInWorkshop[i]["performerServiceNumber"];
	//int jobCode[3];
	int unit = workInWorkshop[i]["unit"].get<int>();
	/*float normOfTime[3];
	float price[3];
	int numberCompletedUnitsMeasure[3];
	float costWork;*/

	*workshopData[i].orderNumber = workInWorkshop[i]["orderNumber"].get<int>();
	//cout << "orderNumber: " << *workshopData[i].orderNumber << endl;

	//тут проблема и. Скорее всего тип который берём это int, а не string (если так то не работает)

	//работает
	//*workshopData[i].performerServiceNumber = "test";

	//не работает.
	//РЕШЕНА))))))
	*workshopData[i].performerServiceNumber = performerServiceNumber;
	//cout << "performerServiceNumber: " << workInWorkshop[i]["performerServiceNumber"].get<int>() << endl;

	*workshopData[i].jobCode = workInWorkshop[i]["jobCode"].get<int>();
	//cout << "jobCode: " << *workshopData[i].jobCode << endl;

	//и тут проблема:)
	//А тут ещё не решена ((((
	*workshopData[i].unit = unit;
	//cout << "unit: " << workInWorkshop[i]["unit"].get<int>() << endl;

	*workshopData[i].normOfTime = workInWorkshop[i]["normOfTime"].get<float>();
	//cout << "normOfTime: " << *workshopData[i].normOfTime << endl;

	*workshopData[i].price = workInWorkshop[i]["price"].get<float>();
	//cout << "price: " << *workshopData[i].price << endl;

	*workshopData[i].numberCompletedUnitsMeasure = workInWorkshop[i]["numberCompletedUnitsMeasure"].get<int>();
	//cout << "numberCompletedUnitsMeasure: " << *workshopData[i].numberCompletedUnitsMeasure << endl;

	workshopData[i].costWork = workInWorkshop[i]["costWork"].get<float>();
	//cout << "costWork: " << workshopData[i].costWork << endl;
}

void addFromJsonToWorkInWorkshop(int key, string item)
{
}

void createWorkInWorkshop(WorkInWorkshop* workshopData, string fileName)
{
	int amountWorkInWorkshop = getAmountWorkInWorkshop(fileName);
	//int performerServiceNumber;
	json jsonData{};
	float costWork;
	string userResponse;

	while (1)
	{
		cout << "Хотите чтобы данные заполнились рандомно? (y/n): ";
		cin >> userResponse;

		if (userResponse == "y")
		{
			int performerServiceNumber;

			for (int i = 0; i < amountWorkInWorkshop; i++)
			{
				*workshopData[i].orderNumber = rand() % 9999;

				performerServiceNumber = requestPerformerServiceNumberForCreateWorkshopData(i);
				*workshopData[i].performerServiceNumber = performerServiceNumber;

				*workshopData[i].jobCode = rand() % 999;
				//*workshopData[i].unit = getRandomStr(5);
				*workshopData[i].unit = rand() % 9999;
				*workshopData[i].normOfTime = (float)(rand()) / ((float)(RAND_MAX / 9));
				*workshopData[i].price = (float)(rand()) / ((float)(RAND_MAX / 9));
				*workshopData[i].numberCompletedUnitsMeasure = rand() % 999;
				workshopData[i].costWork = *workshopData[i].price * *workshopData[i].numberCompletedUnitsMeasure;

				jsonData[i]["orderNumber"] = *workshopData[i].orderNumber;
				jsonData[i]["performerServiceNumber"] = performerServiceNumber;
				jsonData[i]["jobCode"] = *workshopData[i].jobCode;
				jsonData[i]["unit"] = *workshopData[i].unit;
				jsonData[i]["normOfTime"] = *workshopData[i].normOfTime;
				jsonData[i]["price"] = *workshopData[i].price;
				jsonData[i]["numberCompletedUnitsMeasure"] = *workshopData[i].numberCompletedUnitsMeasure;
				jsonData[i]["costWork"] = workshopData[i].costWork;
			}
			break;
		}

		if (userResponse == "n")
		{
			int orderNumber[4];
			int performerServiceNumber[6];
			int jobCode[3];
			int unit[5];
			float normOfTime[3];
			float price[3];
			int numberCompletedUnitsMeasure[3];
			float costWork;

			for (int i = 0; i < amountWorkInWorkshop; i++)
			{
				cout << "Введите данные" << endl;

				cout << "Номер наряда (целые числа, небольше 4 символов):" << endl;
				cin >> *orderNumber;

				cout << "Табельный номер исполнителя (строка, небольше 6 символов):" << endl;
				cin >> *performerServiceNumber;

				cout << "Код работы (целые числа, небольше 3 символов):" << endl;
				cin >> *jobCode;

				cout << "Единица измерения (строка, небольше 5 символов):" << endl;
				cin >> *unit;

				cout << "Норма времени ч. (вещественное число, небольше 3 символов):" << endl;
				cin >> *normOfTime;

				cout << "Расценка руб. коп. (вещественное число, небольше 3 символов):" << endl;
				cin >> *price;

				cout << "Расценка руб. коп. (целое число, небольше 3 символов):" << endl;
				cin >> *numberCompletedUnitsMeasure;

				costWork = *price * *numberCompletedUnitsMeasure;

				jsonData[i]["orderNumber"] = *orderNumber;
				jsonData[i]["performerServiceNumber"] = *performerServiceNumber;
				jsonData[i]["jobCode"] = *jobCode;
				jsonData[i]["unit"] = *unit;
				jsonData[i]["normOfTime"] = *normOfTime;
				jsonData[i]["price"] = *price;
				jsonData[i]["numberCompletedUnitsMeasure"] = *numberCompletedUnitsMeasure;
				jsonData[i]["costWork"] = costWork;
			}
			break;
		}

		if (userResponse != "y" && userResponse != "n")
			cout << "Не корректный ввод" << endl;
	}
	cout << "jsonData: " << jsonData << endl;
	createJsonFile(jsonData, fileName);
}

int requestPerformerServiceNumberForCreateWorkshopData(int index)
{
	int performerServiceNumber;
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

void createJsonFile(json jsonData, string fileName)
{
	ofstream jsonFile(fileName);
	jsonFile << jsonData;
	cout << "Файл " << fileName << " успешно создан" << endl;
	jsonFile.close();
}

void printWorkInWorkshop(WorkInWorkshop* workshopData, string fileName)
{
	int amountWorkshopData = getAmountWorkInWorkshop(fileName);

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

	//cout << "amountWorkshopData sizeof: " << amountWorkshopData << endl;
	for (int i = 0; i < amountWorkshopData; i++)
	{
		cout
			<< setw(4) << i + 1
			<< setw(10) << *workshopData[i].orderNumber
			<< setw(15) << *workshopData[i].performerServiceNumber
			<< setw(12) << *workshopData[i].jobCode
			<< setw(10) << *workshopData[i].unit
			<< setw(13) << *workshopData[i].normOfTime
			<< setw(16) << *workshopData[i].price
			<< setw(32) << *workshopData[i].numberCompletedUnitsMeasure
			<< setw(34) << workshopData[i].costWork
			<< endl;
	}
}

void requestPerformerServiceNumber(WorkInWorkshop* workshopData,
                                   WorkInWorkshop* dataOfSelectedPerformers,
                                   string fileName)
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
		                               stoi(requestedServiceNumber),
		                               fileName);
	}
}

void copySelectedArtist(WorkInWorkshop* workshopData,
                        WorkInWorkshop* dataOfSelectedPerformers,
                        int numberOfLoopExecution,
                        int i)
{
	*dataOfSelectedPerformers[numberOfLoopExecution].orderNumber = *workshopData[i].orderNumber;
	*dataOfSelectedPerformers[numberOfLoopExecution].performerServiceNumber = *workshopData[i].
		performerServiceNumber;
	*dataOfSelectedPerformers[numberOfLoopExecution].jobCode = *workshopData[i].jobCode;
	*dataOfSelectedPerformers[numberOfLoopExecution].unit = *workshopData[i].unit;
	*dataOfSelectedPerformers[numberOfLoopExecution].normOfTime = *workshopData[i].normOfTime;
	*dataOfSelectedPerformers[numberOfLoopExecution].price = *workshopData[i].price;
	*dataOfSelectedPerformers[numberOfLoopExecution].numberCompletedUnitsMeasure =
		*workshopData[i].numberCompletedUnitsMeasure;
	dataOfSelectedPerformers[numberOfLoopExecution].costWork = workshopData[i].costWork;
}

void findCopyAndPrintSelectedArtist(WorkInWorkshop* workshopData,
                                    WorkInWorkshop* dataOfSelectedPerformers,
                                    int requestedServiceNumber,
                                    string fileName)
{
	bool isFoundPerformerServiceNumber;
	int performerServiceNumber,
	    previousPerformerServiceNumber = NULL;
	int amountWorkshopData = getAmountWorkInWorkshop(fileName),
	    numberOfLoopExecution = 0;
	float totalCostOfWork = 0,
	      timeOfExecutionOfListedWorks = 0;

	for (int i = 0; i < amountWorkshopData; i++)
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

void printSelectedArtist(WorkInWorkshop* dataOfSelectedPerformers,
                         int previousPerformerServiceNumber,
                         int index)
{
	int currentPerformerServiceNumber;
	bool isSameServiceNumber;

	currentPerformerServiceNumber = *dataOfSelectedPerformers[index].performerServiceNumber;
	isSameServiceNumber = currentPerformerServiceNumber == previousPerformerServiceNumber;
	if (isSameServiceNumber)
		printRecords(dataOfSelectedPerformers, index);
	else
		printServiceNumberFieldsAndRecords(dataOfSelectedPerformers, index);
}

void printRecords(WorkInWorkshop* dataOfSelectedPerformers, int serialNumber)
{
	cout
		<< "\n"
		<< left
		<< setw(4) << serialNumber + 1
		<< setw(10) << *dataOfSelectedPerformers[serialNumber].orderNumber
		<< setw(12) << *dataOfSelectedPerformers[serialNumber].jobCode
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

void printServiceNumberFieldsAndRecords(WorkInWorkshop* dataOfSelectedPerformers, int serialNumber)
{
	printServiceNumberAndFields(dataOfSelectedPerformers, serialNumber);
	printRecords(dataOfSelectedPerformers, serialNumber);
}

void printServiceNumberAndFields(WorkInWorkshop* dataOfSelectedPerformers, int serialNumber)
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
