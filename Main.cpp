#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

template<typename T>
class node
{
public:
	T data;
	node<T>* next;
};

template<typename T>
class queue
{
public:
	node <T>* front;
	node <T>* rear;
	int size;

	queue()	//O(1)
	{
		front = nullptr;
		rear = nullptr;
		size = 0;
	}
	int Size()
	{
		return size;
	}
	bool isEmpty()	//O(1)
	{
		if (rear == nullptr || size == 0)
			return true;
		return false;
	}
	bool Front(T& amp)	//O(1)
	{
		if (rear == nullptr || size == 0)
			return false;
		amp = front->data;
		return true;
	}
	bool Rear(T& amp)	//O(1)
	{
		if (rear == nullptr || size == 0)
			return false;
		amp = rear->data;
		return true;
	}
	bool dequeue(T& n)	//O(1)
	{
		if (front == nullptr)
			return false;
		node<T>* temp = front;
		front = front->next;
		rear->next = front;
		n = temp->data;
		delete temp;
		size--;
		if (size == 0)
			rear = nullptr;
		return true;
	}
	void enqueue(T val)	//O(1)
	{
		node<T>* temp = new node <T>;
		temp->data = val;
		if (rear != nullptr && size > 0)
			rear->next = temp;
		rear = temp;
		size++;
		if (front == nullptr)
			front = temp;
		temp->next = front;
	}
	void print(RenderWindow & window, queue<T>& discard)//O(n)
	{
		Font font;
		font.loadFromFile("Yagora.ttf");
		if (size == 1)
		{
			string s = to_string(front->data);
			Text num;

			num.setFont(font);
			num.setString("WINNER");
			num.setStyle(Text::Bold);
			num.setCharacterSize(100);
			num.setFillColor(Color(0, 150, 0));
			num.setPosition(Vector2f(360, 180));
			window.draw(num);

			num.setFont(font);
			num.setString(s);
			num.setStyle(Text::Bold);
			num.setCharacterSize(60);
			num.setFillColor(Color(255, 255, 255));
			num.setPosition(Vector2f(520, 670));
			window.draw(num);

			CircleShape temp;

			temp.setRadius(100);
			temp.setPosition(Vector2f(450, 450));

			Texture tex;
			tex.loadFromFile("winner.jpg");
			if (!tex.loadFromFile("winner.jpg"))
			{
				cout << "Picture not loaded\n";
			}

			temp.setTexture(&tex);
			window.draw(temp);
		}
		else
		{
			int i = 1;
			int k = 1;
			node<T>* curr = front;
			for (int j = 0; j < size; j++, k++, curr = curr->next)
			{
				string s = to_string(curr->data);
				Text num;
				num.setFont(font);
				num.setString(s);
				num.setStyle(Text::Bold);
				num.setCharacterSize(20);
				num.setFillColor(Color(150, 150, 150));
				
				
				CircleShape temp;
				
				Texture tex;
				if (j == 0)
				{
					temp.setRadius(80);
					num.setCharacterSize(40);
					num.setPosition(Vector2f(410, 430));
					
					temp.setPosition(Vector2f(430, 470));
					
					tex.loadFromFile("curr.jpg");
					if (!tex.loadFromFile("curr.jpg"))
						cout << "Picture not loaded\n";
					k--;
				}
				else
				{
					temp.setRadius(22);
					if (curr->data < 10)
						num.setPosition(Vector2f(k * 50 + 16, 80 * i + 40));
					else
						num.setPosition(Vector2f(k * 50 + 11, 80 * i + 40));

					temp.setPosition(Vector2f(k * 50 + 2, 80 * i));
					
					tex.loadFromFile("alive.jpg");
					if (!tex.loadFromFile("alive.jpg"))
						cout << "Picture not loaded\n";
				}

				temp.setTexture(&tex);
				window.draw(temp);
				window.draw(num);

				if (j == 15 * i)
				{
					i++;
					k = 0;
				}
			}
		}

		
		Text num;
		num.setFont(font);
		num.setString("DEAD");
		num.setStyle(Text::Bold);
		num.setCharacterSize(30);
		num.setFillColor(Color(200, 0, 0));
		num.setPosition(Vector2f(975, 50));
		window.draw(num);
		CircleShape temp;

		node <T>* curr = discard.front;
		int k = 120;
		int x = 950;
		for (int j = 0; j < discard.size; j++, curr = curr->next)
		{
			string s = to_string(curr->data);
			Text num;
			num.setFont(font);
			num.setString(s);
			num.setStyle(Text::Bold);
			num.setCharacterSize(15);
			num.setFillColor(Color(200, 200, 200));
			num.setPosition(Vector2f(x+15, k-20));
			window.draw(num);
			CircleShape temp;

			temp.setRadius(15);
			temp.setPosition(Vector2f(x, k));

			Texture tex;
			tex.loadFromFile("dead.jpg");
			if (!tex.loadFromFile("dead.jpg"))
			{
				cout << "Picture not loaded\n";
			}

			temp.setTexture(&tex);
			window.draw(temp);

			k += 50;

			if (k > 950)
			{
				x += 50;
				k = 120;
			}
		}
		
	}

