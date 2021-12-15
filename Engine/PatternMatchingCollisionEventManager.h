#pragma once

#include "Box.h"
#include<unordered_map>
#include <functional>

class PatternMatchingCollisionEventManager
{
public:
	void InitMap()
	{
		map["White-Red"] = []()
		{
			// destroy red.
		};
		map["Blue-Yellow"] = []()
		{
			// turn the yellow one blue.
		};
		map["Blue-White"] = []()
		{
			// both split. // should return array
		};
		map["test"] = []() {return 1; };
	}
	std::function<void()>& Case(std::string str)
	{
		return map[str];
	}
	std::function<void()>& Default()
	{
		return def;
	}
	void operator[](const std::string& str) const
	{
		auto i = map.find(str);
		if (i != map.end())
		{
			i->second();
		}
		else
		{
			def();
		}

	}
	std::string& ReverseWords(std::string& str)
	{
		// first word is read until '-'

	}
private:
	std::unordered_map<std::string, std::function<void()>> map;
	std::function<void()> def = []() {};
	//another function. if blue and yellow or yellow and blue collides, call the mapped function.
};
