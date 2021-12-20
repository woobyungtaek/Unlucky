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
	static rapidjson::GenericValue<JSON_UTF16>* GetJsonDataPoint(D2D1_POINT_2F point);
	static rapidjson::GenericValue<JSON_UTF16>* GetJsonDataRect(D2D1_RECT_F rect);

	rapidjson::GenericDocument<JSON_UTF16> Json;
	void SaveDataByDataList(string fileName, vector<RapidJsonData*>& dataList);
	bool LoadDataByFileName(string fileName, rapidjson::GenericDocument<rapidjson::UTF16<>>& openDoc);
};

