#include "pch.h"

#include <string>

#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/reader.h"
#include "../rapidjson/include/rapidjson/filereadstream.h"
#include "../rapidjson/include/rapidjson/encodedstream.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"

#include "BTJsonManager.h"

BTJsonManager* BTJsonManager::mInstance;

rapidjson::GenericValue<JSON_UTF16>* BTJsonManager::GetJsonDataPoint(D2D1_POINT_2F point)
{
	rapidjson::GenericValue<JSON_UTF16>* instValue = new rapidjson::GenericValue<JSON_UTF16>();
	
	RapidJsonData* instData = new RapidJsonData();
	instValue->SetObject();
	instValue->AddMember(
		instData->key.SetString(L"x"), 
		instData->value.SetInt((int)point.x), 
		GetInstance()->Json.GetAllocator());
	instValue->AddMember(
		instData->key.SetString(L"y"),
		instData->value.SetInt((int)point.y),
		GetInstance()->Json.GetAllocator());

	return instValue;
}

rapidjson::GenericValue<JSON_UTF16>* BTJsonManager::GetJsonDataRect(D2D1_RECT_F rect)
{
	rapidjson::GenericValue<JSON_UTF16>* instValue = new rapidjson::GenericValue<JSON_UTF16>();

	RapidJsonData* instData = new RapidJsonData();
	instValue->SetObject();

	instValue->AddMember(
		instData->key.SetString(L"left"),
		instData->value.SetInt((int)rect.left),
		GetInstance()->Json.GetAllocator());

	instValue->AddMember(
		instData->key.SetString(L"top"),
		instData->value.SetInt((int)rect.top),
		GetInstance()->Json.GetAllocator());

	instValue->AddMember(
		instData->key.SetString(L"right"),
		instData->value.SetInt((int)rect.right),
		GetInstance()->Json.GetAllocator());

	instValue->AddMember(
		instData->key.SetString(L"bottom"),
		instData->value.SetInt((int)rect.bottom),
		GetInstance()->Json.GetAllocator());

	return instValue;
}

void BTJsonManager::SaveDataByDataList(string fileName, vector<RapidJsonData*>& dataList)
{
	int loopCount = dataList.size();

	for (int index = 0; index < loopCount; index++)
	{
		Json.AddMember(dataList[index]->key, dataList[index]->value, Json.GetAllocator());
	}

	rapidjson::GenericStringBuffer< JSON_UTF16 > strbuf;
	rapidjson::Writer< rapidjson::GenericStringBuffer<JSON_UTF16>, JSON_UTF16, JSON_UTF16 > writer(strbuf);
	Json.Accept(writer);

	wstring sTemp = wstring(fileName.begin(), fileName.end());
	LPCWSTR sw = sTemp.c_str();

	HANDLE hFile = CreateFile(sw, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE != hFile)
	{
		DWORD dwWrite = 0;

		WORD wUnicode16LEHeader = 0xFEFF;
		WriteFile(hFile, &wUnicode16LEHeader, sizeof(wUnicode16LEHeader), &dwWrite, nullptr);
		WriteFile(hFile, strbuf.GetString(), strbuf.GetSize(), &dwWrite, nullptr);

		CloseHandle(hFile);
	}

	Json.SetObject();
	return;
}

bool BTJsonManager::LoadDataByFileName(string fileName, rapidjson::Document& openDoc)
{
	FILE* fp = nullptr;

	//char fileNameStr[MAX_PATH];
	//strcpy_s(fileNameStr,CT2A(fileName));

	fopen_s(&fp, fileName.c_str(), "rb");

	if (fp != nullptr)
	{		
		char str[20480];
		rapidjson::FileReadStream bis(fp, str, sizeof(str));
		rapidjson::EncodedInputStream<rapidjson::UTF16LE<>, rapidjson::FileReadStream> eis(bis);

		openDoc.ParseStream< 0, rapidjson::UTF16<> >(eis);
		
		fclose(fp);
		return true;
	}
	return false;
}