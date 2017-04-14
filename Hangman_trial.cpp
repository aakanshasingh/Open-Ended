//Hangman game

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <ctype.h>
#include <fstream>
using namespace std;
int c=0;


class Hangman
{
	 
    public:
        Hangman()
        {
        
        	 m_MaxGuesses = 6; m_NumGuesses = 0; m_Guesses.push_back('\0'); 
    	 } //sets allowed amount of guesses to 6 and number of guesses to 0
        ~Hangman()
        {
        	cout<<"Destructor Called\n";
    	}

        void Play(); 
        
        //game play function
        
        bool PlayAgain(string prompt = "\nDo you want to play again? (y/n): ") const;
        
        bool CheckGuess(string& word, char& letter) const;   
        //checks if letter is in word
        
        void DisplayGuess();//uses iter with the help of which we move through all the elements of vector
        
        int Update(string& word, char& letter, vector<char>& guesses, bool g = false); 
        //updates word or guesses, depending on bool value
        
        void Reset();//resets and asks the user for yes or no
        
        vector<char>& GetWord();

        //inlined functions
        int GetMaxGuesses() const 
        {
         return m_MaxGuesses; 
     	}
     	
        int GetGuesses() const 
        {
         return m_NumGuesses;
     	 } //get number of guesses
     	 
     	 void take();
     	 void display();
       

	class HMan
	{
		public:
		    HMan();
		    HMan(vector<char>& Man)
		    {
		         CreateMan(Man);
		    }
		    ~HMan();

		void CreateMan(vector<char>& Man);
		void DrawMan(vector<char>& Man);
		void UpdateMan(int guess, vector<char>& man);
	};

	class HWords
	{
		public:
		    HWords(vector<string>& words, bool populate = false);
		    

		    string m_GetWord() 
		    {
		     return m_Word; //returns word
	        } //inline
		    vector<char>& m_GetHWord();

		    void m_DisplayWord();
		    void m_Populate(vector<string>& words);

		protected:
		    string m_Word;
		    vector<char> m_HiddenWord;
	};

	protected:
		int m_MaxGuesses;
		int m_NumGuesses;
		vector<char> m_Guesses;
		string str;
		string word;
		string hWord;
};

string& vtostr(vector<char>& chars,string& str)//pushes the charcter that is being entered into str
{
    vector<char>::iterator iter = chars.begin();//STL iterator which is used to access vector elements
    char a;
    for (iter = chars.begin(); iter != chars.end(); iter++)
    {
       if (*iter != '_') 
       {
        a = *iter;//character is entered
        str.push_back(a);
       
	   }
	   
    }
     
    return str;
}

bool Hangman::CheckGuess(string& word, char& letter) const //checks if letter is in word
{
    size_t f;//unsigned integer type
    f = word.find(letter);//checks whether there is a letter in the range
    return (f!=string::npos);//greatest possible value of f which is of size_t
}


void Hangman::DisplayGuess()
{
    vector<char>::iterator iter = m_Guesses.begin();
    for (iter = m_Guesses.begin(); iter != m_Guesses.end(); ++iter)//stores the guess letters in m_Guess vector
    {
        cout << *iter;
    }
}

int Hangman::Update(string& word, char& letter, vector<char>& vect, bool g)
{
    vector <char>::iterator iter = vect.begin();
    if (!g) //update word
    {

        if (CheckGuess(word,letter))
        {
            vector<int> places;
            for (unsigned int i = 0; i <= word.size(); i++)
            {
                if (letter == word[i])
                {
                    places.push_back(i);//push the position
                    c++;
                }
            }
            vector<int>::iterator iter = places.begin();
            
            
            for (iter = places.begin(); iter != places.end(); ++iter)
            {

                vect.erase(vect.begin()+(*iter));//erase *iter values
                vect.insert(vect.begin()+(*iter),letter);//update *iter values with letter
                
            }
        }
    }
    else //update guesses
    {
        if (!CheckGuess(word,letter))//letter not present in word
        {
            vector<char>::const_iterator iter1 = vect.begin();
            int t = 0;
            for (iter1 = vect.begin(); iter1 != vect.end(); ++iter1)
            {
                if (letter == *iter1) {++t;}
            }
            if (t <= 0) { vect.push_back(letter); }//push the wrong letter inputs to vect for display later
            else { return 1; }
        }
    }

    return 0;
}

