#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

class err_no_file : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "no such file\n";
    }
};

class file_ut : public err_no_file
{
private:
    vector<string> found_words;

    std::vector<std::string> table;

    const string filename = "5_letter.txt";

public:
    file_ut(const std::string n) : filename(n) {}

    void display_loaded()
    {
        for (auto i : table)
        {
            cout << i << endl;
        }
    }

    void display_found()
    {
        for (auto i : found_words)
        {
            cout << i << endl;
        }
    }

    void load_file()
    {
        string tmp;

        std::ifstream in(filename);

        if (!in)
        {
            throw err_no_file();
        }

        while (!in.eof())
        {
            in >> tmp;
            table.push_back(tmp);
        }
    }

    void search()
    {
        string word;
        bool flag = true;
        string letters_add;
        string letters_not;
        int j = 0;
        int k = 0;

        cout << "====================" << endl
             << "when none press '0'" << endl;

        // THE PROPER LETTER ALIGNMENT
        for (int i = 0; i < 5; ++i)
        {
            char tmp;
            cout << i + 1 << ". letter: ";
            cin >> tmp;
            word.push_back(tmp);
        }

        cout << endl
             << "word: " << word << endl;

        // THE PROPER LETTERS NOT MENTIONED PREVIOUSLY
        cout << "====================" << endl;

        cout << "now additional search parameters. if none press '0'" << endl;

        while (letters_add[j - 1] != '0')
        {
            char tmp;
            cout << "It has to containt letter: ";
            cin >> tmp;
            letters_add.push_back(tmp);
            j++;
        }
        letters_add.pop_back(); // removing zero

        cout << "additional letters: " << letters_add << endl;

        // THE LETTERS NOT IN THE WORD
        cout << "now letters not in the word. if none press '0'" << endl;

        while (letters_not[k - 1] != '0')
        {
            char tmp;
            cout << "It does not containt letter: ";
            cin >> tmp;
            letters_not.push_back(tmp);
            k++;
        }
        letters_not.pop_back(); // removing zero

        cout << "letters not in the word: " << letters_not << endl;

        cout << "====================" << endl;

        for (auto it : table) // 'it' is what we have from the list
        {
            for (int i = 0; i < 5; ++i)
            {
                if (it[i] == word[i] || word[i] == '0')
                {
                }
                else
                {
                    flag = false;
                }
            }

            for (auto letter : letters_add)
            {
                bool is_in_word = false;

                for (int i = 0; i < 5; ++i)
                {
                    if (letter == it[i])
                    {
                        is_in_word = true;
                    }
                }

                if (is_in_word)
                {
                }
                else
                {
                    flag = false;
                }
            }

            for (auto letter : letters_not)
            {
                for (int i = 0; i < 5; ++i)
                {
                    if (letter == it[i])
                    {
                        flag = false;
                        break;
                    }
                }
            }

            if (flag)
            {
                found_words.push_back(it);
            }

            flag = true;
        }
    }
};

int main()
{
    file_ut words("5_letter.txt");

    words.load_file();

    words.display_loaded();

    words.search();

    words.display_found();
}