#include "pch.h"

#include <string>
#include "BTJsonManager.h"

BTJsonManager* BTJsonManager::mInstance;

rapidjson::GenericValue<JSON_UTF16>* BTJsonManager::GetJsonDataPoint(CPoint point)
{
	rapidjson::GenericValue<JSON_UTF16>* instValue = new rapidjson::GenericValue<JSON_UTF16>();
	
	RapidJsonData* instData = new RapidJsonData();
	instValue->SetObject();
	instValue->AddMember(
		instData->key.SetString(L"x"), 
		instData->value.SetInt(point.x), 
		GetInstance()->Json.GetAllocator());
	instValue->AddMember(
		instData->key.SetString(L"y"),
		instData->value.SetInt(point.y),
		GetInstance()->Json.GetAllocator());

	return instValue;
}

rapidjson::GenericValue<JSON_UTF16>* BTJsonManager::GetJsonDataRect(CRect rect)
{
	rapidjson::GenericValue<JSON_UTF16>* instValue = new rapidjson::GenericValue<JSON_UTF16>();

	RapidJsonData* instData = new RapidJsonData();
	instValue->SetObject();

	instValue->AddMember(
		instData->key.SetString(L"left"),
		instData->value.SetInt(rect.left),
		GetInstance()->Json.GetAllocator());

	instValue->AddMember(
		instData->key.SetString(L"top"),
		instData->value.SetInt(rect.top),
		GetInstance()->Json.GetAllocator());

	instValue->AddMember(
		instData->key.SetString(L"right"),
		instData->value.SetInt(rect.right),
		GetInstance()->Json.GetAllocator());

	instValue->AddMember(
		instData->key.SetString(L"bottom"),
		instData->value.SetInt(rect.bottom),
		GetInstance()->Json.GetAllocator());

	return instValue;
}

void BTJsonManager::SaveDataByDataList(CString fileName, vector<RapidJsonData*>& dataList)
{
	int loopCount = dataList.size();

	for (int index = 0; index < loopCount; index++)
	{
		Json.AddMember(dataList[index]->key, dataList[index]->value, Json.GetAllocator());
	}

	rapidjson::GenericStringBuffer< JSON_UTF16 > strbuf;
	rapidjson::Writer< rapidjson::GenericStringBuffer<JSON_UTF16>, JSON_UTF16, JSON_UTF16 > writer(strbuf);
	Json.Accept(writer);

	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
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

bool BTJsonManager::LoadDataByFileName(CString fileName, rapidjson::Document& openDoc)
{
	FILE* fp = nullptr;

	char fileNameStr[MAX_PATH];
	strcpy_s(fileNameStr,CT2A(fileName));

	fopen_s(&fp, fileNameStr, "rb");

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