	void Josephus_Prob(int k) //O(n)
	{
		Font font;
		font.loadFromFile("Yagora.ttf");
		queue<int> discard;
		RenderWindow window(VideoMode(1100, 1000), "Josephus Problem");
		Event event;
		Clock clock;
		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			window.clear(Color(0, 0, 0));
			print(window, discard);
			window.display();
			sleep(milliseconds(500));
			int x;
			while (size != 1)
				for (int i = 1; i <= k; i++)
				{
					window.clear(Color(0, 0, 0));
					print(window, discard);
					window.display();
					dequeue(x);
					sleep(milliseconds(700));

					if (i != k)
						enqueue(x);
					else
						discard.enqueue(x);
				}
		}
	}

	~queue()	//O(n)
	{
		
		if (size > 1)
		{
			node<T>* temp2 = front->next;
			for (node<T>* i = temp2; i != front; i = temp2)
			{
				temp2 = i->next;
				delete i;
			}
		}
		delete front;
	}

};

int main()
{
	queue<int> a;
	int size, k = 1;

	Font font;
	font.loadFromFile("Yagora.ttf");
	
	bool x = true;
	int temp = 0;
	RenderWindow window(VideoMode(800, 600), "Josephus Problem");
	Event event;
	Clock clock;
	Text num1;
	while (window.isOpen())
	{
		window.clear(Color(100, 100, 100));
		
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				{
					temp = temp * 10 + 1;
					
					num1.setFont(font);
					string s = to_string(temp);
					num1.setString(s);
					
					num1.setStyle(Text::Bold);
					num1.setCharacterSize(20);
					num1.setFillColor(Color(0, 0, 0));
					num1.setPosition(Vector2f(320, 270));
					window.draw(num1);
					window.display();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					temp = temp * 10 + 2;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					temp = temp * 10 + 3;
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
				{
					temp = temp * 10 + 4;
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
				{
					temp = temp * 10 + 5;
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
				{
					temp = temp * 10 + 6;
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
				{
					temp = temp * 10 + 7;
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
				{
					temp = temp * 10 + 8;
				
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
				{
					temp = temp * 10 +9;
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
				{
					temp = temp * 10 + 0;
				}
				else
				{
					if (x == true)
					{
						size = temp;
						for (int i = 1; i <= size; i++)
							a.enqueue(i);
						x = false;
						temp = 0;
					}
					else
					{
						k = temp;
						temp = 0;
						window.close();
					}
				}
			}
		}
		if (temp != 0)
		{
			num1.setFont(font);
			string s = to_string(temp);
			num1.setString(s);
			num1.setStyle(Text::Bold);
			num1.setCharacterSize(20);
			num1.setFillColor(Color(0, 0, 0));
			num1.setPosition(Vector2f(520, 270));
			window.draw(num1);
		}
		
		Text num;
		num.setFont(font);
		if (x == true)
			num.setString("Enter number of people: ");
		else
			num.setString("Enter number of terms to skip: ");
		num.setStyle(Text::Bold);
		num.setCharacterSize(20);
		num.setFillColor(Color(0, 0, 0));

		num.setPosition(Vector2f(270, 270));
		if (x == false)
			num.setPosition(Vector2f(200, 270));
		window.draw(num);
		window.display();
	}
	
	a.Josephus_Prob(k);
	

	system("pause");
	return 0;
}