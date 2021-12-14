#pragma once

#include "Box.h"
#include<unordered_map>

class PatternMatchingCollisionEventManager
{
public:
	//void InitMap()
	//{
	//	map[{"blue", "yellow"}] = []() {
	//		//turn the yellow one blue
	//	};
	//	map[{Blue, Yellow}]
	//}
private:
	std::unordered_map<std::pair<Box::ColorTrait, Box::ColorTrait>, void(*)()> map;
	//another function. if blue and yellow or yellow and blue collides, call the mapped function.
};
