#pragma once

#include <map>

template <typename T>
	class ATree
{
public:
	typedef typename std::map<std::string, T>::iterator iterator;
	
	ATree()
	{
		for(int i = 0; i < 27; ++i)
			_maps[i] = NULL;
	}
	
	~ATree()
	{
		for(int i = 0; i < 27; ++i)
			if(_maps[i]) delete _maps[i];
	}
	
	void insert(std::string &key, T value)
	{
		if(!key.length()) return;
		
		char idx = ::tolower(key.at(0));
	
		if(idx >= 'a' && idx <= 'z') idx -= 'a';
		else idx = 26;

		if(!_maps[idx])
			_maps[idx] = new std::map<std::string, T>();

		_maps[idx]->emplace(std::pair<std::string, T>(key, value));
	}
	
	void remove(std::string &key)
	{
		char idx = ::tolower(key.at(0));
	
		if(idx >= 'a' && idx <= 'z') idx -= 'a';
		else idx = 26;

		if(!_maps[idx]) return;

		auto it = _maps[idx]->find(key);
		if(it != _maps[idx]->end())
		{
			_maps[idx]->erase(it);
			
			if(!_maps[idx]->size())
			{
				delete _maps[idx];
				_maps[idx] = NULL;
			}
		}
	}
	
	bool find(std::string &key, iterator &out)
	{
		char idx = ::tolower(key.at(0));
	
		if(idx >= 'a' && idx <= 'z') idx -= 'a';
		else idx = 26;

		if(!_maps[idx]) return false;

		auto it = _maps[idx]->find(key);
		if(it != _maps[idx]->end())
		{
			out = it;
			return true;
		}
		
		return false;
	}
	
private:
	std::map<std::string, T> *_maps[27];
};
