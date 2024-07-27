
#include <iostream>

using namespace std;

enum enOparetionType { sum = 1, sub = 2, mal = 3, dev = 4, mix = 5 };
enum enLevelType { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };

struct stQouesttion
{
	int number1 = 0;
	int number2 = 0;
	enOparetionType qouestiomType;
	enLevelType levelType;
	int correctAnswer = 0;
	int playerAnswer = 0;
	bool answerResult = false;
};
struct stQuiz
{
	stQouesttion quizList[100];
	enOparetionType Optype;
	enLevelType levelType;
	short qouestionNumber = 0;
	int numberOfRightAnswers = 0;
	int numberOfWrongAnswers = 0;
	bool isPass = false;
};
int randomNumber(int from, int to)
{
	int num = rand() % (to - from + 1) + from;
	return num;
}
int readHowManyQouestion()
{
	int num = 0;
	do
	{
		cout << "How Many Questions Do You Want? from 1, To 10 : ";
		cin >> num;
	} while (num < 1 || num>10);

	return num;
}
int readPlayerAnswer()
{
	int answer = 0;
	cin >> answer;
	return answer;
}
enLevelType readQuestionLevel()
{
	int num = 0;
	do
	{
		cout << "chose Level: Easy[1], Med[2], Hard[3], Mix[4]. :  ";
		cin >> num;
	} while (num < 1 || num>4);

	return (enLevelType)num;
}
enOparetionType readQuestionOptype()
{
	int num = 0;
	do
	{
		cout << "chose Level: Sum[1], Sub[2], Mal[3], Div[4], Mix[5]. :  ";
		cin >> num;
	} while (num < 1 || num>5);

	return (enOparetionType)num;
}
string getTypeSymbol(enOparetionType opType)
{
	switch (opType)
	{
	case enOparetionType::sum:
		return "+";

	case enOparetionType::sub:
		return "-";

	case enOparetionType::mal:
		return "*";

	case enOparetionType::dev:
		return "/";

	default:
		return "Mix";
	}
}
string getLevelText(enLevelType level)
{
	switch (level)
	{
	case enLevelType::Easy:
		return "[Easy]";

	case enLevelType::Mid:
		return "[Med]";

	case enLevelType::Hard:
		return "[Hard]";

	default:
		return "[Mix]";
	}
}
void setScreenColor(bool right)
{
	if (right)
	{
		system("color 3F");
	}
	else
	{
		system("color 4F");
		cout << "\a";
	}
}
int simpleCalculater(int num1, int num2, enOparetionType opType)
{
	switch (opType)
	{
	case enOparetionType::sum:
		return num1 + num2;

	case enOparetionType::sub:
		return num1 - num2;
	case enOparetionType::mal:
		return num1 * num2;

	case enOparetionType::dev:
		return num1 / num2;

	default:
		return num1 + num2;
	}

}
enOparetionType generateRandomOptype()
{
	int num = randomNumber(1, 4);
	return(enOparetionType)num;
}
stQouesttion generateQouestion(enLevelType& qouestionLevel, enOparetionType opType)
{
	//Function To Creat Question By Geting Mix OpType, Level and Storge Number1, number2 And Calc Them To Get Result. 
	stQouesttion qouestion;

	if (opType == enOparetionType::mix)
	{
		opType = generateRandomOptype();
	}

	if (qouestionLevel == enLevelType::Mix)
	{
		qouestionLevel = (enLevelType)randomNumber(1, 3);
	}
	qouestion.qouestiomType = opType;
	switch (qouestionLevel)
	{
	case  enLevelType::Easy:
	{
		qouestion.number1 = randomNumber(1, 10);
		qouestion.number2 = randomNumber(1, 10);
		qouestion.levelType = qouestionLevel;
		qouestion.correctAnswer = simpleCalculater(qouestion.number1, qouestion.number2, qouestion.qouestiomType);
		return qouestion;
	}
	case enLevelType::Mid:
	{
		qouestion.number1 = randomNumber(10, 50);
		qouestion.number2 = randomNumber(10, 50);
		qouestion.levelType = qouestionLevel;
		qouestion.correctAnswer = simpleCalculater(qouestion.number1, qouestion.number2, qouestion.qouestiomType);
		return qouestion;
	}
	case enLevelType::Hard:
	{
		qouestion.number1 = randomNumber(50, 100);
		qouestion.number2 = randomNumber(50, 100);
		qouestion.levelType = qouestionLevel;
		qouestion.correctAnswer = simpleCalculater(qouestion.number1, qouestion.number2, qouestion.qouestiomType);
		return qouestion;
	}
	}
	return qouestion;
}
void generateQuizQouestion(stQuiz& quiz)
{
	//function to storage Questions In Array Inside The Struct stQuiz. 
	for (short qouestion = 0; qouestion < quiz.qouestionNumber; qouestion++)
	{
		quiz.quizList[qouestion] = generateQouestion(quiz.levelType, quiz.Optype);
	}
}
void correcTheQuestionAnswer(stQuiz& quiz, short question)
{
	if (quiz.quizList[question].playerAnswer != quiz.quizList[question].correctAnswer)
	{
		quiz.quizList[question].answerResult = false;
		quiz.numberOfRightAnswers++;

		cout << "Worng Answer :-(\n";
		cout << "The Right Answer Is: " << quiz.quizList[question].correctAnswer;
	}
	else
	{
		quiz.quizList[question].answerResult = true;
		quiz.numberOfWrongAnswers++;

		cout << "Right Answer :-)\n";
	}
	cout << endl;
	setScreenColor(quiz.quizList[question].answerResult);

}
void printQuestion(stQuiz& quiz, short QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << quiz.qouestionNumber << "]\n\n";
	cout << quiz.quizList[QuestionNumber].number1 << endl;
	cout << quiz.quizList[QuestionNumber].number2 << " ";
	cout << getTypeSymbol(quiz.quizList[QuestionNumber].qouestiomType);
	cout << "\n__________\n";
}
void askAndCorrectQuestionListAnswers(stQuiz& quiz)
{
	for (short QuNumber = 0; QuNumber < quiz.qouestionNumber; QuNumber++)
	{
		printQuestion(quiz, QuNumber);
		quiz.quizList[QuNumber].playerAnswer = readPlayerAnswer();
		correcTheQuestionAnswer(quiz, QuNumber);
	}
	quiz.isPass = (quiz.numberOfRightAnswers <= quiz.numberOfWrongAnswers);
}
string getFinalResult(bool pass)
{
	if (pass)
	{
		system("color 3F");
		return "PASS*";
	}
	else
		return "FaIl!";
}
void printQuizResults(stQuiz quiz)
{
	cout << "\n________________________________________\n\n";
	cout << "Final Result Is " << getFinalResult(quiz.isPass);
	cout << "\n________________________________________\n\n";

	cout << "Numbre Of Questions    :" << quiz.qouestionNumber << endl;
	cout << "Questions Level        :" << getLevelText(quiz.levelType) << endl;
	cout << "OpType                 :" << getTypeSymbol(quiz.Optype) << endl;
	cout << "Number Of Right Answers:" << quiz.numberOfRightAnswers << endl;
	cout << "Number Of Worng Answers:" << quiz.numberOfWrongAnswers << endl;
	cout << "\n________________________________________\n\n";
}
void playMathGame()
{
	stQuiz quiz;

	quiz.qouestionNumber = readHowManyQouestion();
	quiz.levelType = readQuestionLevel();
	quiz.Optype = readQuestionOptype();

	generateQuizQouestion(quiz);

	askAndCorrectQuestionListAnswers(quiz);

	printQuizResults(quiz);

}
void resetScreen()
{
	system("CLS");
	system("color 0F");
}
void startGame()
{
	char playAgain = 'Y';
	do
	{
		resetScreen();
		playMathGame();

		cout << "Do YouWant To Play Again? Type [y] : ";
		cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	startGame();
}