#include "InputText.h"
#include <clocale>
#include <vector>
#include "Check.h"
#include "FIleOutputText.h"
#include "FileInput.h"
#include "SubStr.h"
#include <locale>
#include <Windows.h>

using namespace std;
enum class Type
{
	console = 1,
	file,
	none
};
enum class Menu
{
	input = 1,
	change,
	repair,
	out,
	none
};

enum class RepairMenu
{
	InputFile = 1,
	UseEntered
};


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "verbeckiy d 415 var 6 kr 4 " << endl;
	RepairMenu repairMenuItem;
	int interval = 0;
	const int Yes = 1;
	bool gHooks = false;
	int substrLen;
	string text = "";
	string changedText = "";
	string repairedText = "";
	Menu menu_item = Menu::none;
	Type type = Type::none;
	int step;
	while (true)
	{


		cout << "\n1 - Input" << endl
			<< "2 - Change text" << endl
			<< "3 - repair text" << endl
			<< "4 - Exit" << endl;
		menu_item = static_cast<Menu>(CheckMenu(4));
		switch (menu_item)
		{
		case Menu::input:
			text.clear();
			cout << "1 - console\n2 - file" << endl;
			type = static_cast<Type>(CheckMenu(2));
			switch (type)
			{
			case Type::console:
				text.clear();
				InputText(&text);
				cout << "Save to file?\n1.Yes\n2.No" << endl;
				if (CheckMenu(2) == Yes)
					FileOutputText(text);
				break;
			case Type::file:
				text.clear();
				FileInput(&text);
				break;
			}
			break;

		case Menu::change:
			if (text.empty())
			{
				cout << "Enter text first" << endl;
				break;
			}
			changedText.clear();
			cout << "Initial text: " << text << endl;
			cout << endl << "Characters: " << text.length() << "\nEnter the length of the substring.  " << endl;;
			substrLen = CheckIntValue();
			changedText = text;
			interval = static_cast<int>(text.length()) - substrLen;
			if (interval <= 0)
			{
				cout << "Substring greater than original text" << endl;
				break;
			}
			else {
				gHooks = Staples(changedText, '{');

				for (int i = 0; i < (interval - 1); i++)
				{
					string findSubstring = changedText.substr(i, substrLen); //выбор подстроки от позиции по количеству замены

					step = CheckSubstr(findSubstring, changedText, i); //шаг сдвига для поиска следующего фрагмента, пропуск пробелов и знаков препинания


					if (step > 0) { i += step - 1; continue; }
					int textStartPos = 0;
					int sPos = i;
					int changes = 0;
					bool count = false;
					do {
						string::size_type n = changedText.find(findSubstring, sPos);
						if (n == string::npos)
						{
							if (changes > 0)
							{
								i = i + (substrLen - 1);
							}
							break;
						}
						else
						{
							if (!count)
							{
								count = true;
								textStartPos = (int)n;
							}
							else
							{
								changes = СhangeText((int)n, textStartPos, substrLen, changedText, gHooks);
							}

							sPos = static_cast<int>(n) + substrLen;
						}

					} while (true);
				}

				cout << "Chenged: " << changedText << endl;

				cout << "Save to file?\n1.Yes\n2.No" << endl;
				if (CheckMenu(2) == Yes)
					FileOutputText(changedText);
				break;
			}
		case Menu::repair:
			cout << "1 - Input text from file\n2 - Used entered text" << endl;
			repairMenuItem = static_cast<RepairMenu>(CheckMenu(2));
			switch (repairMenuItem)
			{
			case RepairMenu::InputFile:
				changedText.clear();
				repairedText.clear();
				FileInput(&repairedText);
				break;
			case RepairMenu::UseEntered:
				if (changedText.empty())
				{
					cout << "No text entered" << endl;
					continue;
				}
				repairedText = changedText;
			}
			cout << "Initial text:\t " << repairedText << endl;
			RepairStartText(repairedText);
			cout << "Changed text:\t" << repairedText << endl;
			cout << "Save to file?\n1.Yes\n2.No" << endl;
			if (CheckMenu(2) == Yes)
				FileOutputText(repairedText);
			break;
		case Menu::out:
			return 0;
		}


	}
}

