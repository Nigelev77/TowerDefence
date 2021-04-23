#pragma once

#include <string>
#include <string_view>



struct TextBillboardComponent
{
	//Maybe use some sort of unsigned int array if using their char codes?
	
	//using <string> class for now to make this safer but slower
	std::string text;
	float r, g, b, a;

	TextBillboardComponent(std::string_view t, float r, float g, float b, float a)
		: text{t.data()}, r{r}, g{g}, b{b}, a{a}
	{}

	TextBillboardComponent()
		: text{}, r{}, g{}, b{}, a{}
	{}

};