void Hangman::Reset()
{
    m_NumGuesses = 0;
    word = "";
    hWord = "";
    m_Guesses.clear();//clears the vector
}

vector<char>& Hangman::GetWord()
{
    return m_Guesses;//character vector containing the guessed letters
}

bool Hangman::PlayAgain(string prompt) const
{
    char choice = 'y';
    do 
    {
        cout << prompt;
        cin >> choice;
    } 
    while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
    return (choice == 'y' || choice == 'Y');
}

void Hangman::Play()
{
	
	
    vector<string> gWords;
    HWords gWord(gWords, true);//constructor

    vector<char> Man;
    HMan* man = 0;
    man->CreateMan(Man);

    vector<char>& vect = GetWord();//stores m_guesses
    vector<char>& vGuess = gWord.m_GetHWord();
    hWord = gWord.m_GetWord();//already present in database

    char guess;
    do {
        cout << "\nWord: "; gWord.m_DisplayWord();//hidden words 
        cout << "\tIncorrect: "; DisplayGuess();//display guessedword
        cout << endl;
        man->DrawMan(Man);
        cout << "\nEnter your choice: ";
        cin >> guess;//guess is the letter we are inputting
        cout << endl;
        if (!CheckGuess(hWord,guess) && isalpha(guess))
        {
            if(Update(hWord, guess, vect, true) != 1)
            {
                ++m_NumGuesses;//letter not present in the string
                man->UpdateMan(GetGuesses()-1, Man);
            }
        }
        Update(hWord, guess, vGuess);
        word = vtostr(vGuess,str);//form the new word
        
    } 
    while ((GetGuesses() < GetMaxGuesses()) && c!=hWord.size());
    
    
   
		
	if (c==hWord.size())
	{
		  cout << "You won!\n";
		   cout << "The word was: " << gWord.m_GetWord();
		    
	}
	else
    {
    	
    	
        cout << endl;
        man->UpdateMan(m_MaxGuesses-1,Man);
        man->DrawMan(Man);
        cout << "Sorry, you lost!\n";
        cout << "The word was: " << gWord.m_GetWord();
   	}
    if (PlayAgain()) 
    { 
    	c=0;//resets c for next word
    	Reset(); 
    	Play();
	 }
}

Hangman::HWords::HWords(vector<string>& words, bool populate)//flag to check if we want to take another random word from the database or not
{
    if (populate) 
    {
    	 m_Populate(words); 
	 }
    random_shuffle(words.begin(), words.end());     //shuffles words
    srand(time(NULL));
    int w = rand()%words.size();        //sets w to random place in vector of strings
    
    m_Word.insert(0,words[w]);       //set word to represent random place
    for (unsigned int i = 1; i<=m_Word.size(); ++i)
    {
        m_HiddenWord.push_back('_');
    }
}

vector<char>& Hangman::HWords::m_GetHWord()
{
    return m_HiddenWord;
}

void Hangman::HWords::m_DisplayWord()
{
    vector<char>::iterator iter = m_HiddenWord.begin();
    for (iter = m_HiddenWord.begin(); iter != m_HiddenWord.end(); ++iter)
    {
        cout << *iter;
    }
}

