#pragma once
#include <string>

#ifndef NULL
#define NULL nullptr
#endif

class Node;



class CharNode
{
public:
	CharNode(char c);
	~CharNode();
	char character;
	class CharNode * next;
	class DLBNode * child;
};

class DLBNode
{
public:
	DLBNode();
	~DLBNode();
	bool hasCharNode(char c);
	class CharNode * getCharNode(char c);
	class CharNode * getOrCreateCharNode(char c);


	class CharNode * head;
};

class DLBTrie
{
public:
	DLBTrie();
	~DLBTrie();

	void addWord(std::string word);


	// Learned today that sometimes you can't
	// separate the Header file forward declaration
	// and .cpp implementation of a template function.

	// Hence, that is why the following two functions are
	// implemented in the header file.
	template <size_t wordSize>
	bool wordExists (char(&str)[wordSize])
	{
		if (str[0] == '\0')
		{
			return false;
		}
		DLBNode * curr = root;
		CharNode * tempCharNode;
		for (char &c : str)
		{
			// If we reach the end of the string
			// without returning an invalid path
			// then it's a valid path
			if (c == '\0')
			{
				CharNode * terminalNode = curr->getCharNode(c);
				if (terminalNode != NULL)
				{
					return true;
				}
				return false;
			}
			tempCharNode = curr->getCharNode(c);
			if (tempCharNode != NULL)
			{
				curr = tempCharNode->child;
			}
			else
			{
				return false;
			}
		}
	}

	template <size_t wordSize>
	bool isValidTriePath(char(&str)[wordSize])
	{
		if (str[0] == '\0')
		{
			return false;
		}
		DLBNode * curr = root;
		CharNode * tempCharNode;
		for (char &c : str)
		{
			// If we reach the end of the string
			// without returning an invalid path
			// then it's a valid path
			if (c == '\0')
			{
				return true;
			}
			tempCharNode = curr->getCharNode(c);
			if (tempCharNode != NULL)
			{
				curr = tempCharNode->child;
			}
			else
			{
				return false;
			}
			if (curr == NULL)
			{
				return false;
			}
		}
	}

private:
	class DLBNode * root;
};
