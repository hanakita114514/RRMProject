#pragma once

#include <map>

class GraphicLoad
{
private:
	std::map<std::string, int> _graphMap;

	GraphicLoad();
	GraphicLoad(const GraphicLoad&);
	GraphicLoad& operator = (const GraphicLoad&);
public:
	~GraphicLoad();

	static GraphicLoad& Instance()
	{
		static GraphicLoad instance;
		return instance;
	}

	int LoadGraph(const std::string& filePath);

	void Delete();
};

