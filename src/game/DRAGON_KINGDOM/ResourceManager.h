#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

template <typename Type, typename Resource>
class ResourceManager 
{
public:
	ResourceManager()
	{
	}
	
	~ResourceManager()
	{
	}

	void SetResource(Type _Key, Resource* _Resource)
	{
		m_ResourceData[_Key] = _Resource;
	}

	Resource* GetResource(Type _Key)
	{
		return m_ResourceData[_Key];
	}


private:
	std::map<Type, Resource*> m_ResourceData;

};

#endif