void Hangman::HWords::m_Populate(vector<string>& words)
{
    string word1 = "india";
    string word2 = "france";
    string word3 = "japan";
    string word4 = "paris";
    string word5 = "rome";
    string word6 = "london";
    string word7 = "vietnam";
    string word8 = "russia";
    string word9 = "kenya";
    string word10= "usa";
    string word11= "mynmar";
    string word12= "beijing";
    string word13= "tokyo";
    string word14= "nepal";
    
    

    words.reserve(14);//requests the vector capacity to be of 14 words
    words.push_back(word1);
    words.push_back(word2);
    words.push_back(word3);
    words.push_back(word4);
    words.push_back(word5);
    words.push_back(word6);
    words.push_back(word7);
    words.push_back(word8);
    words.push_back(word9);
    words.push_back(word10);
    words.push_back(word11);
    words.push_back(word12);
    words.push_back(word13);
    words.push_back(word14);
}

void Hangman::HMan::CreateMan(vector<char>& Man)
{

    Man.push_back(' ');
    Man.push_back(' ');
    Man.push_back(' ');
    Man.push_back(' ');
    Man.push_back(' ');
    Man.push_back(' ');
}

void Hangman::HMan::DrawMan(vector <char>& Man)
{
    cout << endl;
    cout << "  +---+" << endl;
    cout << "  |   |" << endl;
    cout << "  " << Man[0] << "   |" << endl;
    cout << " " << Man[2] << Man[1] << Man[3] << "  |" << endl;
    cout << " " << Man[4] << " " << Man[5] << "  |" << endl;
    cout << " _____|" << endl;
}

void Hangman::HMan::UpdateMan(int guess, vector<char>& man)
{
    switch (guess)
    {
        case 0:
            man[0] = 'O';
            break;
        case 1:
            man[1] = '|';
            break;
        case 2:
            man[2] = '/';
            break;
        case 3:
            man[3] = '\\';
            break;
        case 4:
            man[4] = '/';
            break;
        case 5:
            man[5] = '\\';
            break;
    }
}
string wordn1;
string wordn2;
string wordn3;
string wordn4;
string wordn5;
string wordn6;
string wordn7;
string wordn8;
string wordn9;
string wordn10;
string wordn11;
string wordn12;
string wordn13;
string wordn14;



void Hangman::take()
{
	
    wordn1 = "india";
    wordn2 = "france";
    wordn3 = "japan";
    wordn4 = "paris";
    wordn5 = "rome";
    wordn6 = "london";
    wordn7 = "vietnam";
    wordn8 = "russia";
    wordn9 = "kenya";
    wordn10= "usa";
    wordn11= "mynmar";
    wordn12= "beijing";
    wordn13= "tokyo";
    wordn14= "nepal";
}

void Hangman::display()
{
	cout<<"The words in the bank are\n";
    cout<<wordn1<<endl;
    cout<<wordn2<<endl;
    cout<<wordn3<<endl;
    cout<<wordn4<<endl;
    cout<<wordn5<<endl;
    cout<<wordn6<<endl;
    cout<<wordn7<<endl;
    cout<<wordn8<<endl;
    cout<<wordn9<<endl;
    cout<<wordn10<<endl;
    cout<<wordn11<<endl;
    cout<<wordn12<<endl;
    cout<<wordn13<<endl;
    cout<<wordn14<<endl;
}

int main()
{
    Hangman* game = new Hangman();
    game->Play();
    Hangman obj;
    int i;
    cout<<"If you want to see all the words,press 0\n";
    cin>>i;
    if(i==0)
    {
    	
		ofstream show1("GAME",ios::out|ios::binary);
		obj.take();
		try
		{
		
			if(!show1)
				throw(-1);
		}
		catch(int x)
		{
			cout<<"Exception caught\n";
			cout<<"File unable to open\n";
		}
			
		show1.write((char *)&obj,sizeof(Hangman));
		show1.close();
		
		ifstream show2("GAME",ios::in|ios::ate|ios::binary);
		try
		{
		
			if(!show2)
				throw -1;
		}
		catch(int x1)
		{
			cout<<"Exception Caught\n";
			cout<<"File unable to open\n";
		}
		show2.seekg(0,ios::beg);
		show2.read((char*)&obj,sizeof(Hangman));
		obj.display();
		show2.close();
		
	}
	else
		exit(0);
	return 0;
}
		
