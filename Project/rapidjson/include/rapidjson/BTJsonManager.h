#pragma once

#define JSON_UTF16 rapidjson::UTF16<>
#define JSON_GENERIC_P_VALUE rapidjson::GenericValue<JSON_UTF16>

class RapidJsonData
{
public:
	RapidJsonData() { };
	~RapidJsonData() { };

public:
	rapidjson::GenericValue<JSON_UTF16> key;
	rapidjson::GenericValue<JSON_UTF16> value;


};

class BTJsonManager
{
private:
	static BTJsonManager* mInstance;

public:
	static BTJsonManager* GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new BTJsonManager();
		}
		return mInstance; 
	}

private:
	BTJsonManager() 
	{
		Json.SetObject();
	}

public:
	~BTJsonManager() 
	{
		delete mInstance;
	}

public:
	static rapidjson::GenericValue<JSON_UTF16>* GetJsonDataPoint(CPoint point);
	static rapidjson::GenericValue<JSON_UTF16>* GetJsonDataRect(CRect rect);

	rapidjson::GenericDocument<JSON_UTF16> Json;
	void SaveDataByDataList(CString fileName, vector<RapidJsonData*>& dataList);
	bool LoadDataByFileName(CString fileName, rapidjson::Document& openDoc);
};

